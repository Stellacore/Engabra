/*

MIT License

Copyright (c) 2021 Stellacore Corporation

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/


#ifndef engabra_compare_INCL_
#define engabra_compare_INCL_


#include "g3types.hpp"

#include <cmath>
#include <limits>


namespace engabra
{

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
		if (engabra::g3::isValid(testVal) && engabra::g3::isValid(refVal))
		{
			double const diff{ refVal - testVal };
			same = (std::abs(diff) < tol);
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
		// TODO
		return same;
	}

	/*! \brief True if testVal is nearly equal to refVal at tolerance.
	 *
	 */
	inline
	bool
	nearlyEquals
		( double const & testVal
		, double const & refVal
	 	, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		bool same{ false };
		// TODO
		return same;
	}


} // [engabra]


#endif // engabra_compare_INCL_
