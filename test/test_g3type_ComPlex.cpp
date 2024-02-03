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
\brief Unit tests (and example) code for engabra::g3type
*/


#include "checks.hpp" // testing environment common utilities

#include "g3type.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>


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

		// interaction with std::complex<double>
		using namespace engabra::g3;
		ComPlex const exp{ Scalar{ 1. }, TriVector{ 3. } };
		std::complex<double> const z1{ exp.theSca[0], exp.theTri[0] };
		ComPlex const got{ ComPlex::from(z1) };
		std::complex<double> const z2
			{ static_cast<std::complex<double> >(got) };

		// access individual indices
		double const & reVal = got[0];
		double const & imVal = got[1];

			// [DoxyExample01]

		// casting should be numerically exact !
		if (! ((reVal == std::real(z1)) && (imVal == std::imag(z1))) )
		{
			oss << "Failure of index component test\n";
			oss << "z1: " << z1 << '\n';
			oss << "reVal: " << reVal << '\n';
			oss << "imVal: " << imVal << '\n';
		}

		if (! (z2 == z1)) // casting should be exact
		{
			oss << "Failure of std::complex z2==z1 test\n";
			oss << "z1: " << z1 << '\n';
			oss << "z2: " << z2 << '\n';
		}

		// check ComPlex conversion results
		tst::checkGotExp(oss, got, exp, "exp==got");

		return oss.str();;
	}

}

//! Check behavior of type::ComPlex
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test0();

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

