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

/*! \file
\brief Useful mathematics operations and function extensions to G3 algebra.

\b Overview

This include file provides many conventional mathematical functions that
operate with various engabra::g3 entities.

\b Categories

\arg Utilities - Functions that are generally useful (e.g. sq())

\arg Magnitudes - Functions that return "squared-magnitude" values.

\arg Directions - Functions that provide a unitary value that represents
the direction of non-zero argument values.

\arg Exponential - Functions that provide exponentiation of all the
engabra::g3 types.

\arg Logarithms - Functions for providing a (principal branch) logarithm
value of common argument types for which logarithm values exist. Although
support for argument types is not entirely comprehensive, logarithm
functions are provided for mostly commonly occurring entity types.

\arg Inverses - Functions that provide inverses of all non-zero blades types
as well as several (non-zero) compute types that have well defined inverses.

\b TBD

\arg Circular - Functions providing circular trig function values. These
can be computed using exp() and selecting desired resulting grades.

\arg Hyperbolic - - Functions providing hyperbolic trig function
values. These can be computed using exp() and selecting desired resulting
grades.

\arg Roots - ?

\arg Powers - ?

\b Examples

Magnitude and Direction
\snippet test_g3func.cpp DoxyExampleMagDir

*/




#include "g3type.hpp"

#include "g3ops.hpp"
#include "g3traits.hpp"
#include "g3validity.hpp"


namespace engabra
{

namespace g3
{
	//
	// Math utility functions
	//

	/*! \brief Squaring operation (result of multiplying argument by itself)
	 *
	 * Note that with GA, the return type can be different from the
	 * argument type.
	 *
	 * Some types square to their own type of result. E.g.
	 * \arg Scalar square to Scalar
	 * \arg Spinor square to Spinor
	 * \arg MultiVector square to MultiVector
	 *
	 * While other types square to different type result. E.g.
	 * \arg Vector square to Spinor (with zero BiVector grade)
	 * \arg BiVector square to Spinor (with zero BiVector grade)
	 * \arg TriVector square to Scalar
	 * \arg ImSpin square to Spinor
	 *
	 * Example:
	 * \snippet test_g3func.cpp DoxyExampleSq
	 */
	//	 * \arg Complex square to Complex
	template <typename InType, typename OutType>
	inline
	OutType
	sq
		( InType const & someValue
		)
	{
		return { someValue * someValue };
	}

	//! Cubing operation (result of multiplying argument by itself 3-times)
	template <typename InType, typename OutType>
	inline
	OutType
	cube
		( InType const & someValue
		)
	{
		return { someValue * someValue * someValue };
	}


	//
	// Magnitudes for G3 types
	//

	//! Squared magnitude - specialization for double
	inline
	double
	magSq
		( double const & dub
		)
	{
		return { sq(dub) };
	}


	//! Squared magnitude for blades (Scalar, Vector, BiVector, TriVector)
	template
		< typename Blade
		, std::enable_if_t< is::blade<Blade>::value, bool> = true
		>
	inline
	double
	magSq
		( Blade const & blade
		)
	{
		return priv::prodComm(blade.theData, blade.theData);
	}

	//! Squared magnitude - specialization for Spinor
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

	//! Squared magnitude - specialization for ImSpin
	inline
	double
	magSq
		( ImSpin const & imsp
		)
	{
		double const vecSq{ magSq(imsp.theVec) };
		double const triSq{ sq(imsp.theTri.theData[0]) };
		return {vecSq + triSq };
	}

	//! Squared magnitude - specialization for MultiVector
	inline
	double
	magSq
		( MultiVector const & mv
		)
	{
		double const scaSq{ sq(mv.theSca.theData[0]) };
		double const vecSq{ magSq(mv.theVec) };
		double const bivSq{ magSq(mv.theBiv) };
		double const triSq{ sq(mv.theTri.theData[0]) };
		return { scaSq + vecSq + bivSq + triSq };
	}

	//! Magnitude of element of any type
	template <typename Type>
	inline
	double
	magnitude
		( Type const & element
		)
	{
		return std::sqrt(magSq(element));
	}

	//! Decompose arbitrary blade into magnitude and direction interpretations
	template
		< typename Blade
		, std::enable_if_t< is::blade< Blade >::value, bool> = true
		>
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
	// Inverses
	//

	//! General inverse of a multivector item
	template
		< typename Type
		, std::enable_if_t< is::blade<Type>::value, bool> = true
		>
	inline
	Type
	inverse
		( Type const & someItem
		)
	{
		double const mag2{ magSq(someItem) };
		return Type{ (1./mag2) * reverse(someItem) };
	}


	//
	// Exponential
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


	//
	// Logarithms
	//

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
	// TBD/TODO
	//


} // [g3]

} // [engabra]

#endif // g3_g3func_INCL_
