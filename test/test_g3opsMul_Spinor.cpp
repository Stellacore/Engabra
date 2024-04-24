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
\brief Unit tests (and example) code for engabra::g3opsMul_Spinor
*/


#include "checks.hpp" // testing environment common utilities
#include "test_g3opsMul.hpp" // useful data values: aDub, aSca, ..., aMvec

#include "g3opsMul_Spinor.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using namespace engabra;
	using g3::nearlyEquals;

	//! Check product: Spinor * double
	std::string
	testDub
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDub]
		using namespace engabra::g3;

		Spinor const gotSpinDub{ aSpin * bDub };
		Spinor const expSpinDub
			{ aSpin.theSca * bDub
			, aSpin.theBiv * bDub
			};

			// [DoxyExampleDub]

		tst::checkGotExp(oss, gotSpinDub, expSpinDub, "SpinDub");

		return oss.str();;
	}

	//! Check product: Spinor * Scalar
	std::string
	testSca
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSca]
		using namespace engabra::g3;

		Spinor const gotSpinSca{ aSpin * bSca };
		Spinor const expSpinSca
			{ aSpin.theSca * bSca
			, aSpin.theBiv * bSca
			};

			// [DoxyExampleSca]

		tst::checkGotExp(oss, gotSpinSca, expSpinSca, "SpinSca");

		return oss.str();;
	}

	//! Check product: Spinor * Vector
	std::string
	testVec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleVec]
		using namespace engabra::g3;

		ImSpin const gotSpinVec{ aSpin * bVec };
		ImSpin const expSpinVec
			{ aSpin.theSca * bVec
			+ aSpin.theBiv * bVec
			};

			// [DoxyExampleVec]

		tst::checkGotExp(oss, gotSpinVec, expSpinVec, "SpinVec");

		return oss.str();;
	}

	//! Check product: Spinor * BiVector
	std::string
	testBiv
		()
	{
		std::ostringstream oss;

		// [DoxyExampleBiv]
		using namespace engabra::g3;

		Spinor const gotSpinBiv{ aSpin * bBiv };
		Spinor const expSpinBiv
			{ aSpin.theSca * bBiv
			+ aSpin.theBiv * bBiv
			};

			// [DoxyExampleBiv]

		tst::checkGotExp(oss, gotSpinBiv, expSpinBiv, "SpinBiv");

		return oss.str();;
	}

	//! Check product: Spinor * TriVector
	std::string
	testTri
		()
	{
		std::ostringstream oss;

		// [DoxyExampleTri]
		using namespace engabra::g3;

		ImSpin const gotSpinTri{ aSpin * bTri };
		ImSpin const expSpinTri
			{ aSpin.theSca * bTri
			+ aSpin.theBiv * bTri
			};

			// [DoxyExampleTri]

		tst::checkGotExp(oss, gotSpinTri, expSpinTri, "SpinTri");

		return oss.str();;
	}

	//! Check product: Spinor * Spinor
	std::string
	testSpin
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSpin]
		using namespace engabra::g3;

		Spinor const gotSpinSpin{ aSpin * bSpin };
		Spinor const expSpinSpin
			{ aSpin.theSca * bSpin.theSca
			+ aSpin.theSca * bSpin.theBiv
			+ aSpin.theBiv * bSpin.theSca
			+ aSpin.theBiv * bSpin.theBiv
			};

			// [DoxyExampleSpin]

		tst::checkGotExp(oss, gotSpinSpin, expSpinSpin, "SpinSpin");

		return oss.str();;
	}

	//! Check product: Spinor * ImSpin
	std::string
	testImsp
		()
	{
		std::ostringstream oss;

		// [DoxyExampleImsp]
		using namespace engabra::g3;

		ImSpin const gotSpinImsp{ aSpin * bImsp };
		ImSpin const expSpinImsp
			{ aSpin.theSca * bImsp.theVec
			+ aSpin.theSca * bImsp.theTri
			+ aSpin.theBiv * bImsp.theVec
			+ aSpin.theBiv * bImsp.theTri
			};

			// [DoxyExampleImsp]

		tst::checkGotExp(oss, gotSpinImsp, expSpinImsp, "SpinImsp");

		return oss.str();;
	}

	//! Check product: Spinor * ComPlex
	std::string
	testCplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleCplx]
		using namespace engabra::g3;

		MultiVector const gotSpinCplx{ aSpin * bCplx };
		MultiVector const expSpinCplx
			{ Scalar{ aSpin.theSca * bCplx.theSca }
			, Vector{ aSpin.theBiv * bCplx.theTri }
			, BiVector{ aSpin.theBiv * bCplx.theSca }
			, TriVector{ aSpin.theSca * bCplx.theTri }
			};

			// [DoxyExampleCplx]

		tst::checkGotExp(oss, gotSpinCplx, expSpinCplx, "SpinCplx");

		return oss.str();;
	}

	//! Check product: Spinor * DirPlex
	std::string
	testDplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDplx]
		using namespace engabra::g3;

		MultiVector const gotSpinDplx{ aSpin * bDplx };
		MultiVector const expSpinDplx
			// Add in this order to avoid missing op+() for TBD types
			{ Spinor{ aSpin.theBiv * bDplx.theBiv }
			+ ImSpin{ aSpin.theBiv * bDplx.theVec }
			+ Vector{ aSpin.theSca * bDplx.theVec }
			+ BiVector{ aSpin.theSca * bDplx.theBiv }
			};

			// [DoxyExampleDplx]

		tst::checkGotExp(oss, gotSpinDplx, expSpinDplx, "SpinDplx");

		return oss.str();;
	}

	//! Check product: Spinor * MultiVector
	std::string
	testMvec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleMvec]
		using namespace engabra::g3;

		MultiVector const gotSpinMvec{ aSpin * bMvec };
		MultiVector const expSpinMvec
			// Add in this order to avoid missing op+() for TBD types
			{ Spinor{ aSpin.theBiv * bMvec.theBiv }
			+ ImSpin{ aSpin.theBiv * bMvec.theVec }
			+ Scalar{ aSpin.theSca * bMvec.theSca }
			+ Vector{ aSpin.theSca * bMvec.theVec }
			+ Vector{ aSpin.theBiv * bMvec.theTri }
			+ BiVector{ aSpin.theSca * bMvec.theBiv }
			+ BiVector{ aSpin.theBiv * bMvec.theSca }
			+ TriVector{ aSpin.theSca * bMvec.theTri }
			};

			// [DoxyExampleMvec]

		tst::checkGotExp(oss, gotSpinMvec, expSpinMvec, "SpinMvec");

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

