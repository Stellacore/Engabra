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


#ifndef engabra_g3opsMul_INCL_
#define engabra_g3opsMul_INCL_

/*! \file
\brief Binary operators associated with multiplication actions.

\b Overview

This header file provides functions that overload operator*() for G3
type operations.

e.g.
\snippet test_g3opsMul.cpp DoxyExample01

All combinations of product pairs involving the explicit engabra::g3 types
are supported. The MultiVector*MultiVector product can be used to evaluate
the product of any arbitrary combination of "unusual" argument types.

Explicit product operator implementations include the products described
below. The following description (as well as code layout in this header
file) is organized by the type of the first argument, but operators are
provided for both argument orders of all explicit types.

\b Convenience

\arg (double * ...) -- overload multiplication by native type,
double. This is primarily for coding convenience. In theory the
g3::Scalar type provides this capability. However, in practices, it's
much easier and more efficient (mostly in terms of compilation times)
to type e.g. "17." instead of "Scalar{17.}"

\b Blades

\arg (Scalar * ...) -- increase (or decrease) the magnitude of other argument.

\arg (Vector * ...) -- provides geometric product with other argument.
Generally, this includes a inner product (contracted) grade and also an
outer product (extended) grade constituent for each grade constituent
in the other argument.

\arg (BiVector * ...) -- another geometric product. In G3, the bivector
is dual to vector. These products have "grade-splitting" geometric
properties similar to those of the product involving a vector operand.

\arg (TriVector * ...) -- in G3, trivectors are the pseudo-scalar of the
algebra and multiplication with a trivector is commutative. Multiplication
by the unit magnitude trivector produces an entity's dual.

\b Composites

\arg (Spinor * ...) -- multiplication by spinor types are commonly
encountered during evaluation of intermediate results (e.g. product of
three vectors, a*b*c, in which a*b produces a spinor that then multiplies
the third vector, c). Also, this is a particularly common multiplication
operation involved with rotations.

\arg (ImSpin * ...) -- another multiplication operator that often occurs
during evaluation of intermediate results. These products are dual to the
(Spinor*...) ones.

\arg (MultiVector * ...) -- multiplication operations with the most general
algebraic type entity. This can be used to evaluate multiplication products
of any pair of types. Ref note below.

\b Note/Generality

The (MultiVector*MultiVector) product is the most general
multiplication possible in the algebra. In practical terms, it can be used
to perform multiplication of any two "unusual" composite types that may
not have an explicit operator*() implemented here.

E.g. to evaluate something like
(scalar+trivector)*(vector+bivector+trivector), the two arguments can
first be used to construct two MultiVector entities, and then the general
case operator*(MultiVector,MultiVector) operation can be used to obtain
the result.  \snippet test_g3opsMul.cpp DoxyExample02

*/


#include "g3type.hpp"

#include "g3opsMul_double.hpp"
#include "g3opsMul_Scalar.hpp"
#include "g3opsMul_Vector.hpp"
#include "g3opsMul_BiVector.hpp"
#include "g3opsMul_TriVector.hpp"
#include "g3opsMul_Spinor.hpp"

#include "g3opsAdd_same.hpp"
#include "g3opsSub_same.hpp"

#include "g3opsUni.hpp"
#include "g3_private.hpp"

#include <algorithm>
#include <array>
#include <numeric>


namespace engabra
{

namespace g3
{

	// Contents provide a multiplication table organized in order of:
	// - double
	// - Scalar
	// - Vector
	// - BiVector
	// - TriVector
	// - Spinor
	// - ImSpin
	// - ComPlex
	// - DirPlex
	// - MultiVector

	// NOTE: a number of these functions could be implemented with
	// templates. However, that:
	// - leads to confusion in maintaining the code
	// - often produces extremely verbose error messages for consumers
	// - adds extra compilation overhead to resolve alternatives

	//
	// === ImSpin * QQQ
	//

	//! (ImSpin) product of (ImSpin)*(double)
	inline
	ImSpin
	operator*
		( ImSpin const & imspA
		, double const & dubB
		)
	{
		return ImSpin{ dubB * imspA.theVec, dubB * imspA.theTri };
	}

	//! (ImSpin) product of (ImSpin)*(Scalar)
	inline
	ImSpin
	operator*
		( ImSpin const & imspA
		, Scalar const & scaB
		)
	{
		double const & dubB = scaB.theData[0];
		return ImSpin{ dubB * imspA.theVec, dubB * imspA.theTri };
	}

	//! (Scalar+BiVector) result of (Vector+TriVector)*(Vector)
	inline
	Spinor
	operator*
		( ImSpin const & imspA
		, Vector const & vecB
		)
	{
		// a.b + a^b + A*b
		Spinor const spinAB{ imspA.theVec * vecB };
		BiVector const bivAB{ imspA.theTri * vecB };
		return Spinor{ spinAB.theSca, spinAB.theBiv + bivAB };
	}

	//! (ImSpin) result of (Vector+TriVector)*(BiVector)
	inline
	ImSpin
	operator*
		( ImSpin const & imspA
		, BiVector const & bivB
		)
	{
		ImSpin const imsp1{ imspA.theVec * bivB };
		Vector const vec1{ imspA.theTri * bivB };
		return { imsp1.theVec + vec1, imsp1.theTri };
	}

	//! (Scalar+BiVector) result of (Vector+TriVector)*(TriVector) - ImSpin dual
	inline
	Spinor
	operator*
		( ImSpin const & imspA
		, TriVector const & triB
		)
	{
		return triB*imspA;
	}

	//! (Vector+TriVector) result of (Vector+TriVector)*(Scalar+BiVector)
	inline
	ImSpin
	operator*
		( ImSpin const & imspA
		, Spinor const & spinB
		)
	{
		ImSpin const imsp1{ imspA.theVec * spinB };
		ImSpin const imsp2{ imspA.theTri * spinB };
		return ImSpin{ imsp1 + imsp2 };
	}

	//! (Spinor) result of (Vector+TriVector)*(Vector+TriVector)
	inline
	Spinor
	operator*
		( ImSpin const & imspA
		, ImSpin const & imspB
		)
	{
		Spinor const spin1{ imspA.theVec * imspB };
		Spinor const spin2{ imspA.theTri * imspB };
		return Spinor{ spin1 + spin2 };
	}

	//! (MultiVector) result of (Vector+TriVector)*(MultiVector)
	inline
	MultiVector
	operator*
		( ImSpin const & imspA
		, MultiVector const & mvB
		)
	{
		return MultiVector
			{ imspA.theVec * mvB
			+ imspA.theTri * mvB
			};
	}

	//
	// === MultiVector * QQQ
	//

	//! (MultiVector) product of (MultiVector)*(double)
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, double const dubB
		)
	{
		return MultiVector
			{ dubB * mvA.theSca
			, dubB * mvA.theVec
			, dubB * mvA.theBiv
			, dubB * mvA.theTri
			};
	}

	//! (MultiVector) product of (MultiVector)*(Scalar)
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, Scalar const scaB
		)
	{
		double const & dubB = scaB.theData[0];
		return MultiVector
			{ dubB * mvA.theSca
			, dubB * mvA.theVec
			, dubB * mvA.theBiv
			, dubB * mvA.theTri
			};
	}

	//! (MultiVector) product of (MultiVector)*(Vector)
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, Vector const vecB
		)
	{
		Vector const vec1{ mvA.theSca * vecB };
		Spinor const spin1{ mvA.theVec * vecB };
		ImSpin const imsp1{ mvA.theBiv * vecB };
		BiVector const biv1{ mvA.theTri * vecB };
		return MultiVector
			{ spin1.theSca
			, vec1 + imsp1.theVec
			, biv1 + spin1.theBiv
			, imsp1.theTri
			};
	}

	//! (MultiVector) product of (MultiVector)*(BiVector)
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, BiVector const bivB
		)
	{
		BiVector const biv1{ mvA.theSca * bivB };
		ImSpin const imsp1{ mvA.theVec * bivB };
		Spinor const spin1{ mvA.theBiv * bivB };
		Vector const vec1{ mvA.theTri * bivB };
		return MultiVector
			{ spin1.theSca
			, imsp1.theVec + vec1
			, biv1 + spin1.theBiv
			, imsp1.theTri
			};
	}

	//! (MultiVector) product of (MultiVector)*(TriVector)
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, TriVector const triB
		)
	{
		TriVector const tri1{ mvA.theSca * triB };
		BiVector const biv1{ mvA.theVec * triB };
		Vector const vec1{ mvA.theBiv * triB };
		Scalar const sca1{ mvA.theTri * triB };
		return MultiVector{ sca1, vec1, biv1, tri1 };
	}

	//! (MultiVector) product of (MultiVector)*(Spinor)
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, Spinor const spinB
		)
	{
		return MultiVector
			( mvA * spinB.theSca
			+ mvA * spinB.theBiv
			);
	}

	//! (MultiVector) product of (MultiVector)*(ImSpin)
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, ImSpin const imspB
		)
	{
		return MultiVector
			( mvA * imspB.theVec
			+ mvA * imspB.theTri
			);
	}

	/*! \brief General MultiVector product (most general in 3D)
	 *
	 * This is the most general product of the algebra and represents
	 * a superset of all possible pairwise component operations.
	 *
	 * The implementation involves approximately 128 floating point
	 * operations (64 each multiplies and additions, 8 assignments).
	 * This may represent some overhead if working only with simple
	 * types (e.g. it is a wasteful way to implement Scalar*Scalar
	 * product). However, if either entity has a composite structure,
	 * then casting to/from MultiVector type and using this one
	 * function call can provide reasonably efficient computation.
	 */
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, MultiVector const & mvB
		); // Implemented in g3opsMul.inl

} // [g3]

} // [engabra]

// Include file for more lengthy implementations.
#include "g3opsMul.inl"


#endif // engabra_g3opsMul_INCL_
