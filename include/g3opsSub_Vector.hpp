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


#ifndef engabra_g3opsSub_Vector_INCL_
#define engabra_g3opsSub_Vector_INCL_

/*! \file
\brief Contains operator-() overloads for Vector-{...} and {...}-Vector

\note All of these operations are anti-commutative such that (A-B)=-(B-A).

Example:
\snippet test_g3opsSub_other.cpp DoxyExampleVec

*/


#include "g3opsSub_same.hpp"
#include "g3opsUni.hpp" // unary negation used frequently


namespace engabra
{

namespace g3
{
	//
	// "Backward" order: {other} - Vector
	//

	//TBD: ParaVec from Vector - Scalar

	// -- Vector from Vector - Vector : \ref g3opsSub_same.hpp

	//
	// "Forward" order: Vector - {other}
	//

	//! DirPlex from Vector - BiVector
	inline
	DirPlex
	operator-
		( Vector const & vec
		, BiVector const & biv
		)
	{
		return DirPlex{ vec, -biv };
	}

	//! ImSpin from Vector - TriVector
	inline
	ImSpin
	operator-
		( Vector const & vec
		, TriVector const & tri
		)
	{
		return ImSpin{ vec, -tri };
	}

	//! ImSpin from Vector - ImSpin
	inline
	ImSpin
	operator-
		( Vector const & vec
		, ImSpin const & imsp
		)
	{
		return ImSpin
			{ vec - imsp.theVec
			, -imsp.theTri
			};
	}

	//TBD: NoBiv from Vector - ComPlex

	//! DirPlex from Vector - DirPlex
	inline
	DirPlex
	operator-
		( Vector const & vec
		, DirPlex const & dplx
		)
	{
		return DirPlex
			{ vec - dplx.theVec
			, -dplx.theBiv
			};
	}

	//! MultiVector from Vector - MultiVector
	inline
	MultiVector
	operator-
		( Vector const & vec
		, MultiVector const & mv
		)
	{
		return MultiVector
			{ -mv.theSca
			, vec - mv.theVec
			, -mv.theBiv
			, -mv.theTri
			};
	}

} // [g3]

} // [engabra]


#endif // engabra_g3opsSub_Vector_INCL_
