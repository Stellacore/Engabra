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

Utilities:
\snippet test_g3func.cpp DoxyExampleUtil

Simultaneous magnitude and direction:
\snippet test_g3func.cpp DoxyExampleMagDir

*/




#include "g3type.hpp"

#include "g3ops.hpp"
#include "g3traits.hpp"
#include "g3validity.hpp"

#include "g3io.hpp" // TODO for dev


namespace engabra
{

namespace g3
{
	//
	// Math utility functions
	//

	/*! \brief Squaring operation (result of multiplying argument by itself)
	 *
	 * Only applicable for types that represent a closed sub-algebra.
	 * E.g. double, Scalar, Spinor, Complex, MultiVector.
	 */
	template <typename Type>
	constexpr
	Type
	sq
		( Type const & someValue
		)
	{
		return { someValue * someValue };
	}

	/*! \brief Cubing operation (multiplying by self 3-times)
	 *
	 * Only applicable for types that represent a closed sub-algebra.
	 * E.g. double, Scalar, Spinor, Complex, MultiVector.
	 */
	template <typename Type>
	constexpr
	Type
	cube
		( Type const & someValue
		)
	{
		return { someValue * someValue * someValue };
	}


	//
	// Magnitudes for G3 types
	//

	//! Squared magnitude - specialization for double
	constexpr
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
		< typename Type
// Should apply to other items as well: e.g. Spinor, ImSpin, MultiVector, ...??
//		, std::enable_if_t< is::blade< Type >::value, bool> = true
		>
	inline
	std::pair<double, Type>
	pairMagDirFrom
		( Type const & blade
		)
	{
		std::pair<double, Type> result{ magnitude(blade), null<Type>() };
		double const & mag = result.first;
		// use a tolerance large enough so that computation result
		// retains meaningful precision.
		constexpr double small{ std::numeric_limits<double>::denorm_min() };
		if (small < mag)
		{
			result.second = (1./mag) * blade;
		}
		return result;
	}

	//
	// Directions
	//

	//! Unitary direction of Blade
	template
		< typename Type
//		, std::enable_if_t< is::blade< Type >::value, bool> = true
		>
	inline
	Type
	direction
		( Type const & blade
		)
	{
		return pairMagDirFrom<Type>(blade).second;
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

	// References:
	//
	// General cases for 3D and 4D Clifford algebras
	// https://www.journals.vu.lt/nonlinear-analysis/article
	//  /download/24476/24634/
	//
	// Seems focused on 3D space
	// https://journals.plos.org/plosone/article/file?id=10.1371
	//  /journal.pone.0116943&type=printable
	//
	// Exponentials of general multivector (MV) in 3D Clifford algebras
	// https://arxiv.org/pdf/2104.01905.pdf
	//

	//! Exponential of a bivector
	inline
	Spinor
	exp
		( BiVector const & spinAngle
		)
	{
		Spinor spin{ 1., zero<BiVector>() }; // zero angle default result
		std::pair<double, BiVector> const magdir{ pairMagDirFrom(spinAngle) };
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

namespace priv
{

	//! Evaluation of "sync(x)=sin(x)/x" - including limit case near zero
	inline
	double
	sync
		( double const & angle
		)
	{
		double result{ g3::nan };

		// use series expansion for sync function ((x-x^2/6+x^5/120)/x)
		// residual (for alternating series) less than O(x^6),
		// so to ~18 digits is about (1.e-3)^6.  Use 1.e-4 for safety
		if (angle < 1.e-4)
		{
			// small angle: add from small to large
			result = (sq(sq(angle))/120.  - sq(angle)/6.  + 1.);
		}
		else
		{
			// large angle: evaluate sync with std:: library functions
			result = std::sin(angle) / angle;
		}

		return result;
	}

} // [priv]


	/*! Exponential of general MultiVector element.
	 *
	 * Formula used is from:
	 * \arg Dargys, Adolfas, Acus Arturas,
	 * "Exponentials of general multivector (MV) in 3D Clifford algebras"
	 * ArXiv:2104.01905v1, 18 Feb 2021
	 * https://arxiv.org/pdf/2104.01905.pdf
	 *
* NOTE - ERROR - this paper seems to be wrong
* For example; obvious in that b0, b123, do not reproduce (-1 == exp(I*pi))
	 *
	 */
	inline
	MultiVector
	exp
		( MultiVector const & someItem
		)
	{
		MultiVector result{ null<MultiVector>() };

		if (isValid(someItem))
		{
			// NOTE: the algorithm [Dargys, Arturas] uses bivector
			// decomposition with basis: E12, E23, E13
			// This library uses: e23, e31, e12

			// pull out components from input MV
			double const a0  {  someItem[0] };
			double const a1  {  someItem[1] };
			double const a2  {  someItem[2] };
			double const a3  {  someItem[3] };
			double const a12 {  someItem[6] }; // e12
			double const a13 { -someItem[5] }; // e31
			double const a23 {  someItem[4] }; // e23
			double const a123{  someItem[7] };

			// evaluate scalar angles ([Dargys, Arturas] eqn 3.2)
			double const a3m12{ a3 - a12 };
			double const a3p12{ a3 + a12 };
			double const a2m13{ a2 - a13 };
			double const a2p13{ a2 + a13 };
			double const a1m23{ a1 - a23 };
			double const a1p23{ a1 + a23 };

			double const apos{ sqrt(sq(a3m12) + sq(a2p13) + sq(a1m23)) };
			double const aneg{ sqrt(sq(a3p12) + sq(a2m13) + sq(a1p23)) };

std::cout << "apos: " << apos << std::endl;
std::cout << "aneg: " << aneg << std::endl;

			// evaluate result coefficients ([Dargys, Arturas] eqn 3.1)

			// cosine function is well behaved including near zero
			double const cospos{ std::cos(apos) }; // okay for 0==apos
			double const cosneg{ std::cos(aneg) }; // okay for 0==aneg
			// sync function (sin(x)/x) needs limiting case evaluation
			double const syncpos{ priv::sync(apos) };
			double const syncneg{ priv::sync(aneg) };

std::cout << "cospos: " << cospos << std::endl;
std::cout << "cosneg: " << cosneg << std::endl;

std::cout << "syncpos: " << syncpos << std::endl;
std::cout << "syncneg: " << syncneg << std::endl;

			// leading coefficients
			double const hea0{ .5 * std::exp(a0) }; // half * e(a0)
			double const epa123{ std::exp( a123) }; // e(+a123)
			double const ena123{ std::exp(-a123) }; // e(-a123)

std::cout << "hea0  : " << hea0 << std::endl;
std::cout << "epa123: " << epa123 << std::endl;
std::cout << "ena123: " << ena123 << std::endl;
std::cout << " sum  : " << epa123 + ena123 << std::endl;

			// evaluate the output components

			// Note the special case evaluations could be slightly more
			// optimized, but simple code evaluation is preferred here.

			double const b0  { epa123*cospos + ena123*cosneg };

			double const b1{ epa123*(a1m23)*syncpos + ena123*(a1p23)*syncneg };
			double const b2{ epa123*(a2p13)*syncpos + ena123*(a2m13)*syncneg };
			double const b3{ epa123*(a3m12)*syncpos + ena123*(a3p12)*syncneg };

			double const b12{-epa123*(a3m12)*syncpos + ena123*(a3p12)*syncneg};
			double const b13{ epa123*(a2p13)*syncpos - ena123*(a2m13)*syncneg};
			double const b23{-epa123*(a1m23)*syncpos + ena123*(a1p23)*syncneg};

			double const b123{ epa123*cospos - ena123*cosneg };

			// NOTE restore conventions on basis bivectors
			// e23 :  b23
			// e31 : -b13
			// e12 :  b12
			result = MultiVector{ b0, b1, b2, b3, b23, -b13, b12, b123 };
			// apply overall scale factor
			result = hea0 * result;
		}

		return result;
	}


	//
	// Logarithms
	//

	using G2Item = Spinor;

	//! Logarithm of a (G-2 subalgebra) spinor
	inline
	G2Item
	logG2
		( G2Item const & genSpin
		, BiVector const & bivDirForImaginary = e23
		)
	{
		G2Item gangle{ null<G2Item>() }; // generalized angle (Scalar+BiVector)
		if (isValid(genSpin))
		{
			double const spinMag{ magnitude(genSpin) };

			// check for positive magnitude (no logarithm for zero magnitude)
			if (std::numeric_limits<double>::epsilon() < spinMag)
			{
				double const logSpinMag{ std::log(spinMag) };

				double const invMag{ 1. / spinMag };
				G2Item const spinDir{ invMag * genSpin };

				double const & dirCosValue = spinDir.theSca.theData[0];
				constexpr double almostOne
					{ 1. - std::numeric_limits<double>::epsilon() };

				// check special case of zero rotation
				if (almostOne < dirCosValue)
				{
					gangle = G2Item{ logSpinMag, zero<BiVector>() };
				}
				else
				// check special case of turnHalf
				if (dirCosValue < (-almostOne))
				{
					// Rotation is very near PI
					// - bivector direction not (or not well) defined
					// - use provided argument plane to complete rotation
					// - unitize argument for safety
					BiVector const bivDir{ direction(bivDirForImaginary) };
					gangle = G2Item{ logSpinMag, turnHalf * bivDir };
				}
				else
				// handle as general case
				{
					// Rotation plane should be well defined
					std::pair<double, BiVector> const bivMagDir
						{ pairMagDirFrom(spinDir.theBiv) };
					double const & dirSinMag = bivMagDir.first;
					BiVector const & bivDir = bivMagDir.second;
					// dirCosValue can be +/- while (0 <= dirSinMag)
					double const angleSize
						{ std::atan2(dirSinMag, dirCosValue) };
					gangle = G2Item{ logSpinMag, angleSize * bivDir };
				}
			}
		}
		return gangle;
	}

	//! square root of a (G-2 subalgebra) spinor
	inline
	G2Item
	sqrtG2
		( G2Item const & genSpin
		, BiVector const & bivDirForImaginary = e23
		)
	{
		G2Item root{ null<G2Item>() };
		if (isValid(genSpin))
		{
			double const spinMag{ magnitude(genSpin) };
			constexpr double tol{ 4. * std::numeric_limits<double>::epsilon() };
			if (spinMag < tol)
			{
				root = zero<G2Item>();
			}
			else
			{
				// use arbitrary default plane of e23 in case of -- ? TODO
				G2Item const gangle{ logG2(genSpin, bivDirForImaginary) };
				root = exp(.5 * gangle);
			}
		}
		return root;
	}

	//
	// TBD/TODO
	//


} // [g3]

} // [engabra]

#endif // g3_g3func_INCL_
