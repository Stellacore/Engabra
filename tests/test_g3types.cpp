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

#include "g3types.hpp"

#include "compare.hpp"
#include "g3io.hpp"

#include <iostream> // For test message output

#include <vector>


namespace
{
	// Keep test code focused on internal structure under main project name
	using namespace engabra;

	//! Report item (typeid)name and contents
	template <typename Type>
	inline
	void
	reportErrorFor
		( Type const & item
		, std::string const & msg = {}
		)
	{
		std::string const name{ typeid(item).name() };
		std::cout
			<< "Error"
			<< ": " << msg
			<< ": struct: " << name
			<< ": value: " << item
			<< std::endl;
	}

	//! Check if item is valid and report error if appropriate
	template <typename Type>
	inline
	void
	assessValidityOf
		( Type const & item
		, std::size_t * const & ptErrCount
		, std::string const & msg = {}
		)
	{
		if (! g3::isValid(item))
		{
			++(*ptErrCount);
			reportErrorFor(item, msg);
		}
	}

	//! Check if item is NOT valid and report error if appropriate
	template <typename Type>
	inline
	void
	assessInValidityOf
		( Type const & item
		, std::size_t * const & ptErrCount
		, std::string const & msg = {}
		)
	{
		if (  g3::isValid(item))
		{
			++(*ptErrCount);
			reportErrorFor(item, msg);
		}
	}

	//! Check instantiation of each type
	std::size_t
	test_ctor_default1
		()
	{
		std::size_t errCount{ 0u };

		// NOTE - for initial implementation, seems no need for this?
		/*
		// check default constructions
		g3::Scalar const aSca;
		g3::Vector const aVec;
		g3::BiVector const aBiv;
		g3::TriVector const aTri;
		g3::Spinor const aSpinor;
		g3::ImSpin const aImSpin;
		*/

		return errCount;
	}

	//! Check if default curly-brace construction produces valid instance.
	template <typename Type>
	std::size_t
	checkDefaultCtor
		()
	{
		std::size_t errCount{ 0u };
		Type const item{};
		assessValidityOf(item, &errCount, "default{} construction");
		return errCount;
	}

	//! Check if Type can be used with container default construction
	template <typename Type>
	std::size_t
	checkCtorInContainer
		()
	{
		std::size_t errCount{ 0u };
		// STL containers only require copy constructable
		std::vector<Type> items(2u);
		for (Type const item : items)
		{
			assessValidityOf(item, &errCount, "container default construction");
		}
		return errCount;
	}

	//! Check instantiation of each type
	std::size_t
	test_ctor_default2
		()
	{
		std::size_t errCount{ 0u };

		// check default constructions - valid to use, but random content
		errCount += checkDefaultCtor<g3::Scalar>();
		errCount += checkDefaultCtor<g3::Vector>();
		errCount += checkDefaultCtor<g3::BiVector>();
		errCount += checkDefaultCtor<g3::TriVector>();
		errCount += checkDefaultCtor<g3::Spinor>();
		errCount += checkDefaultCtor<g3::ImSpin>();

		// STL containers only require copy constructable
		errCount += checkCtorInContainer<g3::Scalar>();
		errCount += checkCtorInContainer<g3::Vector>();
		errCount += checkCtorInContainer<g3::BiVector>();
		errCount += checkCtorInContainer<g3::TriVector>();
		errCount += checkCtorInContainer<g3::Spinor>();
		errCount += checkCtorInContainer<g3::ImSpin>();

		return errCount;
	}

	//! Check that null construction produces invalid instance.
	template <typename Type>
	std::size_t
	checkNullCtor
		()
	{
		std::size_t errCount{ 0u };
		Type const item{ g3::null<Type>() };
		// null instances should never be valid
		assessInValidityOf(item, &errCount, "null construction");
		return errCount;
	}

	//! Check null instantiation for each type
	std::size_t
	test_ctor_null
		()
	{
		std::size_t errCount{ 0u };

		using namespace g3;

		// check default constructions
		errCount += checkNullCtor<g3::Scalar>();
		errCount += checkNullCtor<g3::Vector>();
		errCount += checkNullCtor<g3::BiVector>();
		errCount += checkNullCtor<g3::TriVector>();
		errCount += checkNullCtor<g3::Spinor>();
		errCount += checkNullCtor<g3::ImSpin>();

		return errCount;
	}

	//! Check that zero construction produces valid instance
	template <typename Type>
	std::size_t
	checkZeroCtor
		()
	{
		std::size_t errCount{ 0u };
		Type const item{ g3::zero<Type>() };
		assessValidityOf(item, &errCount, "zero construction");
		return errCount;
	}

	//! Check zero instantiation for each type
	std::size_t
	test_ctor_zero
		()
	{
		std::size_t errCount{ 0u };

		using namespace g3;

		// check default constructions
		errCount += checkZeroCtor<g3::Scalar>();
		errCount += checkZeroCtor<g3::Vector>();
		errCount += checkZeroCtor<g3::BiVector>();
		errCount += checkZeroCtor<g3::TriVector>();
		errCount += checkZeroCtor<g3::Spinor>();
		errCount += checkZeroCtor<g3::ImSpin>();

		return errCount;
	}

	//! Check that common functions are present
	std::size_t
	test2
		()
	{
		std::size_t errCount{ 0u };

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

	errCount += test_ctor_default1();
	errCount += test_ctor_default2();
	errCount += test_ctor_null();
	errCount += test_ctor_zero();
	errCount += test2();

	if (0u == errCount) // Only pass if no errors were encountered
	{
		status = tst::CTest::pass;
	}
	return status;
}

