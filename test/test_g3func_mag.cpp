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
	// Keep test code focused on internal structure under main project name
	using namespace engabra;
	using g3::nearlyEquals;

	//! Compute magnitude via full multivector operations
	template <typename Type>
	inline
	double
	expMag
		( Type const & item
		)
	{
		return magnitude(g3::MultiVector(item));
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

		double const gotMag_sca{ magnitude(sca) };
		double const gotMag_vec{ magnitude(vec) };
		double const gotMag_biv{ magnitude(biv) };
		double const gotMag_tri{ magnitude(tri) };
		double const gotMag_spin{ magnitude(spin) };
		double const gotMag_imsp{ magnitude(imsp) };
		double const gotMag_cplx{ magnitude(cplx) };
		double const gotMag_dplx{ magnitude(dplx) };
		double const gotMag_mvec{ magnitude(mvec) };

		// [DoxyExample01]

		// first confirm multivector magnitude operation
		double const mvec_magSq
			{ sq(2.)
			+ sq(3.) + sq(5.) + sq(7.)
			+ sq(11.) + sq(13.) + sq(17.)
			+ sq(23.)
			};
		double const mvec_mag{ std::sqrt(mvec_magSq) };
		tst::checkGotExp(oss, magSq(mvec), mvec_magSq, "mv magSq verify");
		tst::checkGotExp(oss, gotMag_mvec, mvec_mag, "mv mag verify");

		// use multivector magnitude to test others - via expMag()
		double const expMag_sca{ expMag(sca) };
		double const expMag_vec{ expMag(vec) };
		double const expMag_biv{ expMag(biv) };
		double const expMag_tri{ expMag(tri) };
		double const expMag_spin{ expMag(spin) };
		double const expMag_imsp{ expMag(imsp) };
		double const expMag_cplx{ expMag(cplx) };
		double const expMag_dplx{ expMag(dplx) };
		double const expMag_mvec{ expMag(mvec) };

		tst::checkGotExp(oss, gotMag_sca, expMag_sca, "magnitude(sca)");
		tst::checkGotExp(oss, gotMag_vec, expMag_vec, "magnitude(vec)");
		tst::checkGotExp(oss, gotMag_biv, expMag_biv, "magnitude(biv)");
		tst::checkGotExp(oss, gotMag_tri, expMag_tri, "magnitude(tri)");
		tst::checkGotExp(oss, gotMag_spin, expMag_spin, "magnitude(spin)");
		tst::checkGotExp(oss, gotMag_imsp, expMag_imsp, "magnitude(imsp)");
		tst::checkGotExp(oss, gotMag_cplx, expMag_cplx, "magnitude(cplx)");
		tst::checkGotExp(oss, gotMag_dplx, expMag_dplx, "magnitude(dplx)");
		tst::checkGotExp(oss, gotMag_mvec, expMag_mvec, "magnitude(mvec)");

		// check magSq() function explicitly as well
		double const tol{ 2. * std::numeric_limits<double>::epsilon() };
		tst::checkGotExp(oss, magSq(sca), sq(expMag_sca), "magSq(sca)", tol);
		tst::checkGotExp(oss, magSq(vec), sq(expMag_vec), "magSq(vec)", tol);
		tst::checkGotExp(oss, magSq(biv), sq(expMag_biv), "magSq(biv)", tol);
		tst::checkGotExp(oss, magSq(tri), sq(expMag_tri), "magSq(tri)", tol);
		tst::checkGotExp(oss, magSq(spin), sq(expMag_spin), "magSq(spin)", tol);
		tst::checkGotExp(oss, magSq(imsp), sq(expMag_imsp), "magSq(imsp)", tol);
		tst::checkGotExp(oss, magSq(cplx), sq(expMag_cplx), "magSq(cplx)", tol);
		tst::checkGotExp(oss, magSq(dplx), sq(expMag_dplx), "magSq(dplx)", tol);
		tst::checkGotExp(oss, magSq(mvec), sq(expMag_mvec), "magSq(mvec)", tol);

		return oss.str();;
	}

}

//! Check behavior of magnitude functions
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

