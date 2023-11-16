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
\brief Unit tests (and example) code for engabra::g3opsMul_double
*/


#include "checks.hpp" // testing environment common utilities
#include "test_g3opsMul.hpp" // useful data values: aDub, aSca, ..., aMvec

#include "g3opsMul_double.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using namespace engabra;
	using g3::nearlyEquals;

	//! Check product: double * double -- provided by language

	//! Check product: double * Scalar
	std::string
	testSca
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSca]
		using namespace engabra::g3;

		Scalar const gotDubSca{ aDub * bSca };
		Scalar const expDubSca{ (101.*3.) };

			// [DoxyExampleSca]

		tst::checkGotExp(oss, gotDubSca, expDubSca, "DubSca");

		return oss.str();;
	}

	//! Check product: double * Vector
	std::string
	testVec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleVec]
		using namespace engabra::g3;

		Vector const gotDubVec{ aDub * bVec };
		Vector const expDubVec{ (101.*13.), (101.*17), (101.*19.) };

			// [DoxyExampleVec]

		tst::checkGotExp(oss, gotDubVec, expDubVec, "DubVec");

		return oss.str();;
	}

	//! Check product: double * BiVector
	std::string
	testBiv
		()
	{
		std::ostringstream oss;

		// [DoxyExampleBiv]
		using namespace engabra::g3;

		BiVector const gotDubBiv{ aDub * bBiv };
		BiVector const expDubBiv{ (101.*37.), (101.*41.), (101.*43.) };

			// [DoxyExampleBiv]

		tst::checkGotExp(oss, gotDubBiv, expDubBiv, "DubBiv");

		return oss.str();;
	}

	//! Check product: double * TriVector
	std::string
	testTri
		()
	{
		std::ostringstream oss;

		// [DoxyExampleTri]
		using namespace engabra::g3;

		TriVector const gotDubTri{ aDub * bTri };
		TriVector const expDubTri{ (101.*53.) };

			// [DoxyExampleTri]

		tst::checkGotExp(oss, gotDubTri, expDubTri, "DubTri");

		return oss.str();;
	}

	//! Check product: double * Spinor
	std::string
	testSpin
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSpin]
		using namespace engabra::g3;

		Spinor const gotDubSpin{ aDub * bSpin };
		Spinor const expDubSpin
			{ (101.*3.), BiVector{ (101.*37.), (101.*41.), (101.*43.) } };

			// [DoxyExampleSpin]

		tst::checkGotExp(oss, gotDubSpin, expDubSpin, "DubSpin");

		return oss.str();;
	}

	//! Check product: double * ImSpin
	std::string
	testImsp
		()
	{
		std::ostringstream oss;

		// [DoxyExampleImsp]
		using namespace engabra::g3;

		ImSpin const gotDubImsp{ aDub * bImsp };
		ImSpin const expDubImsp
			{ Vector{ (101.*13.), (101.*17.), (101.*19.) }
			, TriVector{ (101.*53.) }
			};

			// [DoxyExampleImsp]

		tst::checkGotExp(oss, gotDubImsp, expDubImsp, "DubImsp");

		return oss.str();;
	}

	//! Check product: double * ComPlex
	std::string
	testCplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleCplx]
		using namespace engabra::g3;

		ComPlex const gotDubCplx{ aDub * bCplx };
		ComPlex const expDubCplx{ (101.*3.), (101.*53.) };

			// [DoxyExampleCplx]

		tst::checkGotExp(oss, gotDubCplx, expDubCplx, "DubCplx");

		return oss.str();;
	}

	//! Check product: double * DirPlex
	std::string
	testDplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDplx]
		using namespace engabra::g3;

		DirPlex const gotDubDplx{ aDub * bDplx };
		DirPlex const expDubDplx
			{ Vector{ (101.*13.), (101.*17.), (101.*19.) }
			, BiVector{ (101.*37.), (101.*41.), (101.*43.) }
			};

			// [DoxyExampleDplx]

		tst::checkGotExp(oss, gotDubDplx, expDubDplx, "DubDplx");

		return oss.str();;
	}

	//! Check product: double * MultiVector
	std::string
	testMvec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleMvec]
		using namespace engabra::g3;

		MultiVector const gotDubMvec{ aDub * bMvec };
		MultiVector const expDubMvec
			{ Scalar{ (101.*3.) }
			, Vector{ (101.*13.), (101.*17.), (101.*19.) }
			, BiVector{ (101.*37.), (101.*41.), (101.*43.) }
			, TriVector{ (101.*53.) }
			};

			// [DoxyExampleMvec]

		tst::checkGotExp(oss, gotDubMvec, expDubMvec, "DubMvec");

		return oss.str();;
	}

/*
double const aDub{ 101. };
double const bDub{ 103. };
Scalar const aSca{ 2. };
Scalar const bSca{ 3. };
Vector const aVec{ 5., 7., 11. };
Vector const bVec{ 13., 17., 19. };
BiVector const aBiv{ 23., 29., 31. };
BiVector const bBiv{ 37., 41., 43. };
TriVector const aTri{ 47. };
TriVector const bTri{ 53. };
*/

/*
	//! Check product: double * ZZ
	std::string
	testQ
		()
	{
		std::ostringstream oss;

		// [DoxyExampleQ]
		using namespace engabra::g3;

		ZZ const gotDubQ{ aDub * bQ };
		ZZ const expDubQ{ null<ZZ>() };

			// [DoxyExampleQ]

		tst::checkGotExp(oss, gotDubQ, expDubQ, "DubQ");

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

