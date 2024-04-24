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


#ifndef engabra_g3opsSub_BiVector_INCL_
#define engabra_g3opsSub_BiVector_INCL_

/*! \file
\brief Contains operator-() overloads for BiVector-{...} and {...}-BiVector

\note All of these operations are anti-commutative such that (A-B)=-(B-A).

Example:
\snippet test_g3opsSub_other.cpp DoxyExampleBiv

*/


#include "g3opsSub_same.hpp"
#include "g3opsUni.hpp" // unary negation used frequently
#include "g3opsSub_Scalar.hpp"
#include "g3opsSub_Vector.hpp"


namespace engabra
{

namespace g3
{
	//
	// "Backward" order: {other} - BiVector
	// -- redirect to forward op-() functions
	//

	//! Spinor from BiVector - Scalar
	inline
	Spinor
	operator-
		( BiVector const & biv
		, Scalar const & sca
		)
	{
		return sca - biv;
	}

	//! DirPlex from BiVector - Vector
	inline
	DirPlex
	operator-
		( BiVector const & biv
		, Vector const & vec
		)
	{
		return vec - biv;
	}

	// -- BiVector from BiVector - BiVector : \ref g3opsSub_same.hpp

	//
	// "Forward" order: BiVector - {other}
	//

	//TBD: ImPara from BiVector - TriVector

	//! Spinor from BiVector - Spinor
	inline
	Spinor
	operator-
		( BiVector const & biv
		, Spinor const & spin
		)
	{
		return Spinor{ -spin.theSca, biv - spin.theBiv };
	}

	//TBD: NoVec from BiVector - ComPlex

	//! DirPlex from BiVector - DirPlex
	inline
	DirPlex
	operator-
		( BiVector const & biv
		, DirPlex const & dplx
		)
	{
		return DirPlex{ -dplx.theVec, biv - dplx.theBiv };
	}

	//! MultiVector from BiVector - MultiVector
	inline
	MultiVector
	operator-
		( BiVector const & biv
		, MultiVector const & mv
		)
	{
		return MultiVector
			{ -mv.theSca
			, -mv.theVec
			, biv - mv.theBiv
			, -mv.theTri
			};
	}

} // [g3]

} // [engabra]


#endif // engabra_g3opsSub_BiVector_INCL_
