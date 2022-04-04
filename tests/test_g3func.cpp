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


#include "test_common.hpp" // testing environment common utilities

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

	//! Check exponential functions
	std::string
	test1
		()
	{
		std::ostringstream oss;

		// [DoxyExampleExp]
		using namespace engabra::g3;

		// An 3D space angle with magnitude of a halfTurn (pi radians)
		// along an arbitrary (bivector) direction in space.
		BiVector const someAngleDir{ direction(e23 + e12) };
		BiVector const halfTurnAngle{ turnHalf * someAngleDir };
		// Euler Identify: exp(pi*i) = Spinor{ -1., zero<BiVector>() };
		Spinor const gotSpin{ exp(halfTurnAngle) };
		Spinor const expSpin{ -1., zero<BiVector>() };
			// [DoxyExampleExp]

		if (! nearlyEquals(gotSpin, expSpin))
		{
			oss << "Failure of exp() Euler identity test\n";
			oss << "expSpin: " << expSpin << '\n';
			oss << "gotSpin: " << gotSpin << '\n';
		}

		return oss.str();;
	}

	//! Check logarithm function
	std::string
	test2
		()
	{
		std::ostringstream oss;

		using namespace engabra::g3;

		// corner case - zero rotation
		// std::cout << "============= zero case\n";
		Spinor const spinZeroInit{  1., zero<BiVector>() };
		Spinor const gotLogZero{ logG2(spinZeroInit) };
		Spinor const expLogZero{ 0., zero<BiVector>() };
		Spinor const spinZeroRedo{ exp(gotLogZero) };
		if ( (! nearlyEquals(gotLogZero.theSca, expLogZero.theSca))
		  || (! nearlyEquals(gotLogZero.theBiv, expLogZero.theBiv))
		   )
		{
			oss << "Failure of logG2() zero angle test\n";
			oss << "expLogZero: " << expLogZero << '\n';
			oss << "gotLogZero: " << gotLogZero << '\n';
		}
		if (! nearlyEquals(spinZeroRedo, spinZeroInit))
		{
			oss << "Failure of logG2() zero reconstruction test\n";
			oss << "spinZeroInit: " << spinZeroInit << '\n';
			oss << "spinZeroRedo: " << spinZeroRedo << '\n';
		}

		// std::cout << "============= half case\n";
		// corner case - half rotation
		BiVector const bivDir{ e31 };
		Spinor const spinHalfInit{ -1., zero<BiVector>() };
		Spinor const gotLogHalf{ logG2(spinHalfInit, bivDir) };
		Spinor const expLogHalf{ std::log(1.), turnHalf * bivDir };
		Spinor const spinHalfRedo{ exp(gotLogHalf) };
		constexpr double tol{ 4. * std::numeric_limits<double>::epsilon() };
		if ( (! nearlyEquals(gotLogHalf.theSca, expLogHalf.theSca, tol))
		  || (! nearlyEquals(gotLogHalf.theBiv, expLogHalf.theBiv, tol))
		   )
		{
			oss << "Failure of logG2() half angle test\n";
			oss << "expLogHalf: " << io::fixed(expLogHalf, 3,21) << '\n';
			oss << "gotLogHalf: " << io::fixed(gotLogHalf, 3,21) << '\n';
		}
		if (! nearlyEquals(spinHalfRedo, spinHalfInit, tol))
		{
			oss << "Failure of logG2() half reconstruction test\n";
			oss << "spinHalfInit: " << io::fixed(spinHalfInit, 3,21) << '\n';
			oss << "spinHalfRedo: " << io::fixed(spinHalfRedo, 3,21) << '\n';
		}

		// std::cout << "============= neg scalar case\n";
		// corner case - half rotation
		Spinor const spinNegsInit{ -3., zero<BiVector>() };
		Spinor const gotLogNegs{ logG2(spinNegsInit, bivDir) };
		Spinor const expLogNegs{ std::log(3.), turnHalf * bivDir };
		Spinor const spinNegsRedo{ exp(gotLogNegs) };
		if ( (! nearlyEquals(gotLogNegs.theSca, expLogNegs.theSca, tol))
		  || (! nearlyEquals(gotLogNegs.theBiv, expLogNegs.theBiv, tol))
		   )
		{
			oss << "Failure of logG2() negative scalar test\n";
			oss << "expLogNegs: " << io::fixed(expLogNegs, 3,21) << '\n';
			oss << "gotLogNegs: " << io::fixed(gotLogNegs, 3,21) << '\n';
		}
		if (! nearlyEquals(spinNegsRedo, spinNegsInit, tol))
		{
			oss << "Failure of logG2() negative scalar reconstruction test\n";
			oss << "spinNegsInit: " << io::fixed(spinNegsInit, 3,21) << '\n';
			oss << "spinNegsRedo: " << io::fixed(spinNegsRedo, 3,21) << '\n';
		}

		// std::cout << "============= general case\n";
		// general case
		Spinor const spinSomeInit{ -2., BiVector{ .5, -.3, .7} };
		Spinor const gotLogSome{ logG2(spinSomeInit) };
		Spinor const spinSomeRedo{ exp(gotLogSome) };
		if (! nearlyEquals(spinSomeRedo, spinSomeInit, tol))
		{
			oss << "Failure of logG2() some reconstruction test\n";
			oss << "spinSomeInit: " << io::fixed(spinSomeInit, 3,21) << '\n';
			oss << "spinSomeRedo: " << io::fixed(spinSomeRedo, 3,21) << '\n';
		}

		// std::cout << "============= \n";
		return oss.str();;
	}


	//! Check sqrt() function for spinors
	std::string
	test3
		()
	{
		std::ostringstream oss;

		using namespace engabra::g3;

		// corner case - zero
		Spinor const gotRootZero{ sqrtG2(zero<Spinor>()) };
		Spinor const expRootZero{ 0., zero<BiVector>() };
		if (! nearlyEquals(gotRootZero, expRootZero))
		{
			oss << "Failure sqrtG2 zero test\n";
			oss << "expRootZero: " << expRootZero << '\n';
			oss << "gotRootZero: " << gotRootZero << '\n';
		}

		{ // corner case - half turn
			Spinor const gotRootHalf{ sqrtG2(one<Spinor>()) };
			Spinor const expRootHalf{ one<Spinor>() };
			if (! nearlyEquals(gotRootHalf, expRootHalf))
			{
				oss << "Failure sqrtG2 half +1 test\n";
				oss << "expRootHalf: " << expRootHalf << '\n';
				oss << "gotRootHalf: " << gotRootHalf << '\n';
			}
		}

		{ // corner case - half turn
			BiVector const bivDir{ e12 };
			Spinor const gotRootHalf{ sqrtG2(-one<Spinor>(), bivDir) };
			Spinor const expRootHalf{ 0., bivDir };
			if (! nearlyEquals(gotRootHalf, expRootHalf))
			{
				oss << "Failure sqrtG2 half -1 test\n";
				oss << "expRootHalf: " << expRootHalf << '\n';
				oss << "gotRootHalf: " << gotRootHalf << '\n';
			}
		}

		// a general case
		Vector const aVec{  -.8,  .2,  .7 };
		Vector const bVec{  1.2,  .9, 1.3 };
		Spinor const abInit{ aVec * bVec };
		Spinor const abRoot{ sqrtG2(abInit) };
		Spinor const abRedo{ sq(abRoot) };
		constexpr double tol{ 64. * std::numeric_limits<double>::epsilon() };
		if (! nearlyEquals(abRedo, abInit, tol))
		{
			oss << "Failure sqrtG2 simple general test\n";
			oss << "abInit: " << abInit << '\n';
			oss << "abRedo: " << abRedo << '\n';
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
	oss << test1();
	oss << test2();
	oss << test3();

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

