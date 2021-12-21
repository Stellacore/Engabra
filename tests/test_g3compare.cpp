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
\brief Unit tests (and example) code for engabra::compare
*/


#include "test_common.hpp" // testing environment common utilities

#include "engabra.hpp"

#include <iostream> // For test message output


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

		//
		// Typical compare result
		//

		// [DoxyExample01]

		// note tolerance relative to general magnitude of numbers
		constexpr double diffTol{  1./1000./123. }; // significant difference
		double const baseVal{ 123.456 }; // relative to
		double const nearVal{ 123.457 }; // is nearly equal
		double const awayVal{ 123.458}; // NOT nearly equal

		// Tests determine if values are essentially equal within
		// relative tolerance threshold.
		bool const okayNear{ (  g3::nearlyEquals(nearVal, baseVal, diffTol)) };
		bool const okayAway{ (! g3::nearlyEquals(awayVal, baseVal, diffTol)) };

		// [DoxyExample01]

		if ((! okayNear) || (! okayAway))
		{
			++errCount;
			std::cerr << std::endl;
			std::cerr << "Failure of nearlyEqual example test" << '\n';
			std::cerr << "okayNear: " << std::boolalpha << okayNear << '\n';
			std::cerr << "okayAway: " << std::boolalpha << okayAway << '\n';
		}

		//
		// Check compare of normalized value
		//

		constexpr double diffNorm{  1./1024. }; // difference of significance
		double const baseNorm{ 1. }; // relative to
		double const nearNorm{ baseNorm + .5*diffNorm }; // is nearly equal
		double const awayNorm{ baseNorm + diffNorm }; // NOT nearly equal

		// Absolute value compare test result
		{
			bool const okayNear
				{ (  g3::nearlyEqualsAbs(nearNorm, baseNorm, diffNorm)) };
			bool const okayAway
				{ (! g3::nearlyEqualsAbs(awayNorm, baseNorm, diffNorm)) };

			if ((! okayNear) || (! okayAway))
			{
				++errCount;
				std::cerr << "Failure of nearlyEqualsAbs Norm test\n";
				std::cerr << "okayNear: " << std::boolalpha << okayNear << '\n';
				std::cerr << "okayAway: " << std::boolalpha << okayAway << '\n';
			}
		}

		// Relative value compare test result
		{
			bool const okayNear
				{ (  g3::nearlyEqualsRel(nearNorm, baseNorm, diffNorm)) };
			bool const okayAway
				{ (! g3::nearlyEqualsRel(awayNorm, baseNorm, diffNorm)) };

			if ((! okayNear) || (! okayAway))
			{
				++errCount;
				std::cerr << "Failure of nearlyEqualsRel Norm test\n";
				std::cerr << "okayNear: " << std::boolalpha << okayNear << '\n';
				std::cerr << "okayAway: " << std::boolalpha << okayAway << '\n';
			}
		}

		//
		// Check compare of large value
		//

		// need to allow some room for noise from test computation
		// constexpr double eps{ std::numeric_limits<double>::epsilon() };
		constexpr double eps{ 1.e-15 / diffNorm };
		constexpr double less{ 1. - eps };
		constexpr double more{ 1. + eps };

		constexpr double big{ 1024.*1024. };
		constexpr double huge{ big * big * big };
		double const diffHuge{ huge * diffNorm };
		double const baseHuge{ huge * baseNorm };
		double const nearHuge{ baseHuge + less*diffHuge }; // is nearly equal
		double const awayHuge{ baseHuge + more*diffHuge }; // NOT nearly equal

		{
			// For large values absolute compare loses precision, and
			// relative test is appropriate to use
			bool const okayNear
				{ (  g3::nearlyEqualsRel(nearHuge, baseHuge, diffNorm)) };
			bool const okayAway
				{ (! g3::nearlyEqualsRel(awayHuge, baseHuge, diffNorm)) };

			if ((! okayNear) || (! okayAway))
			{
				++errCount;
				std::cerr << "Failure of nearlyEqualsRel Huge test\n";
				std::cerr << "okayNear: " << std::boolalpha << okayNear << '\n';
				std::cerr << "okayAway: " << std::boolalpha << okayAway << '\n';
			}
		}

		//
		// Check compare of small value
		//

		constexpr double tiny{ 1. / huge };

		double const diffTiny{ tiny * diffNorm };
		double const baseTiny{ tiny * baseNorm };
		double const nearTiny{ baseTiny + less*diffTiny }; // is nearly equal
		double const awayTiny{ baseTiny + more*diffTiny }; // NOT nearly equal

		// For small values absolute test passes too easily
		{
			bool const okayNear
				{ (  g3::nearlyEqualsAbs(nearTiny, baseTiny, diffTiny)) };
			bool const okayAway
				{ (! g3::nearlyEqualsAbs(awayTiny, baseTiny, diffTiny)) };

			if ((! okayNear) || (! okayAway))
			{
				++errCount;
				std::cerr << "Failure of nearlyEqualsAbs Tiny test\n";
				std::cerr << "okayNear: " << std::boolalpha << okayNear << '\n';
				std::cerr << "okayAway: " << std::boolalpha << okayAway << '\n';
			}
		}

		// For small values relative test is tightest
		{
			bool const okayNear
				{ (  g3::nearlyEqualsRel(nearTiny, baseTiny, diffNorm)) };
			bool const okayAway
				{ (! g3::nearlyEqualsRel(awayTiny, baseTiny, diffNorm)) };

			if ((! okayNear) || (! okayAway))
			{
				++errCount;
				std::cerr << "Failure of nearlyEqualsRel Tiny test\n";
				std::cerr << "okayNear: " << std::boolalpha << okayNear << '\n';
				std::cerr << "okayAway: " << std::boolalpha << okayAway << '\n';
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

