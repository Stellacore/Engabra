//
// MIT License
//
// Copyright (c) 2020 Stellacore Corporation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//


#ifndef g3_g3funcs_INCL_
#define g3_g3funcs_INCL_

/*! \file
\brief Useful mathematics operations and function extensions to G3 algebra.
*/


#include "g3ops.hpp"
#include "g3types.hpp"
#include "g3validity.hpp"


namespace engabra
{

namespace g3
{
	//
	// Math utility functions
	//

	//! Square operation (result of multiplying argument by itself)
	template <typename Type>
	inline
	Type
	sq
		( Type const & someValue
		)
	{
		return { someValue * someValue };
	}

	//! Squared magnitude
	template <typename Blade>
	inline
	double
	magSq
		( Blade const & blade
		)
	{
		return prodComm(blade.theData, blade.theData);
	}

	//! Squared magnitude - specialization for Spinor
	template <>
	inline
	double
	magSq
		( Spinor const & spin
		)
	{
		double const scaSq{ sq(spin.theSca.theData[0]) };
		double const bivSq{ magSq(spin.theBiv) };
		return {scaSq + bivSq };
	}

	//! Magnitude of blade
	template <typename Blade>
	inline
	double
	magnitude
		( Blade const & blade
		)
	{
		return std::sqrt(magSq(blade));
	}

	//! Decompose arbitrary blade into magnitude and direction interpretations
	template <typename Blade>
	inline
	std::pair<double, Blade>
	magDirPairFrom
		( Blade const & blade
		)
	{
		double const mag{ magnitude(blade) };
		Blade dir{ null<Blade>() };
		if (0. != mag)
		{
			dir = (1./mag) * blade;
		}
		return {mag, dir};
	}

	//
	// Math library type functions
	//

	//! Exponential of a bivector
	inline
	Spinor
	exp
		( BiVector const & spinAngle
		)
	{
		Spinor spin{ 1., zero<BiVector>() }; // zero angle default result
		std::pair<double, BiVector> const magdir{ magDirPairFrom(spinAngle) };
		double const & mag = magdir.first;
		BiVector const & dir = magdir.second;
		if (isValid(dir)) // zero angle direction undefined - return default
		{
			spin = Spinor{ std::cos(mag), std::sin(mag)*dir };
		}
		return spin;
	}

	//! Exponential of a G2 element
	inline
	Spinor
	exp
		( Spinor const & someItem
		)
	{
		return { std::exp(someItem.theSca.theData[0]) * exp(someItem.theBiv) };
	}

	//! Logarithm of a (G-2 subalgebra) spinor
	inline
	Spinor
	logG2
		( Spinor const & spin
		)
	{
		Spinor gangle{ null<Spinor>() }; // generalized angle (Scalar+BiVector)
		double const spinMag{ magnitude(spin) };
		// check for positive magnitude (no logarithm for zero magnitude)
		if (std::numeric_limits<double>::epsilon() < spinMag)
		{
			double const logSpinMag{ std::log(spinMag) };

			double const invMag{ 1. / spinMag };
			Spinor const spinDir{ invMag * spin };

			double const & angleMagCos = spinDir.theSca.theData[0];

			constexpr double nearNegOne
				{ -(1. - std::numeric_limits<double>::epsilon()) };
			if (angleMagCos < nearNegOne)
			{
				// Rotation is very near PI
				// - bivector direction not (or not well) defined
				// - use provided argument plane to complete rotation
				gangle = Spinor{ logSpinMag, null<BiVector>() };
			}
			else
			{
				// Rotation plane should be well defined
				std::pair<double, BiVector> const bivMagDir
					{ magDirPairFrom(spinDir.theBiv) };
				double const & angleMagSin = bivMagDir.first;
				BiVector const & angleDir = bivMagDir.second;

				double const angleVal{ std::atan2(angleMagSin, angleMagCos) };

				gangle = Spinor{ logSpinMag, angleVal * angleDir };
			}

		}
		return gangle;
	}

	//
	// Algebraic operations
	//

	//! General inverse of a multivector item
	template <typename Type>
	inline
	Type
	inverse
		( Type const & someItem
		)
	{
		double const mag2{ magSq(someItem) };
		return Type{ (1./mag2) * reverse(someItem) };
	}

} // [g3]

} // [engabra]

#endif // g3_g3funcs_INCL_
