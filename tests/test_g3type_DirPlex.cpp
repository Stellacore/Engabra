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
\brief Unit tests (and example) code for engabra::g3type
*/


#include "checks.hpp" // testing environment common utilities

#include "g3type.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;
	using g3::nearlyEquals;

	//! Examples for documentation
	std::string
	test0
		()
	{
		std::ostringstream oss;

		// [DoxyExample01]

		// DirPlex type comprises the spatially directed grades
		g3::Vector const expVec{ 1.1, 1.2, 1.3 };
		g3::BiVector const expBiv{ 2.1, 2.2, 2.3 };
		g3::DirPlex const dplex{ expVec, expBiv };

		// access vector grade components by index
		double const & vec0 = dplex[0];
		double const & vec1 = dplex[1];
		double const & vec2 = dplex[2];
		// access bivector grade components by index
		double const & biv0 = dplex[3];
		double const & biv1 = dplex[4];
		double const & biv2 = dplex[5];

		// [DoxyExample01]

		g3::Vector const gotVec{ vec0, vec1, vec2 };
		g3::BiVector const gotBiv{ biv0, biv1, biv2 };

		tst::checkGotExp(oss, gotVec, expVec, "vector grade indexing");
		tst::checkGotExp(oss, gotBiv, expBiv, "bivector grade indexing");

		return oss.str();;
	}

}

//! Check behavior of type DirPlex
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test0();

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

