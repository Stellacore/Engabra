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


#ifndef engabra_g3consts_INCL_
#define engabra_g3consts_INCL_

/*! \file
\brief Useful constants and standard entities (zero, unity, basis, etc).
*/


#include "g3types.hpp"

#include <cmath>


namespace engabra
{

namespace g3
{

	//
	// Constants
	//

	//! Classic value of Pi (consistent with gnu math library)
	constexpr double pi{ 3.141592653589793 };
	//! Convenience mnemonic for Pi/2.
	constexpr double piHalf{ .5 * pi };
	//! Convenience mnemonic for Pi/4.
	constexpr double piQtr{ .5 * piHalf };

	//! Angle associated with a full turn (rotation returning to start) [rad]
	constexpr double turnFull{ 2.*pi };
	//! Angle associated with a half turn (pointing opposite direction) [rad]
	constexpr double turnHalf{ pi };
	//! Angle associated with quarter turn (pointing orthogonal direction) [rad]
	constexpr double turnQtr{ piHalf };


	//
	// Zero values
	//

	//! Zero value instance of requested Type
	template <typename Type>
	constexpr
	Type
	zero
		()
	{
		return Type{ 0. };
	}

	// NOTE: Scalar handled by default template
	//! Zero as a Vector instance
	template <> constexpr Vector zero<Vector>()
		{ return Vector{ 0., 0., 0. }; }
	//! Zero as a BiVector instance
	template <> constexpr BiVector zero<BiVector>()
		{ return BiVector{ 0., 0., 0. }; }
	// NOTE: TriVector handled by default template


	//
	// Basis blades
	//

	// Scalar basis element - (unique)
	static Scalar const e0{ 1. }; //!< Magnitude [e.g. 'units' in use]

	// Vector basis elements - Mutually orthogonal, dextral and unitary
	static Vector const e1{ 1., 0., 0. }; //!< First direction [e.g. 'x' axis]
	static Vector const e2{ 0., 1., 0. }; //!< Second direction [e.g. 'y' axis]
	static Vector const e3{ 0., 0., 1. }; //!< Third direction [e.g. 'z' axis]

	// Bivector basis elements - Mutually orthogonal, dextral and unitary
	static BiVector const e23{ 1., 0., 0. }; //!< First plane [e.g. 'yz' plane]
	static BiVector const e31{ 0., 1., 0. }; //!< Second plane [e.g. 'zx' plane]
	static BiVector const e12{ 0., 0., 1. }; //!< Third plane [e.g. 'xy' plane]

	// Trivector basis element (unique in 3D)
	static TriVector const e123{ 1. }; //!< Volume [e.g. 'xyz' dextral cube]

} // [g3]

} // [engabra]


#endif // engabra_g3consts_INCL_
