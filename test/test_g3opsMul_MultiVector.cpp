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
\brief Unit tests (and example) code for engabra::g3opsMul_MultiVector
*/


#include "checks.hpp" // testing environment common utilities
#include "test_g3opsMul.hpp" // useful data values: aDub, aSca, ..., aMvec

#include "g3opsMul_MultiVector.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using namespace engabra;
	using g3::nearlyEquals;

	//! Check product: MultiVector * double
	std::string
	testDub
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDub]
		using namespace engabra::g3;

		MultiVector const gotMvecDub{ aMvec * bDub };
		MultiVector const expMvecDub
			{ aMvec.theSca * bDub
			, aMvec.theVec * bDub
			, aMvec.theBiv * bDub
			, aMvec.theTri * bDub
			};

			// [DoxyExampleDub]

		tst::checkGotExp(oss, gotMvecDub, expMvecDub, "MvecDub");

		return oss.str();;
	}

	//! Check product: MultiVector * Scalar
	std::string
	testSca
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSca]
		using namespace engabra::g3;

		MultiVector const gotMvecSca{ aMvec * bSca };
		MultiVector const expMvecSca
			{ aMvec.theSca * bSca
			, aMvec.theVec * bSca
			, aMvec.theBiv * bSca
			, aMvec.theTri * bSca
			};

			// [DoxyExampleSca]

		tst::checkGotExp(oss, gotMvecSca, expMvecSca, "MvecSca");

		return oss.str();;
	}

	//! Check product: MultiVector * Vector
	std::string
	testVec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleVec]
		using namespace engabra::g3;

		MultiVector const gotMvecVec{ aMvec * bVec };
		MultiVector const expMvecVec
			// cast first item to avoid missing op+() for TBD types
			{ MultiVector(aMvec.theSca * bVec)
			+ aMvec.theVec * bVec
			+ aMvec.theBiv * bVec
			+ aMvec.theTri * bVec
			};

			// [DoxyExampleVec]

		tst::checkGotExp(oss, gotMvecVec, expMvecVec, "MvecVec");

		return oss.str();;
	}

	//! Check product: MultiVector * BiVector
	std::string
	testBiv
		()
	{
		std::ostringstream oss;

		// [DoxyExampleBiv]
		using namespace engabra::g3;

		MultiVector const gotMvecBiv{ aMvec * bBiv };
		MultiVector const expMvecBiv
			// cast first item to avoid missing op+() for TBD types
			{ MultiVector(aMvec.theSca * bBiv)
			+ aMvec.theVec * bBiv
			+ aMvec.theBiv * bBiv
			+ aMvec.theTri * bBiv
			};

			// [DoxyExampleBiv]

		tst::checkGotExp(oss, gotMvecBiv, expMvecBiv, "MvecBiv");

		return oss.str();;
	}

	//! Check product: MultiVector * TriVector
	std::string
	testTri
		()
	{
		std::ostringstream oss;

		// [DoxyExampleTri]
		using namespace engabra::g3;

		MultiVector const gotMvecTri{ aMvec * bTri };
		MultiVector const expMvecTri
			// cast first item to avoid missing op+() for TBD types
			{ MultiVector(aMvec.theSca * bTri)
			+ aMvec.theVec * bTri
			+ aMvec.theBiv * bTri
			+ aMvec.theTri * bTri
			};

			// [DoxyExampleTri]

		tst::checkGotExp(oss, gotMvecTri, expMvecTri, "MvecTri");

		return oss.str();;
	}

	//! Check product: MultiVector * Spinor
	std::string
	testSpin
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSpin]
		using namespace engabra::g3;

		MultiVector const gotMvecSpin{ aMvec * bSpin };
		MultiVector const expMvecSpin
			{ aMvec.theSca * bSpin
			+ aMvec.theVec * bSpin
			+ aMvec.theBiv * bSpin
			+ aMvec.theTri * bSpin
			};

			// [DoxyExampleSpin]

		tst::checkGotExp(oss, gotMvecSpin, expMvecSpin, "MvecSpin");

		return oss.str();;
	}

	//! Check product: MultiVector * ImSpin
	std::string
	testImsp
		()
	{
		std::ostringstream oss;

		// [DoxyExampleImsp]
		using namespace engabra::g3;

		MultiVector const gotMvecImsp{ aMvec * bImsp };
		MultiVector const expMvecImsp
			{ aMvec.theSca * bImsp
			+ aMvec.theVec * bImsp
			+ aMvec.theBiv * bImsp
			+ aMvec.theTri * bImsp
			};

			// [DoxyExampleImsp]

		tst::checkGotExp(oss, gotMvecImsp, expMvecImsp, "MvecImsp");

		return oss.str();;
	}

	//! Check product: MultiVector * ComPlex
	std::string
	testCplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleCplx]
		using namespace engabra::g3;

		MultiVector const gotMvecCplx{ aMvec * bCplx };
		MultiVector const expMvecCplx
			// cast first item to avoid missing op+() for TBD types
			{ MultiVector(aMvec.theSca * bCplx)
			+ aMvec.theVec * bCplx
			+ aMvec.theBiv * bCplx
			+ aMvec.theTri * bCplx
			};

			// [DoxyExampleCplx]

		tst::checkGotExp(oss, gotMvecCplx, expMvecCplx, "MvecCplx");

		return oss.str();;
	}

	//! Check product: MultiVector * DirPlex
	std::string
	testDplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDplx]
		using namespace engabra::g3;

		MultiVector const gotMvecDplx{ aMvec * bDplx };
		MultiVector const expMvecDplx
			// cast first item to avoid missing op+() for TBD types
			{ aMvec.theSca * bDplx
			+ aMvec.theVec * bDplx
			+ aMvec.theBiv * bDplx
			+ aMvec.theTri * bDplx
			};

			// [DoxyExampleDplx]

		tst::checkGotExp(oss, gotMvecDplx, expMvecDplx, "MvecDplx");

		return oss.str();;
	}

	//! Check product: MultiVector * MultiVector
	std::string
	testMvec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleMvec]
		using namespace engabra::g3;

		MultiVector const gotMvecMvec{ aMvec * bMvec };
		MultiVector const expMvecMvec
			{ aMvec.theSca * bMvec
			+ aMvec.theVec * bMvec
			+ aMvec.theBiv * bMvec
			+ aMvec.theTri * bMvec
			};

			// [DoxyExampleMvec]

		tst::checkGotExp(oss, gotMvecMvec, expMvecMvec, "MvecMvec");

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

