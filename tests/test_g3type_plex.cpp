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
\brief Unit tests (and example) code for engabra::g3type (ComPlex and DirPlex)
*/


#include "test_common.hpp" // testing environment common utilities

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

	//! Check ComPlex basics
	std::string
	test0
		()
	{
		std::ostringstream oss;

		// [DoxyExample01]
		using namespace engabra::g3;

		// A null instance
		ComPlex const aNull{ null<ComPlex>() };
		// Initialize members
		ComPlex const cplx1{ Scalar{1.0}, TriVector{1.3} };
		// Construct from standard complex type
		ComPlex const cplx2(std::complex<double>(2.0, 2.3));

		// [DoxyExample01]

		if ( isValid(aNull))
		{
			oss << "Failure of ComPlex null validity test\n";
		}

		// check stream i/o
		std::ostringstream obuf;
		obuf << "cplx1: " << cplx1 << std::endl;
		obuf << aNull << '\n' << cplx2 << '\n';
		// std::cout << obuf.str() << '\n';

		std::string name; // to absorb keys
		std::istringstream ibuf(obuf.str());
		ComPlex got1{ null<ComPlex>() };
		ibuf >> name >> got1;
		if (! isValid(got1))
		{
			oss << "Failure of stream input/output test\n";
		}

		if (! nearlyEquals(got1, cplx1))
		{
			oss << "Failure of ComPlex nearlyEquals test\n";
		}

		return oss.str();;
	}

	//! Check DirPlex basics
	std::string
	test1
		()
	{
		std::ostringstream oss;

		// [DoxyExample02]
		using namespace engabra::g3;

		// A null instance
		DirPlex const aNull{ null<DirPlex>() };
		// Initialize members
		DirPlex const dplx1
			{ Vector{ 1.1, 1.2, 1.3 }, BiVector{ 1.4, 1.5, 1.6 } };

		// [DoxyExample02]

		if ( isValid(aNull))
		{
			oss << "Failure of DirPlex null validity test\n";
		}

		// check stream i/o
		std::ostringstream obuf;
		obuf << "dplx1: " << dplx1 << '\n';
		obuf << aNull << '\n';

		std::istringstream ibuf(obuf.str());
		std::string name; // to absorb keys
		DirPlex got1;
		ibuf >> name >> got1;
		if (! isValid(got1))
		{
			oss << "Failure of stream input/output test\n";
		}

		if (! nearlyEquals(got1, dplx1))
		{
			oss << "Failure of DirPlex nearlyEquals test\n";
		}

		return oss.str();;
	}

}

//! Check behavior of types ComPlex and DirPlex
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test0();
	oss << test1();

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

