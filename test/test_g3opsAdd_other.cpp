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
\brief Unit tests (and example) code for engabra::g3opsAdd_Scalar
*/


#include "checks.hpp" // testing environment common utilities

#include "g3opsAdd_Scalar.hpp"
#include "g3opsAdd_Vector.hpp"
#include "g3opsAdd_BiVector.hpp"
#include "g3opsAdd_TriVector.hpp"
#include "g3opsAdd_Spinor.hpp"
#include "g3opsAdd_ImSpin.hpp"
#include "g3opsAdd_ComPlex.hpp"
#include "g3opsAdd_DirPlex.hpp"
#include "g3opsAdd_MultiVector.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	// Keep test code expressions concise
	using namespace engabra;
	using g3::nearlyEquals;

	namespace
	{
		using namespace g3;

		Scalar const aSca{ 11. };
		Vector const aVec{ 21., 22., 23. };
		BiVector const aBiv{ 31., 32., 33. };
		TriVector const aTri{ 41. };
		Spinor const aSpin
			{ Scalar{ 111. }
			, BiVector{ 121., 122, 123 }
			};
		ImSpin const aImsp
			{ Vector{ 221., 222., 223. }
			, TriVector{ 241. }
			};
		ComPlex const aCplx
			{ Scalar{ 311. }
			, TriVector{ 341. }
			};
		DirPlex const aDplx
			{ Vector{ 421., 422., 423. }
			, BiVector{ 431., 432., 433. }
			};
		MultiVector const aMvec
			{ Scalar{ 511. }
			, Vector{ 521., 522., 523. }
			, BiVector{ 531., 532., 533. }
			, TriVector{ 541. }
			};
	}

	//! Check Scalar + Other types
	std::string
	testSca
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSca]

		// Addition of Scalar and mixed grade types

		// == same type addition - ref. test_g3opsAdd_same
		// TBD: ParaVec const gotScaVec{ sca + vec };
		Spinor const gotScaBiv{ aSca + aBiv };
		ComPlex const gotScaTri{ aSca + aTri };
		Spinor const gotScaSpin{ aSca + aSpin };
		// TBD: NoTri const gotScaImsp{ aSca + aImsp };
		ComPlex const gotScaCplx{ aSca + aCplx };
		// TBD: NoTri const gotScaDplx{ aSca + aDplx };
		MultiVector const gotScaMvec{ aSca + aMvec };

		// expected values
		Spinor const expScaBiv{ aSca, aBiv };
		ComPlex const expScaTri{ aSca, aTri };
		Spinor const expScaSpin{ aSca + aSpin.theSca, aSpin.theBiv };
		ComPlex const expScaCplx{ aSca + aCplx.theSca, aCplx.theTri };
		MultiVector const expScaMvec
			{ aSca + aMvec.theSca, aMvec.theVec, aMvec.theBiv, aMvec.theTri };

			// [DoxyExampleSca]

		tst::checkGotExp(oss, gotScaBiv, expScaBiv, "ScaBiv");
		tst::checkGotExp(oss, gotScaTri, expScaTri, "ScaTri");
		tst::checkGotExp(oss, gotScaSpin, expScaSpin, "ScaSpin");
		tst::checkGotExp(oss, gotScaCplx, expScaCplx, "ScaCplx");
		tst::checkGotExp(oss, gotScaMvec, expScaMvec, "ScaMvec");

		return oss.str();;
	}

	//! Check Vector + Other types
	std::string
	testVec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleVec]

		// Addition of Vector and mixed grade types

		// TBD: ParaVec const gotVecSca{ aVec + aSca };
		// == same type addition - ref. test_g3opsAdd_same
		DirPlex const gotVecBiv{ aVec + aBiv };
		ImSpin const gotVecTri{ aVec + aTri };
		// TBD: NoTri const gotVecSpin{ aVec + aSpin };
		ImSpin const gotVecImsp{ aVec + aImsp };
		// TBD: NoBiv const gotVecCplx{ aVec + aCplx };
		DirPlex const gotVecDplx{ aVec + aDplx };
		MultiVector const gotVecMvec{ aVec + aMvec };

		// expected values
		DirPlex const expVecBiv{ aVec, aBiv };
		ImSpin const expVecTri{ aVec, aTri };
		ImSpin const expVecImsp{ aVec + aImsp.theVec, aImsp.theTri };
		DirPlex const expVecDplx{ aVec + aDplx.theVec, aDplx.theBiv };
		MultiVector const expVecMvec
			{ aMvec.theSca, aVec + aMvec.theVec, aMvec.theBiv, aMvec.theTri };


			// [DoxyExampleVec]

		tst::checkGotExp(oss, gotVecBiv, expVecBiv, "VecBiv");
		tst::checkGotExp(oss, gotVecTri, expVecTri, "VecTri");
		tst::checkGotExp(oss, gotVecImsp, expVecImsp, "VecImsp");
		tst::checkGotExp(oss, gotVecDplx, expVecDplx, "VecDplx");
		tst::checkGotExp(oss, gotVecMvec, expVecMvec, "VecMvec");


		return oss.str();;
	}

	//! Check BiVector + Other types
	std::string
	testBiv
		()
	{
		std::ostringstream oss;

		// [DoxyExampleBiv]

		// Addition of BiVector and mixed grade types

		Spinor const gotBivSca{ aBiv + aSca };
		DirPlex const gotBivVec{ aBiv + aVec };
		// == same type addition - ref. test_g3opsAdd_same
		// TBD: ImPara const gotBivTri{ aBiv + aTri };
		Spinor const gotBivSpin{ aBiv + aSpin };
		// TBD: NoSca const gotBivImsp{ aBiv + aImsp };
		// TBD: NoVec const gotBivCplx{ aBiv + aCplx };
		DirPlex const gotBivDplx{ aBiv + aDplx };
		MultiVector const gotBivMvec{ aBiv + aMvec };

		// expected values
		Spinor const expBivSca{ aSca, aBiv };
		DirPlex const expBivVec{ aVec, aBiv };
		Spinor const expBivSpin{ aSpin.theSca, aBiv + aSpin.theBiv };
		DirPlex const expBivDplx{ aDplx.theVec, aBiv + aDplx.theBiv };
		MultiVector const expBivMvec
			{ aMvec.theSca, aMvec.theVec, aBiv + aMvec.theBiv, aMvec.theTri };

			// [DoxyExampleBiv]

		tst::checkGotExp(oss, gotBivSca, expBivSca, "BivSca");
		tst::checkGotExp(oss, gotBivVec, expBivVec, "BivVec");
		tst::checkGotExp(oss, gotBivSpin, expBivSpin, "BivSpin");
		tst::checkGotExp(oss, gotBivDplx, expBivDplx, "BivDplx");
		tst::checkGotExp(oss, gotBivMvec, expBivMvec, "BivMvec");

		return oss.str();;
	}

	//! Check TriVector + Other types
	std::string
	testTri
		()
	{
		std::ostringstream oss;

		// [DoxyExampleTri]

		// Addition of TriVector and mixed grade types

		ComPlex const gotTriSca{ aTri + aSca };
		ImSpin const gotTriVec{ aTri + aVec };
		// TBD: ImPara const gotTriBiv{ aTri + aBiv };
		// == same type addition - ref. test_g3opsAdd_same
		// TBD: NoVec const gotTriSpin{ aTri + aSpin };
		ImSpin const gotTriImsp{ aTri + aImsp };
		ComPlex const gotTriCplx{ aTri + aCplx };
		// TBD: NoSca const gotTriDplx{ aTri + aDplx };
		MultiVector const gotTriMvec{ aTri + aMvec };

		// expected values
		ComPlex const expTriSca{ aSca, aTri };
		ImSpin const expTriVec{ aVec, aTri };
		ImSpin const expTriImsp{ aImsp.theVec, aTri + aImsp.theTri };
		ComPlex const expTriCplx{ aCplx.theSca, aTri + aCplx.theTri };
		MultiVector const expTriMvec
			{ aMvec.theSca, aMvec.theVec, aMvec.theBiv, aTri + aMvec.theTri };

			// [DoxyExampleTri]

		tst::checkGotExp(oss, gotTriSca, expTriSca, "TriSca");
		tst::checkGotExp(oss, gotTriVec, expTriVec, "TriVec");
		tst::checkGotExp(oss, gotTriImsp, expTriImsp, "TriImsp");
		tst::checkGotExp(oss, gotTriCplx, expTriCplx, "TriCplx");
		tst::checkGotExp(oss, gotTriMvec, expTriMvec, "TriMvec");

		return oss.str();;
	}

	//! Check Spinor + Other types
	std::string
	testSpin
		()
	{
		std::ostringstream oss;

		// [DoxyExampleSpin]

		// Addition of Spinor and mixed grade types

		Spinor const gotSpinSca{ aSpin + aSca };
		// TBD: NoTri const gotSpinVec{ aSpin + aVec };
		Spinor const gotSpinBiv{ aSpin + aBiv };
		// TBD: NoVec const gotSpinTri{ aSpin + aTri };
		// == same type addition - ref. test_g3opsAdd_same
		MultiVector const gotSpinImsp{ aSpin + aImsp };
		// TBD: NoVec const gotSpinCplx{ aSpin + aCplx };
		// TBD: NoTri const gotSpinDplx{ aSpin + aDplx };
		MultiVector const gotSpinMvec{ aSpin + aMvec };

		// expected values
		Spinor const expSpinSca{ aSpin.theSca + aSca, aSpin.theBiv };
		Spinor const expSpinBiv{ aSpin.theSca, aSpin.theBiv + aBiv };
		MultiVector const expSpinImsp
			{ aSpin.theSca, aImsp.theVec, aSpin.theBiv, aImsp.theTri };
		MultiVector const expSpinMvec
			{ aSpin.theSca + aMvec.theSca
			, aMvec.theVec
			, aSpin.theBiv + aMvec.theBiv
			, aMvec.theTri
			};

			// [DoxyExampleSpin]

		tst::checkGotExp(oss, gotSpinSca, expSpinSca, "SpinSca");
		tst::checkGotExp(oss, gotSpinBiv, expSpinBiv, "SpinBiv");
		tst::checkGotExp(oss, gotSpinImsp, expSpinImsp, "SpinImsp");
		tst::checkGotExp(oss, gotSpinMvec, expSpinMvec, "SpinMvec");
		return oss.str();;
	}

	//! Check ImSpin + Other types
	std::string
	testImsp
		()
	{
		std::ostringstream oss;

		// [DoxyExampleImsp]

		// Addition of ImSpin and mixed grade types

		// TBD: NoBiv const gotImspSca{ aImsp + aSca };
		ImSpin const gotImspVec{ aImsp + aVec };
		// TBD: NoSca const gotImspBiv{ aImsp + aBiv };
		ImSpin const gotImspTri{ aImsp + aTri };
		MultiVector const gotImspSpin{ aImsp + aSpin };
		// == same type addition - ref. test_g3opsAdd_same
		// TBD: NoBiv const gotImspCplx{ aImsp + aCplx };
		// TBD: NoSca const gotImspDplx{ aImsp + aDplx };
		MultiVector const gotImspMvec{ aImsp + aMvec };

		// expected values
		ImSpin const expImspVec{ aImsp.theVec + aVec, aImsp.theTri};
		ImSpin const expImspTri{ aImsp.theVec, aImsp.theTri + aTri };
		MultiVector const expImspSpin
			{ aSpin.theSca , aImsp.theVec , aSpin.theBiv , aImsp.theTri };
		MultiVector const expImspMvec
			{ aMvec.theSca
			, aImsp.theVec + aMvec.theVec
			, aMvec.theBiv
			, aImsp.theTri + aMvec.theTri
			};

			// [DoxyExampleImsp]

		tst::checkGotExp(oss, gotImspVec, expImspVec, "ImspVec");
		tst::checkGotExp(oss, gotImspTri, expImspTri, "ImspTri");
		tst::checkGotExp(oss, gotImspSpin, expImspSpin, "ImspSpin");
		tst::checkGotExp(oss, gotImspMvec, expImspMvec, "ImspMvec");

		return oss.str();;
	}

	//! Check ComPlex + Other types
	std::string
	testCplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleCplx]

		// Addition of ComPlex and mixed grade types

		ComPlex const gotCplxSca{ aCplx + aSca };
		// TBD: NoBiv const gotCplxVec{ aCplx + aVec };
		// TBD: NoVec const gotCplxBiv{ aCplx + aBiv };
		ComPlex const gotCplxTri{ aCplx + aTri };
		// TBD: NoVec const gotCplxSpin{ aCplx + aSpin };
		// TBD: NoBiv const gotCplxImsp{ aCplx + aImsp };
		// == same type addition - ref. test_g3opsAdd_same
		MultiVector const gotCplxDplx{ aCplx + aDplx };
		MultiVector const gotCplxMvec{ aCplx + aMvec };

		// expected values
		ComPlex const expCplxSca{ aCplx.theSca + aSca, aCplx.theTri };
		ComPlex const expCplxTri{ aCplx.theSca, aCplx.theTri + aTri };
		MultiVector const expCplxDplx
			{ aCplx.theSca, aDplx.theVec, aDplx.theBiv, aCplx.theTri };
		MultiVector const expCplxMvec
			{ aCplx.theSca + aMvec.theSca
			, aMvec.theVec
			, aMvec.theBiv
			, aCplx.theTri + aMvec.theTri
			};

			// [DoxyExampleCplx]

		tst::checkGotExp(oss, gotCplxSca, expCplxSca, "CplxSca");
		tst::checkGotExp(oss, gotCplxTri, expCplxTri, "CplxTri");
		tst::checkGotExp(oss, gotCplxDplx, expCplxDplx, "CplxDplx");
		tst::checkGotExp(oss, gotCplxMvec, expCplxMvec, "CplxMvec");

		return oss.str();;
	}

	//! Check DirPlex + Other types
	std::string
	testDplx
		()
	{
		std::ostringstream oss;

		// [DoxyExampleDplx]

		// Addition of DirPlex and mixed grade types

		// TBD: NoTri const gotDplxSca{ aDplx + aSca };
		DirPlex const gotDplxVec{ aDplx + aVec };
		DirPlex const gotDplxBiv{ aDplx + aBiv };
		// TBD: NoSca const gotDplxTri{ aDplx + aTri };
		// TBD: NoTri const gotDplxSpin{ aDplx + aSpin };
		// TBD: NoBiv const gotDplxImsp{ aDplx + aImsp };
		// == same type addition - ref. test_g3opsAdd_same
		MultiVector const gotDplxCplx{ aDplx + aCplx };
		MultiVector const gotDplxMvec{ aDplx + aMvec };

		// expected values
		DirPlex const expDplxVec{ aDplx.theVec + aVec, aDplx.theBiv };
		DirPlex const expDplxBiv{ aDplx.theVec, aDplx.theBiv + aBiv };
		MultiVector const expDplxCplx
			{ aCplx.theSca, aDplx.theVec, aDplx.theBiv, aCplx.theTri };
		MultiVector const expDplxMvec
			{ aMvec.theSca
			, aDplx.theVec + aMvec.theVec
			, aDplx.theBiv + aMvec.theBiv
			, aMvec.theTri
			};

			// [DoxyExampleDplx]

		tst::checkGotExp(oss, gotDplxVec, expDplxVec, "DplxVec");
		tst::checkGotExp(oss, gotDplxBiv, expDplxBiv, "DplxBiv");
		tst::checkGotExp(oss, gotDplxCplx, expDplxCplx, "DplxCplx");
		tst::checkGotExp(oss, gotDplxMvec, expDplxMvec, "DplxMvec");

		return oss.str();;
	}

	//! Check MultiVector + Other types
	std::string
	testMvec
		()
	{
		std::ostringstream oss;

		// [DoxyExampleMvec]

		// Addition of MultiVector and mixed grade types

		MultiVector const gotMvecSca{ aMvec + aSca };
		MultiVector const gotMvecVec{ aMvec + aVec };
		MultiVector const gotMvecBiv{ aMvec + aBiv };
		MultiVector const gotMvecTri{ aMvec + aTri };
		MultiVector const gotMvecSpin{ aMvec + aSpin };
		MultiVector const gotMvecImsp{ aMvec + aImsp };
		MultiVector const gotMvecCplx{ aMvec + aCplx };
		MultiVector const gotMvecDplx{ aMvec + aDplx };
		// == same type addition - ref. test_g3opsAdd_same

		// expected values
		MultiVector const expMvecSca
			{ aMvec.theSca + aSca
			, aMvec.theVec
			, aMvec.theBiv
			, aMvec.theTri
			};
		MultiVector const expMvecVec
			{ aMvec.theSca
			, aMvec.theVec + aVec
			, aMvec.theBiv
			, aMvec.theTri
			};
		MultiVector const expMvecBiv
			{ aMvec.theSca
			, aMvec.theVec
			, aMvec.theBiv + aBiv
			, aMvec.theTri
			};
		MultiVector const expMvecTri
			{ aMvec.theSca
			, aMvec.theVec
			, aMvec.theBiv
			, aMvec.theTri + aTri
			};
		MultiVector const expMvecSpin
			{ aMvec.theSca + aSpin.theSca
			, aMvec.theVec
			, aMvec.theBiv + aSpin.theBiv
			, aMvec.theTri
			};
		MultiVector const expMvecImsp
			{ aMvec.theSca
			, aMvec.theVec + aImsp.theVec
			, aMvec.theBiv
			, aMvec.theTri + aImsp.theTri
			};
		MultiVector const expMvecCplx
			{ aMvec.theSca + aCplx.theSca
			, aMvec.theVec
			, aMvec.theBiv
			, aMvec.theTri + aCplx.theTri
			};
		MultiVector const expMvecDplx
			{ aMvec.theSca
			, aMvec.theVec + aDplx.theVec
			, aMvec.theBiv + aDplx.theBiv
			, aMvec.theTri
			};

			// [DoxyExampleMvec]

		tst::checkGotExp(oss, gotMvecSca, expMvecSca, "MvecSca");
		tst::checkGotExp(oss, gotMvecVec, expMvecVec, "MvecVec");
		tst::checkGotExp(oss, gotMvecBiv, expMvecBiv, "MvecBiv");
		tst::checkGotExp(oss, gotMvecTri, expMvecTri, "MvecTri");
		tst::checkGotExp(oss, gotMvecSpin, expMvecSpin, "MvecSpin");
		tst::checkGotExp(oss, gotMvecImsp, expMvecImsp, "MvecImsp");
		tst::checkGotExp(oss, gotMvecCplx, expMvecCplx, "MvecCplx");
		tst::checkGotExp(oss, gotMvecDplx, expMvecDplx, "MvecDplx");

		return oss.str();;
	}

	//! Check order-dependent of addition operations
	std::string
	testOrdering
		()
	{
		std::ostringstream oss;

		// used in main README.md documentation
		// [DoxyExampleOrder01]

		// -- Consider this expression which
		//    requires ParaVec, NoTri intermediate type support
		// MultiVector const gotMvec{ aSca + aVec + aBiv + aTri };
		// -- Instead, order arguments to produce
		//    supported ComPlex and DirPlex temporaries which then
		//    combine into a MultiVector result
		MultiVector const gotMvec{ (aSca + aTri) + (aVec + aBiv) };
		// -- Or cast individual arguments to MultiVector type first
		MultiVector const expMvec
			{ MultiVector(aSca)
			+ MultiVector(aVec)
			+ MultiVector(aBiv)
			+ MultiVector(aTri)
			};

			// [DoxyExampleOrder01]
		tst::checkGotExp(oss, gotMvec, expMvec, "addSVBT order");

		return oss.str();;
	}

}

//! Check behavior of operator+() with Scalar and higher rank types
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << testSca();
	oss << testVec();
	oss << testBiv();
	oss << testTri();
	oss << testSpin();
	oss << testImsp();
	oss << testCplx();
	oss << testDplx();
	oss << testMvec();
	oss << testOrdering();

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

