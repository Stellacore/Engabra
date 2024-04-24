//
// MIT License
//
// Copyright (c) 2023 Stellacore Corporation
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


/*! \file
\brief Unit tests (and example) code for engabra::g3_private
*/


#include "checks.hpp" // testing environment common utilities

#include "g3_private.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <algorithm>
#include <functional>

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using engabra::g3::nearlyEquals;

	//! Examples for documentation
	std::string
	test0
		()
	{
		std::ostringstream oss;

		// [DoxyExample01]

		using namespace engabra::g3;

		// test blade operations with vector data
		// (same underlying std::vector<double>() type in all other blades)
		Vector const aVec  {  21.11, 21.22, 21.33 };
		Vector const bVec  {  11.10, 11.20, 11.30 };
		Vector const expAdd{  32.21, 32.42, 32.63 };
		Vector const expSub{  10.01, 10.02, 10.03 };

		// check binaryElementByElement operations with addition
		Vector const gotAdd
			{ engabra::g3::priv::binaryElementByElement
				( aVec
				, bVec
				, [] (double const & aa, double const bb) { return aa + bb; }
				)
			};

		// check binaryElementByElement operations with subtraction
		Vector const gotSub
			{ engabra::g3::priv::binaryElementByElement
				( aVec
				, bVec
				, [] (double const & aa, double const bb) { return aa - bb; }
				)
			};

			// [DoxyExample01]

		tst::checkGotExp(oss, gotAdd, expAdd, "Add");
		tst::checkGotExp(oss, gotSub, expSub, "Sub");

		return oss.str();
	}

}

//! Check behavior of g3_private functions
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test0();
	// oss << test1();

	if (oss.str().empty()) // Only pass if no errors were encountered
	{
		status = tst::CTest::pass;
	}
	else
	{
		// else report error messages
		std::cerr << "### FAILURE in test file: " << __FILE__ << std::endl;
		std::cerr << oss.str();
	}
	return status;
}

