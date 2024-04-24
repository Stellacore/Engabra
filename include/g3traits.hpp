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


#ifndef engabra_g3traits_INCL_
#define engabra_g3traits_INCL_

/*! \file
\brief Constructs useful for template constructions.

Example using helper types to qualify template instantiation:
\snippet test_g3traits_all.cpp DoxyExample00

\snippet test_g3traits_all.cpp DoxyExample01
*/


#include "g3type.hpp"

#include <type_traits>


namespace engabra
{

namespace g3
{

//! Type support namespace (e.g. as in "is [a ...]")
namespace is
{

	//
	// Type support
	//

	// For conditional template specializations based on enable_if_t,
	// ref: https://en.cppreference.com/w/cpp/types/enable_if
	/*
	template
		< typename Blade
		// second template arguments is "bool = true" for blades
		, std::enable_if_t<   g3::is::blade<Blade>::value, bool > = true
		>
	void foo() {}; // created only for blades

	// Instantiated for Not-A-Blade types (e.g. double, Spinor, Foo, ...)
	template
		< typename Blade
		// second template arguments is "! bool = true" for not blades
		, std::enable_if_t< ! g3::is::blade<Blade>::value, bool > = true
		>
	void foo() {}; // created only for Not-blades
	*/

	//! Any types not explicitly overridden are not a blade
	template <typename Type>
	struct blade : std::false_type
	{
	};

	//! Scalar is a blade (0-vector)
	template <> struct blade<Scalar> : std::true_type {};

	//! Vector is a blade (1-vector)
	template <> struct blade<Vector> : std::true_type {};

	//! BiVector is a blade (2-vector)
	template <> struct blade<BiVector> : std::true_type {};

	//! TriVector is a blade (3-vector)
	template <> struct blade<TriVector> : std::true_type {};

	//
	// Specific type tests
	//

	//! True for Scalar type (only)
	template <typename Type>
	struct Scalar : std::false_type
	{
	};
	//! True for Scalar argument (is::multiVector<...>)
	template <> struct Scalar<g3::Scalar> : std::true_type {};

	//! True for Vector type (only)
	template <typename Type>
	struct Vector : std::false_type
	{
	};
	//! True for Vector argument (is::multiVector<...>)
	template <> struct Vector<g3::Vector> : std::true_type {};

	//! True for BiVector type (only)
	template <typename Type>
	struct BiVector : std::false_type
	{
	};
	//! True for BiVector argument (is::multiVector<...>)
	template <> struct BiVector<g3::BiVector> : std::true_type {};

	//! True for TriVector type (only)
	template <typename Type>
	struct TriVector : std::false_type
	{
	};
	//! True for TriVector argument (is::multiVector<...>)
	template <> struct TriVector<g3::TriVector> : std::true_type {};

	//! True for Spinor type (only)
	template <typename Type>
	struct Spinor : std::false_type
	{
	};
	//! True for Spinor argument (is::multiVector<...>)
	template <> struct Spinor<g3::Spinor> : std::true_type {};

	//! True for ImSpin type (only)
	template <typename Type>
	struct ImSpin : std::false_type
	{
	};
	//! True for ImSpin argument (is::multiVector<...>)
	template <> struct ImSpin<g3::ImSpin> : std::true_type {};

	//! True for ComPlex type (only)
	template <typename Type>
	struct ComPlex : std::false_type
	{
	};
	//! True for ComPlex argument (is::multiVector<...>)
	template <> struct ComPlex<g3::ComPlex> : std::true_type {};

	//! True for DirPlex type (only)
	template <typename Type>
	struct DirPlex : std::false_type
	{
	};
	//! True for DirPlex argument (is::multiVector<...>)
	template <> struct DirPlex<g3::DirPlex> : std::true_type {};

	//! True for MultiVector type (only)
	template <typename Type>
	struct MultiVector : std::false_type
	{
	};
	//! True for MultiVector argument (is::multiVector<...>)
	template <> struct MultiVector<g3::MultiVector> : std::true_type {};

} // [is]

} // [g3]

} // [engabra]


#endif // engabra_g3traits_INCL_
