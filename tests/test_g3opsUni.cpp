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


#include "test_common.hpp" // testing environment common utilities

#include "engabra.hpp"

// For test message output
#include <iostream>
#include <sstream>


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;

	//! Check unitary negation and revision
	std::string
	test1
		()
	{
		std::ostringstream oss;

		// check simple reversion operations
		// [DoxyExample01]

		// arbitrary data values for testing
		g3::Scalar const aFwdScalar{ 900. };
		g3::Vector const aFwdVector{ 901.0, 902.0, 903.0 };
		g3::BiVector const aFwdBiVector{ 902.0, 902.1, 902.2 };
		g3::TriVector const aFwdTriVector{ 903.0 };
		g3::Spinor const aFwdSpinor{ aFwdScalar, aFwdBiVector };
		g3::ImSpin const aFwdImSpin{ aFwdVector, aFwdTriVector };

		// get values returned by reverse() operation
		g3::Scalar const gotRevScalar{ g3::reverse(aFwdScalar) };
		g3::Vector const gotRevVector{ g3::reverse(aFwdVector) };
		g3::BiVector const gotRevBiVector{ g3::reverse(aFwdBiVector) };
		g3::TriVector const gotRevTriVector{ g3::reverse(aFwdTriVector) };
		g3::Spinor const gotRevSpinor{ g3::reverse(aFwdSpinor) };
		g3::ImSpin const gotRevImSpin{ g3::reverse(aFwdImSpin) };

		// corresponding expected values
		// Note use of unitary op-() on several items
		using g3::operator-;
		g3::Scalar const expRevScalar{  aFwdScalar };
		g3::Vector const expRevVector{  aFwdVector };
		g3::BiVector const expRevBiVector{ -aFwdBiVector };
		g3::TriVector const expRevTriVector{ -aFwdTriVector };
		g3::Spinor const expRevSpinor{  aFwdScalar, -aFwdBiVector };
		g3::ImSpin const expRevImSpin{  aFwdVector, -aFwdTriVector };

		// [DoxyExample01]

		bool const okayS{ g3::nearlyEquals(gotRevScalar, expRevScalar) };
		bool const okayV{ g3::nearlyEquals(gotRevVector, expRevVector) };
		bool const okayB{ g3::nearlyEquals(gotRevBiVector, expRevBiVector) };
		bool const okayT{ g3::nearlyEquals(gotRevTriVector, expRevTriVector) };
		bool const okaySB{ g3::nearlyEquals(gotRevSpinor, expRevSpinor) };
		bool const okayVT{ g3::nearlyEquals(gotRevImSpin, expRevImSpin) };

		if (! (okayS && okayV && okayB && okayT && okaySB && okayVT))
		{
			oss << "Failure of reverse test\n";
			oss << " okayS: " << std::boolalpha << okayS << '\n';
			oss << " okayV: " << std::boolalpha << okayV << '\n';
			oss << " okayB: " << std::boolalpha << okayB << '\n';
			oss << " okayT: " << std::boolalpha << okayT << '\n';
			oss << "okaySB: " << std::boolalpha << okaySB << '\n';
			oss << "okayVT: " << std::boolalpha << okayVT << '\n';
		}

		return oss.str();
	}

	//! Check negation of compound types
	std::string
	test2
		()
	{
		std::ostringstream oss;

		using namespace g3;

		Spinor const posSpin{ Scalar{ 1.}, BiVector{ 2., 3., 4. } };
		Spinor const negSpin{ Scalar{-1.}, BiVector{ -2., -3., -4. } };
		Spinor const gotSpin{ -posSpin };
		Spinor const expSpin{  negSpin };
		if (! nearlyEquals(gotSpin, expSpin))
		{
			oss << "Failure of -Spinor test" << std::endl;
		}
		return oss.str();;
	}

	//! Check dual() operations
	std::string
	test3
		()
	{
		std::ostringstream oss;

		using namespace g3;

		TriVector const gotTri{ dual(Scalar{ 7. }) };
		BiVector const gotBiv{ dual(Vector{ 7., 5., 3. }) };
		Vector const gotVec{ dual(BiVector{ 13., 17., 19. }) };
		Scalar const gotSca{ dual(TriVector{ 29. }) };

		TriVector const expTri{ 7. };
		BiVector const expBiv{ 7., 5., 3. };
		Vector const expVec{ -13., -17., -19. };
		Scalar const expSca{ -29. };

		if (! nearlyEquals(gotTri, expTri))
		{
			oss << "Failure of dual(Tri) test" << std::endl;
		}
		if (! nearlyEquals(gotBiv, expBiv))
		{
			oss << "Failure of dual(Biv) test" << std::endl;
		}
		if (! nearlyEquals(gotVec, expVec))
		{
			oss << "Failure of dual(Vec) test" << std::endl;
		}
		if (! nearlyEquals(gotSca, expSca))
		{
			oss << "Failure of dual(Sca) test" << std::endl;
		}

		return oss.str();;
	}

	//! Check unitary operations (reverse(), oddverse(), dirverse())
	std::string
	test4
		()
	{
		std::ostringstream oss;

		using namespace g3;

		Scalar const aSca{ 1. };
		Vector const aVec{ 2., 3., 4. };
		BiVector const aBiv{ 5., 6., 7. };
		TriVector const aTri{ 8. };
		Spinor const aSpin{ aSca, aBiv };
		ImSpin const aImsp{ aVec, aTri };
		MultiVector const aMV{ aSca, aVec, aBiv, aTri };

		// reverse
		// oddverse
		// dirverse

		// [DoxyExample02]
		MultiVector const expNeg{ -aSca, -aVec, -aBiv, -aTri }; // operator-()
		MultiVector const expRev{  aSca,  aVec, -aBiv, -aTri }; // reverse()
		MultiVector const expOdd{  aSca, -aVec,  aBiv, -aTri }; // oddverse()
		MultiVector const expDiv{  aSca, -aVec, -aBiv,  aTri }; // dirverse()
		// [DoxyExample02]
		MultiVector const gotNeg{ -aMV };
		MultiVector const gotOdd{ oddverse(aMV) };
		MultiVector const gotDiv{ dirverse(aMV) };
		MultiVector const gotRev{ reverse(aMV) };

		// check general operations
		if ( (! nearlyEquals(gotNeg, expNeg))
		  || (! nearlyEquals(gotRev, expRev))
		  || (! nearlyEquals(gotOdd, expOdd))
		  || (! nearlyEquals(gotDiv, expDiv))
		   )
		{
			oss << "Failure of involution operator definition test\n";
			oss << "expNeg: " << expNeg << '\n';
			oss << "gotNeg: " << gotNeg << '\n';
			oss << "difNeg: " << gotNeg - expNeg << '\n';
			oss << '\n';
			oss << "expOdd: " << expOdd << '\n';
			oss << "gotOdd: " << gotOdd << '\n';
			oss << "difOdd: " << gotOdd - expOdd << '\n';
			oss << '\n';
			oss << "expRev: " << expRev << '\n';
			oss << "gotRev: " << gotRev << '\n';
			oss << "difRev: " << gotRev - expRev << '\n';
			oss << '\n';
			oss << "expDiv: " << expDiv << '\n';
			oss << "gotDiv: " << gotDiv << '\n';
			oss << "difDiv: " << gotDiv - expDiv << '\n';
		}

		//
		// negation (via op-()) - negates Sca/Vec/Biv/Tri
		//

		// check blades
		if ( (! nearlyEquals(-aSca, expNeg.theSca))
		  || (! nearlyEquals(-aVec, expNeg.theVec))
		  || (! nearlyEquals(-aBiv, expNeg.theBiv))
		  || (! nearlyEquals(-aTri, expNeg.theTri))
		   )
		{
			oss << "Failure of negation MV components test\n";
		}

		// check composites
		Spinor const expNegSpin{ expNeg.theSca, expNeg.theBiv };
		ImSpin const expNegImsp{ expNeg.theVec, expNeg.theTri };
		if ( (! nearlyEquals(-(aSpin), expNegSpin))
		  || (! nearlyEquals(-(aImsp), expNegImsp))
		   )
		{
			oss << "Failure of negation Spin/ImSpin test\n";
		}

		//
		// reverse() - negates Biv/Tri
		//

		// check blades
		if ( (! nearlyEquals(reverse(aSca), expRev.theSca))
		  || (! nearlyEquals(reverse(aVec), expRev.theVec))
		  || (! nearlyEquals(reverse(aBiv), expRev.theBiv))
		  || (! nearlyEquals(reverse(aTri), expRev.theTri))
		   )
		{
			oss << "Failure of reverse MV components test\n";
		}

		// check composites
		Spinor const expRevSpin{ expRev.theSca, expRev.theBiv };
		ImSpin const expRevImsp{ expRev.theVec, expRev.theTri };
		if ( (! nearlyEquals(reverse(aSpin), expRevSpin))
		  || (! nearlyEquals(reverse(aImsp), expRevImsp))
		   )
		{
			oss << "Failure of reverse Spin/ImSpin test\n";
		}


		//
		// oddverse() - negates Vec/Tri
		//

		// check blades
		if ( (! nearlyEquals(oddverse(aSca), expOdd.theSca))
		  || (! nearlyEquals(oddverse(aVec), expOdd.theVec))
		  || (! nearlyEquals(oddverse(aBiv), expOdd.theBiv))
		  || (! nearlyEquals(oddverse(aTri), expOdd.theTri))
		   )
		{
			oss << "Failure of oddverse MV components test\n";
		}

		// check composites
		Spinor const expOddSpin{ expOdd.theSca, expOdd.theBiv };
		ImSpin const expOddImsp{ expOdd.theVec, expOdd.theTri };
		if ( (! nearlyEquals(oddverse(aSpin), expOddSpin))
		  || (! nearlyEquals(oddverse(aImsp), expOddImsp))
		   )
		{
			oss << "Failure of oddverse Spin/ImSpin test\n";
		}

		//
		// dirverse() - negates Vec/Biv
		//

		// check blades
		if ( (! nearlyEquals(dirverse(aSca), expDiv.theSca))
		  || (! nearlyEquals(dirverse(aVec), expDiv.theVec))
		  || (! nearlyEquals(dirverse(aBiv), expDiv.theBiv))
		  || (! nearlyEquals(dirverse(aTri), expDiv.theTri))
		   )
		{
			oss << "Failure of dirverse MV components test\n";
			oss << "expDiv: " << expDiv << '\n';
			oss << "gotSca: " << dirverse(aSca) << '\n';
			oss << "gotVec: " << dirverse(aVec) << '\n';
			oss << "gotBiv: " << dirverse(aBiv) << '\n';
			oss << "gotTri: " << dirverse(aTri) << '\n';
		}

		// check composites
		Spinor const expDivSpin{ expDiv.theSca, expDiv.theBiv };
		ImSpin const expDivImsp{ expDiv.theVec, expDiv.theTri };
		if ( (! nearlyEquals(dirverse(aSpin), expDivSpin))
		  || (! nearlyEquals(dirverse(aImsp), expDivImsp))
		   )
		{
			oss << "Failure of dirverse Spin/ImSpin test\n";
			oss << "expDiv: " << expDiv << '\n';
			oss << "gotSpin: " << dirverse(aSpin) << '\n';
			oss << "gotImsp: " << dirverse(aImsp) << '\n';
		}

		return oss.str();;
	}

	//! Check involution and composition properties
	std::string
	test5
		()
	{
		std::ostringstream oss;

		using namespace g3;

		Scalar const aSca{ 1. };
		Vector const aVec{ 2., 3., 4. };
		BiVector const aBiv{ 5., 6., 7. };
		TriVector const aTri{ 8. };
		MultiVector const aMV{ aSca, aVec, aBiv, aTri };

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

	//! Check commutativity of uniary operations
	std::string
	test6
		()
	{
		std::ostringstream oss;

		using namespace g3;

		Scalar const aSca{ 1. };
		Vector const aVec{ 2., 3., 4. };
		BiVector const aBiv{ 5., 6., 7. };
		TriVector const aTri{ 8. };
		MultiVector const aMV{ aSca, aVec, aBiv, aTri };

		MultiVector const expNeg{ -aSca, -aVec, -aBiv, -aTri }; // operator-()
		MultiVector const expRev{  aSca,  aVec, -aBiv, -aTri }; // reverse()
		MultiVector const expOdd{  aSca, -aVec,  aBiv, -aTri }; // oddverse()
		MultiVector const expDiv{  aSca, -aVec, -aBiv,  aTri }; // dirverse()

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
	oss << test4();
	oss << test5();
	oss << test6();

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
