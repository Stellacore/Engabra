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


#include "test_common.hpp" // testing environment common utilities

#include "g3io.hpp"

#include <iostream> // For test message output
#include <sstream>
#include <vector>


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;

	//! Check TODO
	std::size_t
	test1
		()
	{
		std::size_t errCount{ 0u };

		g3::Vector const vec{ 1.23, 3.45, 5.67 };

		// Formatter local to g3::io, not really for public consumption
		g3::io::DoubleFormat const fmt{};

		// Expected: default formatter should be <sign><3><.><6>
		std::string const expString
			{ "   -3.123400  -23.123400 -123.123400" };
		std::vector<double> const vals
			{   -3.1234
			,  -23.1234
			, -123.1234
			};

		// Format several values with formatter
		std::ostringstream oss;
		for (double const & val : vals)
		{
			oss << fmt << val;
		}
		std::string const gotString{ oss.str() };

		if (! (gotString == expString))
		{
			++errCount;
			std::cout << "Failure of g3::io::DoubleFormat test" << '\n';
			std::cout << "got: '" << gotString << "'\n";
			std::cout << "exp: '" << expString << "'\n";
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

