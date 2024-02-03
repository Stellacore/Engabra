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
\brief Unit tests (and example) code for engabra::g3func
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

	//! Check inverse function evaluation for this instance
	template <typename Type>
	void
	checkInverse
		( std::ostream & ostrm
		, Type const & fwd
		, std::string const & title
		, double const & tol = std::numeric_limits<double>::epsilon()
		)
	{
		Type const inv{ engabra::g3::inverse<Type>(fwd) };

		using namespace engabra::g3;

		// perform test with full multivector type
		// (although inverse is same grade as original object, the
		// following test code multiplication (e.g. fwd*inv) can
		// produce different grades)
		MultiVector const mvFwd(fwd); // cast to multivector
		MultiVector const mvInv(inv); // cast to multivector
		MultiVector const gotFI{ mvFwd * mvInv };
		MultiVector const gotIF{ mvInv * mvFwd };
		static MultiVector const expIdent(one<MultiVector>());
		MultiVector const & expFI = expIdent;
		MultiVector const & expIF = expIdent;
		if (! nearlyEquals(gotFI, expIdent, tol))
		{
			ostrm << "Failure of inverse " << title << " test\n";
			ostrm << "fwd: " << fwd << '\n';
			ostrm << "inv: " << inv << '\n';
			ostrm << "gotFI:" << gotFI << '\n';
			ostrm << "gotFI:" << io::enote(gotFI, 5u) << '\n';
			ostrm << "expFI:" << io::enote(expFI, 5u) << '\n';
			ostrm << "  tol:" << io::enote(tol, 5u) << '\n';
		}
		if (! nearlyEquals(gotFI, expIdent, tol))
		{
			ostrm << "Failure of inverse " << title << " test\n";
			ostrm << "fwd: " << fwd << '\n';
			ostrm << "inv: " << inv << '\n';
			ostrm << "gotIF:" << gotIF << '\n';
			ostrm << "gotIF:" << io::enote(gotIF, 5u) << '\n';
			ostrm << "expIF:" << io::enote(expIF, 5u) << '\n';
			ostrm << "  tol:" << io::enote(tol, 5u) << '\n';
		}
	}

	//! Examples for documentation
	std::string
	test0
		()
	{
		std::ostringstream oss;

		// [DoxyExample01]

		using namespace g3;

		// An algebraic inverse available for any object for which
		// the amplitude is non-zero.
		// E.g. for which magSq(amp(Item)) is not zero.

		// Here, demonstrate inverse for a multivector instance
		Scalar const sca{ 0.1 };
		Vector const vec{ 1.1, 1.2, 1.3 };
		BiVector const biv{ 2.1, 2.2, 2.3 };
		TriVector const tri{ 3.1 };
		MultiVector const mvFwd{ sca, vec, biv, tri };

		MultiVector const mvInv{ inverse<MultiVector>(mvFwd) };
		// validity of return indicates if inverse exists
		bool const hasInverse{ isValid(mvInv) };

		// [DoxyExample01]

		double const tol{ 2. * std::numeric_limits<double>::epsilon() };
		checkInverse(oss, sca, "inv(sca)", tol);
		checkInverse(oss, vec, "inv(vec)", tol);
		checkInverse(oss, biv, "inv(biv)", tol);
		checkInverse(oss, tri, "inv(tri)", tol);

		if (! hasInverse)
		{
			oss << "Failure of mvFwd inverse validity test\n";
			oss << "mvFwd: " << mvFwd << '\n';
			oss << "mvInv: " << mvInv << '\n';
		}
		else
		{
			checkInverse(oss, mvFwd, "inv(mvFwd)", tol);
		}

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

//! Check behavior of algebraic inverse functions
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

