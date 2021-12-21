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


#ifndef engabra_g3opsUni_INCL_
#define engabra_g3opsUni_INCL_

/*! \file
\brief Contains unitary operator functions for basic types

This file provides operator that act on a single entity of any GA type.
\arg negation (additive inverse)
\arg reverse (often denoted with a dagger or tilde)

esage and behavior of the reverse() and unitary negation operator is
demonstrated in this section of unit test code.
\snippet test_g3opsUni.cpp DoxyExample01

*/

/* TODO? TBD
\arg conjugate
\arg involute
*/

#include "g3types.hpp"

#include <algorithm>

namespace engabra
{

namespace g3
{

	//
	// Unitary negation
	//

	//! Unitary negation
	template <typename Blade>
	inline
	Blade
	operator-
		( Blade const & anyBlade
		)
	{
		Blade outBlade{}; // okay uninitialized, each element is filled
		std::transform
			( std::cbegin(anyBlade.theData)
			, std::cend(anyBlade.theData)
			, std::begin(outBlade.theData)
			, [] (double const & elem) { return -elem; }
			);
		return outBlade;
	}

	//! Specialization - Unitary negation (Spinor)
	inline
	Spinor
	operator-
		( Spinor const & anySpin
		)
	{
		return Spinor{ anySpin.theSca, -anySpin.theBiv };
	}

	//
	// Unitary reversion
	//

	//! Reverse of Scalar (is same as input)
	inline
	Scalar
	reverse
	(Scalar const & blade)
	{
		return blade;
	}

	//! Reverse of Vector (is same as input)
	inline
	Vector
	reverse
		(Vector const & blade)
	{
		return blade;
	}

	//! Reverse of BiVector (negates the input)
	inline
	BiVector
	reverse
		(BiVector const & blade)
	{
		return -blade;
	}

	//! Reverse of TriVector (negates the input)
	inline
	TriVector
	reverse
		(TriVector const & blade)
	{
		return -blade;
	}

	//! Reverse of Spinor (same scalar, negative bivector)
	inline
	Spinor
	reverse
		(Spinor const & spin)
	{
		return Spinor{spin.theSca, -spin.theBiv};
	}

	//! Reverse of ImSpin (same vector, negative trivector)
	inline
	ImSpin
	reverse
		(ImSpin const & imsp)
	{
		return ImSpin{imsp.theVec, -imsp.theTri};
	}

	//
	// TODO - perhaps add conjugation an involution?
	//

} // [g3]

} // [engabra]


#endif // engabra_g3opsUni_INCL_
