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
\brief Unit tests (and example) code for engabra::g3opsMul_ComPlex
*/


#include "checks.hpp" // testing environment common utilities
#include "test_g3opsMul.hpp" // useful data values: aDub, aSca, ..., aMvec

#include "g3opsMul_ComPlex.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using namespace engabra;
	using g3::nearlyEquals;

	//! Check product: ComPlex * double
	std::string
	testDub
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDub]
		using namespace engabra::g3;

		ComPlex const gotCplxDub{ aCplx * bDub };
		ComPlex const expCplxDub
			{ aCplx.theSca * bDub
			, aCplx.theTri * bDub
			};

			// [DoxyExampleDub]

		tst::checkGotExp(oss, gotCplxDub, expCplxDub, "CplxDub");

		return oss.str();;
	}

	//! Check product: ComPlex * Scalar
	std::string
	testSca
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSca]
		using namespace engabra::g3;

		ComPlex const gotCplxSca{ aCplx * bSca };
		ComPlex const expCplxSca
			{ aCplx.theSca * bSca
			, aCplx.theTri * bSca
			};

			// [DoxyExampleSca]

		tst::checkGotExp(oss, gotCplxSca, expCplxSca, "CplxSca");

		return oss.str();;
	}

	//! Check product: ComPlex * Vector
	std::string
	testVec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleVec]
		using namespace engabra::g3;

		DirPlex const gotCplxVec{ aCplx * bVec };
		DirPlex const expCplxVec
			{ aCplx.theSca * bVec
			+ aCplx.theTri * bVec
			};

			// [DoxyExampleVec]

		tst::checkGotExp(oss, gotCplxVec, expCplxVec, "CplxVec");

		return oss.str();;
	}

	//! Check product: ComPlex * BiVector
	std::string
	testBiv
		()
	{
		std::ostringstream oss;

		// [DoxyExampleBiv]
		using namespace engabra::g3;

		DirPlex const gotCplxBiv{ aCplx * bBiv };
		DirPlex const expCplxBiv
			{ aCplx.theTri * bBiv
			+ aCplx.theSca * bBiv
			};

			// [DoxyExampleBiv]

		tst::checkGotExp(oss, gotCplxBiv, expCplxBiv, "CplxBiv");

		return oss.str();;
	}

	//! Check product: ComPlex * TriVector
	std::string
	testTri
		()
	{
		std::ostringstream oss;

		// [DoxyExampleTri]
		using namespace engabra::g3;

		ComPlex const gotCplxTri{ aCplx * bTri };
		ComPlex const expCplxTri
			{ aCplx.theTri * bTri
			+ aCplx.theSca * bTri
			};

			// [DoxyExampleTri]

		tst::checkGotExp(oss, gotCplxTri, expCplxTri, "CplxTri");

		return oss.str();;
	}

	//! Check product: ComPlex * Spinor
	std::string
	testSpin
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSpin]
		using namespace engabra::g3;

		MultiVector const gotCplxSpin{ aCplx * bSpin };
		MultiVector const expCplxSpin
			{ aCplx.theSca * bSpin
			+ aCplx.theTri * bSpin
			};

			// [DoxyExampleSpin]

		tst::checkGotExp(oss, gotCplxSpin, expCplxSpin, "CplxSpin");

		return oss.str();;
	}

	//! Check product: ComPlex * ImSpin
	std::string
	testImsp
		()
	{
		std::ostringstream oss;

		// [DoxyExampleImsp]
		using namespace engabra::g3;

		MultiVector const gotCplxImsp{ aCplx * bImsp };
		MultiVector const expCplxImsp
			{ aCplx.theSca * bImsp
			+ aCplx.theTri * bImsp
			};

			// [DoxyExampleImsp]

		tst::checkGotExp(oss, gotCplxImsp, expCplxImsp, "CplxImsp");

		return oss.str();;
	}

	//! Check product: ComPlex * ComPlex
	std::string
	testCplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleCplx]
		using namespace engabra::g3;

		ComPlex const gotCplxCplx{ aCplx * bCplx };
		ComPlex const expCplxCplx
			{ Scalar{ aCplx.theSca * bCplx.theSca }
			+ Scalar{ aCplx.theTri * bCplx.theTri }
			, TriVector{ aCplx.theSca * bCplx.theTri }
			+ TriVector{ aCplx.theTri * bCplx.theSca }
			};

			// [DoxyExampleCplx]

		tst::checkGotExp(oss, gotCplxCplx, expCplxCplx, "CplxCplx");

		return oss.str();;
	}

	//! Check product: ComPlex * DirPlex
	std::string
	testDplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDplx]
		using namespace engabra::g3;

		DirPlex const gotCplxDplx{ aCplx * bDplx };
		DirPlex const expCplxDplx
			{ Vector{ aCplx.theTri * bDplx.theBiv }
			+ Vector{ aCplx.theSca * bDplx.theVec }
			, BiVector{ aCplx.theTri * bDplx.theVec }
			+ BiVector{ aCplx.theSca * bDplx.theBiv }
			};

			// [DoxyExampleDplx]

		tst::checkGotExp(oss, gotCplxDplx, expCplxDplx, "CplxDplx");

		return oss.str();;
	}

	//! Check product: ComPlex * MultiVector
	std::string
	testMvec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleMvec]
		using namespace engabra::g3;

		MultiVector const gotCplxMvec{ aCplx * bMvec };
		MultiVector const expCplxMvec
			{ Scalar{ aCplx.theSca * bMvec.theSca }
			+ Scalar{ aCplx.theTri * bMvec.theTri }
			, Vector{ aCplx.theSca * bMvec.theVec }
			+ Vector{ aCplx.theTri * bMvec.theBiv }
			, BiVector{ aCplx.theTri * bMvec.theVec }
			+ BiVector{ aCplx.theSca * bMvec.theBiv }
			, TriVector{ aCplx.theTri * bMvec.theSca }
			+ TriVector{ aCplx.theSca * bMvec.theTri }
			};

			// [DoxyExampleMvec]

		tst::checkGotExp(oss, gotCplxMvec, expCplxMvec, "CplxMvec");

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

