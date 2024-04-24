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
\brief Unit tests (and example) code for engabra::publish
*/


#include "checks.hpp" // testing environment common utilities

#include "engabra.hpp"

// [DoxyExample01]
#include "g3publish.hpp"
// [DoxyExample01]

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


		std::ostringstream someStream;
		// Use of fully qualified names
		{
			// [DoxyExample02]
			using namespace engabra; // includes g3publish.hpp

			// fully qualified type declarations
			g3::Vector const vecA{ 1.0, 1.1, 1.2 };
			g3::Vector const vecB{ 2.0, 2.1, 2.2 };
			// the various operator functions are available in global
			// namespace after including "g3publish.hpp" header.
			g3::Vector const vecC{ vecA + (-vecB) };
			someStream
				<< " vecC: " << vecC  // engabra op<<() also global
				<< " ok: " << g3::isValid(vecC)
				<< '\n';
			// [DoxyExample02]
		}

		if (someStream.str().empty())
		{
			++errCount;
		}

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

