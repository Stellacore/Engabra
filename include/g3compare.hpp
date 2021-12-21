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

The various "nearlyEquals()" functions are useful for testing if two
entities are approximately the same. Note that the comparisons are
purely mathematic and numeric in nature. Individual components of various
entities are evaluated.  This is particularly useful in many situations
(especially for writing unit tests) but may not be appropriate for all
application domain situations.

Note that the numeric comparision may be (very) different from what
constitutes near equivalence if evaluated by application specific
criteria. For example, an angle value of 3.1415 and value of 6.2830
may represent identical physical attitudes in space, but do not test
"nearlyEqual" to each other.

Example:
\snippet test_g3compare.cpp DoxyExample01

*/


#include "g3types.hpp"
#include "g3validity.hpp"

#include <cmath>
#include <limits>


namespace engabra
{

namespace g3
{
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
		return (std::abs(diff) < tol);
	}

	//! Reusable expression for 
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

	//! True if all components of each entity are numerically nearly equal.
	template <typename Entity>
	inline
	bool
	nearlyEquals
		( Entity const & entityA
		, Entity const & entityB
	 	, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		bool same{ false };
		if (isValid(entityA) && isValid(entityB))
		{
			bool sameSoFar{ true };
			std::size_t const numComp{ entityA.theData.size() };
			for (std::size_t ndx{0u} ; ndx < numComp ; ++ndx)
			{
				sameSoFar &= nearlyEquals(entityA[ndx], entityB[ndx], tol);
				if (! sameSoFar)
				{
					break;
				}
			}
		}
		return same;
	}

} // [g3]

} // [engabra]


#endif // engabra_compare_INCL_
