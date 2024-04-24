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


#ifndef engabra_g3opsSub_Spinor_INCL_
#define engabra_g3opsSub_Spinor_INCL_

/*! \file
\brief Contains operator-() overloads for Spinor - {..., MulitVector}

\note All of these operations are anti-commutative such that (A-B)=-(B-A).

Example:
\snippet test_g3opsSub_other.cpp DoxyExampleSpin

*/


#include "g3opsSub_same.hpp"
#include "g3opsUni.hpp" // unary negation used frequently
#include "g3opsSub_Scalar.hpp"
#include "g3opsSub_BiVector.hpp"


namespace engabra
{

namespace g3
{
	//
	// "Backward" order: {other} - Spinor
	// -- redirect to forward op-() functions
	//

	//! Spinor from Spinor - Scalar
	inline
	Spinor
	operator-
		( Spinor const & spin
		, Scalar const & sca
		)
	{
		return sca - spin;
	}

	//TBD: NoTri from Spinor - Vector

	//! Spinor from Spinor - BiVector
	inline
	Spinor
	operator-
		( Spinor const & spin
		, BiVector const & biv
		)
	{
		return biv - spin;
	}

	//TBD: NoVec from Spinor - TriVector

	// -- Spinor from Spinor - Spinor : \ref g3opsSub_same.hpp

	//
	// "Forward" order: Spinor - {other}
	//

	//! MultiVector from Spinor - ImSpin
	inline
	MultiVector
	operator-
		( Spinor const & spin
		, ImSpin const & imsp
		)
	{
		return MultiVector
			{ spin.theSca
			, -imsp.theVec
			, spin.theBiv
			, -imsp.theTri
			};
	}

	//TBD: NoVec from Spinor - ComPlex

	//TBD: NoTri from Spinor - DirPlex

	//! MultiVector from Spinor - MultiVector
	inline
	MultiVector
	operator-
		( Spinor const & spin
		, MultiVector const & mv
		)
	{
		return MultiVector
			{ spin.theSca - mv.theSca
			, -mv.theVec
			, spin.theBiv - mv.theBiv
			, -mv.theTri
			};
	}

} // [g3]

} // [engabra]


#endif // engabra_g3opsSub_Spinor_INCL_
