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
\brief Unit tests (and example) code for engabra::g3opsMul_DirPlex
*/


#include "checks.hpp" // testing environment common utilities
#include "test_g3opsMul.hpp" // useful data values: aDub, aSca, ..., aMvec

#include "g3opsMul_DirPlex.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using namespace engabra;
	using g3::nearlyEquals;

	//! Check product: DirPlex * double
	std::string
	testDub
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDub]
		using namespace engabra::g3;

		DirPlex const gotDplxDub{ aDplx * bDub };
		DirPlex const expDplxDub
			{ aDplx.theVec * bDub
			, aDplx.theBiv * bDub
			};

			// [DoxyExampleDub]

		tst::checkGotExp(oss, gotDplxDub, expDplxDub, "DplxDub");

		return oss.str();;
	}

	//! Check product: DirPlex * Scalar
	std::string
	testSca
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSca]
		using namespace engabra::g3;

		DirPlex const gotDplxSca{ aDplx * bSca };
		DirPlex const expDplxSca
			{ aDplx.theVec * bSca
			, aDplx.theBiv * bSca
			};

			// [DoxyExampleSca]

		tst::checkGotExp(oss, gotDplxSca, expDplxSca, "DplxSca");

		return oss.str();;
	}

	//! Check product: DirPlex * Vector
	std::string
	testVec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleVec]
		using namespace engabra::g3;

		MultiVector const gotDplxVec{ aDplx * bVec };
		MultiVector const expDplxVec
			{ aDplx.theVec * bVec
			+ aDplx.theBiv * bVec
			};

			// [DoxyExampleVec]

		tst::checkGotExp(oss, gotDplxVec, expDplxVec, "DplxVec");

		return oss.str();;
	}

	//! Check product: DirPlex * BiVector
	std::string
	testBiv
		()
	{
		std::ostringstream oss;

		// [DoxyExampleBiv]
		using namespace engabra::g3;

		MultiVector const gotDplxBiv{ aDplx * bBiv };
		MultiVector const expDplxBiv
			{ aDplx.theVec * bBiv
			+ aDplx.theBiv * bBiv
			};

			// [DoxyExampleBiv]

		tst::checkGotExp(oss, gotDplxBiv, expDplxBiv, "DplxBiv");

		return oss.str();;
	}

	//! Check product: DirPlex * TriVector
	std::string
	testTri
		()
	{
		std::ostringstream oss;

		// [DoxyExampleTri]
		using namespace engabra::g3;

		DirPlex const gotDplxTri{ aDplx * bTri };
		DirPlex const expDplxTri
			{ aDplx.theVec * bTri
			+ aDplx.theBiv * bTri
			};

			// [DoxyExampleTri]

		tst::checkGotExp(oss, gotDplxTri, expDplxTri, "DplxTri");

		return oss.str();;
	}

	//! Check product: DirPlex * Spinor
	std::string
	testSpin
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSpin]
		using namespace engabra::g3;

		MultiVector const gotDplxSpin{ aDplx * bSpin };
		MultiVector const expDplxSpin
			{ aDplx.theVec * bSpin
			+ aDplx.theBiv * bSpin
			};

			// [DoxyExampleSpin]

		tst::checkGotExp(oss, gotDplxSpin, expDplxSpin, "DplxSpin");

		return oss.str();;
	}

	//! Check product: DirPlex * ImSpin
	std::string
	testImsp
		()
	{
		std::ostringstream oss;

		// [DoxyExampleImsp]
		using namespace engabra::g3;

		MultiVector const gotDplxImsp{ aDplx * bImsp };
		MultiVector const expDplxImsp
			{ aDplx.theVec * bImsp
			+ aDplx.theBiv * bImsp
			};

			// [DoxyExampleImsp]

		tst::checkGotExp(oss, gotDplxImsp, expDplxImsp, "DplxImsp");

		return oss.str();;
	}

	//! Check product: DirPlex * ComPlex
	std::string
	testCplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleCplx]
		using namespace engabra::g3;

		DirPlex const gotDplxCplx{ aDplx * bCplx };
		DirPlex const expDplxCplx
			{ Vector{ aDplx.theVec * bCplx.theSca }
			+ Vector{ aDplx.theBiv * bCplx.theTri }
			, BiVector{ aDplx.theVec * bCplx.theTri }
			+ BiVector{ aDplx.theBiv * bCplx.theSca }
			};

			// [DoxyExampleCplx]

		tst::checkGotExp(oss, gotDplxCplx, expDplxCplx, "DplxCplx");

		return oss.str();;
	}

	//! Check product: DirPlex * DirPlex
	std::string
	testDplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDplx]
		using namespace engabra::g3;

		MultiVector const gotDplxDplx{ aDplx * bDplx };
		MultiVector const expDplxDplx
			{ Spinor{ aDplx.theBiv * bDplx.theBiv }
			+ Spinor{ aDplx.theVec * bDplx.theVec }
			+ ImSpin{ aDplx.theBiv * bDplx.theVec }
			+ ImSpin{ aDplx.theVec * bDplx.theBiv }
			};

			// [DoxyExampleDplx]

		tst::checkGotExp(oss, gotDplxDplx, expDplxDplx, "DplxDplx");

		return oss.str();;
	}

	//! Check product: DirPlex * MultiVector
	std::string
	testMvec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleMvec]
		using namespace engabra::g3;

		MultiVector const gotDplxMvec{ aDplx * bMvec };
		MultiVector const expDplxMvec
			// Add in this order to avoid missing op+() for TBD types
			{ Spinor{ aDplx.theVec * bMvec.theVec }
			+ Spinor{ aDplx.theBiv * bMvec.theBiv }
			+ ImSpin{ aDplx.theBiv * bMvec.theVec }
			+ ImSpin{ aDplx.theVec * bMvec.theBiv }
			+ Vector{ aDplx.theVec * bMvec.theSca }
			+ Vector{ aDplx.theBiv * bMvec.theTri }
			+ BiVector{ aDplx.theBiv * bMvec.theSca }
			+ BiVector{ aDplx.theVec * bMvec.theTri }
			};

			// [DoxyExampleMvec]

		tst::checkGotExp(oss, gotDplxMvec, expDplxMvec, "DplxMvec");

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

