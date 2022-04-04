/*

MIT License

Copyright (c) 2021 Stellacore Corporation

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/


#include "test_common.hpp" // testing environment common utilities

#include "g3io.hpp"

#include "g3compare.hpp"
#include "g3ops.hpp"

#include <iostream> // For test message output
#include <regex>
#include <sstream>
#include <vector>


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;
	using g3::nearlyEquals;

	std::string
	test0
		()
	{
		std::ostringstream oss;
		// [DoxyExample01]
		// Note: white space separators only (no special characters)
		std::istringstream iss{ "0.25 \t 2.1 2.2 2.3" };

		engabra::g3::Spinor spin; // uninitialized here
		iss >> spin; // filled with value if can be, else is set to null

		// perhaps some time later, can test if extraction was successful
		if (engabra::g3::isValid(spin))
		{
			// have a valid instance containing stream data
		}
			// [DoxyExample01]
		else
		{
			oss << "Failure of input stream example test\n";
		}

		return oss.str();
	}

	//! Check basicformatting
	std::string
	test1
		()
	{
		std::ostringstream oss;

		// Expected: default formatter should be <sign><3><.><6>
		std::string const expString
			{ "   -3.123400  -23.123400 -123.123400" };
		std::vector<double> const vals
			{   -3.1234
			,  -23.1234
			, -123.1234
			};

		// Format several values with formatter
		std::ostringstream msg;
		for (double const & val : vals)
		{
			msg << g3::io::fixed(val);
		}
		std::string const gotString{ msg.str() };

		if (! (gotString == expString))
		{
			oss << "Failure of g3::io::DoubleFormat test" << '\n';
			oss << "got: '" << gotString << "'\n";
			oss << "exp: '" << expString << "'\n";
		}

		return oss.str();
	}

	//! Remove the "[eE][+-][0-9]* " parts from string - hardcoded strip
	std::string
	removeEPartWithoutRegEx
		( std::string const & istr
		)
	{
		std::string ostr;
		std::size_t ndx{ 0u };
		for ( ; ndx < istr.size() ; ++ndx)
		{
			std::string::size_type const & inchar = istr[ndx];
			bool const isE
				{  ('e' == inchar)
				|| ('E' == inchar)
				};
			if (isE)
			{
				// skip until end of e-notation part
				for (std::size_t ntmp{ndx+1u} ; ntmp < istr.size() ; ++ntmp)
				{
					std::string::size_type const & tmpchar = istr[ntmp];
					// only worry about spaces for test cases
					bool const isSpace(' ' == tmpchar);
					if (isSpace)
					{
						break;
					}
				}
			}
			else
			{
				ostr += inchar;
			}
		}
		return ostr;
	}

	//! Remove the "[eE][+-][0-9]* " parts from string
	std::string
	removeEPart
		( std::string const & str
		)
	{
		return removeEPartWithoutRegEx(str);
		/*
		std::ostringstream oss;
		// Compile time (gcc10.1.0,linux) - very slow with <regex>
		//  4.4s  w/o regex constructor or regex_replace
		//  3.8s  w/o regex_replace
		//  1.6s  w/o any regular expression parts
		std::regex const rxEPart("e.[0-9]*");
		std::regex_replace
			( std::ostreambuf_iterator<char>(oss)
			, std::cbegin(str), std::cend(str)
			, rxEPart
			, std::string{} // replace with empty
			);
		return oss.str();
		*/
	}

	//! Check format operators
	std::string
	test2
		()
	{
		std::ostringstream oss;

		using namespace g3;
		Scalar const sca{ (1./2.) * Scalar{ 1. } };
		Vector const vec{ (1./1024.) * Vector{ 1. } };
		BiVector const biv{ (1024./1.) * BiVector{ 1. } };
		TriVector const tri{ (3./1.) * TriVector{ 1. } };

		// compute type overloads use the base op<<() functions
		Spinor const spin{ sca, biv };
		ImSpin const imsp{ vec, tri };
		MultiVector const mv{ sca, vec, biv, tri };

		std::ostringstream gotFix;
		gotFix << io::fixed(spin, 3u, 6u) << '\n';
		gotFix << io::fixed(imsp, 3u, 6u) << '\n';
		gotFix << io::fixed(mv, 3u, 6u) << '\n';

		// kind of a lame tests - rather arbitrary
		// just paste-here example to use as 'standard'
		std::ostringstream expFix;
		expFix <<
			"    0.500000   1024.000000    0.000000    0.000000\n"
			"    0.000977    0.000000    0.000000      3.000000\n"
			"    0.500000      0.000977    0.000000    0.000000   "
				"1024.000000    0.000000    0.000000      3.000000\n"
			;

		if (! (gotFix.str() == expFix.str()))
		{
			oss << "Failure of io:: fixed output test" << std::endl;
			oss << "exp:\n===\n" << expFix.str() << std::endl;
			oss << "got:\n===\n" << gotFix.str() << std::endl;
		}

		std::ostringstream gotSciFull;
		gotSciFull << io::enote(spin) << '\n';
		gotSciFull << io::enote(imsp) << '\n';
		gotSciFull << io::enote(mv) << '\n';

		std::ostringstream expSciFull;
		// example string with one standard library
		expSciFull <<
			" 5.000000000000000e-01   1.024000000000000e+03  "
				"0.000000000000000e+00  0.000000000000000e+00\n"
			" 9.765625000000000e-04  0.000000000000000e+00  "
				"0.000000000000000e+00   3.000000000000000e+00\n"
			" 5.000000000000000e-01   9.765625000000000e-04  "
				"0.000000000000000e+00  0.000000000000000e+00   "
				"1.024000000000000e+03  0.000000000000000e+00  "
				"0.000000000000000e+00   3.000000000000000e+00\n"
			;
		// Remove the "e*" part of numbers before comparison in order
		// to check only the number of digits (the trailing "e" portion
		// varies for different system libraries)
		std::string const expSciPart{ removeEPart(expSciFull.str()) };
		std::string const gotSciPart{ removeEPart(gotSciFull.str()) };

		if (! (gotSciPart == expSciPart))
		{
			oss << "Failure of io:: enotation output test" << std::endl;
			oss << "expFull:\n===\n" << expSciFull.str() << std::endl;
			oss << "gotFull:\n===\n" << gotSciFull.str() << std::endl;
			oss << "expPart:\n===\n" << expSciPart << std::endl;
			oss << "gotPart:\n===\n" << gotSciPart << std::endl;
		}

		return oss.str();;
	}

	//! Check basic input operations
	std::string
	test3
		()
	{
		std::ostringstream oss;

		using namespace g3;

		// expected values
		Vector const expVec{ 1.1, 1.2, 1.3 };
		BiVector const expBiv{ 2.1, 2.2, 2.3 };
		ImSpin const expImsp{ expVec * expBiv };
		Spinor const expSpin{ expImsp * e123 };
//		MultiVector const expMV(expImsp + expSpin);
		MultiVector const expMV(expSpin);

		// use operator<<() to place values in output stream
		std::ostringstream oflow;
		// incorporate some white space into test
		std::string const wspc{ "  \t \n " };
		// use full e-notation precision to allow comparison below
		oflow << wspc << io::enote(expVec) << wspc;
		oflow << wspc << io::enote(expBiv) << wspc;
		oflow << wspc << io::enote(expImsp) << wspc;
		oflow << wspc << io::enote(expSpin) << wspc;
		oflow << wspc << io::enote(expMV) << wspc;
		
		// use operator>>() to extract values from input stream
		std::istringstream iflow{ oflow.str() };
		Vector gotVec; // define (unitialized) space where to place values
		BiVector gotBiv;
		ImSpin gotImsp;
		Spinor gotSpin;
		MultiVector gotMV;
		iflow >> gotVec >> gotBiv >> gotImsp >> gotSpin >> gotMV;

		// for this test, expect result to be valid and same as output
		constexpr double tol{ 4. * std::numeric_limits<double>::epsilon() };
		if (! (isValid(gotVec) && nearlyEquals(gotVec, expVec, tol)))
		{
			oss << "Failure of Vec extraction operator test\n";
			oss << "expVec: " << expVec << '\n';
			oss << "gotVec: " << gotVec << '\n';
		}
		if (! (isValid(gotBiv) && nearlyEquals(gotBiv, expBiv, tol)))
		{
			oss << "Failure of Biv extraction operator test\n";
			oss << "expBiv: " << expBiv << '\n';
			oss << "gotBiv: " << gotBiv << '\n';
		}
		if (! (isValid(gotImsp) && nearlyEquals(gotImsp, expImsp, tol)))
		{
			oss << "Failure of Imsp extraction operator test\n";
			ImSpin const difImsp{ gotImsp - expImsp };
			oss << "expImsp: " << expImsp << '\n';
			oss << "gotImsp: " << gotImsp << '\n';
			oss << "difImsp: " << io::fixed(difImsp,3u,21u) << '\n';
		}
		if (! (isValid(gotSpin) && nearlyEquals(gotSpin, expSpin, tol)))
		{
			oss << "Failure of Spin extraction operator test\n";
			oss << "expSpin: " << expSpin << '\n';
			oss << "gotSpin: " << gotSpin << '\n';
		}
		if (! (isValid(gotMV) && nearlyEquals(gotMV, expMV, tol)))
		{
			oss << "Failure of MV extraction operator test\n";
			oss << "expMV: " << expMV << '\n';
			oss << "gotMV: " << gotMV << '\n';
		}

		// partial completion test
		std::istringstream buf{ "1., 2. " }; // not enough to fill a vector
		Vector badVec;
		buf >> badVec;
		if (  isValid(badVec))
		{
			oss << "Failure of badVec test\n";
		}

		return oss.str();;
	}

}

//! Check behavior of TODO
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test0();
	oss << test1();
	oss << test2();
	oss << test3();

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

