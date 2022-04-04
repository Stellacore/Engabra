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


/*! \file
\brief Unit tests (and example) code for engabra::opsAdd
*/


#include "test_common.hpp" // testing environment common utilities

#include "g3opsAdd.hpp"
#include "engabra.hpp"

// For test message output
#include <iostream>
#include <sstream>


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;
	using g3::nearlyEquals;
	using g3::io::fixed;


	//! Check operations on basis blades
	std::string
	test1
		()
	{
		std::ostringstream oss;


		// [DoxyExample01]
		// example addition/subraction of two blades
		g3::Vector const vecA{ 1., 2., 3. };
		g3::Vector const vecB{ 9., 7., 5. };
		g3::Vector const gotSum{ vecA + vecB };
		g3::Vector const gotDif{ vecA - vecB };
		// [DoxyExample01]

		g3::Vector const expSum{ 10., 9., 8. };
		g3::Vector const expDif{ -8., -5., -2. };

		if (! nearlyEquals(gotSum, expSum))
		{
			g3::Vector const difSum{ gotSum - expSum };
			oss << "Failure of Sum/Vector test" << std::endl;
			oss << "exp: " << expSum << std::endl;
			oss << "got: " << gotSum << std::endl;
			oss << "dif: " << fixed(difSum,3,18) << std::endl;
		}

		if (! nearlyEquals(gotDif, expDif))
		{
			oss << "Failure of Dif/Vector test" << std::endl;
			oss << "exp: " << expDif << std::endl;
			oss << "got: " << gotDif << std::endl;
		}

		return oss.str();;
	}
}

//! Check behavior of NS
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test1();
	// oss << test2();

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

