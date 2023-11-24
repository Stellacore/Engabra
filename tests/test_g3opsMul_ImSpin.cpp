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
\brief Unit tests (and example) code for engabra::g3opsMul_ImSpin
*/


#include "checks.hpp" // testing environment common utilities
#include "test_g3opsMul.hpp" // useful data values: aDub, aSca, ..., aMvec

#include "g3opsMul_ImSpin.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using namespace engabra;
	using g3::nearlyEquals;

	//! Check product: ImSpin * double
	std::string
	testDub
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDub]
		using namespace engabra::g3;

		ImSpin const gotImspDub{ aImsp * bDub };
		ImSpin const expImspDub
			{ aImsp.theVec * bDub
			, aImsp.theTri * bDub
			};

			// [DoxyExampleDub]

		tst::checkGotExp(oss, gotImspDub, expImspDub, "ImspDub");

		return oss.str();;
	}

	//! Check product: ImSpin * Scalar
	std::string
	testSca
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSca]
		using namespace engabra::g3;

		ImSpin const gotImspSca{ aImsp * bSca };
		ImSpin const expImspSca
			{ aImsp.theVec * bSca
			, aImsp.theTri * bSca
			};

			// [DoxyExampleSca]

		tst::checkGotExp(oss, gotImspSca, expImspSca, "ImspSca");

		return oss.str();;
	}

	//! Check product: ImSpin * Vector
	std::string
	testVec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleVec]
		using namespace engabra::g3;

		Spinor const gotImspVec{ aImsp * bVec };
		Spinor const expImspVec
			{ aImsp.theVec * bVec
			+ aImsp.theTri * bVec
			};

			// [DoxyExampleVec]

		tst::checkGotExp(oss, gotImspVec, expImspVec, "ImspVec");

		return oss.str();;
	}

	//! Check product: ImSpin * BiVector
	std::string
	testBiv
		()
	{
		std::ostringstream oss;

		// [DoxyExampleBiv]
		using namespace engabra::g3;

		ImSpin const gotImspBiv{ aImsp * bBiv };
		ImSpin const expImspBiv
			{ aImsp.theVec * bBiv
			+ aImsp.theTri * bBiv
			};

			// [DoxyExampleBiv]

		tst::checkGotExp(oss, gotImspBiv, expImspBiv, "ImspBiv");

		return oss.str();;
	}

	//! Check product: ImSpin * TriVector
	std::string
	testTri
		()
	{
		std::ostringstream oss;

		// [DoxyExampleTri]
		using namespace engabra::g3;

		Spinor const gotImspTri{ aImsp * bTri };
		Spinor const expImspTri
			{ aImsp.theVec * bTri
			+ aImsp.theTri * bTri
			};

			// [DoxyExampleTri]

		tst::checkGotExp(oss, gotImspTri, expImspTri, "ImspTri");

		return oss.str();;
	}

	//! Check product: ImSpin * Spinor
	std::string
	testSpin
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSpin]
		using namespace engabra::g3;

		ImSpin const gotImspSpin{ aImsp * bSpin };
		ImSpin const expImspSpin
			{ aImsp.theVec * bSpin.theSca
			+ aImsp.theVec * bSpin.theBiv
			+ aImsp.theTri * bSpin.theSca
			+ aImsp.theTri * bSpin.theBiv
			};

			// [DoxyExampleSpin]

		tst::checkGotExp(oss, gotImspSpin, expImspSpin, "ImspSpin");

		return oss.str();;
	}

	//! Check product: ImSpin * ImSpin
	std::string
	testImsp
		()
	{
		std::ostringstream oss;

		// [DoxyExampleImsp]
		using namespace engabra::g3;

		Spinor const gotImspImsp{ aImsp * bImsp };
		Spinor const expImspImsp
			{ aImsp.theVec * bImsp.theVec
			+ aImsp.theVec * bImsp.theTri
			+ aImsp.theTri * bImsp.theVec
			+ aImsp.theTri * bImsp.theTri
			};

			// [DoxyExampleImsp]

		tst::checkGotExp(oss, gotImspImsp, expImspImsp, "ImspImsp");

		return oss.str();;
	}

	//! Check product: ImSpin * ComPlex
	std::string
	testCplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleCplx]
		using namespace engabra::g3;

		MultiVector const gotImspCplx{ aImsp * bCplx };
		MultiVector const expImspCplx
			{ Scalar{ aImsp.theTri * bCplx.theTri }
			, Vector{ aImsp.theVec * bCplx.theSca }
			, BiVector{ aImsp.theVec * bCplx.theTri }
			, TriVector{ aImsp.theTri * bCplx.theSca }
			};

			// [DoxyExampleCplx]

		tst::checkGotExp(oss, gotImspCplx, expImspCplx, "ImspCplx");

		return oss.str();;
	}

	//! Check product: ImSpin * DirPlex
	std::string
	testDplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDplx]
		using namespace engabra::g3;

		MultiVector const gotImspDplx{ aImsp * bDplx };
		MultiVector const expImspDplx
			// Add in this order to avoid missing op+() for TBD types
			{ Spinor{ aImsp.theVec * bDplx.theVec }
			+ ImSpin{ aImsp.theVec * bDplx.theBiv }
			+ Vector{ aImsp.theTri * bDplx.theBiv }
			+ BiVector{ aImsp.theTri * bDplx.theVec }
			};

			// [DoxyExampleDplx]

		tst::checkGotExp(oss, gotImspDplx, expImspDplx, "ImspDplx");

		return oss.str();;
	}

	//! Check product: ImSpin * MultiVector
	std::string
	testMvec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleMvec]
		using namespace engabra::g3;

		MultiVector const gotImspMvec{ aImsp * bMvec };
		MultiVector const expImspMvec
			// Add in this order to avoid missing op+() for TBD types
			{ Spinor{ aImsp.theVec * bMvec.theVec }
			+ ImSpin{ aImsp.theVec * bMvec.theBiv }
			+ Scalar{ aImsp.theTri * bMvec.theTri }
			+ Vector{ aImsp.theVec * bMvec.theSca }
			+ Vector{ aImsp.theTri * bMvec.theBiv }
			+ BiVector{ aImsp.theVec * bMvec.theTri }
			+ BiVector{ aImsp.theTri * bMvec.theVec }
			+ TriVector{ aImsp.theTri * bMvec.theSca }
			};

			// [DoxyExampleMvec]

		tst::checkGotExp(oss, gotImspMvec, expImspMvec, "ImspMvec");

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

