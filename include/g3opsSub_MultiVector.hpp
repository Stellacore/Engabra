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


#ifndef engabra_g3opsSub_MultiVector_INCL_
#define engabra_g3opsSub_MultiVector_INCL_

/*! \file
\brief Contains operator-() for MultiVector-{...} and {...}-MultiVector

\note All of these operations are anti-commutative such that (A-B)=-(B-A).

Example:
\snippet test_g3opsSub_other.cpp DoxyExampleMvec

*/


#include "g3opsSub_same.hpp"
#include "g3opsUni.hpp" // unary negation used frequently
#include "g3opsSub_Scalar.hpp"
#include "g3opsSub_Vector.hpp"
#include "g3opsSub_BiVector.hpp"
#include "g3opsSub_TriVector.hpp"
#include "g3opsSub_Spinor.hpp"
#include "g3opsSub_ImSpin.hpp"
#include "g3opsSub_ComPlex.hpp"
#include "g3opsSub_DirPlex.hpp"



namespace engabra
{

namespace g3
{
	//
	// "Backward" order: {other} - MultiVector
	// -- redirect to forward op-() functions
	//

	//! MultiVector from MultiVector - Scalar
	inline
	MultiVector
	operator-
		( MultiVector const & mv
		, Scalar const & sca
		)
	{
		return -(sca - mv);
	}

	//! MultiVector from MultiVector - Vector
	inline
	MultiVector
	operator-
		( MultiVector const & mv
		, Vector const & vec
		)
	{
		return -(vec - mv);
	}

	//! MultiVector from MultiVector - BiVector
	inline
	MultiVector
	operator-
		( MultiVector const & mv
		, BiVector const & biv
		)
	{
		return -(biv - mv);
	}

	//! MultiVector from MultiVector - TriVector
	inline
	MultiVector
	operator-
		( MultiVector const & mv
		, TriVector const & tri
		)
	{
		return -(tri - mv);
	}

	//! MultiVector from MultiVector - Spinor
	inline
	MultiVector
	operator-
		( MultiVector const & mv
		, Spinor const & spin
		)
	{
		return -(spin - mv);
	}

	//! MultiVector from MultiVector - ImSpin
	inline
	MultiVector
	operator-
		( MultiVector const & mv
		, ImSpin const & imsp
		)
	{
		return -(imsp - mv);
	}

	//! MultiVector from MultiVector - ComPlex
	inline
	MultiVector
	operator-
		( MultiVector const & mv
		, ComPlex const & cplx
		)
	{
		return -(cplx - mv);
	}

	//! MultiVector from MultiVector - DirPlex
	inline
	MultiVector
	operator-
		( MultiVector const & mv
		, DirPlex const & dplx
		)
	{
		return -(dplx - mv);
	}


} // [g3]

} // [engabra]


#endif // engabra_g3opsSub_MultiVector_INCL_
