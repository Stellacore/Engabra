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
\brief Unit tests (and example) code for engabra::g3
*/


#include "checks.hpp" // testing environment common utilities

#include "g3func.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


namespace
{
	using namespace engabra;
	using g3::nearlyEquals;

	//! Compute amplitude using full multivector operations
	g3::ComPlex
	expAmp
		( g3::MultiVector const & mv
		)
	{
		g3::MultiVector const mvSq{ mv * g3::dirverse(mv) };
		std::complex<double> zSq{ mvSq[0], mvSq[7] }; // re,im parts
		std::complex<double> zAmp{ std::sqrt(zSq) };
		return g3::ComPlex::from(zAmp);
	}

	//! Shorthand cast item to MultiVector type
	template <typename Type>
	inline
	g3::MultiVector
	mv
		( Type const & item
		)
	{
		return g3::MultiVector(item);
	}

	//! Examples for documentation
	std::string
	test0
		()
	{
		std::ostringstream oss;

		// [DoxyExample01]
		using namespace engabra::g3;

		// blade test values
		Scalar const sca{ 2. };
		Vector const vec{ 3., 5., 7. };
		BiVector const biv{ 11., 13., 17. };
		TriVector const tri{ 23. };

		// compound test values
		Spinor const spin{ sca, biv };
		ImSpin const imsp{ vec, tri };
		ComPlex const cplx{ sca, tri };
		DirPlex const dplx{ vec, biv };
		MultiVector const mvec{ sca, vec, biv, tri };

		// Amplitude for basic types
		ComPlex const gotAmpSca{ amplitude(sca) };
		ComPlex const gotAmpVec{ amplitude(vec) };
		ComPlex const gotAmpBiv{ amplitude(biv) };
		ComPlex const gotAmpTri{ amplitude(tri) };

		// Amplitude for compound types
		ComPlex const gotAmpSpin{ amplitude(spin) };
		ComPlex const gotAmpImsp{ amplitude(imsp) };
		ComPlex const gotAmpCplx{ amplitude(cplx) };
		ComPlex const gotAmpDplx{ amplitude(dplx) };
		ComPlex const gotAmpMVec{ amplitude(mvec) };

		// Amplitude for complex types

		// [DoxyExample01]

		// compare with full multivector computation
		ComPlex const expAmpSca{ expAmp(mv(sca)) };
		ComPlex const expAmpVec{ expAmp(mv(vec)) };
		ComPlex const expAmpBiv{ expAmp(mv(biv)) };
		ComPlex const expAmpTri{ expAmp(mv(tri)) };

		ComPlex const expAmpSpin{ expAmp(mv(spin)) };
		ComPlex const expAmpImsp{ expAmp(mv(imsp)) };
		ComPlex const expAmpCplx{ expAmp(mv(cplx)) };
		ComPlex const expAmpDplx{ expAmp(mv(dplx)) };

		ComPlex const expAmpMVec{ expAmp(mv(mvec)) };

		tst::checkGotExp(oss, gotAmpSca, expAmpSca, "amp(Sca)");
		tst::checkGotExp(oss, gotAmpVec, expAmpVec, "amp(Vec)");
		tst::checkGotExp(oss, gotAmpBiv, expAmpBiv, "amp(Biv)");
		tst::checkGotExp(oss, gotAmpTri, expAmpTri, "amp(Tri)");

		tst::checkGotExp(oss, gotAmpSpin, expAmpSpin, "amp(Spin)");
		tst::checkGotExp(oss, gotAmpImsp, expAmpImsp, "amp(Imsp)");
		tst::checkGotExp(oss, gotAmpCplx, expAmpCplx, "amp(Cplx)");
		tst::checkGotExp(oss, gotAmpDplx, expAmpDplx, "amp(Dplx)");

		tst::checkGotExp(oss, gotAmpMVec, expAmpMVec, "amp(MVec)");

		return oss.str();;
	}

	/*
	//! Check ### TODO
	std::string
	test1
		()
	{
		std::ostringstream oss;

			oss << "Failure of ### test\n";

		return oss.str();;
	}

	//! Check ### TODO
	std::string
	test2
		()
	{
		std::ostringstream oss;
			oss << "Failure of ### test\n";
		return oss.str();;
	}
	*/

}

//! Check behavior of g3 "amplitude" functions
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test0();
	// oss << test1();
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

