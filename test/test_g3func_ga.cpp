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
\brief Unit tests (and example) code for engabra::g3func
*/


#include "checks.hpp" // testing environment common utilities

#include "g3func.hpp"

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

		// [DoxyExampleUtil]
		using namespace engabra::g3;
		Spinor const aSpin{ 1., -.5, .25, .75 };

		Spinor const expSq{ aSpin * aSpin };
		Spinor const gotSq{ sq(aSpin) };

		Spinor const expCube{ aSpin * aSpin * aSpin };
		Spinor const gotCube{ cube(aSpin) };
			// [DoxyExampleUtil]

		if (! nearlyEquals(gotSq, expSq))
		{
			oss << "Failure of sq() \n";
		}
		if (! nearlyEquals(gotCube, expCube))
		{
			oss << "Failure of cube() test\n";
		}

		// [DoxyExampleMagDir]
		// Factor element into magnitude and direction parts
		using namespace engabra::g3;
		Vector const someVec{ -3., -5., 7. };

		std::pair<double, Vector> const vecMagDir{ pairMagDirFrom(someVec) };
		double const & mag = vecMagDir.first;
		Vector const & dir = vecMagDir.second;

		// reconsitute
		Vector const reconVec{ mag * dir };
			// [DoxyExampleMagDir]

		constexpr double tol{ 2.* std::numeric_limits<double>::epsilon() };
		if (! nearlyEquals(reconVec, someVec, tol))
		{
			oss << "Failure of mag*dir factor test\n";
			oss << "expVec: " << someVec << '\n';
			oss << "gotVec: " << reconVec << '\n';
		}

		return oss.str();;
	}

}

//! Check behavior of func
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

