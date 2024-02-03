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
\brief Unit tests (and example) code for engabra::validity
*/


#include "checks.hpp" // testing environment common utilities

#include "engabra.hpp"

#include <iostream> // For test message output


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;

	//! Check underlying null/validity construct
	std::string
	test0
		()
	{
		std::ostringstream oss;

		std::array<double, 3u> const null{ 1., 2., g3::nan };
		if (  g3::isValid(null))
		{
			oss << "Failure of good validity test" << std::endl;
		}

		std::array<double, 3u> const good{ 1., 2., 3. };
		if (! g3::isValid(good))
		{
			oss << "Failure of null validity test" << std::endl;
		}

		return oss.str();
	}

	//! Check underlying null/validity construct
	std::string
	test1
		()
	{
		std::ostringstream oss;

		// [DoxyExample01]

		// Basic null pattern usage example (illustration with 'double')
		double someValue{ g3::null<double>() }; // default to null (e.g. fail)
		someValue = 1.25; // simulate success of some computation
		// check value validity to know if success (any time later) 
		if (g3::isValid(someValue))
		{
			// operation/assignment was successful
		}

		// [DoxyExample01]
		else
		{
			oss << "Failure of 'example01' test\n";
		}

		// A null value tests to "not-isValid"
		double const aNullValue{ g3::null<double>() };
		bool const isNull(! g3::isValid(aNullValue));

		// Good values (including zero and any isnormal()) test "isValid"
		bool const isGood(  g3::isValid(1.25));


		if (! isNull)
		{
			// the default null value should not be valid
			oss << "Failure of 'isNull' test" << std::endl;
		}
		if (! isGood)
		{
			oss << "Failure of 'isGood' test" << std::endl;
		}

		// Be sure zero is considered a good
		if (! g3::isValid(0.))
		{
			oss << "Failure of 'isZero' test" << std::endl;
		}

		return oss.str();
	}

	//! Check underlying null/validity construct
	std::string
	test2
		()
	{
		std::ostringstream oss;
		// [DoxyExample02]

		g3::Scalar const nullScalar{ g3::null<g3::Scalar>() };
		g3::Vector const nullVector{ g3::null<g3::Vector>() };
		g3::BiVector const nullBiVector{ g3::null<g3::BiVector>() };
		g3::TriVector const nullTriVector{ g3::null<g3::TriVector>() };
		g3::Spinor const nullSpinor{ g3::null<g3::Spinor>() };
		g3::ImSpin const nullImSpin{ g3::null<g3::ImSpin>() };

		bool const allNull
			{  (! g3::isValid(nullScalar))
			&& (! g3::isValid(nullVector))
			&& (! g3::isValid(nullBiVector))
			&& (! g3::isValid(nullTriVector))
			&& (! g3::isValid(nullSpinor))
			&& (! g3::isValid(nullImSpin))
			};

		// [DoxyExample02]

		if (! allNull)
		{
			oss << "Failure of 'allNull' test for basic types\n";
		}

		return oss.str();
	}

}

//! Check behavior of TODO
int
main
	()
{
	int status{ tst::CTest::fail };
	std::ostringstream oss;

	oss << test0();
	oss << test1();
	oss << test2();

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

