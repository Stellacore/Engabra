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
\brief Unit tests (and example) code for engabra::g3opsMulAll
*/


#include "checks.hpp" // testing environment common utilities

#include "g3opsMul.hpp"

#include "g3compare.hpp"
#include "g3func.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>
#include <typeinfo>


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;
	using g3::nearlyEquals;


	template <typename TypeA, typename TypeB>
	inline
	std::string
	check
		( TypeA const & itemA
		, TypeB const & itemB
		)
	{
		std::ostringstream oss;
		using namespace g3;

		// check against MultiVector*MultiVector operation (the implementation
		// of which has been extracted from a previously verified library).
		MultiVector const mvA(itemA);
		MultiVector const mvB(itemB);
		MultiVector const expAB{ mvA * mvB };

		// compute product and construct multivector around it for testing
		auto const prodAB{ itemA * itemB }; // operator*() evaluation
		MultiVector const gotAB(prodAB); // requires appropriate ctor

		// allow for some MV*MV computation and geometry noise
		constexpr double tol{ 1.e-14 };
		// compare
		if (! nearlyEquals(gotAB, expAB, tol))
		{
			MultiVector const difAB{ gotAB - expAB };
			double const difMag{ magnitude(difAB) };
			oss << "Failure of generic product test\n";
			oss
				<< " typeA: " << typeid(TypeA).name()
				<< " typeB: " << typeid(TypeB).name()
				<< '\n';
			oss << " expAB: " << expAB << '\n';
			oss << " gotAB: " << gotAB << '\n';
			oss
				<< " difAB: " << difAB
				<< "   difMag: " << std::scientific << difMag << '\n';
		}

		return oss.str();
	}

	//! Check full table of multiplication operations.
	std::string
	test1
		()
	{
		std::ostringstream oss;

		using namespace g3;

		// note: scale near unity to make testing tolerances more uniform
		double const dubA{  .875 };
		Scalar const scaA{ (1./20.) * -2. };
		Vector const vecA{ (1./6.) * Vector{ 3., -5., 7. } };
		BiVector const bivA{ (1./15.) * BiVector{ -11., 13., 17. } };
		TriVector const triA{ (1./20.) * 21. };
		Spinor const spinA{ scaA, bivA };
		ImSpin const imspA{ vecA, triA };
		ComPlex const cplxA{ scaA, triA };
		DirPlex const dplxA{ vecA, bivA };
		MultiVector const mvA(scaA, vecA, bivA, triA);

		double const dubB{ 1.125 };
		Scalar const scaB{ (1./20.) * 23. };
		Vector const vecB{ (1./30.) * Vector{ 27., 29., 31. } };
		BiVector const bivB{ (1./40.) * BiVector{ 37., 39., -41. } };
		TriVector const triB{ (1./42.) * -43. };
		Spinor const spinB{ scaB, bivB };
		ImSpin const imspB{ vecB, triB };
		ComPlex const cplxB{ scaB, triB };
		DirPlex const dplxB{ vecB, bivB };
		MultiVector const mvB(scaB, vecB, bivB, triB);

		// double*...
		oss << check<double, double>(dubA, dubB);
		oss << check<double, Scalar>(dubA, scaB);
		oss << check<double, Vector>(dubA, vecB);
		oss << check<double, BiVector>(dubA, bivB);
		oss << check<double, TriVector>(dubA, triB);
		oss << check<double, Spinor>(dubA, spinB);
		oss << check<double, ImSpin>(dubA, imspB);
		oss << check<double, ComPlex>(dubA, cplxB);
		oss << check<double, DirPlex>(dubA, dplxB);
		oss << check<double, MultiVector>(dubA, mvB);

		// Scalar*...
		oss << check<Scalar, double>(scaA, dubB);
		oss << check<Scalar, Scalar>(scaA, scaB);
		oss << check<Scalar, Vector>(scaA, vecB);
		oss << check<Scalar, BiVector>(scaA, bivB);
		oss << check<Scalar, TriVector>(scaA, triB);
		oss << check<Scalar, Spinor>(scaA, spinB);
		oss << check<Scalar, ImSpin>(scaA, imspB);
		oss << check<Scalar, ComPlex>(scaA, cplxB);
		oss << check<Scalar, DirPlex>(scaA, dplxB);
		oss << check<Scalar, MultiVector>(scaA, mvB);

		// Vector*...
		oss << check<Vector, double>(vecA, dubB);
		oss << check<Vector, Scalar>(vecA, scaB);
		oss << check<Vector, Vector>(vecA, vecB);
		oss << check<Vector, BiVector>(vecA, bivB);
		oss << check<Vector, TriVector>(vecA, triB);
		oss << check<Vector, Spinor>(vecA, spinB);
		oss << check<Vector, ImSpin>(vecA, imspB);
		oss << check<Vector, ComPlex>(vecA, cplxB);
		oss << check<Vector, DirPlex>(vecA, dplxB);
		oss << check<Vector, MultiVector>(vecA, mvB);

		// BiVector*...
		oss << check<BiVector, double>(bivA, dubB);
		oss << check<BiVector, Scalar>(bivA, scaB);
		oss << check<BiVector, Vector>(bivA, vecB);
		oss << check<BiVector, BiVector>(bivA, bivB);
		oss << check<BiVector, TriVector>(bivA, triB);
		oss << check<BiVector, Spinor>(bivA, spinB);
		oss << check<BiVector, ImSpin>(bivA, imspB);
		oss << check<BiVector, ComPlex>(bivA, cplxB);
		oss << check<BiVector, DirPlex>(bivA, dplxB);
		oss << check<BiVector, MultiVector>(bivA, mvB);

		// TriVector*...
		oss << check<TriVector, double>(triA, dubB);
		oss << check<TriVector, Scalar>(triA, scaB);
		oss << check<TriVector, Vector>(triA, vecB);
		oss << check<TriVector, BiVector>(triA, bivB);
		oss << check<TriVector, TriVector>(triA, triB);
		oss << check<TriVector, Spinor>(triA, spinB);
		oss << check<TriVector, ImSpin>(triA, imspB);
		oss << check<TriVector, ComPlex>(triA, cplxB);
		oss << check<TriVector, DirPlex>(triA, dplxB);
		oss << check<TriVector, MultiVector>(triA, mvB);

		// Spinor*...
		oss << check<Spinor, double>(spinA, dubB);
		oss << check<Spinor, Scalar>(spinA, scaB);
		oss << check<Spinor, Vector>(spinA, vecB);
		oss << check<Spinor, BiVector>(spinA, bivB);
		oss << check<Spinor, TriVector>(spinA, triB);
		oss << check<Spinor, Spinor>(spinA, spinB);
		oss << check<Spinor, ImSpin>(spinA, imspB);
		oss << check<Spinor, ComPlex>(spinA, cplxB);
		oss << check<Spinor, DirPlex>(spinA, dplxB);
		oss << check<Spinor, MultiVector>(spinA, mvB);

		// ImSpin*...
		oss << check<ImSpin, double>(imspA, dubB);
		oss << check<ImSpin, Scalar>(imspA, scaB);
		oss << check<ImSpin, Vector>(imspA, vecB);
		oss << check<ImSpin, BiVector>(imspA, bivB);
		oss << check<ImSpin, TriVector>(imspA, triB);
		oss << check<ImSpin, Spinor>(imspA, spinB);
		oss << check<ImSpin, ImSpin>(imspA, imspB);
		oss << check<ImSpin, ComPlex>(imspA, cplxB);
		oss << check<ImSpin, DirPlex>(imspA, dplxB);
		oss << check<ImSpin, MultiVector>(imspA, mvB);

		// ComPlex*...
		oss << check<ComPlex, double>(cplxA, dubB);
		oss << check<ComPlex, Scalar>(cplxA, scaB);
		oss << check<ComPlex, Vector>(cplxA, vecB);
		oss << check<ComPlex, BiVector>(cplxA, bivB);
		oss << check<ComPlex, TriVector>(cplxA, triB);
		oss << check<ComPlex, Spinor>(cplxA, spinB);
		oss << check<ComPlex, ImSpin>(cplxA, imspB);
		oss << check<ComPlex, ComPlex>(cplxA, cplxB);
		oss << check<ComPlex, DirPlex>(cplxA, dplxB);
		oss << check<ComPlex, MultiVector>(cplxA, mvB);

		// DirPlex*...
		oss << check<DirPlex, double>(dplxA, dubB);
		oss << check<DirPlex, Scalar>(dplxA, scaB);
		oss << check<DirPlex, Vector>(dplxA, vecB);
		oss << check<DirPlex, BiVector>(dplxA, bivB);
		oss << check<DirPlex, TriVector>(dplxA, triB);
		oss << check<DirPlex, Spinor>(dplxA, spinB);
		oss << check<DirPlex, ImSpin>(dplxA, imspB);
		oss << check<DirPlex, ComPlex>(dplxA, cplxB);
		oss << check<DirPlex, DirPlex>(dplxA, dplxB);
		oss << check<DirPlex, MultiVector>(dplxA, mvB);

		// MultiVector*...
		oss << check<MultiVector, double>(mvA, dubB);
		oss << check<MultiVector, Scalar>(mvA, scaB);
		oss << check<MultiVector, Vector>(mvA, vecB);
		oss << check<MultiVector, BiVector>(mvA, bivB);
		oss << check<MultiVector, TriVector>(mvA, triB);
		oss << check<MultiVector, Spinor>(mvA, spinB);
		oss << check<MultiVector, ImSpin>(mvA, imspB);
		oss << check<MultiVector, ComPlex>(mvA, cplxB);
		oss << check<MultiVector, DirPlex>(mvA, dplxB);
		oss << check<MultiVector, MultiVector>(mvA, mvB);

		return oss.str();;
	}

}

//! Check behavior of opsMulAll
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test1();
	// oss << test2();

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

