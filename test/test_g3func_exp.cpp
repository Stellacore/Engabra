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
\brief Unit tests (and example) code for engabra::g3::exp()

Test results by comparing result of the library function with a 
brute-force series expansion evaluation.

*/


#include "checks.hpp" // testing environment common utilities

#include <iostream> // TODO - remove
#include "g3func.hpp"

#include "g3compare.hpp"
#include "g3io.hpp"

#include <iostream>
#include <sstream>
#include <vector>


namespace
{

using namespace engabra;

// computeExp convergence limit and test tolerance (3 bits for compute noise)
constexpr double sSmallMag{ 8. * std::numeric_limits<double>::epsilon() };

//! Evaluate exponential function by brute-force series evaluation
g3::MultiVector
computeExp
	( engabra::g3::MultiVector const & mvArg
	)
{
	g3::MultiVector result{ g3::null<g3::MultiVector>() };

	if (isValid(mvArg))
	{

		// note that (exp(A)*exp(B)=exp(A+B) if multivectors A and B commute
		// For A'=(1/2)A, A=A'+A'=A'+B'. Thus, exp(A)=exp(A'+B')=exp(A')*exp(B')
		// where B'(=A'). Since A' necessarily commutes with itself, the 
		// sum A'+A' leads to a product of 2 terms exp(A')*exp(A') in the exp().
		// This process can be repeated recursively until the next iteration's
		// magnitude of A' is sufficiently small that the series terms converge
		// rapidly.  This series value can then be repeately squared to 'undo'
		// the sequence of argument halvings.
		constexpr bool useReduction{ true };

		// reduce argument by integer number of halves until small.
		g3::MultiVector tmpArg{ mvArg };
		std::size_t nHalves{ 0 };
		if (useReduction)
		{
			while (0.5 < magnitude(tmpArg))
			{
				tmpArg = .5 * tmpArg;
				++nHalves;
			}
		}

		// summation and product accumulators for series and sequence terms
		g3::MultiVector expSum{ g3::zero<g3::MultiVector>() };

		// 'k=0' arg^0/0!
		std::size_t seriesNdx{ 0u };
		g3::MultiVector nextTerm{ g3::one<g3::MultiVector>() };
		expSum = expSum + nextTerm;   // sum at k=1 term now (1)

		// 'k=1' arg^1/1!
		++seriesNdx;
		nextTerm = tmpArg;
		expSum = expSum + nextTerm;   // sum at k=1 term now (1 + arg)

		bool converged{ false };
		std::size_t nTerms{ 0u };
		while (! converged)
		{
			// compute next term in the series
			++seriesNdx; // increment to next factor in factorial term

			// note: reall should accumulate in reverse order to
			// improve precision of sum

			// accumulate (arg^k) power term in numerator
			nextTerm = nextTerm * tmpArg;
			// accumluate (k!) factorial in denominator
			nextTerm = (1./static_cast<double>(seriesNdx)) * nextTerm;

			// estimate Taylor series residual (before accumulating next term)
			g3::MultiVector const taylorResid{ expSum * nextTerm };

			// update running sum - accumulate series summation into expSum
			expSum = expSum + nextTerm;

			// check relative estimated Taylor series residual for convergence
			if((magnitude(taylorResid)/magnitude(expSum)) < sSmallMag)
			{
				converged = true;
			}

			// note number of terms and check against non-convergence case
			++nTerms;
			if (55u < nTerms) // essentially number of bits in a double
			{
				break; // "converged" is false at this point
			}
		}

		// check if iterative process has converged
		// then rescale intermediate result for full return value
		if (converged)
		{
			// square expSum value by nHalves number of times 
			// to compensate for nHalves initial down-scaling of tmpArg
			if (useReduction)
			{
				for (std::size_t ii{0u} ; ii < nHalves ; ++ii)
				{
					expSum = expSum * expSum;
				}
			}
			result = expSum;
		}
	}

	return result;
}

} // [anon]


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

		// trivial example computing "exp(I*pi)".
		g3::MultiVector const mvSome{ 0., 0., 0., 0., 0., 0., 0., g3::pi };
		g3::MultiVector const gotVal{ g3::exp(mvSome) }; // expect '-1'

		// [DoxyExample01]

		g3::MultiVector const expVal{ computeExp(mvSome) };
		if (! g3::nearlyEquals(gotVal, expVal, sSmallMag))
		{
			g3::MultiVector const difVal{ gotVal - expVal };
			oss << "Failure of simple exponentiation test\n";
			oss << "expVal: " << expVal << '\n';
			oss << "gotVal: " << gotVal << '\n';
			oss << "difVal: " << g3::io::enote(difVal) << '\n';
			oss << "tolVal: " << g3::io::enote(sSmallMag) << '\n';
		}

		/*
		std::cout << '\n';
		std::cout << "mvSome: " << mvSome << '\n';
		std::cout << "expVal: " << expVal << '\n';
		std::cout << "gotVal: " << gotVal << '\n';
		*/


		return oss.str();;
	}

	//! Check exponentiation (against brute force series eval)
	bool
	check
		( std::ostream & oss
		, g3::MultiVector const & mvSome
		, std::string const & tname
		)
	{
		bool okay{ true }; // be optimistic
		g3::MultiVector const gotVal{ g3::exp(mvSome) };
		g3::MultiVector const expVal{ computeExp(mvSome) };
		if (! g3::nearlyEquals(gotVal, expVal, sSmallMag))
		{
			g3::MultiVector const difVal{ gotVal - expVal };
			oss << "Failure of exponentiation test: '" << tname << "'\n";
			oss << "expVal: " << expVal << '\n';
			oss << "gotVal: " << gotVal << '\n';
			oss << "difVal: " << g3::io::enote(difVal) << '\n';
			oss << "tolVal: " << g3::io::enote(sSmallMag) << '\n';
			okay = false;
		}
		return okay;
	}

	//! Check ### TODO
	std::string
	test1
		()
	{
		std::ostringstream oss;
		using namespace engabra::g3;

		// collection of test values
		std::vector<std::pair<MultiVector, std::string> > const mvs
			{ std::make_pair(zero<MultiVector>(), "zero")
			, std::make_pair(MultiVector(e0), "scalar(e0)")
			, std::make_pair(MultiVector(e1), "vector(e1)")
			, std::make_pair(MultiVector(e2), "vector(e2)")
			, std::make_pair(MultiVector(e3), "vector(e3)")
			, std::make_pair(MultiVector(e23), "bivector(e23)")
			, std::make_pair(MultiVector(e31), "bivector(e31)")
			, std::make_pair(MultiVector(e12), "bivector(e12)")
			, std::make_pair(MultiVector(e123), "trivector(e123)")
			};

		for (std::pair<MultiVector, std::string> const & mv : mvs)
		{
			bool const okay{ check(oss, mv.first, mv.second) };
			if (! okay)
			{
				oss << "Failure of special value exponentiation test\n";
//				break;
			}
		}

		return oss.str();;
	}

}

//! Check behavior of 
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test0();
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

