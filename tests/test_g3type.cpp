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

#include "g3type.hpp"

#include "g3compare.hpp"
#include "g3const.hpp"
#include "g3io.hpp"
#include "g3ops.hpp"

#include <iostream> // For test message output

#include <typeinfo>
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
	std::string
	assessValidityOf
		( Type const & item
		, std::string const & tname
		)
	{
		std::ostringstream oss;
		if (! g3::isValid(item))
		{
			oss << "assessment error\n";
			reportErrorFor(item, tname);
		}
		return oss.str();
	}

	//! Check if item is NOT valid and report error if appropriate
	template <typename Type>
	inline
	std::string
	assessInValidityOf
		( Type const & item
		, std::string const & tname
		)
	{
		std::ostringstream oss;
		if (  g3::isValid(item))
		{
			oss << "assessment error\n";
			reportErrorFor(item, tname);
		}
		return oss.str();
	}

	//! Code for documentation examples
	std::string
	test_ctor_examples
		()
	{
		std::ostringstream oss;

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

		// bad data i/o should produce null instances
		std::istringstream iss{ "a b c d e f g h %@ *(" };
		iss
			>> anUnsetScalar
			>> anUnsetVector
			>> anUnsetBiVector
			>> anUnsetTriVector
			>> anUnsetSpinor
			>> anUnsetImSpin
			;

		bool const allNull
			{  (! isValid(anUnsetScalar))
			&& (! isValid(anUnsetVector))
			&& (! isValid(anUnsetBiVector))
			&& (! isValid(anUnsetTriVector))
			&& (! isValid(anUnsetSpinor))
			&& (! isValid(anUnsetImSpin))
			};
		if (! allNull)
		{
			oss << "Failure of uninitialized bad extraction test\n";
		}

		// [DoxyExample02]

		// null value constructions
		g3::Scalar const aNullScalar{ g3::null<g3::Scalar>() };
		g3::Vector const aNullVector{ g3::null<g3::Vector>() };
		g3::BiVector const aNullBiVector{ g3::null<g3::BiVector>() };
		g3::TriVector const aNullTriVector{ g3::null<g3::TriVector>() };
		g3::Spinor const aNullSpinor{ g3::null<g3::Spinor>() };
		g3::ImSpin const aNullImSpin{ g3::null<g3::ImSpin>() };

			// [DoxyExample02]
		bool const nullOkay
			{  (! g3::isValid(aNullScalar))
			&& (! g3::isValid(aNullVector))
			&& (! g3::isValid(aNullBiVector))
			&& (! g3::isValid(aNullTriVector))
			&& (! g3::isValid(aNullSpinor))
			&& (! g3::isValid(aNullImSpin))
			};
		if (! nullOkay)
		{
			oss << "Failure of null validity test\n";
		}

		// [DoxyExample03]

		// null value constructions
		g3::Scalar const aZeroScalar{ g3::zero<g3::Scalar>() };
		g3::Vector const aZeroVector{ g3::zero<g3::Vector>() };
		g3::BiVector const aZeroBiVector{ g3::zero<g3::BiVector>() };
		g3::TriVector const aZeroTriVector{ g3::zero<g3::TriVector>() };
		g3::Spinor const aZeroSpinor{ g3::zero<g3::Spinor>() };
		g3::ImSpin const aZeroImSpin{ g3::zero<g3::ImSpin>() };

			// [DoxyExample03]

		bool okayZeroNull
			{  (! g3::nearlyEquals(aZeroScalar, aNullScalar))
			&& (! g3::nearlyEquals(aZeroVector, aNullVector))
			&& (! g3::nearlyEquals(aZeroBiVector, aNullBiVector))
			&& (! g3::nearlyEquals(aZeroTriVector, aNullTriVector))
			&& (! g3::nearlyEquals(aZeroSpinor, aNullSpinor))
			&& (! g3::nearlyEquals(aZeroImSpin, aNullImSpin))
			};
		if (! okayZeroNull)
		{
			oss << "Failure of zero/null compare test\n";
		}

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

		using g3::isValid;
		bool const allValid
			{  isValid(aScalar)
			&& isValid(aVector)
			&& isValid(aBiVector)
			&& isValid(aTriVector)
			&& isValid(aSpinor)
			&& isValid(aImSpin)
			&& isValid(buildSpinor)
			&& isValid(buildImSpin)
			};

		if (! allValid)
		{
//			oss << "Failure of data construction validity test\n";
		}

		return oss.str();
	}

	//! Check if default curly-brace construction produces valid instance.
	template <typename Type>
	std::string
	checkDefaultCtor
		( std::string const & tname
		)
	{
		std::ostringstream oss;
		Type const item{};
		oss << assessValidityOf(item, "default ctor: " + tname);
		return oss.str();
	}

	//! Check if Type can be used with container default construction
	template <typename Type>
	std::string
	checkCtorInContainer
		( std::string const & tname
		)
	{
		std::ostringstream oss;
		// STL containers only require copy constructable
		std::vector<Type> items(2u);
		for (Type const item : items)
		{
			oss << assessValidityOf(item, "container ctor: " + tname);
		}
		return oss.str();
	}

	//! Check instantiation of each type
	std::string
	test_ctor_default2
		()
	{
		std::ostringstream oss;

		// check default constructions - valid to use, but random content
		oss << checkDefaultCtor<g3::Scalar>("Scalar");
		oss << checkDefaultCtor<g3::Vector>("Vector");
		oss << checkDefaultCtor<g3::BiVector>("BiVector");
		oss << checkDefaultCtor<g3::TriVector>("TriVector");
		oss << checkDefaultCtor<g3::Spinor>("Spinor");
		oss << checkDefaultCtor<g3::ImSpin>("ImSpin");

		// STL containers only require copy constructable
		oss << checkCtorInContainer<g3::Scalar>("Scalar");
		oss << checkCtorInContainer<g3::Vector>("Vector");
		oss << checkCtorInContainer<g3::BiVector>("BiVector");
		oss << checkCtorInContainer<g3::TriVector>("TriVector");
		oss << checkCtorInContainer<g3::Spinor>("Spinor");
		oss << checkCtorInContainer<g3::ImSpin>("ImSpin");

		return oss.str();
	}

	//! Check that null construction produces invalid instance.
	template <typename Type>
	std::string
	checkNullCtor
		( std::string const & tname
		)
	{
		std::ostringstream oss;
		Type const item{ g3::null<Type>() };
		// null instances should never be valid
		oss << assessInValidityOf(item, "null construction: " + tname);
		return oss.str();
	}

	//! Check null instantiation for each type
	std::string
	test_ctor_null
		()
	{
		std::ostringstream oss;

		using namespace g3;

		// check default constructions
		oss << checkNullCtor<g3::Scalar>("Scalar");
		oss << checkNullCtor<g3::Vector>("Vector");
		oss << checkNullCtor<g3::BiVector>("BiVector");
		oss << checkNullCtor<g3::TriVector>("TriVector");
		oss << checkNullCtor<g3::Spinor>("Spinor");
		oss << checkNullCtor<g3::ImSpin>("ImSpin");

		return oss.str();
	}

	//! Check that zero construction produces valid instance
	template <typename Type>
	std::string
	checkZeroCtor
		( std::string const & tname
		)
	{
		std::ostringstream oss;
		Type const item{ g3::zero<Type>() };
		oss << assessValidityOf(item, "zero construction" + tname);
		return oss.str();
	}

	//! Check zero instantiation for each type
	std::string
	test_ctor_zero
		()
	{
		std::ostringstream oss;

		using namespace g3;

		// check default constructions
		oss << checkZeroCtor<g3::Scalar>("Scalar");
		oss << checkZeroCtor<g3::Vector>("Vector");
		oss << checkZeroCtor<g3::BiVector>("BiVector");
		oss << checkZeroCtor<g3::TriVector>("TriVector");
		oss << checkZeroCtor<g3::Spinor>("Spinor");
		oss << checkZeroCtor<g3::ImSpin>("ImSpin");

		return oss.str();
	}

	//! Check that common functions are present
	std::string
	test2
		()
	{
		std::ostringstream oss;

		return oss.str();
	}

}

//! Check behavior of TODO
int
main
	()
{
	int status{ tst::CTest::fail };
	std::stringstream oss;

	oss << test_ctor_examples();
	oss << test_ctor_default2();
	oss << test_ctor_null();
	oss << test_ctor_zero();
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

