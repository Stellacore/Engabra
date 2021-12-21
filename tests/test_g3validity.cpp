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


#include "test_common.hpp" // testing environment common utilities

#include "engabra.hpp"

#include <iostream> // For test message output


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;

	//! Check underlying null/validity construct
	std::size_t
	test1
		()
	{
		std::size_t errCount{ 0u };

		// [DoxyExample01]
		// Basic null pattern usage example (illustration with 'double')
		double someValue{ g3::null<double>() }; // default to 'null'
		someValue = 1.25; // simulate success of some computation
		if (g3::isValid(someValue)) // test if returned values is usable
		{
			// operation/assignment was successful
		}

		// [DoxyExample01]
		else
		{
			++errCount;
			std::cerr << "Failure of 'example01' test\n";
		}

		// A null value tests to "not-isValid"
		double const aNullValue{ g3::null<double>() };
		bool const isNull(! g3::isValid(aNullValue));

		// Good values (including zero and any isnormal()) test "isValid"
		bool const isGood(  g3::isValid(1.25));


		if (! isNull)
		{
			// the default null value should not be valid
			++errCount;
			std::cerr << "Failure of 'isNull' test" << std::endl;
		}
		if (! isGood)
		{
			++errCount;
			std::cerr << "Failure of 'isGood' test" << std::endl;
		}

		// Be sure zero is considered a good
		if (! g3::isValid(0.))
		{
			++errCount;
			std::cerr << "Failure of 'isZero' test" << std::endl;
		}

		return errCount;
	}

	//! Check underlying null/validity construct
	std::size_t
	test2
		()
	{
		std::size_t errCount{ 0u };
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
			++errCount;
			std::cerr << "Failure of 'allNull' test for basic types\n";
		}

		return errCount;
	}

}

//! Check behavior of TODO
int
main
	()
{
	int status{ tst::CTest::fail };
	std::size_t errCount{ 0u };

	errCount += test1();
	errCount += test2();

	if (0u == errCount) // Only pass if no errors were encountered
	{
		status = tst::CTest::pass;
	}
	return status;
}

