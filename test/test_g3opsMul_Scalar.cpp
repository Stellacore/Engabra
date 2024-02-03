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
\brief Unit tests (and example) code for engabra::g3opsMul_Scalar
*/


#include "checks.hpp" // testing environment common utilities
#include "test_g3opsMul.hpp" // useful data values: aDub, aSca, ..., aMvec

#include "g3opsMul_Scalar.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using namespace engabra;
	using g3::nearlyEquals;

	//! Check product: Scalar * double
	std::string
	testDub
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDub]
		using namespace engabra::g3;

		Scalar const gotScaDub{ aSca * bDub };
		Scalar const expScaDub{ (2.*103.) };

			// [DoxyExampleDub]

		tst::checkGotExp(oss, gotScaDub, expScaDub, "ScaDub");

		return oss.str();;
	}

	//! Check product: Scalar * Scalar
	std::string
	testSca
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSca]
		using namespace engabra::g3;

		Scalar const gotScaSca{ aSca * bSca };
		Scalar const expScaSca{ (2.*3.) };

			// [DoxyExampleSca]

		tst::checkGotExp(oss, gotScaSca, expScaSca, "ScaSca");

		return oss.str();;
	}

	//! Check product: Scalar * Vector
	std::string
	testVec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleVec]
		using namespace engabra::g3;

		Vector const gotScaVec{ aSca * bVec };
		Vector const expScaVec{ (2.*13.), (2.*17), (2.*19.) };

			// [DoxyExampleVec]

		tst::checkGotExp(oss, gotScaVec, expScaVec, "ScaVec");

		return oss.str();;
	}

	//! Check product: Scalar * BiVector
	std::string
	testBiv
		()
	{
		std::ostringstream oss;

		// [DoxyExampleBiv]
		using namespace engabra::g3;

		BiVector const gotScaBiv{ aSca * bBiv };
		BiVector const expScaBiv{ (2.*37.), (2.*41.), (2.*43.) };

			// [DoxyExampleBiv]

		tst::checkGotExp(oss, gotScaBiv, expScaBiv, "ScaBiv");

		return oss.str();;
	}

	//! Check product: Scalar * TriVector
	std::string
	testTri
		()
	{
		std::ostringstream oss;

		// [DoxyExampleTri]
		using namespace engabra::g3;

		TriVector const gotScaTri{ aSca * bTri };
		TriVector const expScaTri{ (2.*53.) };

			// [DoxyExampleTri]

		tst::checkGotExp(oss, gotScaTri, expScaTri, "ScaTri");

		return oss.str();;
	}

	//! Check product: Scalar * Spinor
	std::string
	testSpin
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSpin]
		using namespace engabra::g3;

		Spinor const gotScaSpin{ aSca * bSpin };
		Spinor const expScaSpin
			{ (2.*3.), BiVector{ (2.*37.), (2.*41.), (2.*43.) } };

			// [DoxyExampleSpin]

		tst::checkGotExp(oss, gotScaSpin, expScaSpin, "ScaSpin");

		return oss.str();;
	}

	//! Check product: Scalar * ImSpin
	std::string
	testImsp
		()
	{
		std::ostringstream oss;

		// [DoxyExampleImsp]
		using namespace engabra::g3;

		ImSpin const gotScaImsp{ aSca * bImsp };
		ImSpin const expScaImsp
			{ Vector{ (2.*13.), (2.*17.), (2.*19.) }
			, TriVector{ (2.*53.) }
			};

			// [DoxyExampleImsp]

		tst::checkGotExp(oss, gotScaImsp, expScaImsp, "ScaImsp");

		return oss.str();;
	}

	//! Check product: Scalar * ComPlex
	std::string
	testCplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleCplx]
		using namespace engabra::g3;

		ComPlex const gotScaCplx{ aSca * bCplx };
		ComPlex const expScaCplx{ (2.*3.), (2.*53.) };

			// [DoxyExampleCplx]

		tst::checkGotExp(oss, gotScaCplx, expScaCplx, "ScaCplx");

		return oss.str();;
	}

	//! Check product: Scalar * DirPlex
	std::string
	testDplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDplx]
		using namespace engabra::g3;

		DirPlex const gotScaDplx{ aSca * bDplx };
		DirPlex const expScaDplx
			{ Vector{ (2.*13.), (2.*17.), (2.*19.) }
			, BiVector{ (2.*37.), (2.*41.), (2.*43.) }
			};

			// [DoxyExampleDplx]

		tst::checkGotExp(oss, gotScaDplx, expScaDplx, "ScaDplx");

		return oss.str();;
	}

	//! Check product: Scalar * MultiVector
	std::string
	testMvec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleMvec]
		using namespace engabra::g3;

		MultiVector const gotScaMvec{ aSca * bMvec };
		MultiVector const expScaMvec
			{ Scalar{ (2.*3.) }
			, Vector{ (2.*13.), (2.*17.), (2.*19.) }
			, BiVector{ (2.*37.), (2.*41.), (2.*43.) }
			, TriVector{ (2.*53.) }
			};

			// [DoxyExampleMvec]

		tst::checkGotExp(oss, gotScaMvec, expScaMvec, "ScaMvec");

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

