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


#ifndef engabra_g3opsSub_Scalar_INCL_
#define engabra_g3opsSub_Scalar_INCL_

/*! \file
\brief Contains operator-() overloads for Scalar-{...} and {...}-Scalar

\note All of these operations are anti-commutative such that (A-B)=-(B-A).

Example:
\snippet test_g3opsSub_other.cpp DoxyExampleSca

*/


#include "g3opsSub_same.hpp"
#include "g3opsUni.hpp" // unary negation used frequently


namespace engabra
{

namespace g3
{
	// -- Scalar from Scalar - Scalar : \ref g3opsSub_same.hpp

	//
	// "Forward" order: Scalar - {other}
	//

	//TBD: ParaVec from Scalar - Vector

	//! Spinor from Scalar - BiVector
	inline
	Spinor
	operator-
		( Scalar const & sca
		, BiVector const & biv
		)
	{
		return Spinor{ sca, -biv };
	}

	//! ComPlex from Scalar - TriVector
	inline
	ComPlex
	operator-
		( Scalar const & sca
		, TriVector const & tri
		)
	{
		return ComPlex{ sca, -tri };
	}

	//! Spinor from Scalar - Spinor
	inline
	Spinor
	operator-
		( Scalar const & sca
		, Spinor const & spin
		)
	{
		return
			{ sca - spin.theSca
			, -spin.theBiv
			};
	}

	//TBD: NoBiv from Scalar - ImSpin

	//! ComPlex from Scalar - ComPlex
	inline
	ComPlex
	operator-
		( Scalar const & sca
		, ComPlex const & cplx
		)
	{
		return ComPlex
			{ sca - cplx.theSca
			, -cplx.theTri
			};
	}

	//TBD: NoTri from Scalar - DirPlex

	//! MultiVector from Scalar - MultiVector
	inline
	MultiVector
	operator-
		( Scalar const & sca
		, MultiVector const & mv
		)
	{
		return MultiVector
			{ sca - mv.theSca
			, -mv.theVec
			, -mv.theBiv
			, -mv.theTri
			};
	}


} // [g3]

} // [engabra]


#endif // engabra_g3opsSub_Scalar_INCL_
