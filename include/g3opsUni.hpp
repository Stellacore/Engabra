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

This file provides operators that act on a single entity of any GA type.

There are several involution operators. These are:

\arg negation: via operator-().
	Changes sign on all grades.
	(denoted by leading negative sign)
\arg reverse(): flip the \b permutation \b order of vector factors in a blade.
	Changes sign on bivectors and trivectors.
	(often denoted with a dagger or tilde)
\arg oddverse(): flip orientation of \b odd \b grade entities.
	Is associated with reflecting all basis vectors (of a coordinate frame)
	through the origin. This changes the sign of any blade entity that is the
	product of an odd number of vectors.
	When applied to Complex type, this is the same as "complex conjugate".
	Changes sign on vectors and trivectors.
	(often denoted with a asterix superscript)
\arg dirverse(): flip orientation of \b spatially \b directed quantities
	leaving scalars or pseudo-scalars unchanged.
	Changes sign on vectors and bivectors - aka "Clifford conjugate"
	(often denoted with an overbar)

The pattern of negations is illustrated in the following code.
\snippet test_g3opsUni.cpp DoxyExample02

Note on Naming: the name "conjugate" could perhaps be used instead of
"dirverse". However, that would lead to confusion between:

\arg [Clifford] conjugate - dirverse(Complex{})
\arg [Complex] conjugate - reverse(Complex{}) == oddverse(Complex{})

To avoid the ambiguity which type of interpretation of conjugate should
be used, the new name, "dirverse", has been introduced to eliminate the
ambiguity.

All of the above operations are involutions (successive application
twice returns to original starting value) - i.e.

\arg x = op(op(x)) : for all of operator-(), reverse(), oddverse(), dirverse().

The various involution operations are compositionally commutative with
each other. E.g. for any entity, 'x'

\arg opA(opB(x)) == opB(opA(x))

For the three operations, reverse(), oddverse(), dirverse(), composition
of any two operations produces the same result as the third operation. I.e.:

\arg reverse() == oddverse(dirverse()) == dirverse(oddverse())
\arg oddverse() == dirverse(reverse()) == reverse(dirverse())
\arg dirverse() == reverse(oddverse()) == oddverse(reverse())

*/

/*
Usage and behavior of the reverse() and unitary negation operator is
demonstrated in this section of unit test code.
\snippet test_g3opsUni.cpp DoxyExample01
*/



#include "g3type.hpp"
#include "g3traits.hpp"

#include <algorithm>

namespace engabra
{

namespace g3
{

	//
	// Unitary negation
	//

	//! Unitary negation
	template
		< typename Blade
		, std::enable_if_t<is::blade<Blade>::value, bool> = true
		>
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

	//! Specialization - Unitary negation
	inline
	Spinor
	operator-
		( Spinor const & spin
		)
	{
		return Spinor{ -spin.theSca, -spin.theBiv };
	}

	//! Specialization - Unitary negation
	inline
	ImSpin
	operator-
		( ImSpin const & imsp
		)
	{
		return ImSpin{ -imsp.theVec, -imsp.theTri };
	}

	//! Specialization - Unitary negation
	inline
	MultiVector
	operator-
		( MultiVector const & mv
		)
	{
		return MultiVector{ -mv.theSca, -mv.theVec, -mv.theBiv, -mv.theTri };
	}

	//
	// Unitary reversion (Biv & Tri)
	//

	//! Reverse of double (is same as input)
	inline
	double
	reverse
		( double const & dub
		)
	{
		return dub;
	}

	//! Reverse of Scalar (is same as input)
	inline
	Scalar
	reverse
		( Scalar const & sca
		)
	{
		return sca;
	}

	//! Reverse of Vector (is same as input)
	inline
	Vector
	reverse
		( Vector const & vec
		)
	{
		return vec;
	}

	//! Reverse of BiVector (negates the input)
	inline
	BiVector
	reverse
		( BiVector const & biv
		)
	{
		// could use "return -biv" - but may as well save compiler work/time
		return BiVector{ -biv.theData[0], -biv.theData[1], -biv.theData[2] };
	}

	//! Reverse of TriVector (negates the input)
	inline
	TriVector
	reverse
		( TriVector const & tri
		)
	{
		return TriVector{ -tri.theData[0] };
	}

	//! Reverse of Spinor (same scalar, negative bivector)
	inline
	Spinor
	reverse
		( Spinor const & spin
		)
	{
		// return Spinor{ spin.theSca, -spin.theBiv };
		return Spinor
			{ reverse(spin.theSca)
			, reverse(spin.theBiv)
			};
	}

	//! Reverse of ImSpin (same vector, negative trivector)
	inline
	ImSpin
	reverse
		( ImSpin const & imsp
		)
	{
		// return ImSpin{ imsp.theVec, -imsp.theTri };
		return ImSpin
			{ reverse(imsp.theVec)
			, reverse(imsp.theTri)
			};
	}

	//! Reverse of MultiVector (same sca,vec, negated biv,tri)
	inline
	MultiVector
	reverse
		( MultiVector const & mv
		)
	{
		// return MultiVector{ mv.theSca, mv.theVec, -mv.theBiv, -mv.theTri };
		return MultiVector
			{ reverse(mv.theSca)
			, reverse(mv.theVec)
			, reverse(mv.theBiv)
			, reverse(mv.theTri)
			};
	}

	//
	// Oddverse(): Flip coordinate frame basis vectors (Vec & Tri)
	//

	//! Same as sca
	inline
	Scalar
	oddverse
		( Scalar const & sca
		)
	{
		return sca;
	}

	//! Changes sign on vector
	inline
	Vector
	oddverse
		( Vector const & vec
		)
	{
		return Vector{ -vec.theData[0], -vec.theData[1], -vec.theData[2] };
	}

	//! Same as biv
	inline
	BiVector
	oddverse
		( BiVector const & biv
		)
	{
		return biv;
	}

	//! Changes sign on trivector
	inline
	TriVector
	oddverse
		( TriVector const & tri
		)
	{
		return TriVector{ -tri.theData[0] };;
	}

	//! Same as spin
	inline
	Spinor
	oddverse
		( Spinor const & spin
		)
	{
		return spin;
	}

	//! Changes sign on imsp (both vector and trivector grades)
	inline
	ImSpin
	oddverse
		( ImSpin const & imsp
		)
	{
		return ImSpin
			{ oddverse(imsp.theVec)
			, oddverse(imsp.theTri)
			};
	}

	//! Changes sign on vector and trivector grades
	inline
	MultiVector
	oddverse
		( MultiVector const & mv
		)
	{
		// return MultiVector{ mv.theSca, -mv.theVec, mv.theBiv, -mv.theTri };
		return MultiVector
			{ oddverse(mv.theSca)
			, oddverse(mv.theVec)
			, oddverse(mv.theBiv)
			, oddverse(mv.theTri)
			};
	}


	//
	// Dirverse(): Flip directed spatial entities (Vec & Biv)
	//

	//! Same as sca
	inline
	Scalar
	dirverse
		( Scalar const sca
		)
	{
		return sca;
	}

	//! Changes sign of vec
	inline
	Vector
	dirverse
		( Vector const vec
		)
	{
		return Vector{ -vec.theData[0], -vec.theData[1], -vec.theData[2] };
	}

	//! Changes sign of biv
	inline
	BiVector
	dirverse
		( BiVector const biv
		)
	{
		return BiVector{ -biv.theData[0], -biv.theData[1], -biv.theData[2] };
	}

	//! Same as tri
	inline
	TriVector
	dirverse
		( TriVector const tri
		)
	{
		return tri;
	}

	//! Changes sign of bivector grade (same as reverse)
	inline
	Spinor
	dirverse
		( Spinor const spin
		)
	{
		// return Spinor{ spin.theSca, -spin.theBiv };
		return Spinor
			{ dirverse(spin.theSca)
			, dirverse(spin.theBiv)
			};
	}

	//! Negative of imsp (changes sign on both vector and bivector grades)
	inline
	ImSpin
	dirverse
		( ImSpin const imsp
		)
	{
		// return ImSpin{ -imsp.theVec, imsp.theTri };
		return ImSpin
			{ dirverse(imsp.theVec)
			, dirverse(imsp.theTri)
			};
			
	}

	//! Changes sign on spatially directed vector and bivector grades
	inline
	MultiVector
	dirverse
		( MultiVector const & mv
		)
	{
		// return MultiVector{ mv.theSca, -mv.theVec, -mv.theBiv, mv.theTri };
		return MultiVector
			{ dirverse(mv.theSca)
			, dirverse(mv.theVec)
			, dirverse(mv.theBiv)
			, dirverse(mv.theTri)
			};
	}

	//
	// Dual entities (unit trivector times argument)
	//

	//! TriVector that is dual to double
	inline
	TriVector
	dual
		( double const & dub
		)
	{
		return TriVector{ dub };
	}

	//! TriVector that is dual to Scalar
	inline
	TriVector
	dual
		( Scalar const & sca
		)
	{
		return TriVector{ sca.theData };
	}

	//! BiVector that is dual to Vector
	inline
	BiVector
	dual
		( Vector const & vec
		)
	{
		return BiVector{ vec.theData };
	}

	//! Vector that is dual to BiVector
	inline
	Vector
	dual
		( BiVector const & biv
		)
	{
		return Vector
			{ - biv.theData[0]
			, - biv.theData[1]
			, - biv.theData[2]
			};
	}

	//! Scalar that is dual to TriVector
	inline
	Scalar
	dual
		( TriVector const & tri
		)
	{
		return Scalar{ - tri.theData[0] };
	}

	//! ImSpin that is dual to Spinor
	inline
	ImSpin
	dual
		( Spinor const & spin
		)
	{
		return ImSpin{ dual(spin.theBiv), dual(spin.theSca) };
	}

	//! Spinor that is dual to ImSpin
	inline
	Spinor
	dual
		( ImSpin const & imsp
		)
	{
		return Spinor{ dual(imsp.theTri), dual(imsp.theVec) };
	}

	//! MultiVector that is dual to mv
	inline
	MultiVector
	dual
		( MultiVector const & mv
		)
	{
		return MultiVector
			( dual(mv.theTri)
			, dual(mv.theBiv)
			, dual(mv.theVec)
			, dual(mv.theSca)
			);
	}

} // [g3]

} // [engabra]


#endif // engabra_g3opsUni_INCL_
