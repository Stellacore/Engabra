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

Example:
\snippet test_g3traits.cpp DoxyExample01

*/


namespace engabra
{

namespace g3
{

	//
	// Type support
	//

	//! Any types not explicitly overridden are not a blade
	template <typename Type>
	struct is_blade : std::false_type
	{
	};

	//! Scalar is a 0-vector blade
	template <> struct is_blade<Scalar> : std::true_type {};

	//! Vector is a 1-vector blade
	template <> struct is_blade<Vector> : std::true_type {};

	//! BiVector is a 2-vector blade
	template <> struct is_blade<BiVector> : std::true_type {};

	//! TriVector is a 3-vector blade
	template <> struct is_blade<TriVector> : std::true_type {};

	//
	// Useful traits for implementation
	//

	//! True if argument is a Vector or BiVector or TriVector
	template <typename Type>
	struct is_SVBT : std::false_type
	{
	};
	template <> struct is_SVBT<Scalar> : std::true_type {};
	template <> struct is_SVBT<Vector> : std::true_type {};
	template <> struct is_SVBT<BiVector> : std::true_type {};
	template <> struct is_SVBT<TriVector> : std::true_type {};

	//! True if argument is a Vector or BiVector or TriVector
	template <typename Type>
	struct is_VBT : std::false_type
	{
	};
	template <> struct is_VBT<Vector> : std::true_type {};
	template <> struct is_VBT<BiVector> : std::true_type {};
	template <> struct is_VBT<TriVector> : std::true_type {};

	//! True if argument is a BiVector or TriVector
	template <typename Type>
	struct is_BT : std::false_type
	{
	};
	template <> struct is_BT<BiVector> : std::true_type {};
	template <> struct is_BT<TriVector> : std::true_type {};

	//! True if argument is a TriVector
	template <typename Type>
	struct is_T : std::false_type
	{
	};
	template <> struct is_T<TriVector> : std::true_type {};


} // [g3]

} // [engabra]


#endif // engabra_g3traits_INCL_
