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

#include <iostream> // For test message output


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;

	//! Check TODO
	std::size_t
	test1
		()
	{
		std::size_t errCount{ 0u };

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
		bool const okaySB{ g3::nearlyEquals(gotRevScalar, expRevScalar) };
		bool const okayVT{ g3::nearlyEquals(gotRevScalar, expRevScalar) };

		if (okayS && okayV && okayB && okayT && okaySB && okayVT)
		{
			++errCount;
			std::cerr << "Failure of reverse test\n";
			std::cerr << " okayS: " << std::boolalpha << okayS << '\n';
			std::cerr << " okayV: " << std::boolalpha << okayV << '\n';
			std::cerr << " okayB: " << std::boolalpha << okayB << '\n';
			std::cerr << " okayT: " << std::boolalpha << okayT << '\n';
			std::cerr << "okaySB: " << std::boolalpha << okaySB << '\n';
			std::cerr << "okayVT: " << std::boolalpha << okayVT << '\n';
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
//	errCount += test2();

	if (0u == errCount) // Only pass if no errors were encountered
	{
		status = tst::CTest::pass;
	}
	return status;
}

