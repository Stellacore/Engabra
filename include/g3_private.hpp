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
\brief Contains ######

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

} // [priv]


} // [g3]

} // [engabra]


#endif // engabra_g3_private_INCL_
