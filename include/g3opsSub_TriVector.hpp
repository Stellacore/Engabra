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


#ifndef engabra_g3opsSub_TriVector_INCL_
#define engabra_g3opsSub_TriVector_INCL_

/*! \file
\brief Contains operator-() overloads for TriVector-{...} and {...}-TriVector

\note All of these operations are anti-commutative such that (A-B)=-(B-A).

Example:
\snippet test_g3opsSub_other.cpp DoxyExampleTri

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
	// "Backward" order: {other} - TriVector
	// -- redirect to forward op-() functions
	//

	//! ComPlex from TriVector - Scalar
	inline
	ComPlex
	operator-
		( TriVector const & tri
		, Scalar const & sca
		)
	{
		return sca - tri;
	}

	//! ImSpin from TriVector - Vector
	inline
	ImSpin
	operator-
		( TriVector const & tri
		, Vector const & vec
		)
	{
		return vec - tri;
	}

	//TBD: ImPara from TriVector - BiVector

	// -- TriVector from TriVector - TriVector : \ref g3opsSub_same.hpp

	//
	// "Forward" order: TriVector - {other}
	//

	//TBD: NoVec from TriVector - Spinor

	//! ImSpin from TriVector - ImSpin
	inline
	ImSpin
	operator-
		( TriVector const & tri
		, ImSpin const & imsp
		)
	{
		return ImSpin{ -imsp.theVec, tri - imsp.theTri };
	}

	//! ComPlex from TriVector - ComPlex
	inline
	ComPlex
	operator-
		( TriVector const & tri
		, ComPlex const & cplx
		)
	{
		return ComPlex{ -cplx.theSca, tri - cplx.theTri };
	}

	//TBD: NoSca from TriVector - DirPlex

	//! MultiVector from TriVector - MultiVector
	inline
	MultiVector
	operator-
		( TriVector const & tri
		, MultiVector const & mv
		)
	{
		return MultiVector
			{ -mv.theSca
			, -mv.theVec
			, -mv.theBiv
			, tri - mv.theTri
			};
	}

} // [g3]

} // [engabra]


#endif // engabra_g3opsSub_TriVector_INCL_
