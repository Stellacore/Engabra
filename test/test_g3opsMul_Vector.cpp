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
\brief Unit tests (and example) code for engabra::g3opsMul_Vector
*/


#include "checks.hpp" // testing environment common utilities
#include "test_g3opsMul.hpp" // useful data values: aDub, aSca, ..., aMvec

#include "g3opsMul_Vector.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using namespace engabra;
	using g3::nearlyEquals;

	//! Check product: Vector * double
	std::string
	testDub
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDub]
		using namespace engabra::g3;

		Vector const gotVecDub{ aVec * bDub };
		Vector const expVecDub{ (5.*103.), (7.*103.), (11.*103.) };

			// [DoxyExampleDub]

		tst::checkGotExp(oss, gotVecDub, expVecDub, "VecDub");

		return oss.str();;
	}

	//! Check product: Vector * Scalar
	std::string
	testSca
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSca]
		using namespace engabra::g3;

		Vector const gotVecSca{ aVec * bSca };
		Vector const expVecSca{ (5.*3.), (7.*3.), (11*3.) };

			// [DoxyExampleSca]

		tst::checkGotExp(oss, gotVecSca, expVecSca, "VecSca");

		return oss.str();;
	}

	//! Check product: Vector * Vector
	std::string
	testVec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleVec]
		using namespace engabra::g3;

		Spinor const gotVecVec{ aVec * bVec };
		Spinor const expVecVec
			{ Scalar
				{ 5.*13. + 7.*17. + 11.*19. }
			, BiVector
				{  (7.*19. - 17.*11.)
				, -(5.*19. - 13.*11.)
				,  (5.*17. - 13.*7.)
				}
			};

			// [DoxyExampleVec]

		tst::checkGotExp(oss, gotVecVec, expVecVec, "VecVec");

		return oss.str();;
	}

	//! Check product: Vector * BiVector
	std::string
	testBiv
		()
	{
		std::ostringstream oss;

		// [DoxyExampleBiv]
		using namespace engabra::g3;

		ImSpin const gotVecBiv{ aVec * bBiv };
		ImSpin const expVecBiv
			{ Vector
				{ -( 7.*43. - 41.*11.)
				,  ( 5.*43. - 37.*11.)
				, -( 5.*41. - 37.* 7.)
				}
			, TriVector
				{ (5.*37. + 7.*41. + 11.*43.) }
			};

			// [DoxyExampleBiv]

		tst::checkGotExp(oss, gotVecBiv, expVecBiv, "VecBiv");

		return oss.str();;
	}

	//! Check product: Vector * TriVector
	std::string
	testTri
		()
	{
		std::ostringstream oss;

		// [DoxyExampleTri]
		using namespace engabra::g3;

		BiVector const gotVecTri{ aVec * bTri };
		BiVector const expVecTri{ (5.*53.), (7.*53.), (11.*53.) };

			// [DoxyExampleTri]

		tst::checkGotExp(oss, gotVecTri, expVecTri, "VecTri");

		return oss.str();;
	}

	//! Check product: Vector * Spinor
	std::string
	testSpin
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSpin]
		using namespace engabra::g3;

		ImSpin const gotVecSpin{ aVec * bSpin };
		ImSpin const expVecSpin
			{ Vector // aVec * bSpin.theSca
				{ (5.*3.), (7.*3.), (11.*3.) }
			+ Vector // aVec . bSpin.theBiv
				{ -( 7.*43. - 41.*11.)
				,  ( 5.*43. - 37.*11.)
				, -( 5.*41. - 37.* 7.)
				}
			, TriVector // aVec ^ bSpin.theBiv
				{ (5.*37. + 7.*41. + 11.*43.) }
			};

			// [DoxyExampleSpin]

		tst::checkGotExp(oss, gotVecSpin, expVecSpin, "VecSpin");

		return oss.str();;
	}

	//! Check product: Vector * ImSpin
	std::string
	testImsp
		()
	{
		std::ostringstream oss;

		// [DoxyExampleImsp]
		using namespace engabra::g3;

		Spinor const gotVecImsp{ aVec * bImsp };

		Spinor const expVecImsp
			{ Scalar // aVec . bImsp.theVec
				{ ( 5.*13. +  7.*17. + 11.*19.) }
			, BiVector // aVec ^ bImsp.theVec
				{  ( 7.*19. - 17.*11.)
				, -( 5.*19. - 13.*11.)
				,  ( 5.*17. - 13.* 7.)
				}
			+ BiVector // aVec * bImsp.theTri
				{ (5.*53.), (7.*53.), (11.*53.) }
			};

			// [DoxyExampleImsp]

		tst::checkGotExp(oss, gotVecImsp, expVecImsp, "VecImsp");

		return oss.str();;
	}

	//! Check product: Vector * ComPlex
	std::string
	testCplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleCplx]
		using namespace engabra::g3;

		DirPlex const gotVecCplx{ aVec * bCplx };
		DirPlex const expVecCplx
			{ Vector{  (5.*3.),  (7.*3.), (11.*3.) }
			, BiVector{  (5.*53.),  (7.*53.), (11.*53.) }
			};

			// [DoxyExampleCplx]

		tst::checkGotExp(oss, gotVecCplx, expVecCplx, "VecCplx");

		return oss.str();;
	}

	//! Check product: Vector * DirPlex
	std::string
	testDplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDplx]
		using namespace engabra::g3;

		MultiVector const gotVecDplx{ aVec * bDplx };
		MultiVector const expVecDplx
			{ Scalar
				{ 5.*13. + 7.*17. + 11.*19. }
			, Vector
				{ -( 7.*43. - 41.*11.)
				,  ( 5.*43. - 37.*11.)
				, -( 5.*41. - 37.* 7.)
				}
			, BiVector
				{  (7.*19. - 17.*11.)
				, -(5.*19. - 13.*11.)
				,  (5.*17. - 13.*7.)
				}
			, TriVector
				{ (5.*37. + 7.*41. + 11.*43.) }
			};

			// [DoxyExampleDplx]

		tst::checkGotExp(oss, gotVecDplx, expVecDplx, "VecDplx");

		return oss.str();;
	}

	//! Check product: Vector * MultiVector
	std::string
	testMvec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleMvec]
		using namespace engabra::g3;

		MultiVector const gotVecMvec{ aVec * bMvec };
		MultiVector const expVecMvec
			{ Scalar // aVec . bMvec.theVec
				{ ( 5.*13.) + ( 7.*17.) + (11.*19.) }
			, Vector // aVec * bMvec.theSca
				{ ( 5.*3.), ( 7.*3.), (11.*3.) }
			+ Vector // I*[aVec ^ (-I*bMvec.theBiv)
				{ -( 7.*43. - 41.*11.)
				,  ( 5.*43. - 37.*11.)
				, -( 5.*41. - 37.* 7.)
				}
			, BiVector // aVec ^ bMvec.theVec
				{  (7.*19. - 17.*11.)
				, -(5.*19. - 13.*11.)
				,  (5.*17. - 13.*7.)
				}
			+ BiVector // aVec * bMvec.theTri
				{  ( 5.*53.),  ( 7.*53.), (11.*53.) }
			, TriVector // I*[aVec . (-I*bMvec.theBiv)
				{ ( 5.*37. +  7.*41. + 11.*43.) }
			};

			// [DoxyExampleMvec]

		tst::checkGotExp(oss, gotVecMvec, expVecMvec, "VecMvec");

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

