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
\brief Unit tests (and example) code for engabra::g3opsMul_BiVector
*/


#include "checks.hpp" // testing environment common utilities
#include "test_g3opsMul.hpp" // useful data values: aDub, aSca, ..., aMvec

#include "g3opsMul_BiVector.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using namespace engabra;
	using g3::nearlyEquals;

	//! Check product: BiVector * double
	std::string
	testDub
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDub]
		using namespace engabra::g3;

		BiVector const gotBivDub{ aBiv * bDub };
		BiVector const expBivDub{ (23.*103.), (29.*103.), (31.*103.) };

			// [DoxyExampleDub]

		tst::checkGotExp(oss, gotBivDub, expBivDub, "BivDub");

		return oss.str();;
	}

	//! Check product: BiVector * Scalar
	std::string
	testSca
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSca]
		using namespace engabra::g3;

		BiVector const gotBivSca{ aBiv * bSca };
		BiVector const expBivSca{ (23.*3.), (29.*3.), (31.*3.) };

			// [DoxyExampleSca]

		tst::checkGotExp(oss, gotBivSca, expBivSca, "BivSca");

		return oss.str();;
	}

	//! Check product: BiVector * Vector
	std::string
	testVec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleBiv]
		using namespace engabra::g3;

		ImSpin const gotBivVec{ aBiv * bVec };
		ImSpin const expBivVec
			{ Vector
				{ -(29.*19. - 17.*31.)
				,  (23.*19. - 13.*31.)
				, -(23.*17. - 13.*29.)
				}
			, TriVector
				{ 23.*13. + 29.*17. + 31.*19. }
			};

			// [DoxyExampleBiv]

		tst::checkGotExp(oss, gotBivVec, expBivVec, "BivVec");

		return oss.str();;
	}

	//! Check product: BiVector * BiVector
	std::string
	testBiv
		()
	{
		std::ostringstream oss;

		// [DoxyExampleBiv]
		using namespace engabra::g3;

		Spinor const gotBivBiv{ aBiv * bBiv };
		Spinor const expBivBiv
			{ Scalar
				{ -(23.*37. + 29.*41. + 31.*43.) }
			, BiVector
				{ -(29.*43. - 41.*31.)
				,  (23.*43. - 37.*31.)
				, -(23.*41. - 37.*29.)
				}
			};

			// [DoxyExampleBiv]

		tst::checkGotExp(oss, gotBivBiv, expBivBiv, "BivBiv");

		return oss.str();;
	}

	//! Check product: BiVector * TriVector
	std::string
	testTri
		()
	{
		std::ostringstream oss;

		// [DoxyExampleTri]
		using namespace engabra::g3;

		Vector const gotBivTri{ aBiv * bTri };
		Vector const expBivTri{ -(23.*53.), -(29.*53.), -(31.*53.) };

			// [DoxyExampleTri]

		tst::checkGotExp(oss, gotBivTri, expBivTri, "BivTri");

		return oss.str();;
	}

	//! Check product: BiVector * Spinor
	std::string
	testSpin
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSpin]
		using namespace engabra::g3;

		Spinor const gotBivSpin{ aBiv * bSpin };
		Spinor const expBivSpin
			{ Scalar // aBiv . bSpin.theBiv
				{ -(23.*37. + 29.*41. + 31.*43.) }
			, BiVector // aBiv * bSpin.theSca
				{ (23.*3.), (29.*3.), (31.*3.) }
			+ BiVector // aBiv (x) bSpin.theBiv
				{ -( 29.*43. - 41.*31.)
				,  ( 23.*43. - 37.*31.)
				, -( 23.*41. - 37.*29.)
				}
			};

			// [DoxyExampleSpin]

		tst::checkGotExp(oss, gotBivSpin, expBivSpin, "BivSpin");

		return oss.str();;
	}

	//! Check product: BiVector * ImSpin
	std::string
	testImsp
		()
	{
		std::ostringstream oss;

		// [DoxyExampleImsp]
		using namespace engabra::g3;

		ImSpin const gotBivImsp{ aBiv * bImsp };

		ImSpin const expBivImsp
			{ Vector // I*[(-I*aBiv) ^ bImsp.theVec]
				{ -(29.*19. - 17.*31.)
				,  (23.*19. - 13.*31.)
				, -(23.*17. - 13.*29.)
				}
			+ Vector // aBiv * bImsp.theTri
				{ -(23.*53.), -(29.*53.), -(31.*53.) }
			, TriVector // I*[(-I*aBiv) . bImsp.theVec]
				{ ( 23.*13. + 29.*17. + 31.*19.) }
			};

			// [DoxyExampleImsp]

		tst::checkGotExp(oss, gotBivImsp, expBivImsp, "BivImsp");

		return oss.str();;
	}

	//! Check product: BiVector * ComPlex
	std::string
	testCplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleCplx]
		using namespace engabra::g3;

		DirPlex const gotBivCplx{ aBiv * bCplx };
		DirPlex const expBivCplx
			{ Vector // aBiv * bCplx.theTri
				{ -(23.*53.), -(29.*53.), -(31.*53.) }
			, BiVector // aBiv * bCplx.theSca
				{  (23.*3.),  (29.*3.),  (31.*3.) }
			};

			// [DoxyExampleCplx]

		tst::checkGotExp(oss, gotBivCplx, expBivCplx, "BivCplx");

		return oss.str();;
	}

	//! Check product: BiVector * DirPlex
	std::string
	testDplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDplx]
		using namespace engabra::g3;

		MultiVector const gotBivDplx{ aBiv * bDplx };
		MultiVector const expBivDplx
			{ Scalar // [aBiv . bDplx.theBiv]
				{ -(23.*37. + 29.*41. + 31.*43.) }
			, Vector // I*[(-I*aBiv) ^ bDplx.theVec]
				{ -( 29.*19. - 17.*31.)
				,  ( 23.*19. - 13.*31.)
				, -( 23.*17. - 13.*29.)
				}
			, BiVector // [aBiv (x) bDplx.theBiv]
				{ -(29.*43. - 41.*31.)
				,  (23.*43. - 37.*31.)
				, -(23.*41. - 37.*29.)
				}
			, TriVector // I*[(-I*aBiv) . bDplx.theVec]
				{ (23.*13. + 29.*17. + 31.*19.) }
			};

			// [DoxyExampleDplx]

		tst::checkGotExp(oss, gotBivDplx, expBivDplx, "BivDplx");

		return oss.str();;
	}

	//! Check product: BiVector * MultiVector
	std::string
	testMvec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleMvec]
		using namespace engabra::g3;

		MultiVector const gotBivMvec{ aBiv * bMvec };
		MultiVector const expBivMvec
			{ Scalar // aBiv . bMvec.theBiv
				{ -((23.*37.) + (29.*41.) + (31.*43.)) }
			, Vector // aBiv * bMvec.theTri
				{ -(23.*53.), -(29.*53.), -(31.*53.) }
			+ Vector // aBiv . bMvec.theVec
				{ -(29.*19. - 17.*31.)
				,  (23.*19. - 13.*31.)
				, -(23.*17. - 13.*29.)
				}
			, BiVector // aBiv * bMvec.theSca
				{ (23.*3.), (29.*3.), (31.*3.) }
			+ BiVector // aBiv (x) bMvec.theBiv
				{ -(29.*43. - 41.*31.)
				,  (23.*43. - 37.*31.)
				, -(23.*41. - 37.*29.)
				}
			, TriVector // I*[(-I*aBiv) ^ bMvec.theVec]
				{  (23.*13. + 29.*17. + 31.*19.) }
			};

			// [DoxyExampleMvec]

		tst::checkGotExp(oss, gotBivMvec, expBivMvec, "BivMvec");

		return oss.str();;
	}

/*
	//! Check product: double * ZZ
	std::string
	testQ
		()
	{
		std::ostringstream oss;

		// [DoxyExampleQ]
		using namespace engabra::g3;

		ZZ const gotScaQ{ aSca * bQ };
		ZZ const expScaQ{ null<ZZ>() };

			// [DoxyExampleQ]

		tst::checkGotExp(oss, gotScaQ, expScaQ, "ScaQ");

		return oss.str();;
	}
*/

}

//! Check behavior of opsMul_double
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << testDub();
	oss << testSca();
	oss << testVec();
	oss << testBiv();
	oss << testTri();
	oss << testSpin();
	oss << testImsp();
	oss << testCplx();
	oss << testDplx();
	oss << testMvec();

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

