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
\brief Unit tests (and example) code for engabra::g3opsMul_TriVector
*/


#include "checks.hpp" // testing environment common utilities
#include "test_g3opsMul.hpp" // useful data values: aDub, aSca, ..., aMvec

#include "g3opsMul_TriVector.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using namespace engabra;
	using g3::nearlyEquals;

	//! Check product: TriVector * double
	std::string
	testDub
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDub]
		using namespace engabra::g3;

		TriVector const gotTriDub{ aTri * bDub };
		TriVector const expTriDub{ (47.*103.) };

			// [DoxyExampleDub]

		tst::checkGotExp(oss, gotTriDub, expTriDub, "TriDub");

		return oss.str();;
	}

	//! Check product: TriVector * Scalar
	std::string
	testSca
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSca]
		using namespace engabra::g3;

		TriVector const gotTriSca{ aTri * bSca };
		TriVector const expTriSca{ (47.*3.) };

			// [DoxyExampleSca]

		tst::checkGotExp(oss, gotTriSca, expTriSca, "TriSca");

		return oss.str();;
	}

	//! Check product: TriVector * Vector
	std::string
	testVec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleVec]
		using namespace engabra::g3;

		BiVector const gotTriVec{ aTri * bVec };
		BiVector const expTriVec{ (47.*13.), (47.*17), (47.*19.) };

			// [DoxyExampleVec]

		tst::checkGotExp(oss, gotTriVec, expTriVec, "TriVec");

		return oss.str();;
	}

	//! Check product: TriVector * BiVector
	std::string
	testBiv
		()
	{
		std::ostringstream oss;

		// [DoxyExampleBiv]
		using namespace engabra::g3;

		Vector const gotTriBiv{ aTri * bBiv };
		Vector const expTriBiv{ -(47.*37.), -(47.*41.), -(47.*43.) };

			// [DoxyExampleBiv]

		tst::checkGotExp(oss, gotTriBiv, expTriBiv, "TriBiv");

		return oss.str();;
	}

	//! Check product: TriVector * TriVector
	std::string
	testTri
		()
	{
		std::ostringstream oss;

		// [DoxyExampleTri]
		using namespace engabra::g3;

		Scalar const gotTriTri{ aTri * bTri };
		Scalar const expTriTri{ -(47.*53.) };

			// [DoxyExampleTri]

		tst::checkGotExp(oss, gotTriTri, expTriTri, "TriTri");

		return oss.str();;
	}

	//! Check product: TriVector * Spinor
	std::string
	testSpin
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSpin]
		using namespace engabra::g3;

		ImSpin const gotTriSpin{ aTri * bSpin };
		ImSpin const expTriSpin
			{ Vector
				{ -(47.*37.), -(47.*41.), -(47.*43.) }
			, TriVector
				{ (47.*3.) }
			};

			// [DoxyExampleSpin]

		tst::checkGotExp(oss, gotTriSpin, expTriSpin, "TriSpin");

		return oss.str();;
	}

	//! Check product: TriVector * ImSpin
	std::string
	testImsp
		()
	{
		std::ostringstream oss;

		// [DoxyExampleImsp]
		using namespace engabra::g3;

		Spinor const gotTriImsp{ aTri * bImsp };
		Spinor const expTriImsp
			{ Scalar{ -(47.*53.) }
			, BiVector{ (47.*13.), (47.*17.), (47.*19.) }
			};

			// [DoxyExampleImsp]

		tst::checkGotExp(oss, gotTriImsp, expTriImsp, "TriImsp");

		return oss.str();;
	}

	//! Check product: TriVector * ComPlex
	std::string
	testCplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleCplx]
		using namespace engabra::g3;

		ComPlex const gotTriCplx{ aTri * bCplx };
		ComPlex const expTriCplx
				{ Scalar // aTri * bCplx.theTri
					{ -(47.*53.) }
				, TriVector // aTri * bCplx.theSca
					{  (47.*3.) }
				};

			// [DoxyExampleCplx]

		tst::checkGotExp(oss, gotTriCplx, expTriCplx, "TriCplx");

		return oss.str();;
	}

	//! Check product: TriVector * DirPlex
	std::string
	testDplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDplx]
		using namespace engabra::g3;

		DirPlex const gotTriDplx{ aTri * bDplx };
		DirPlex const expTriDplx
			{ Vector // aTri * bDplx.theBiv
				{ -(47.*37.), -(47.*41.), -(47.*43.) }
			, BiVector // aTri * bDplx.theVec
				{ (47.*13.), (47.*17.), (47.*19.) }
			};

			// [DoxyExampleDplx]

		tst::checkGotExp(oss, gotTriDplx, expTriDplx, "TriDplx");

		return oss.str();;
	}

	//! Check product: TriVector * MultiVector
	std::string
	testMvec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleMvec]
		using namespace engabra::g3;

		MultiVector const gotTriMvec{ aTri * bMvec };
		MultiVector const expTriMvec
			{ Scalar{ -(47.*53.) }
			, Vector{ -(47.*37.), -(47.*41.), -(47.*43.) }
			, BiVector{ (47.*13.), (47.*17.), (47.*19.) }
			, TriVector{ (47.*3.) }
			};

			// [DoxyExampleMvec]

		tst::checkGotExp(oss, gotTriMvec, expTriMvec, "TriMvec");

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

		ZZ const gotTriQ{ aSca * bQ };
		ZZ const expTriQ{ null<ZZ>() };

			// [DoxyExampleQ]

		tst::checkGotExp(oss, gotTriQ, expTriQ, "ScaQ");

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

