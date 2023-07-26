//
// MIT License
//
// Copyright (c) 2022 Stellacore Corporation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//


#ifndef engabra_compare_INCL_
#define engabra_compare_INCL_

/*! \file
\brief Functions for comparing numeric values.

\b Overview

The various "nearlyEquals()" functions are useful for testing if two
entities are approximately the same while allowing for some degree
of error associated with computational precision, data uncertainties,
roundoff, convergence of approximating functions, and so on.

The functions have three arguments with general interpretation:
\arg testValue - the more arbitrary value (e.g. a result, or measurement).
\arg refValue - the reference value expected (e.g. from knowledge/prediction).
\arg tol - a tolerance threshold with which to compare (ref discussion below).

\b Tolerances

In general, the third, 'tol', argument specifies a tolerance by which to
compare the two argument values. For general nearlyEquals() functions,
the tolerance is interpreted as a fractional tolerance relative to the
\a refValue.

To qualify as "nearly equal" the test value should be within the range
of values of "refValue plus/minus (tol*refValue)". This condition is
applied to each individual component of compound entities (e.g. arrays,
Spinor, etc).

For reference values near zero, the relative condition is ill-defined.
In this case an absolute comparison is performed that compares values
based on abs(testVal-refVal) being less than the tolerance.

The default tolerance value is machine relative precision, aka 'epsilon'.
This may be appropriate for fairly exact computations and when working
with relatively normalized and stable data values. However, in practice,
it may be convenient to specify a tolerance value several bits larger
than this. E.g. perhaps 64.*espilon() or whatever is appropriate for an
application at hand.

\b Notes

The comparisons have a purely mathematical and numeric interpretation.
Individual components of various entities are evaluated.  This is
particularly useful in many situations (especially for testing) but may
not be appropriate for all application domain situations.

Therefore, the numeric comparison may be (very) different from what
constitutes near equivalence in the context of some specific application
criteria. For example, an angle value of 3.1415 and value of 6.2830 may
represent identical physical attitudes in space, while the two numeric
values do not test as "nearlyEqual" to each other.

Example:
\snippet test_g3compare_all.cpp DoxyExample01

*/


#include "g3traits.hpp"
#include "g3type.hpp"
#include "g3validity.hpp"

#include <cmath>
#include <limits>
#include <numeric>


namespace engabra
{

namespace g3
{
	//! Reusable expression for (std::abs(testVal - refVal) < tol);
	inline
	bool
	isSmallAbs
		( double const & testVal
		, double const & tol
		)
	{
		return (std::abs(testVal) < tol);
	}

	//! Reusable expression for (std::abs(testVal - refVal) < tol);
	inline
	bool
	isSmallAbsDiff
		( double const & testVal
		, double const & refVal
		, double const & tol
		)
	{
		double const diff{ testVal - refVal };
		return isSmallAbs(diff, tol);
	}

	//! Reusable expression for checking validity of two arguments.
	inline
	bool
	bothAreValid
		( double const & valA
		, double const & valB
		)
	{
		return (engabra::g3::isValid(valA) && engabra::g3::isValid(valB));
	}

	/*! \brief Compare two double values using absolute tolerances.
	 *
	 * Returns true if testVal and refVal are both valid and they are
	 * nearly the same within the tolerance value.
	 *
	 * Comparison is performed using simple subtraction. Returns true
	 * if the absolute value of the difference is strictly less than
	 * the provided tolerance. (A negative tolerance value will always
	 * result in return of false)
	 *
	 * This function is most suitable for use, if the two values are
	 * expected to have values near one, so that a simple arithmetic
	 * difference is meaningful.
	 *
	 * To compare values that have large dynamic range, refer to
	 * \arg nearlyEqualsRel()
	 * \arg nearlyEquals()
	 *
	 * TODO - Check for handling subnormal numbers
	 */
	inline
	bool
	nearlyEqualsAbs
		( double const & testVal
		, double const & refVal
		, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		bool same{ false };
		if (bothAreValid(testVal, refVal))
		{
			same = isSmallAbsDiff(testVal, refVal, tol);
		}
		return same;
	}

	/*! \brief True if testVal is proportionally (relatively) near refVal.
	 *
	 * TODO - algorithm for this
	 */
	inline
	bool
	nearlyEqualsRel
		( double const & testVal
		, double const & refVal
		, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		bool same{ false };
		if (bothAreValid(testVal, refVal))
		{
			// tolerance for being near zero
			constexpr double pad{ 1./std::numeric_limits<double>::epsilon() };
			constexpr double small{ std::numeric_limits<double>::min() };
			constexpr double tolToZero{ small * pad };

			// is reference value too near zero to normalize?
			if (std::abs(refVal) < tolToZero)
			{
				// if so, do direct compare
				same = isSmallAbsDiff(testVal, refVal, tol);
			}
			else // reference value has significant magnitude
			{
				// otherwise, normalize by reference value
				double const testNorm{ testVal / refVal };
				constexpr double refNorm{ 1. };
				same = isSmallAbsDiff(testNorm, refNorm, tol);
			}

		}
		return same;
	}

	/*! \brief True if testVal is nearly equal to refVal at tolerance.
	 *
	 * Redirects to nearlyEqualsRel() (which is the more general case).
	 */
	inline
	bool
	nearlyEquals
		( double const & testVal
		, double const & refVal
		, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		return nearlyEqualsRel(testVal, refVal, tol);
	}

	//
	// Specializations
	//

	//! True if logic values are the same
	inline
	bool
	nearlyEquals
		( bool const & boolA
		, bool const & boolB
		)
	{
		return (boolA == boolB);
	}

	/*! \brief Specialization for std::array<double, DIM>
	 *
	 * The similarity of the two data arrays is evaluated in a "geometric"
	 * sense for two distinct cases:
	 *
	 * \arg For arrays with RSS (root of sum of squares) magnitude that
	 * is less than machine minimum value, then the absolute difference of
	 * individual array component values is compared (within specified
	 * tolerance).
	 *
	 * \arg For arrays with RSS values that are not smaller than machine
	 * minimum value, then the RSS of the "vector-like difference" is computed
	 * and the relative ratio value (RSS-of-difference / RSS-of-reference)
	 * is compared absolutely to zero (within specified tolerance)
	 */
	template <std::size_t Dim>
	inline
	bool
	nearlyEquals
		( std::array<double, Dim> const & dataGot
		, std::array<double, Dim> const & dataRef
		, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		bool same{ false };

		if (isValid(dataGot) && isValid(dataRef))
		{

			// small value to use for comparison case selection
			constexpr double minDub{ std::numeric_limits<double>::min() };

			// get RSS for reference array
			double const magSqRef
				{ std::inner_product
					( dataRef.cbegin(), dataRef.cend(), dataRef.cbegin(), 0.)
				};
			double const magRef{ std::sqrt(magSqRef) };

			// select which test case to use (small absolute, or relative)
			if (magRef < minDub)
			{
				// vector is near zero - compare each component individually
				// to check if all components are within absolute tolerance
				same = nearlyEqualsAbs(dataGot[0], dataRef[0], tol);
				for (std::size_t ndx{1u} ; (ndx < Dim) && same ; ++ndx)
				{
					same = isSmallAbsDiff(dataGot[ndx], dataRef[ndx], tol);
				}
			}
			else
			{
				// some component is relatively large - compare vector
				// difference magnitude e.g. along the lines of:
				//   vecDif = vecGot - vecRef;
				//   sqrt(magSq(vecDif) / magSq(vecRef)) < tol
				double magSqDif{ 0. };
				for (std::size_t ndx{0u} ; ndx < Dim ; ++ndx)
				{
					double const dif{ dataGot[ndx] - dataRef[ndx] };
					magSqDif += dif * dif;
				}
				double const gotMagRel{ std::sqrt(magSqDif / magSqRef) };
				same = isSmallAbs(gotMagRel, tol);
			}
		}
		return same;
	}

	//! True if all components of each entity are numerically nearly same.
	template
		< typename Blade
		, std::enable_if_t< is::blade<Blade>::value, bool> = true
		>
	inline
	bool
	nearlyEquals
		( Blade const & bladeA
		, Blade const & bladeB
		, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		return nearlyEquals(bladeA.theData, bladeB.theData, tol);
	}

	//! True if all components of each Spinor are numerically nearly same.
	inline
	bool
	nearlyEquals
		( Spinor const & itemA
		, Spinor const & itemB
		, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		return
			(  nearlyEquals(itemA.theSca, itemB.theSca, tol)
			&& nearlyEquals(itemA.theBiv, itemB.theBiv, tol)
			);
	}

	//! True if all components of each ImSpin are numerically nearly same.
	inline
	bool
	nearlyEquals
		( ImSpin const & itemA
		, ImSpin const & itemB
		, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		return
			(  nearlyEquals(itemA.theVec, itemB.theVec, tol)
			&& nearlyEquals(itemA.theTri, itemB.theTri, tol)
			);
	}

	//! True if all components of each ComPlex are numerically nearly same.
	inline
	bool
	nearlyEquals
		( ComPlex const & cplxA
		, ComPlex const & cplxB
		, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		return
			(  nearlyEquals(cplxA.theSca, cplxB.theSca, tol)
			&& nearlyEquals(cplxA.theTri, cplxB.theTri, tol)
			);
	}

	//! True if all components of each DirPlex are numerically nearly same.
	inline
	bool
	nearlyEquals
		( DirPlex const & dplxA
		, DirPlex const & dplxB
		, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		return
			(  nearlyEquals(dplxA.theVec, dplxB.theVec, tol)
			&& nearlyEquals(dplxA.theBiv, dplxB.theBiv, tol)
			);
	}

	//! True if all components of each MultiVector are numerically nearly same.
	inline
	bool
	nearlyEquals
		( MultiVector const & itemA
		, MultiVector const & itemB
		, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		return
			(  nearlyEquals(itemA.theSca, itemB.theSca, tol)
			&& nearlyEquals(itemA.theVec, itemB.theVec, tol)
			&& nearlyEquals(itemA.theBiv, itemB.theBiv, tol)
			&& nearlyEquals(itemA.theTri, itemB.theTri, tol)
			);
	}

	//
	// Exact comparison (e.g. bitwise same)
	//

	//! True if data values are bit-wise identical
	inline
	bool
	operator==
		( std::array<double, 3u> const & dataA
		, std::array<double, 3u> const & dataB
		)
	{
		return
			(  (dataA[0] == dataB[0])
			&& (dataA[1] == dataB[1])
			&& (dataA[2] == dataB[2])
			);
	}


	//! True if data values are bit-wise identical
	inline
	bool
	operator==
		( Scalar const & scaA
		, Scalar const & scaB
		)
	{
		return (scaA.theData[0] == scaB.theData[0]);
	}

	//! True if data values are bit-wise identical
	inline
	bool
	operator==
		( Vector const & vecA
		, Vector const & vecB
		)
	{
		return (vecA.theData == vecB.theData);
	}

	//! True if data values are bit-wise identical
	inline
	bool
	operator==
		( BiVector const & bivA
		, BiVector const & bivB
		)
	{
		return (bivA.theData == bivB.theData);
	}

	//! True if data values are bit-wise identical
	inline
	bool
	operator==
		( TriVector const & triA
		, TriVector const & triB
		)
	{
		return (triA.theData[0] == triB.theData[0]);
	}

	//! True if data values are bit-wise identical
	inline
	bool
	operator==
		( Spinor const & spinA
		, Spinor const & spinB
		)
	{
		return
			(  (spinA.theSca == spinB.theSca)
			&& (spinA.theBiv == spinB.theBiv)
			);
	}

	//! True if data values are bit-wise identical
	inline
	bool
	operator==
		( ImSpin const & imspA
		, ImSpin const & imspB
		)
	{
		return
			(  (imspA.theVec == imspB.theVec)
			&& (imspA.theTri == imspB.theTri)
			);
	}

	//! True if data values are bit-wise identical
	inline
	bool
	operator==
		( MultiVector const & mvA
		, MultiVector const & mvB
		)
	{
		return
			(  (mvA.theSca == mvB.theSca)
			&& (mvA.theVec == mvB.theVec)
			&& (mvA.theBiv == mvB.theBiv)
			&& (mvA.theTri == mvB.theTri)
			);
	}

} // [g3]

} // [engabra]


#endif // engabra_compare_INCL_
