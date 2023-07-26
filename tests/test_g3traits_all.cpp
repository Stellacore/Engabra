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
\brief Unit tests (and example) code for engabra::g3traits
*/


#include "checks.hpp" // testing environment common utilities

#include "g3traits.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>
#include <utility>
#include <vector>


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;
	using g3::nearlyEquals;

	// [DoxyExample00]

	// Instantiated for Blade types (Scalar, Vector, BiVector, TriVector)
	template
		< typename Type
		// second template arguments is "bool = true" for (Type is blade)
		, std::enable_if_t<   g3::is::blade<Type>::value, bool > = true
		>
	bool isBladeType () { return true; }

	// Instantiated for Not-A-Blade types (e.g. double, Spinor, Foo, ...)
	template
		< typename Type
		// second template arguments is "! bool = true" for (Type not blade)
		, std::enable_if_t< ! g3::is::blade<Type>::value, bool > = true
		>
	bool isBladeType () { return false; }

		// [DoxyExample00]

	//! Test template constructions for blade and non-blade types
	std::string
	test0
		()
	{
		std::ostringstream oss;

		// [DoxyExample01]

		// "got" vs "expected" performance of above template functions
		using namespace engabra::g3;
		std::vector<std::pair<bool, bool> > const pairsGotExp
			{ { isBladeType<double>(), false }
			, { isBladeType<Scalar>(), true }
			, { isBladeType<Vector>(), true }
			, { isBladeType<BiVector>(), true }
			, { isBladeType<TriVector>(), true }
			, { isBladeType<Spinor>(), false }
			, { isBladeType<ImSpin>(), false }
			, { isBladeType<MultiVector>(), false }
			};

		// [DoxyExample01]

		// check if template instantiations are as expected
		for (std::pair<bool, bool> const & pairGotExp : pairsGotExp)
		{
			bool const & got = pairGotExp.first;
			bool const & exp = pairGotExp.second;
			if(! nearlyEquals(got, exp))
			{
				oss << "Failure of isBladeType test\n";
			}
		}

		// if some problem, then report detail info
		if (! oss.str().empty())
		{
			for (std::size_t ndx{0u} ; ndx < pairsGotExp.size() ; ++ndx)
			{
				bool const & got = pairsGotExp[ndx].first;
				bool const & exp = pairsGotExp[ndx].second;
				oss << " ndx:exp,got:"
					<< " " << ndx << ": " << exp << ", " << got << '\n';
			}
		}

		return oss.str();;
	}
}

//! Check behavior of traits
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

