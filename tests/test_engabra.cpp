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
\brief Unit tests (and example) code for 'engabra' level items
*/


#include "test_common.hpp" // testing environment common utilities

#include "engabra.hpp"

#include <cassert>
#include <iostream> // For test message output
#include <sstream>


namespace
{
	//! Check TODO
	std::size_t
	test1
		()
	{
		std::size_t errCount{ 0u };

		// [DoxyExample01]

		std::ostringstream someStream;
		// Use of fully qualified names
		{
			// fully qualified operations
			engabra::g3::Vector const vecA{ 1.0, 1.1, 1.2 };
			engabra::g3::Vector const vecB{ 2.0, 2.1, 2.2 };
			using engabra::g3::operator+;  // required here
			using engabra::g3::operator-;  // required here
			engabra::g3::Vector const vecC{ vecA + (-vecB) };
			someStream
				<< " vecC: " << vecC  // engabra's global scope ::operator<<
				<< " ok: " << engabra::g3::isValid(vecC)
				<< '\n';
		}

			// [DoxyExample01]

		// [DoxyExample02]

		// Implicit use of "G3" subspace within engabra
		{
			using namespace engabra;

			// relatively compact notation with short namespace qualification
			g3::Vector const vecA{ 1.0, 1.1, 1.2 };
			g3::Vector const vecB{ 2.0, 2.1, 2.2 };
			using g3::operator+;
			g3::Vector const vecC{ vecA + vecB };
			someStream
				<< " vecC: " << vecC  // engabra's global scope ::operator<<
				<< " ok: " << g3::isValid(vecC)
				<< '\n';
		}

			// [DoxyExample02]

		// [DoxyExample03]

		// Implicit use of all basic items within the library
		{
			using namespace engabra::g3;

			// relatively compact notation with short namespace qualification
			Vector const vecA{ 1.0, 1.1, 1.2 };
			Vector const vecB{ 2.0, 2.1, 2.2 };
			Vector const vecC{ vecA + vecB }; // op+() implicitly
			someStream
				<< " vecC: " << vecC  // engabra's global scope ::operator<<
				<< " ok: " << isValid(vecC) // implicit engabra function
				<< '\n';
		}

			// [DoxyExample03]

		std::cout << someStream.str();

		return errCount;
	}
}

//! Check behavior of TODO
int
main
	()
{
	int status{ tst::CTest::fail };
	std::size_t errCount{ 0u };

	errCount += test1();
//	errCount += test2();

	if (0u == errCount) // Only pass if no errors were encountered
	{
		status = tst::CTest::pass;
	}
	return status;
}

