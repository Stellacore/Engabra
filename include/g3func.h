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


#ifndef g3_g3func_INCL_
#define g3_g3func_INCL_


#include "g3.h"


namespace g3
{

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

	//! Exponential of a bivector
	inline
	Spinor
	exp
		( Biv const & spinAngle
		)
	{
		Spinor spin{ 1., zero<Biv>() }; // zero angle default result
		std::pair<double, Biv> const magdir{ magDirPairFrom(spinAngle) };
		double const & mag = magdir.first;
		Biv const & dir = magdir.second;
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
		Spinor gangle{ null<Spinor>() }; // generalized angle (Sca+Biv)
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
				gangle = Spinor{ logSpinMag, null<Biv>() };
			}
			else
			{
				// Rotation plane should be well defined
				std::pair<double, Biv> const bivMagDir
					{ magDirPairFrom(spinDir.theBiv) };
				double const & angleMagSin = bivMagDir.first;
				Biv const & angleDir = bivMagDir.second;

				double const angleVal{ std::atan2(angleMagSin, angleMagCos) };

				gangle = Spinor{ logSpinMag, angleVal * angleDir };
			}

		}
		return gangle;
	}

} // [g3]

#endif // g3_g3func_INCL_
