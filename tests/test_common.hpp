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


#include "g3compare.hpp"

#include <iostream>
#include <limits>
#include <string>


//! Code common to unit testing infrastructure
namespace tst
{
	/*! CTest (by default) checks for these main return values
	 *
	 * An environment variable can be set (before running ctest) to
	 * have CTest report output from test programs on failure. E.g.
	 * \arg $ make && CTEST_OUTPUT_ON_FAILURE=1 ctest
	 * \arg $ make && CTEST_OUTPUT_ON_FAILURE=1 bash -c 'ctest <args> <etc>'
	 *
	 */
	struct CTest
	{
		static constexpr int pass{ 0 }; // main() return for success
		static constexpr int fail{ 1 }; // main() return for test failure
	};

	//! Compare 'got' results with 'expected' value - if error, put to stream
	void
	checkGotExp
		( std::ostream & ostrm
		, double const & got
		, double const & exp
		, std::string const & title
		, double const & tol = { std::numeric_limits<double>::epsilon() }
		)
	{
		if (! engabra::g3::nearlyEquals(got, exp, tol))
		{
			ostrm << "Failure of " << title << " test\n";
			ostrm << "exp: " << exp << std::endl;
			ostrm << "got: " << got << std::endl;
		}
	}

}

