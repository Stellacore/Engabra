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


#ifndef engabra_g3opsAdd_ImSpin_INCL_
#define engabra_g3opsAdd_ImSpin_INCL_

/*! \file
\brief Contains operator+() overloads for ImSpin+{...} and {...}+ImSpin

\note All of these operations are commutative such that (A+B)=(B+A).

Example:
\snippet test_g3opsAdd_other.cpp DoxyExampleImsp

*/


#include "g3opsAdd_same.hpp"
#include "g3opsAdd_Vector.hpp"
#include "g3opsAdd_TriVector.hpp"
#include "g3opsAdd_Spinor.hpp"


namespace engabra
{

namespace g3
{
	//
	// "Backward" order: {other} + ImSpin
	// -- redirect to forward op+() functions
	//

	//TBD: NoBiv from ImSpin + Scalar

	//! ImSpin from ImSpin + Vector
	inline
	ImSpin
	operator+
		( ImSpin const & imsp
		, Vector const & vec
		)
	{
		return vec + imsp;
	}

	//TBD: NoSca from ImSpin + BiVector

	//! ImSpin from ImSpin + TriVector
	inline
	ImSpin
	operator+
		( ImSpin const & imsp
		, TriVector const & tri
		)
	{
		return tri + imsp;
	}

	//! MultiVector from ImSpin + Spinor
	inline
	MultiVector
	operator+
		( ImSpin const & imsp
		, Spinor const & spin
		)
	{
		return spin + imsp;
	}

	// -- ImSpin from ImSpin + ImSpin - \ref g3opsAdd_same.hpp

	//
	// "Forward" order: ImSpin + {other}
	//

	//TBD: NoBiv from ImSpin + ComPlex

	//TBD: NoSca from ImSpin + DirPlex

	//! MultiVector from ImSpin + MultiVector
	inline
	MultiVector
	operator+
		( ImSpin const & imsp
		, MultiVector const & mv
		)
	{
		return MultiVector
			{ mv.theSca
			, imsp.theVec + mv.theVec
			, mv.theBiv
			, imsp.theTri + mv.theTri
			};
	}

} // [g3]

} // [engabra]


#endif // engabra_g3opsAdd_ImSpin_INCL_
