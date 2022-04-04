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


#include "test_common.hpp" // testing environment common utilities

#include "g3compare.hpp"
#include "g3const.hpp"

#include "g3io.hpp"

#include <cmath>
#include <iostream> // For test message output


namespace
{
	// Keep test code focused on internal structure under main project name
	namespace g3 = engabra::g3;

	//! Check (hardcoded) value of pi against math library implementation
	std::size_t
	test1
		()
	{
		std::size_t errCount{ 0u };

		// display results to about full IEEE-754 precision.
		using engabra::g3::io::fixed;

		double const piGot{ g3::pi };
		double const piLib{ 4. * std::atan(1.) };
		if (! g3::nearlyEqualsAbs(piGot, piLib))
		{
			++errCount;
			std::cout << "Failure of 'pi' value check" << '\n';
			std::cout << "piGot: " << fixed(piGot) << '\n';
			std::cout << "piLib: " << fixed(piLib) << '\n';
		}

		{ // Check fractions of pi

			double const gotFromHalf{ 2. * g3::piHalf };
			if (! g3::nearlyEqualsAbs(gotFromHalf, piLib))
			{
				++errCount;
				std::cout << "Failure of 'piHalf' value check" << '\n';
				std::cout << "gotFromHalf: " << fixed(gotFromHalf) << '\n';
				std::cout << "      piLib: " << fixed(piLib) << '\n';
			}
			double const gotFromQtr{ 4. * g3::piQtr };
			if (! g3::nearlyEqualsAbs(gotFromQtr, piLib))
			{
				++errCount;
				std::cout << "Failure of 'piQtr' value check" << '\n';
				std::cout << "gotFromQtr: " << fixed(gotFromQtr) << '\n';
				std::cout << "     piLib: " << fixed(piLib) << '\n';
			}
		}

		{ // Check fractions of full cycle turn

			double const gotFromFull{ .5 * g3::turnFull };
			if (! g3::nearlyEqualsAbs(gotFromFull, piLib))
			{
				++errCount;
				std::cout << "Failure of 'piFull' value check" << '\n';
				std::cout << "gotFromFull: " << fixed(gotFromFull) << '\n';
				std::cout << "      piLib: " << fixed(piLib) << '\n';
			}
			double const gotFromHalf{ g3::turnHalf };
			if (! g3::nearlyEqualsAbs(gotFromHalf, piLib))
			{
				++errCount;
				std::cout << "Failure of 'piHalf' value check" << '\n';
				std::cout << "gotFromHalf: " << fixed(gotFromHalf) << '\n';
				std::cout << "      piLib: " << fixed(piLib) << '\n';
			}
			double const gotFromQtr{ 2. * g3::turnQtr };
			if (! g3::nearlyEqualsAbs(gotFromQtr, piLib))
			{
				++errCount;
				std::cout << "Failure of 'piQtr' value check" << '\n';
				std::cout << "gotFromQtr: " << fixed(gotFromQtr) << '\n';
				std::cout << "     piLib: " << fixed(piLib) << '\n';
			}
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

