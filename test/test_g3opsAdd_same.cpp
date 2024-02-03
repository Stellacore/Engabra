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
\brief Unit tests (and example) code for engabra::opsAdd_same
*/


#include "checks.hpp" // testing environment common utilities

#include "g3opsAdd_same.hpp"

#include "engabra.hpp"
#include "g3validity.hpp"

// For test message output
#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using namespace engabra;
	using g3::nearlyEquals;

	//! Run tests to compare addition
	template <typename Type>
	inline
	void
	checkAdd
		( std::ostream & ostrm
		, Type const & itemA
		, Type const & itemB
		, Type const & expSum
		, std::string const & title
		, double const & tol = std::numeric_limits<double>::epsilon()
		)
	{
		// test addition with null as each argument
		// check that result should NOT be valid
		static Type const null{ g3::null<Type>() };
		Type const gotANull{ itemA + null };
		if ( isValid(gotANull))
		{
			ostrm << "Failure of (itemA+null): " << title << "test\n";
		}
		Type const gotNullB{ null + itemB };
		if ( isValid(gotNullB))
		{
			ostrm << "Failure of (null+itemB): " << title << "test\n";
		}

		// check standard use case
		Type const gotSum{ itemA + itemB };
		tst::checkGotExp(ostrm, gotSum, expSum, title+".sum", tol);
	}

	//! Check operations on basis blades
	std::string
	test0
		()
	{
		std::ostringstream oss;

		using namespace g3;

		Scalar const aSca{ 11.00 };
		Vector const aVec{ 21.00, 22.00, 23.00 };
		BiVector const aBiv{ 31.00, 32.00, 33.00 };
		TriVector const aTri{ 41.00 };
		Spinor const aSpin{ aSca, aBiv };
		ImSpin const aImsp{ aVec, aTri };
		ComPlex const aCplx{ aSca, aTri };
		DirPlex const aDplx{ aVec, aBiv };
		MultiVector const aMvec{ aSca, aVec, aBiv, aTri };

		Scalar const bSca{ .11 };
		Vector const bVec{ .21, .22, .23 };
		BiVector const bBiv{ .31, .32, .33 };
		TriVector const bTri{ .41 };
		Spinor const bSpin{ bSca, bBiv };
		ImSpin const bImsp{ bVec, bTri };
		ComPlex const bCplx{ bSca, bTri };
		DirPlex const bDplx{ bVec, bBiv };
		MultiVector const bMvec{ bSca, bVec, bBiv, bTri };

		Scalar const expSca{ 11.11 };
		Vector const expVec{ 21.21, 22.22, 23.23 };
		BiVector const expBiv{ 31.31, 32.32, 33.33 };
		TriVector const expTri{ 41.41 };
		Spinor const expSpin{ expSca, expBiv };
		ImSpin const expImsp{ expVec, expTri };
		ComPlex const expCplx{ expSca, expTri };
		DirPlex const expDplx{ expVec, expBiv };
		MultiVector const expMvec{ expSca, expVec, expBiv, expTri };

		// [DoxyExample01]

		// Addition of like grade elements

		Scalar const abScaSca{ aSca + bSca };
		Vector const abVecVec{ aVec + bVec };
		BiVector const abBivBiv{ aBiv + bBiv };
		TriVector const abTriTri{ aTri + bTri };
		Spinor const abSpinSpin{ aSpin + bSpin };
		ImSpin const abImspImsp{ aImsp + bImsp };
		ComPlex const abCplxCplx{ aCplx + bCplx };
		DirPlex const abDplxDplx{ aDplx + bDplx };
		MultiVector const abMvecMvec{ aMvec + bMvec };

		// Note: Addition operations are commutative
		//       (also true for addition in general - including for all
		//       mixed type additions as in test_g3opsAdd_other.cpp)
		Scalar const baScaSca{ bSca + aSca };
		Vector const baVecVec{ bVec + aVec };
		BiVector const baBivBiv{ bBiv + aBiv };
		TriVector const baTriTri{ bTri + aTri };
		Spinor const baSpinSpin{ bSpin + aSpin };
		ImSpin const baImspImsp{ bImsp + aImsp };
		ComPlex const baCplxCplx{ bCplx + aCplx };
		DirPlex const baDplxDplx{ bDplx + aDplx };
		MultiVector const baMvecMvec{ bMvec + aMvec };

			// [DoxyExample01]

		tst::checkGotExp(oss, abScaSca, baScaSca, "(ab)ScaSca");
		tst::checkGotExp(oss, abVecVec, baVecVec, "(ab)VecVec");
		tst::checkGotExp(oss, abBivBiv, baBivBiv, "(ab)BivBiv");
		tst::checkGotExp(oss, abTriTri, baTriTri, "(ab)TriTri");
		tst::checkGotExp(oss, abSpinSpin, baSpinSpin, "(ab)SpinSpin");
		tst::checkGotExp(oss, abImspImsp, baImspImsp, "(ab)ImspImsp");
		tst::checkGotExp(oss, abCplxCplx, baCplxCplx, "(ab)CplxCplx");
		tst::checkGotExp(oss, abDplxDplx, baDplxDplx, "(ab)DplxDplx");
		tst::checkGotExp(oss, abMvecMvec, baMvecMvec, "(ab)MvecMvec");

		checkAdd(oss, aSca, bSca, expSca, "abSca");
		checkAdd(oss, aVec, bVec, expVec, "abVec");
		checkAdd(oss, aBiv, bBiv, expBiv, "abBiv");
		checkAdd(oss, aTri, bTri, expTri, "abTri");
		checkAdd(oss, aSpin, bSpin, expSpin, "abSpin");
		checkAdd(oss, aImsp, bImsp, expImsp, "abImsp");
		checkAdd(oss, aCplx, bCplx, expCplx, "abCplx");
		checkAdd(oss, aDplx, bDplx, expDplx, "abDplx");
		checkAdd(oss, aMvec, bMvec, expMvec, "abMvec");

		return oss.str();
	}
}

//! Check behavior of NS
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test0();
//	oss << test1();

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

