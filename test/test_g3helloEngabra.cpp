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

#include <Engabra> // require top level include file(s)

#include "checks.hpp" // Require test environment to be present

#include <iostream> // classic 'hello' style reporting


namespace
{

	//! Examples for documentation
	std::string
	test0
		()
	{
		std::ostringstream oss;

		// [DoxyExample01]

		std::string const gotVer{ engabra::projectVersion() };
		std::string const gotSid{ engabra::sourceIdentity() };

		// [DoxyExample01]

		constexpr std::string::value_type aDot('.');
		constexpr long int expDotCount{ 2u };
		long int const gotDotCount
			{ std::count(gotVer.cbegin(), gotVer.cend(), aDot) };
		if (! (gotDotCount == expDotCount))
		{
			oss << "Failure of projectVersion string test\n";
			oss << "expDotCount: " << expDotCount << '\n';
			oss << "gotDotCount: " << gotDotCount << '\n';
			oss << "     gotVer: '" << gotVer << "'\n";
		}

		std::string const tagStart("t_");
		bool const gotTagStart{ std::string::npos != gotSid.find(tagStart) };
		if (! gotTagStart)
		{
			oss << "Failure of sourceIdentity string test\n";
			oss << " got: '" << gotSid << "'\n";
			oss << "    : perhaps need git config to enable 'git describe'\n";
			oss << "    : with command similar to:\n";
			oss << "    : 'git config "
				"--global --add safe.directory /repos/Engabra'" << '\n';
		}

		return oss.str();;
	}

} // [anon]

/*! Trivial test program to demonstrate Engabra build/test environment.
 */
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

