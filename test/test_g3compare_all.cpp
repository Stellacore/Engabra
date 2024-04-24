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


#include "checks.hpp" // testing environment common utilities

#include "engabra.hpp"

// For test message output
#include <iostream>
#include <sstream>


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;
	using g3::nearlyEquals;

	//! Check TODO
	std::string
	test1
		()
	{
		std::ostringstream oss;

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
			oss << std::endl;
			oss << "Failure of nearlyEqual example test" << '\n';
			oss << "okayNear: " << std::boolalpha << okayNear << '\n';
			oss << "okayAway: " << std::boolalpha << okayAway << '\n';
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
				oss << "Failure of nearlyEqualsAbs Norm test\n";
				oss << "okayNear: " << std::boolalpha << okayNear << '\n';
				oss << "okayAway: " << std::boolalpha << okayAway << '\n';
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
				oss << "Failure of nearlyEqualsRel Norm test\n";
				oss << "okayNear: " << std::boolalpha << okayNear << '\n';
				oss << "okayAway: " << std::boolalpha << okayAway << '\n';
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
				oss << "Failure of nearlyEqualsRel Huge test\n";
				oss << "okayNear: " << std::boolalpha << okayNear << '\n';
				oss << "okayAway: " << std::boolalpha << okayAway << '\n';
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
				oss << "Failure of nearlyEqualsAbs Tiny test\n";
				oss << "okayNear: " << std::boolalpha << okayNear << '\n';
				oss << "okayAway: " << std::boolalpha << okayAway << '\n';
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
				oss << "Failure of nearlyEqualsRel Tiny test\n";
				oss << "okayNear: " << std::boolalpha << okayNear << '\n';
				oss << "okayAway: " << std::boolalpha << okayAway << '\n';
			}
		}

		return oss.str();
	}

	//! Check more complex entities
	std::string
	test2
		()
	{
		std::ostringstream oss;

		g3::Vector const vecA{ 2., -3., 5. };
		if (! nearlyEquals(vecA, vecA))
		{
			oss << "Failure of nearlyEquals Vector/Same test" << '\n';
		}
		g3::Vector const vecB{ vecA[0], vecA[1], vecA[2]+1. };
		if (  nearlyEquals(vecA, vecB))
		{
			oss << "Failure of nearlyEquals Vector/Diff test" << '\n';
		}

		g3::MultiVector const mvA(0.1,  1.1, 1.2, 1.3,  2.1, 2.2, 2.3,  3.1);
		if (!  nearlyEquals(mvA, mvA))
		{
			oss << "Failure of multivector nearlyEquals self test" << '\n';
		}

		g3::MultiVector mvB{};
		for (std::size_t ndx{0u} ; ndx < 8u ; ++ndx)
		{
			constexpr double eps{ 10.*std::numeric_limits<double>::epsilon() };
			mvB = mvA;
			mvB[ndx] += eps;
			if (  nearlyEquals(mvA, mvB))
			{
				oss << "Failure of multivector nearlyEquals test" << '\n';
				oss << "for ndx: " << ndx << std::endl;
			}

		}

		return oss.str();;
	}


	//! Check nearlyEquals with array that has large dynamic range
	std::string
	test3
		()
	{
		std::ostringstream oss;

		constexpr double magBig{ 1000000. };
		constexpr double tol{ .001 };

		// test fudge factor for generating data
		// likely related to sqrt(mach.epsilon) for RSS stats in nearlyEquals?
		constexpr double eps{ 1.e-6 };

		constexpr double magSame{ .5 * tol * magBig };
		constexpr double magDiff{ (1. + eps) * tol * magBig };

		g3::Vector const vecBase{ 0.,      0., magBig };
		g3::Vector const vecSame{ 0., magSame, magBig };
		g3::Vector const vecDiff{ 0., magDiff, magBig };

		// expect same at this tol
		if (! g3::nearlyEquals(vecBase, vecSame, tol))
		{
			g3::Vector const dif{ (1./magBig) * (vecBase - vecSame) };
			oss << "Failure of nearlyEquals Same big and small test\n";
			using namespace engabra::g3::io;
			oss << "vecBase: " << fixed(vecBase, 5u, 16u) << '\n';
			oss << "vecSame: " << fixed(vecSame, 5u, 16u) << '\n';
			oss << "    dif: " << fixed(dif, 5u, 16u) << '\n';
			oss << "    tol: " << fixed(tol, 5u, 16u) << '\n';
		}

		// expect different at this tol
		if (  g3::nearlyEquals(vecBase, vecDiff, tol))
		{
			g3::Vector const dif{ (1./magBig) * (vecBase - vecDiff) };
			oss << "Failure of nearlyEquals Diff big and small test\n";
			using namespace engabra::g3::io;
			oss << "vecBase: " << fixed(vecBase, 5u, 16u) << '\n';
			oss << "vecDiff: " << fixed(vecDiff, 5u, 16u) << '\n';
			oss << "    dif: " << fixed(dif, 5u, 16u) << '\n';
			oss << "    tol: " << fixed(tol, 5u, 16u) << '\n';
		}

		return oss.str();;
	}

	//! Special case reported as error
	std::string
	test4
		()
	{
		std::ostringstream oss;

		using namespace engabra::g3;

		double const tol{ 100. * std::numeric_limits<double>::epsilon() };
		double const gtol{ 10. * tol };
		Vector const meaVec
			{ -0.0000000000000035, -5.3033008588991040, 5.3033008588991093 };
		Vector const estVec
			{ -0.0000000000000033, -5.3033008588991049, 5.3033008588991084 };

		// as vector, RSS test should report that vectors equal
		if (! nearlyEquals(meaVec, estVec, gtol))
		{
			oss << "Failure of expected equality test" << '\n';
		}

		// however components tests should differ on the small value
		if (  nearlyEquals(meaVec[0], estVec[0], gtol))
		{
			oss << "Failure on component[0]\n";
		}
		// while testing same on the larger values
		if (! nearlyEquals(meaVec[1], estVec[1], gtol))
		{
			oss << "Failure on component[1]\n";
		}
		if (! nearlyEquals(meaVec[2], estVec[2], gtol))
		{
			oss << "Failure on component[2]\n";
		}

		return oss.str();
	}

}

//! Check behavior of TODO
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test1();
	oss << test2();
	oss << test3();
	oss << test4();

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

