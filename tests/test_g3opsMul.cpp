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
\brief Unit tests (and example) code for engabra g3opsMul
*/


#include "test_common.hpp" // testing environment common utilities

#include "g3opsMul.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"
#include "g3opsAdd.hpp"

#include <iostream>
#include <sstream>
#include <typeinfo>


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;
	using g3::nearlyEquals;

	//! Examples for documentation
	std::string
	test0
		()
	{
		std::ostringstream oss;

		// [DoxyExample01]
		using namespace engabra::g3;

		// two arbitrary vectors defined by amounts of basis vectors
		Vector const vecA{ 2.*e1 + 3.*e2 };
		Vector const vecB{ 5.*e2 + .25*e3 };

		// a "classic" geometric product of two vectors
		Spinor const spinAB{ vecA * vecB };
			// [DoxyExample01]


		Spinor const spinBA{ vecB * vecA };
		if (! nearlyEquals(spinBA, reverse(spinAB)))
		{
			oss << "Failure of spinAB/BA reverse test\n";
		}

		// [DoxyExample02]
		// Example using MultiVectors to evaluate the product of 
		// two entities having "unusual" composite grades.
		using namespace engabra::g3;

		// E.g.: (scalar+trivector)*(vector+bivector+trivector)
		MultiVector const mvA // construct MV for first argument
			( Scalar{ -3. }
			, zero<Vector>() // i.e. Vector{ 0., 0., 0. }
			, zero<BiVector>() // i.e. BiVector{ 0., 0., 0. }
			, TriVector{ 7. }
			);
		MultiVector const mvB // construct MV for second argument
			( zero<Scalar>() // i.e. Scalar{ 0. }
			, Vector{ 1., -2., 3. }
			, BiVector{ -5., 4., 11. }
			, zero<TriVector>() // i.e. TriVector{ 0. }
			);

		// use MV*MV product
		MultiVector const mvAB{ mvA * mvB };

		// pickoff grades of interest, e.g.
		Scalar const & scaAB = mvAB.theSca;
		Vector const & vecAB = mvAB.theVec;
		BiVector const & bivAB = mvAB.theBiv;
		TriVector const & triAB = mvAB.theTri;
			// [DoxyExample02]

		// use unused variables above to checks
		MultiVector const mvBA{ mvB * mvA };
		// since mvA has scalar and trivector grades, it commutes with mvB
		if (! nearlyEquals(scaAB, mvBA.theSca))
		{
			oss << "Failure of mvAB/BA.theSca test\n";
		}
		if (! nearlyEquals(vecAB, mvBA.theVec))
		{
			oss << "Failure of mvAB/BA.theVec test\n";
		}
		if (! nearlyEquals(bivAB, mvBA.theBiv))
		{
			oss << "Failure of mvAB/BA.theBiv test\n";
		}
		if (! nearlyEquals(triAB, mvBA.theTri))
		{
			oss << "Failure of mvAB/BA.theTri test\n";
		}

		return oss.str();;
	}

	//! Check Implementation functions
	std::string
	test1
		()
	{
		std::ostringstream oss;

		std::array<double, 3u> const dataA{  2.,  3.,  5. };
		std::array<double, 3u> const dataB{  7., -11., 13. };

		using g3::priv::prodComm;
		using g3::priv::prodAnti;

		// check symmetry of commutative product
		double const commAB{ prodComm(dataA, dataB) };
		double const commBA{ prodComm(dataB, dataA) };
		if (! nearlyEquals(commAB, commBA))
		{
			oss << "Failure of prodComm symmetry test" << std::endl;
		}

		// check anti-symmetry of anti-commutative product
		std::array<double, 3u> const antiAB{ prodAnti(dataA, dataB) };
		std::array<double, 3u> const antiBA{ prodAnti(dataB, dataA) };
		std::array<double, 3u> const negBA
			{ -antiBA[0], -antiBA[1], -antiBA[2] };
		if (! nearlyEquals(antiAB, negBA))
		{
			oss << "Failure of prodAnti anti-symmetry test" << std::endl;
		}

		// check anti-symmetry is zero with self
		std::array<double, 3u> const sameAA{ prodAnti(dataA, dataA) };
		std::array<double, 3u> const zeros{ 0., 0., 0. };
		if (! nearlyEquals(sameAA, zeros))
		{
			oss << "Failure of anti-symmetry zero test" << std::endl;
		}

		return oss.str();;
	}

	//! Run multiplication tests on Type using data from arrays
	template <typename Type, std::size_t Dim>
	std::string
	checkMul
		( std::array<double, 3u> const useData
		, std::array<double, 3u> const expData
		, double const & factor
		)
	{
		std::ostringstream oss;

		// extract 'Dim' amount from (oversized) input data
		std::array<double, Dim> initData;
		std::copy
			( std::cbegin(useData), std::cbegin(useData) + Dim
			, initData.begin()
			);
		std::array<double, Dim> multData;
		std::copy
			( expData.cbegin(), expData.cbegin() + Dim
			, multData.begin()
			);

		// construct g3 instances from extracted data
		Type const initEntity{ initData };
		Type const expEntity{ multData };

		// conduct test
		{
			// pre-multiply by factor
			Type const gotEntity{ factor * initEntity };
			if (! nearlyEquals(gotEntity, expEntity))
			{
				oss << "Failure of checkMul pre-dub test" << std::endl;
				oss << "template Type: " << typeid(Type).name() << std::endl;
			}
		}

		{
			// post-multiply by factor
			Type const gotEntity{ initEntity * factor };
			if (! nearlyEquals(gotEntity, expEntity))
			{
				oss << "Failure of checkMul post-dub test" << std::endl;
				oss << "template Type: " << typeid(Type).name() << std::endl;
			}
		}

		return oss.str();
	}

	//! Check basic double type multiplications
	std::string
	test2
		()
	{
		std::ostringstream oss;

		// data examples to use
		std::array<double, 3u> const dataInit{ 2.5, 3.25, 5.125 };
		std::array<double, 3u> const dataTwox{ 5.0, 6.50, 10.25 };
		double const multBy{ 2. };

		oss << checkMul<g3::Scalar, 1u>(dataInit, dataTwox, multBy);
		oss << checkMul<g3::Vector, 3u>(dataInit, dataTwox, multBy);
		oss << checkMul<g3::BiVector, 3u>(dataInit, dataTwox, multBy);
		oss << checkMul<g3::TriVector, 1u>(dataInit, dataTwox, multBy);

		return oss.str();;
	}

	//! Check products of various numbers of vectors
	std::string
	test3
		()
	{
		std::ostringstream oss;

		using namespace g3;

		Spinor const gotE23{ e2 * e3 };
		Spinor const gotE31{ e3 * e1 };
		Spinor const gotE12{ e1 * e2 };
		Spinor const expE23{ 0., e23 };
		Spinor const expE31{ 0., e31 };
		Spinor const expE12{ 0., e12 };
		bool const okay23{ nearlyEquals(gotE23, expE23) };
		bool const okay31{ nearlyEquals(gotE31, expE31) };
		bool const okay12{ nearlyEquals(gotE12, expE12) };
		if (! (okay23 && okay31 && okay12))
		{
			oss << "Failure on simple basis Spinor test" << std::endl;
			oss << "expE23: " << expE23 << std::endl;
			oss << "gotE23: " << gotE23 << std::endl;
			oss << "expE31: " << expE31 << std::endl;
			oss << "gotE31: " << gotE31 << std::endl;
			oss << "expE12: " << expE12 << std::endl;
			oss << "gotE12: " << gotE12 << std::endl;
		}

		// use general MultiVector computation as cross-check
		Vector const vA{ 3., 5., 7. };
		Vector const vB{ 11., 13., 17. };
		Spinor const gotAB{ vA * vB };
		MultiVector const mvA{ vA };
		MultiVector const mvB{ vB };
		MultiVector const mvAB{ mvA * mvB };
		Spinor const expAB{ mvAB.theSca, mvAB.theBiv };
		if (! nearlyEquals(gotAB, expAB))
		{
			oss << "Failure on MultiVector Spinor compare test\n";
			oss << "expAB: " << expAB << std::endl;
			oss << "gotAB: " << gotAB << std::endl;
		}

		// orthogonal unitary trivector product
		ImSpin const got123{ e1 * e2 * e3 };
		ImSpin const exp123{ zero<Vector>(), 1. };
		if (! nearlyEquals(got123, exp123))
		{
			oss << "Failure of orthogonal triple vector product test\n";
			oss << "exp123: " << exp123 << std::endl;
			oss << "got123: " << got123 << std::endl;
		}

		// use general MultiVector computation as cross-check
		Vector const vC{ 19., 23., 27. };
		ImSpin const gotABC{ vA * vB * vC };
		MultiVector const mvC{ vC };
		MultiVector const mvABC{ mvA * mvB * mvC };
		ImSpin const expABC{ mvABC.theVec, mvABC.theTri };

		if (! nearlyEquals(gotABC, expABC))
		{
			oss << "Failure on MultiVector ImSpin compare test\n";
			oss << "expABC: " << expABC << std::endl;
			oss << "gotABC: " << gotABC << std::endl;
		}

		Vector const vD{ 29., 31., 37. };
		Spinor const gotABCD{ vA * vB * vC * vD };
		MultiVector const mvD{ vD };
		MultiVector const mvABCD{ mvA * mvB * mvC * mvD };
		Spinor const expABCD{ mvABCD.theSca, mvABCD.theBiv };
		if (! nearlyEquals(gotABCD, expABCD))
		{
			oss << "Failure on MultiVector Spinor compare test\n";
			oss << "expABCD: " << expABCD << std::endl;
			oss << "gotABCD: " << gotABCD << std::endl;
		}

		return oss.str();;
	}

	//! Test pairs for given template types
	template <typename Type1, typename Type2>
	inline
	std::string
	pairProduct
		( std::array<double, 3u> const & dataA
		, std::array<double, 3u> const & dataB
		, std::string const & tname
		)
	{
		std::ostringstream oss;

		using namespace g3;

		Vector const itemA{ dataA };
		Vector const itemB{ dataB };
		MultiVector const mvA{ itemA };
		MultiVector const mvB{ itemB };
		MultiVector const expAB{ mvA * mvB };
		MultiVector const gotAB{ itemA * itemB };
		if (! nearlyEquals(gotAB, expAB))
		{
			oss << "Failure of test: '" << tname << "'\n";
			oss << "expAB: " << expAB << std::endl;
			oss << "gotAB: " << gotAB << std::endl;
		}
		return oss.str();
	}

	//! Check the more "complicated" product pairs in G3
	std::string
	test4
		()
	{
		std::ostringstream oss;

		using namespace g3;

		// Use full MultiVector product to cross check
		std::array<double, 3u> const dataA{ 3., -5., 7. };
		std::array<double, 3u> const dataB{ 27., 29., 31. };
		oss << pairProduct<Vector, Vector>(dataA, dataB, "vec*vec pair");
		oss << pairProduct<Vector, BiVector>(dataA, dataB, "vec*biv pair");
		oss << pairProduct<BiVector, Vector>(dataA, dataB, "biv*vec pair");
		oss << pairProduct<BiVector, BiVector>(dataA, dataB, "biv*biv pair");

		return oss.str();;
	}

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

	//! Check multivector*multivector product
	std::string
	test5
		()
	{
		std::ostringstream oss;

		using namespace g3;

		Scalar const scaA{ -2. };
		Vector const vecA{ 3., -5., 7. };
		BiVector const bivA{ -11., 13., 17. };
		TriVector const triA{ 21. };

		Scalar const scaB{ 23. };
		Vector const vecB{ 27., 29., 31. };
		BiVector const bivB{ 37., 39., -41. };
		TriVector const triB{ -43. };

		MultiVector const mvA{ scaA, vecA, bivA, triA };
		MultiVector const mvB{ scaB, vecB, bivB, triB };

		// Check net-combinations of products via product()

		MultiVector const expAB{ product(mvA, mvB) };
		MultiVector const gotAB{ mvA * mvB };

		constexpr double tol{ 100. * std::numeric_limits<double>::epsilon() };
		if (! nearlyEquals(gotAB, expAB, tol))
		{
			oss << "Failure of general mv*mv product test" << std::endl;
			oss << "expAB: " << expAB << std::endl;
			oss << "gotAB: " << gotAB << std::endl;
		}

		return oss.str();;
	}

	//! Check associativity of vector product
	std::string
	test6
		()
	{
		std::ostringstream oss;

		using namespace g3;

		Vector const vA{ 3., 5., 7. };
		Vector const vB{ 11., 13., 17. };
		Vector const vC{ 19., 23., 27. };
		Vector const vD{ 29., 31., 37. };
		Vector const vE{ 41., 43., 47. };

		MultiVector const mvProd
			{ MultiVector{vA}
			* MultiVector{vB}
			* MultiVector{vC}
			* MultiVector{vD}
			* MultiVector{vE}
			};
		ImSpin const exp{ mvProd.theVec, mvProd.theTri };

		ImSpin const got1{ vA * vB * vC * vD * vE };
		ImSpin const got2{ (vA * vB) * vC * (vD * vE) };
		ImSpin const got3{ vA * (vB * vC * vD) * vE };
		ImSpin const got4{ (vA * vB * vC) * (vD * vE) };
		ImSpin const got5{ (vA * vB) * (vC * vD * vE) };
		ImSpin const got6{ (vA * vB * vC * vD) * vE };
		ImSpin const got7{ vA * (vB * vC * vD * vE) };

		if (! nearlyEquals(got1, exp))
		{
			oss << "Failure of associativity no.1 test" << std::endl;
		}
		if (! nearlyEquals(got2, exp))
		{
			oss << "Failure of associativity no.2 test" << std::endl;
		}
		if (! nearlyEquals(got3, exp))
		{
			oss << "Failure of associativity no.3 test" << std::endl;
		}
		if (! nearlyEquals(got4, exp))
		{
			oss << "Failure of associativity no.4 test" << std::endl;
		}
		if (! nearlyEquals(got5, exp))
		{
			oss << "Failure of associativity no.5 test" << std::endl;
			oss << "exp: " << exp << std::endl;
			oss << "got: " << got5 << std::endl;
		}
		if (! nearlyEquals(got6, exp))
		{
			oss << "Failure of associativity no.6 test" << std::endl;
		}
		if (! nearlyEquals(got7, exp))
		{
			oss << "Failure of associativity no.7 test" << std::endl;
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

	oss << test0();
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

