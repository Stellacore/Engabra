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


#include "test_common.hpp" // testing environment common utilities

#include "g3types.hpp"

#include "g3compare.hpp"
#include "g3consts.hpp"
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

	//! Code for documentation examples
	std::size_t
	test_ctor_examples
		()
	{
		std::size_t errCount{ 0u };

		// [DoxyExample01]

		// Example constructions - withOUT initialization
		//
		// Note that default ctors follow rules of aggregate initialization
		// (e.g. **NO** explicit initilization - may have arbitrary values)
		//
		g3::Scalar anUnsetScalar;  // NOT initialized, must be set later
		g3::Vector anUnsetVector;
		g3::BiVector anUnsetBiVector;
		g3::TriVector anUnsetTriVector;
		g3::Spinor anUnsetSpinor;
		g3::ImSpin anUnsetImSpin;

			// [DoxyExample01]


		// [DoxyExample02]

		// null value constructions
		g3::Scalar const aNullScalar{ g3::null<g3::Scalar>() };
		g3::Vector const aNullVector{ g3::null<g3::Vector>() };
		g3::BiVector const aNullBiVector{ g3::null<g3::BiVector>() };
		g3::TriVector const aNullTriVector{ g3::null<g3::TriVector>() };
		g3::Spinor const aNullSpinor{ g3::null<g3::Spinor>() };
		g3::ImSpin const aNullImSpin{ g3::null<g3::ImSpin>() };

			// [DoxyExample02]


		// [DoxyExample03]

		// null value constructions
		g3::Scalar const aZeroScalar{ g3::zero<g3::Scalar>() };
		g3::Vector const aZeroVector{ g3::zero<g3::Vector>() };
		g3::BiVector const aZeroBiVector{ g3::zero<g3::BiVector>() };
		g3::TriVector const aZeroTriVector{ g3::zero<g3::TriVector>() };
		g3::Spinor const aZeroSpinor{ g3::zero<g3::Spinor>() };
		g3::ImSpin const aZeroImSpin{ g3::zero<g3::ImSpin>() };

			// [DoxyExample03]

		// [DoxyExample04]

		// Explicit value constructions
		// numeric values here suggest (Dimension.Component)
		g3::Scalar const aScalar{ 0.0 };
		g3::Vector const aVector{ 1.0, 1.1, 1.2 };
		g3::BiVector const aBiVector{ 2.0, 2.1, 2.2 };
		g3::TriVector const aTriVector{ 3.0 };
		g3::Spinor const aSpinor{ 0.0,  2.0, 2.1, 2.2 };
		g3::ImSpin const aImSpin{ 1.0, 1.1, 1.2,  3.0 };

			// [DoxyExample04]


		// [DoxyExample05]

		// Composite type initialization with constituents
		g3::Spinor const buildSpinor{ aScalar, aBiVector };
		g3::ImSpin const buildImSpin{ aVector, aTriVector };

			// [DoxyExample05]

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

	errCount += test_ctor_examples();
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

