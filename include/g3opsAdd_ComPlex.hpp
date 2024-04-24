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


#ifndef engabra_g3opsAdd_ComPlex_INCL_
#define engabra_g3opsAdd_ComPlex_INCL_

/*! \file
\brief Contains operator+() overloads for ComPlex+{...} and {...}+ComPlex

\note All of these operations are commutative such that (A+B)=(B+A).

Example:
\snippet test_g3opsAdd_other.cpp DoxyExampleCplx

*/


#include "g3opsAdd_same.hpp"
#include "g3opsAdd_Scalar.hpp"
#include "g3opsAdd_TriVector.hpp"



namespace engabra
{

namespace g3
{
	//
	// "Backward" order: {other} + ComPlex
	// -- redirect to forward op+() functions
	//

	//! ComPlex from ComPlex + Scalar
	inline
	ComPlex
	operator+
		( ComPlex const & cplx
		, Scalar const & sca
		)
	{
		return sca + cplx;
	}

	//TBD: NoBiv from ComPlex + Vector

	//TBD: NoVec from ComPlex + BiVector

	//! ImSpin from ComPlex + TriVector
	inline
	ComPlex
	operator+
		( ComPlex const & cplx
		, TriVector const & tri
		)
	{
		return tri + cplx;
	}

	//TBD: NoVec from ComPlex + Spinor

	//TBD: NoBiv from ComPlex + ImSpin

	// -- ComPlex from ComPlex + ComPlex - \ref g3opsAdd_same.hpp

	//
	// "Forward" order: ComPlex + {other}
	//

	//! MultiVector from ComPlex + DirPlex
	inline
	MultiVector
	operator+
		( ComPlex const & cplx
		, DirPlex const & dplx
		)
	{
		return MultiVector
			{ cplx.theSca
			, dplx.theVec
			, dplx.theBiv
			, cplx.theTri
			};
	}

	//! MultiVector from ComPlex + MultiVector
	inline
	MultiVector
	operator+
		( ComPlex const & cplx
		, MultiVector const & mv
		)
	{
		return MultiVector
			{ cplx.theSca + mv.theSca
			, mv.theVec
			, mv.theBiv
			, cplx.theTri + mv.theTri
			};
	}

} // [g3]

} // [engabra]


#endif // engabra_g3opsAdd_ComPlex_INCL_
