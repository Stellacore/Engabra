// 
// MIT License
// 
// Copyright (c) 2022 Stellacore Corporation
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
\brief Unit tests (and example) code for engabra g3opsMul_same.hpp
*/


#include "checks.hpp" // testing environment common utilities

#include "g3opsMul_same.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include "g3const.hpp"
#include "g3opsAdd.hpp"
#include "g3opsUni.hpp"

#include <iostream>
#include <sstream>
#include <typeinfo>


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;
	using g3::nearlyEquals;

	// test data
	namespace
	{
		// [DoxyExampleData]
		using namespace engabra::g3;

		// example data values
		Scalar const aSca{ 2. };
		Scalar const bSca{ 3. };
		Vector const aVec{ 5., 7., 11. };
		Vector const bVec{ 13., 17., 19. };
		BiVector const aBiv{ 23., 29., 31. };
		BiVector const bBiv{ 37., 41., 43. };
		TriVector const aTri{ 47. };
		TriVector const bTri{ 53. };

			// [DoxyExampleData]
	}


	//! Examples for documentation
	std::string
	test0
		()
	{
		std::ostringstream oss;

		// [DoxyExample01]
		using namespace engabra::g3;

			// [DoxyExample01]

		return oss.str();;
	}

	//! Check product: Scalar * Scalar
	std::string
	testSca
		()
	{
		std::ostringstream oss;
		using namespace engabra::g3;

		// Scalar const aSca{ 2. };
		// Scalar const bSca{ 3. };

		// [DoxyExampleSca]

		Scalar const gotScaSca{ aSca * bSca };
		Scalar const expScaSca{ (2. * 3.) };

			// [DoxyExampleSca]

		tst::checkGotExp(oss, gotScaSca, expScaSca, "ScaSca");

		return oss.str();;
	}

	//! Check product: Vector * Vector
	std::string
	testVec
		()
	{
		std::ostringstream oss;
		using namespace engabra::g3;

		// [DoxyExampleVecA]

		// check orthogonal basis vector products
		Spinor const got23{ e2 * e3 };
		Spinor const exp23{ 0., e23 };
		Spinor const got31{ e3 * e1 };
		Spinor const exp31{ 0., e31 };
		Spinor const got12{ e1 * e2 };
		Spinor const exp12{ 0., e12 };

		// check aligned basis products
		Spinor const got11{ e1 * e1 };
		Spinor const exp11{ 1., zero<BiVector>() };
		Spinor const got22{ e2 * e2 };
		Spinor const exp22{ 1., zero<BiVector>() };
		Spinor const got33{ e3 * e3 };
		Spinor const exp33{ 1., zero<BiVector>() };

		// check a combination
		Spinor const gotA{ (e1 + e2) * e3 };
		static BiVector const e13{ -e31 }; // orthogonal vectors anti-commute
		Spinor const expA{ 0., e13 + e23 };

			// [DoxyExampleVecA]

		// Vector const aVec{ 5., 7., 11. };
		// Vector const bVec{ 13., 17., 19. };

		// [DoxyExampleVecB]

		// check a general vector
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

			// [DoxyExampleVecB]

		tst::checkGotExp(oss, got23, exp23, "23");
		tst::checkGotExp(oss, got31, exp31, "31");
		tst::checkGotExp(oss, got12, exp12, "12");
		tst::checkGotExp(oss, got11, exp11, "11");
		tst::checkGotExp(oss, got22, exp22, "22");
		tst::checkGotExp(oss, got33, exp33, "33");
		tst::checkGotExp(oss, gotA, expA, "A");
		tst::checkGotExp(oss, gotVecVec, expVecVec, "VecVec");

		return oss.str();;
	}

	//! Check product: BiVector * BiVector
	std::string
	testBiv
		()
	{
		std::ostringstream oss;
		using namespace engabra::g3;

		// BiVector const aBiv{ 23., 29., 31. };
		// BiVector const bBiv{ 37., 41., 43. };

		// [DoxyExampleBiv]

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

	//! Check product: TriVector * TriVector
	std::string
	testTri
		()
	{
		std::ostringstream oss;
		using namespace engabra::g3;

		// TriVector const aTri{ 47. };
		// TriVector const bTri{ 53. };

		// [DoxyExampleTri]

		Scalar const gotTriTri{ aTri * bTri };
		Scalar const expTriTri{ -(47. * 53.) };

			// [DoxyExampleTri]

		tst::checkGotExp(oss, gotTriTri, expTriTri, "TriTri");

		return oss.str();;
	}

	//! Check product: Spinor * Spinor
	std::string
	testSpin
		()
	{
		std::ostringstream oss;
		using namespace engabra::g3;

		// Scalar const aSca{ 2. };
		// Scalar const bSca{ 3. };
		// BiVector const aBiv{ 23., 29., 31. };
		// BiVector const bBiv{ 37., 41., 43. };

		// [DoxyExampleSpin]

		Spinor const aSpin{ aSca, aBiv };
		Spinor const bSpin{ bSca, bBiv };
		Spinor const gotSpinSpin{ aSpin * bSpin };
		Spinor const expSpinSpin
			{ aSca * bSca 
			+ BiVector{ (3.*23.), (3.*29.), (3.*31.) }
			+ BiVector{ (37.*2.), (41.*2.), (43.*2.) }
			+ aBiv * bBiv
			};

			// [DoxyExampleSpin]

		tst::checkGotExp(oss, gotSpinSpin, expSpinSpin, "SpinSpin");

		return oss.str();;
	}

/*
	//! Check product: ImSpin * ImSpin
	std::string
	testImsp
		()
	{
		std::ostringstream oss;

		// [DoxyExampleImsp]
		using namespace engabra::g3;

		ImSpin const aImsp{ aVec, aTri };
		ImSpin const bImsp{ bVec, bTri };
		Spinor const gotImspImsp{ aImsp * bImsp };
		Spinor const expImspImsp
			{ aSca * bSca 
			+ BiVector{ (3.*23.), (3.*29.), (3.*31.) }
			+ BiVector{ (37.*2.), (41.*2.), (43.*2.) }
			+ aBiv * bBiv
			};

			// [DoxyExampleImsp]

		tst::checkGotExp(oss, gotImspImsp, expImspImsp, "ImspImsp");

		return oss.str();;
	}
*/

/*
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
	//! Check product: Type * Type
	std::string
	testQ
		()
	{
		std::ostringstream oss;

		// [DoxyExampleQ]
		using namespace engabra::g3;

		Type const gotQQ{ aQ * bQ };
		Type const expQQ{ 6. };

			// [DoxyExampleQ]

		tst::checkGotExp(oss, gotQQ, expQQ, "QQ");

		return oss.str();;
	}
*/

/*
	// full MV multiply
	g3::MultiVector
	product
		( g3::MultiVector const & mvA
		, g3::MultiVector const & mvB
		)
	{
		// various grade components of full product

		// constituent intermediate blades
		g3::Scalar const sca
			{ mvA.theSca * mvB.theSca
			+ mvA.theTri * mvB.theTri
			};
		g3::Vector const vec
			{ mvA.theSca * mvB.theVec
			+ mvA.theVec * mvB.theSca
			+ mvA.theBiv * mvB.theTri
			+ mvA.theTri * mvB.theBiv
			};
		g3::BiVector const biv
			{ mvA.theSca * mvB.theBiv
			+ mvA.theVec * mvB.theTri
			+ mvA.theBiv * mvB.theSca
			+ mvA.theTri * mvB.theVec
			};
		g3::TriVector const tri
			{ mvA.theSca * mvB.theTri
			+ mvA.theTri * mvB.theSca
			};
		// constituent composite portions
		g3::Spinor const spin
			{ mvA.theVec * mvB.theVec
			+ mvA.theBiv * mvB.theBiv
			};
		g3::ImSpin const imsp
			{ mvA.theVec * mvB.theBiv
			+ mvA.theBiv * mvB.theVec
			};
		// re-gather into full multivector result
		return g3::MultiVector
			{ sca + spin.theSca
			, vec + imsp.theVec
			, biv + spin.theBiv
			, tri + imsp.theTri
			};
	}
*/

}

//! Check behavior of NS
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test0();
	oss << testSca();
	oss << testVec();
	oss << testBiv();
	oss << testTri();
	oss << testSpin();
//	oss << testImsp();
//	oss << testCplx();
//	oss << testDplx();
//	oss << testMvec();

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

