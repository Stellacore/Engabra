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


#ifndef engabra_g3_private_INCL_
#define engabra_g3_private_INCL_

/*! \file
\brief Contains internal libary implementation support functions.

Example:
\snippet test_g3_private.cpp DoxyExample01

*/


namespace engabra
{

namespace g3
{

/*! \brief Engabra implementation detail private namespace.
*/
namespace priv
{
	//
	// Elementwise patterns
	//

	//! Element-by-element operation on same type (A (op) B)
	template <typename BladeType, typename Func>
	inline
	BladeType
	binaryElementByElement
		( BladeType const & bladeA
		, BladeType const & bladeB
		, Func const & op
		)
	{
		BladeType outBlade{}; // okay uninitialized, each element is filled
		std::transform
			( std::cbegin(bladeA.theData)
			, std::cend(bladeA.theData)
			, std::cbegin(bladeB.theData)
			, std::begin(outBlade.theData)
			, op
			);
		return outBlade;
	}

	//
	// Commutative product patterns
	//

	//! Commutative product - product of contraction
	inline
	double
	prodComm
		( std::array<double, 3u> const & argA
		, std::array<double, 3u> const & argB
		)
	{
		return std::inner_product
			( std::cbegin(argA)
			, std::cend(argA)
			, std::cbegin(argB)
			, 0.
			);
	}

	//! Specialization Commutative product for Scalar/TriVector support
	inline
	double
	prodComm
		( std::array<double, 1u> const & argA
		, std::array<double, 1u> const & argB
		)
	{
		return (argA[0] * argB[0]);
	}

	//
	// Anti-commutative product patterns
	//

	//! Anticommutative product - product of extension
	inline
	std::array<double, 3u>
	prodAnti
		( std::array<double, 3u> const & argA
		, std::array<double, 3u> const & argB
		)
	{
		return
			{ argA[1]*argB[2] - argA[2]*argB[1]
			, argA[2]*argB[0] - argA[0]*argB[2]
			, argA[0]*argB[1] - argA[1]*argB[0]
			};
	}


} // [priv]


} // [g3]

} // [engabra]


#endif // engabra_g3_private_INCL_
