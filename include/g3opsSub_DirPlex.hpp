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


#ifndef engabra_g3opsSub_DirPlex_INCL_
#define engabra_g3opsSub_DirPlex_INCL_

/*! \file
\brief Contains operator-() overloads for DirPlex-{...} and {...}-DirPlex

\note All of these operations are anti-commutative such that (A-B)=-(B-A).

Example:
\snippet test_g3opsSub_other.cpp DoxyExampleDplx

*/


#include "g3opsSub_same.hpp"
#include "g3opsUni.hpp" // unary negation used frequently
#include "g3opsSub_Vector.hpp"
#include "g3opsSub_BiVector.hpp"
#include "g3opsSub_ComPlex.hpp"



namespace engabra
{

namespace g3
{
	//
	// "Backward" order: {other} - DirPlex
	// -- redirect to forward op-() functions
	//

	//TBD: NoTri from DirPlex - Scalar

	//! DirPlex from DirPlex - Vector
	inline
	DirPlex
	operator-
		( DirPlex const & dplx
		, Vector const & vec
		)
	{
		return -(vec - dplx);
	}

	//! DirPlex from DirPlex - BiVector
	inline
	DirPlex
	operator-
		( DirPlex const & dplx
		, BiVector const & biv
		)
	{
		return -(biv - dplx);
	}

	//TBD: NoSca from DirPlex - TriVector

	//TBD: NoTri from DirPlex - Spinor

	//TBD: NoSca from DirPlex - ImSpin

	//! MultiVector from DirPlex - ComPlex
	inline
	MultiVector
	operator-
		( DirPlex const & dplx
		, ComPlex const & cplx
		)
	{
		return -(cplx - dplx);
	}

	// -- DirPlex from DirPlex - DirPlex : \ref g3opsSub_same.hpp

	//
	// "Forward" order: DirPlex - {other}
	//

	//! MultiVector from DirPlex - MultiVector
	inline
	MultiVector
	operator-
		( DirPlex const & dplx
		, MultiVector const & mv
		)
	{
		return MultiVector
			{ -mv.theSca
			, dplx.theVec - mv.theVec
			, dplx.theBiv - mv.theBiv
			, -mv.theTri
			};
	}

} // [g3]

} // [engabra]


#endif // engabra_g3opsSub_DirPlex_INCL_
