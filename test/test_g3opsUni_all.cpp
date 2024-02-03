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
\brief Unit tests (and example) code for engabra::NS
*/


#include "checks.hpp" // testing environment common utilities

#include "engabra.hpp"

// For test message output
#include <iostream>
#include <sstream>


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;
	using namespace g3;

	// convenient values for testing
	static Scalar const posSca{  0.1 };
	static Vector const posVec{  1.1,  1.2,  1.3 };
	static BiVector const posBiv{  2.1,  2.2,  2.3 };
	static TriVector const posTri{  3.1 };
	static Spinor const posSpinor{ posSca, posBiv };
	static ImSpin const posImSpin{ posVec, posTri };
	static ComPlex const posComPlex{ posSca, posTri };
	static DirPlex const posDirPlex{ posVec, posBiv };
	static MultiVector const posMultiVector{ posSca, posVec, posBiv, posTri };

	static Scalar const negSca{ -0.1 };
	static Vector const negVec{ -1.1, -1.2, -1.3 };
	static BiVector const negBiv{ -2.1, -2.2, -2.3 };
	static TriVector const negTri{ -3.1 };

	// naming more clear for involution operator context
	static Scalar const & aFwdScalar = posSca;
	static Vector const & aFwdVector = posVec;
	static BiVector const & aFwdBiVector = posBiv;
	static TriVector const & aFwdTriVector = posTri;
	static Spinor const & aFwdSpinor = posSpinor;
	static ImSpin const & aFwdImSpin = posImSpin;
	static ComPlex const & aFwdComPlex = posComPlex;
	static DirPlex const & aFwdDirPlex = posDirPlex;
	static MultiVector const & aFwdMultiVector = posMultiVector;


	//! Check uniary negation
	std::string
	test1
		()
	{
		std::ostringstream oss;

		// expected results by construction
		Scalar const expSca{ negSca };
		Vector const expVec{ negVec };
		BiVector const expBiv{ negBiv };
		TriVector const expTri{ negTri };
		Spinor const expSpinor{ negSca, negBiv };
		ImSpin const expImSpin{ negVec, negTri };
		ComPlex const expComPlex{ negSca, negTri };
		DirPlex const expDirPlex{ negVec, negBiv };
		MultiVector const expMultiVector{ negSca, negVec, negBiv, negTri };

		// observed results from function
		Scalar const gotSca{ -posSca };
		Vector const gotVec{ -posVec };
		BiVector const gotBiv{ -posBiv };
		TriVector const gotTri{ -posTri };
		Spinor const gotSpinor{ -posSpinor };
		ImSpin const gotImSpin{ -posImSpin };
		ComPlex const gotComPlex{ -posComPlex };
		DirPlex const gotDirPlex{ -posDirPlex };
		MultiVector const gotMultiVector{ -posMultiVector };

		tst::checkGotExp(oss, gotSca, expSca, "negate Sca");
		tst::checkGotExp(oss, gotVec, expVec, "negate Vec");
		tst::checkGotExp(oss, gotBiv, expBiv, "negate Biv");
		tst::checkGotExp(oss, gotTri, expTri, "negate Tri");
		tst::checkGotExp(oss, gotSpinor, expSpinor, "negate Spinor");
		tst::checkGotExp(oss, gotImSpin, expImSpin, "negate ImSpin");
		tst::checkGotExp(oss, gotComPlex, expComPlex, "negate ComPlex");
		tst::checkGotExp(oss, gotDirPlex, expDirPlex, "negate DirPlex");
		tst::checkGotExp
			(oss, gotMultiVector, expMultiVector, "negate MultiVector");

		return oss.str();;
	}

	//! Check dual() operations
	std::string
	test2
		()
	{
		std::ostringstream oss;

		using namespace g3;

		Scalar const gotScaFromTri{ dual(posTri) };
		Vector const gotVecFromBiv{ dual(posBiv) };
		BiVector const gotBivFromVec{ dual(posVec) };
		TriVector const gotTriFromSca{ dual(posSca) };
		Spinor const gotSpiFromIms{ dual(posImSpin) };
		ImSpin const gotImsFromSpi{ dual(posSpinor) };
		ComPlex const gotComFromCom{ dual(posComPlex) };
		DirPlex const gotDirFromDir{ dual(posDirPlex) };
		MultiVector const gotMulFromMul{ dual(posMultiVector) };

		Scalar const expScaFromTri{ -posTri[0] };
		Vector const expVecFromBiv{ -posBiv[0], -posBiv[1], -posBiv[2] };
		BiVector const expBivFromVec{  posVec[0],  posVec[1],  posVec[2] };
		TriVector const expTriFromSca{  posSca[0] };
		Spinor const expSpiFromIms{ expScaFromTri, expBivFromVec };
		ImSpin const expImsFromSpi{ expVecFromBiv, expTriFromSca };
		ComPlex const expComFromCom{ expScaFromTri, expTriFromSca };
		DirPlex const expDirFromDir{ expVecFromBiv, expBivFromVec };
		MultiVector const expMulFromMul
			{ expScaFromTri, expVecFromBiv, expBivFromVec, expTriFromSca };

		tst::checkGotExp(oss, gotScaFromTri, expScaFromTri, "dual ScaFromTri");
		tst::checkGotExp(oss, gotVecFromBiv, expVecFromBiv, "dual VecFromBiv");
		tst::checkGotExp(oss, gotBivFromVec, expBivFromVec, "dual BivFromVec");
		tst::checkGotExp(oss, gotTriFromSca, expTriFromSca, "dual TriFromSca");
		tst::checkGotExp(oss, gotSpiFromIms, expSpiFromIms, "dual SpiFromIms");
		tst::checkGotExp(oss, gotImsFromSpi, expImsFromSpi, "dual ImsFromSpi");
		tst::checkGotExp(oss, gotComFromCom, expComFromCom, "dual ComFromCom");
		tst::checkGotExp(oss, gotDirFromDir, expDirFromDir, "dual DirFromDir");
		tst::checkGotExp(oss, gotMulFromMul, expMulFromMul, "dual MulFromMul");

		return oss.str();;
	}

	//! Check basic overall involution patterns (and provide doxy example)
	std::string
	test3
		()
	{
		std::ostringstream oss;

		Scalar const & aSca = posSca;
		Vector const & aVec = posVec;
		BiVector const & aBiv = posBiv;
		TriVector const & aTri = posTri;

		// illustrate basic involution operators
		// [DoxyExample03]

		MultiVector const expPos{  aSca,  aVec,  aBiv,  aTri }; // operator-()
		MultiVector const expNeg{ -aSca, -aVec, -aBiv, -aTri }; // operator-()
		MultiVector const expRev{  aSca,  aVec, -aBiv, -aTri }; // reverse()
		MultiVector const expOdd{  aSca, -aVec,  aBiv, -aTri }; // oddverse()
		MultiVector const expDir{  aSca, -aVec, -aBiv,  aTri }; // dirverse()

			// [DoxyExample03]

		tst::checkGotExp(oss, -expPos, expNeg, "mv operator-");
		tst::checkGotExp(oss, reverse(expPos), expRev, "mv reverse()");
		tst::checkGotExp(oss, oddverse(expPos), expOdd, "mv oddverse()");
		tst::checkGotExp(oss, dirverse(expPos), expDir, "mv dirverse()");

		return oss.str();
	}

	//! Check revision operations - associated with product order reversal
	std::string
	test3rev
		()
	{
		std::ostringstream oss;

		// check simple reversion operations
		// [DoxyExample01rev]

		// get values returned by reverse() operation
		Scalar const gotRevScalar{ reverse(aFwdScalar) };
		Vector const gotRevVector{ reverse(aFwdVector) };
		BiVector const gotRevBiVector{ reverse(aFwdBiVector) };
		TriVector const gotRevTriVector{ reverse(aFwdTriVector) };
		Spinor const gotRevSpinor{ reverse(aFwdSpinor) };
		ImSpin const gotRevImSpin{ reverse(aFwdImSpin) };
		ComPlex const gotRevComPlex{ reverse(aFwdComPlex) };
		DirPlex const gotRevDirPlex{ reverse(aFwdDirPlex) };
		MultiVector const gotRevMultiVector{ reverse(aFwdMultiVector) };

		// corresponding expected values
		// Note use of unitary op-() on several items
		using g3::operator-;
		Scalar const expRevScalar{  aFwdScalar };
		Vector const expRevVector{  aFwdVector };
		BiVector const expRevBiVector{ -aFwdBiVector };
		TriVector const expRevTriVector{ -aFwdTriVector };
		Spinor const expRevSpinor{  aFwdScalar, -aFwdBiVector };
		ImSpin const expRevImSpin{  aFwdVector, -aFwdTriVector };
		ComPlex const expRevComPlex{  aFwdScalar, -aFwdTriVector };
		DirPlex const expRevDirPlex{  aFwdVector, -aFwdBiVector };
		MultiVector const expRevMultiVector
			{  aFwdScalar,  aFwdVector, -aFwdBiVector, -aFwdTriVector };

		// [DoxyExample01rev]

		bool const okayS{ nearlyEquals(gotRevScalar, expRevScalar) };
		bool const okayV{ nearlyEquals(gotRevVector, expRevVector) };
		bool const okayB{ nearlyEquals(gotRevBiVector, expRevBiVector) };
		bool const okayT{ nearlyEquals(gotRevTriVector, expRevTriVector) };
		bool const okaySpin{ nearlyEquals(gotRevSpinor, expRevSpinor) };
		bool const okayImSp{ nearlyEquals(gotRevImSpin, expRevImSpin) };
		bool const okayComP{ nearlyEquals(gotRevComPlex, expRevComPlex) };
		bool const okayDirP{ nearlyEquals(gotRevDirPlex, expRevDirPlex) };
		bool const okayMult
			{ nearlyEquals(gotRevMultiVector, expRevMultiVector) };

		if (!
			(  okayS && okayV && okayB && okayT
			&& okaySpin && okayImSp
			&& okayComP && okayDirP
			&& okayMult
			))
		{
			oss << "Failure of reverse test\n";
			oss << " okayS: " << std::boolalpha << okayS << '\n';
			oss << " okayV: " << std::boolalpha << okayV << '\n';
			oss << " okayB: " << std::boolalpha << okayB << '\n';
			oss << " okayT: " << std::boolalpha << okayT << '\n';
			oss << "okaySpin: " << std::boolalpha << okaySpin << '\n';
			oss << "okayImSp: " << std::boolalpha << okayImSp << '\n';
			oss << "okayComP: " << std::boolalpha << okayComP << '\n';
			oss << "okayDirP: " << std::boolalpha << okayDirP << '\n';
			oss << "okayMult: " << std::boolalpha << okayMult << '\n';
		}

		return oss.str();
	}

	//! Check oddverse operations (negation of basis vectors)
	std::string
	test3odd
		()
	{
		std::ostringstream oss;

		// check simple reversion operations
		// [DoxyExample01odd]

		// get values returned by oddverse() operation
		Scalar const gotRevScalar{ oddverse(aFwdScalar) };
		Vector const gotRevVector{ oddverse(aFwdVector) };
		BiVector const gotRevBiVector{ oddverse(aFwdBiVector) };
		TriVector const gotRevTriVector{ oddverse(aFwdTriVector) };
		Spinor const gotRevSpinor{ oddverse(aFwdSpinor) };
		ImSpin const gotRevImSpin{ oddverse(aFwdImSpin) };
		ComPlex const gotRevComPlex{ oddverse(aFwdComPlex) };
		DirPlex const gotRevDirPlex{ oddverse(aFwdDirPlex) };
		MultiVector const gotRevMultiVector{ oddverse(aFwdMultiVector) };

		// corresponding expected values
		// Note use of unitary op-() on several items
		using g3::operator-;
		Scalar const expRevScalar{  aFwdScalar };
		Vector const expRevVector{ -aFwdVector };
		BiVector const expRevBiVector{  aFwdBiVector };
		TriVector const expRevTriVector{ -aFwdTriVector };
		Spinor const expRevSpinor{  aFwdScalar,  aFwdBiVector };
		ImSpin const expRevImSpin{ -aFwdVector, -aFwdTriVector };
		ComPlex const expRevComPlex{  aFwdScalar, -aFwdTriVector };
		DirPlex const expRevDirPlex{ -aFwdVector,  aFwdBiVector };
		MultiVector const expRevMultiVector
			{  aFwdScalar, -aFwdVector,  aFwdBiVector, -aFwdTriVector };

		// [DoxyExample01odd]

		bool const okayS{ nearlyEquals(gotRevScalar, expRevScalar) };
		bool const okayV{ nearlyEquals(gotRevVector, expRevVector) };
		bool const okayB{ nearlyEquals(gotRevBiVector, expRevBiVector) };
		bool const okayT{ nearlyEquals(gotRevTriVector, expRevTriVector) };
		bool const okaySpin{ nearlyEquals(gotRevSpinor, expRevSpinor) };
		bool const okayImSp{ nearlyEquals(gotRevImSpin, expRevImSpin) };
		bool const okayComP{ nearlyEquals(gotRevComPlex, expRevComPlex) };
		bool const okayDirP{ nearlyEquals(gotRevDirPlex, expRevDirPlex) };
		bool const okayMult
			{ nearlyEquals(gotRevMultiVector, expRevMultiVector) };

		if (!
			(  okayS && okayV && okayB && okayT
			&& okaySpin && okayImSp
			&& okayComP && okayDirP
			&& okayMult
			))
		{
			oss << "Failure of oddverse test\n";
			oss << " okayS: " << std::boolalpha << okayS << '\n';
			oss << " okayV: " << std::boolalpha << okayV << '\n';
			oss << " okayB: " << std::boolalpha << okayB << '\n';
			oss << " okayT: " << std::boolalpha << okayT << '\n';
			oss << "okaySpin: " << std::boolalpha << okaySpin << '\n';
			oss << "okayImSp: " << std::boolalpha << okayImSp << '\n';
			oss << "okayComP: " << std::boolalpha << okayComP << '\n';
			oss << "okayDirP: " << std::boolalpha << okayDirP << '\n';
			oss << "okayMult: " << std::boolalpha << okayMult << '\n';
		}

		return oss.str();
	}

	//! Check dirverse operations (negation of spatially directed grades)
	std::string
	test3dir
		()
	{
		std::ostringstream oss;

		// check simple reversion operations
		// [DoxyExample01dir]

		// get values returned by dirverse() operation
		Scalar const gotRevScalar{ dirverse(aFwdScalar) };
		Vector const gotRevVector{ dirverse(aFwdVector) };
		BiVector const gotRevBiVector{ dirverse(aFwdBiVector) };
		TriVector const gotRevTriVector{ dirverse(aFwdTriVector) };
		Spinor const gotRevSpinor{ dirverse(aFwdSpinor) };
		ImSpin const gotRevImSpin{ dirverse(aFwdImSpin) };
		ComPlex const gotRevComPlex{ dirverse(aFwdComPlex) };
		DirPlex const gotRevDirPlex{ dirverse(aFwdDirPlex) };
		MultiVector const gotRevMultiVector{ dirverse(aFwdMultiVector) };

		// corresponding expected values
		// Note use of unitary op-() on several items
		using g3::operator-;
		Scalar const expRevScalar{  aFwdScalar };
		Vector const expRevVector{ -aFwdVector };
		BiVector const expRevBiVector{ -aFwdBiVector };
		TriVector const expRevTriVector{  aFwdTriVector };
		Spinor const expRevSpinor{  aFwdScalar, -aFwdBiVector };
		ImSpin const expRevImSpin{ -aFwdVector,  aFwdTriVector };
		ComPlex const expRevComPlex{  aFwdScalar,  aFwdTriVector };
		DirPlex const expRevDirPlex{ -aFwdVector, -aFwdBiVector };
		MultiVector const expRevMultiVector
			{  aFwdScalar, -aFwdVector, -aFwdBiVector,  aFwdTriVector };

		// [DoxyExample01dir]

		bool const okayS{ nearlyEquals(gotRevScalar, expRevScalar) };
		bool const okayV{ nearlyEquals(gotRevVector, expRevVector) };
		bool const okayB{ nearlyEquals(gotRevBiVector, expRevBiVector) };
		bool const okayT{ nearlyEquals(gotRevTriVector, expRevTriVector) };
		bool const okaySpin{ nearlyEquals(gotRevSpinor, expRevSpinor) };
		bool const okayImSp{ nearlyEquals(gotRevImSpin, expRevImSpin) };
		bool const okayComP{ nearlyEquals(gotRevComPlex, expRevComPlex) };
		bool const okayDirP{ nearlyEquals(gotRevDirPlex, expRevDirPlex) };
		bool const okayMult
			{ nearlyEquals(gotRevMultiVector, expRevMultiVector) };

		if (!
			(  okayS && okayV && okayB && okayT
			&& okaySpin && okayImSp
			&& okayComP && okayDirP
			&& okayMult
			))
		{
			oss << "Failure of dirverse test\n";
			oss << " okayS: " << std::boolalpha << okayS << '\n';
			oss << " okayV: " << std::boolalpha << okayV << '\n';
			oss << " okayB: " << std::boolalpha << okayB << '\n';
			oss << " okayT: " << std::boolalpha << okayT << '\n';
			oss << "okaySpin: " << std::boolalpha << okaySpin << '\n';
			oss << "okayImSp: " << std::boolalpha << okayImSp << '\n';
			oss << "okayComP: " << std::boolalpha << okayComP << '\n';
			oss << "okayDirP: " << std::boolalpha << okayDirP << '\n';
			oss << "okayMult: " << std::boolalpha << okayMult << '\n';
		}

		return oss.str();
	}

	//! Check involution function composition properties
	std::string
	test4a
		()
	{
		std::ostringstream oss;

		MultiVector const & aMV = posMultiVector;

		// check cyclic composition permutations
		if (! nearlyEquals( reverse(aMV), oddverse(dirverse(aMV)) ))
		{
			oss << "Failure of rev=ori(dir) test\n";
		}
		if (! nearlyEquals( oddverse(aMV), dirverse(reverse(aMV)) ))
		{
			oss << "Failure of ori=dir(rev) test\n";
		}
		if (! nearlyEquals( dirverse(aMV), reverse(oddverse(aMV)) ))
		{
			oss << "Failure of dir=rev(ori) test\n";
		}

		return oss.str();;
	}

	//! Check involution function commutativity
	std::string
	test4b
		()
	{
		std::ostringstream oss;

		using namespace g3;

		MultiVector const & aMV = posMultiVector;

		// check op==()
		if (! (aMV == aMV))
		{
			oss << "Failure of op==() test\n";
		}

		// negation and next three
		if(! (-(reverse(aMV)) == reverse(-aMV)))
		{
			oss << "Failure of op commutativity test for {-,rev}\n";
		}
		if(! (-(oddverse(aMV)) == oddverse(-aMV)))
		{
			oss << "Failure of op commutativity test for {-,odd}\n";
		}
		if(! (-(dirverse(aMV)) == dirverse(-aMV)))
		{
			oss << "Failure of op commutativity test for {-,dir}\n";
		}

		// reverse and next two
		if(! (reverse(oddverse(aMV)) == oddverse(reverse(aMV))))
		{
			oss << "Failure of op commutativity test for {rev,odd}\n";
		}
		if(! (reverse(dirverse(aMV)) == dirverse(reverse(aMV))))
		{
			oss << "Failure of op commutativity test for {dir,rev}\n";
		}

		// oddverse and remaining one
		if(! (oddverse(dirverse(aMV)) == oddverse(dirverse(aMV))))
		{
			oss << "Failure of op commutativity test for {odd,dir}\n";
		}

		return oss.str();;
	}
}

//! Check behavior of NS
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test1();
	oss << test2();
	oss << test3();
	oss << test3rev();
	oss << test3odd();
	oss << test3dir();
	oss << test4a();
	oss << test4b();

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
