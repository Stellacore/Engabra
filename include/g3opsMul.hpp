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

#include "g3opsAdd_same.hpp"
#include "g3opsUni.hpp"

#include <algorithm>
#include <array>
#include <numeric>


namespace engabra
{

namespace g3
{

namespace priv
{
	//
	// Commutative patterns
	//

	//! Commutative product - product of contraction
	inline
	double
	prodComm
		( std::array<double, 3u> const & argA
		, std::array<double, 3u> const & argB
		)
	{
		return std::inner_product
			( std::cbegin(argA)
			, std::cend(argA)
			, std::cbegin(argB)
			, 0.
			);
	}

	//! Specialization Commutative product for Scalar/TriVector support
	inline
	double
	prodComm
		( std::array<double, 1u> const & argA
		, std::array<double, 1u> const & argB
		)
	{
		return (argA[0] * argB[0]);
	}

	//
	// Anti-commutative patterns
	//

	//! Anticommutative product - product of extension
	inline
	std::array<double, 3u>
	prodAnti
		( std::array<double, 3u> const & argA
		, std::array<double, 3u> const & argB
		)
	{
		return
			{ argA[1]*argB[2] - argA[2]*argB[1]
			, argA[2]*argB[0] - argA[0]*argB[2]
			, argA[0]*argB[1] - argA[1]*argB[0]
			};
	}

} // [priv]


	// Contents provide a multiplication table organized in order of:
	// - double
	// - Scalar
	// - Vector
	// - BiVector
	// - TriVector
	// - Spinor
	// - ImSpin
	// - MultiVector

	// NOTE: a number of these functions could be implemented with
	// templates. However, that:
	// - leads to confusion in maintaining the code
	// - often produces extremely verbose error messages for consumers
	// - adds extra compilation overhead to resolve alternatives

	//
	// === double * QQQ
	//

	// double * double  -- via language

	//! (Double*Scalar) dilation/contraction product
	inline
	Scalar
	operator*
		( double const & dubA
		, Scalar const & scaB
		)
	{
		return Scalar{ dubA * scaB.theData[0] };
	}

	//! (Double*Vector) dilation/contraction product
	inline
	Vector
	operator*
		( double const & dubA
		, Vector const & vecB
		)
	{
		return Vector
			{ dubA * vecB.theData[0]
			, dubA * vecB.theData[1]
			, dubA * vecB.theData[2]
			};
	}

	//! (Double*BiVector) dilation/contraction product
	inline
	BiVector
	operator*
		( double const & dubA
		, BiVector const & bivB
		)
	{
		return BiVector
			{ dubA * bivB.theData[0]
			, dubA * bivB.theData[1]
			, dubA * bivB.theData[2]
			};
	}

	//! (Double*TriVector) dilation/contraction product
	inline
	TriVector
	operator*
		( double const & dubA
		, TriVector const & triB
		)
	{
		return TriVector{ dubA * triB.theData[0] };
	}

	//! (Double*Spinor) specialized of (double*Blade)
	inline
	Spinor
	operator*
		( double const & dubA
		, Spinor const & spinB
		)
	{
		return Spinor{ dubA*spinB.theSca, dubA*spinB.theBiv };
	}

	//! (Double*ImSpin) specialized of (double*Blade)
	inline
	ImSpin
	operator*
		( double const & dubA
		, ImSpin const & imspB
		)
	{
		return ImSpin{ dubA * imspB.theVec, dubA * imspB.theTri};
	}

	//! (Double*MultiVector) specialized of (double*Blade)
	inline
	MultiVector
	operator*
		( double const & dubA
		, MultiVector const & mvB
		)
	{
		return MultiVector
			{ dubA * mvB.theSca
			, dubA * mvB.theVec
			, dubA * mvB.theBiv
			, dubA * mvB.theTri
			};
	}

	//
	// === Scalar * QQQ
	//

	//! (Scalar*double) product
	inline
	Scalar
	operator*
		( Scalar const & scaA
		, double const & dubB
		)
	{
		return dubB * scaA;
	}

	//! (Scalar*Scalar) product
	inline
	Scalar
	operator*
		( Scalar const & scaA
		, Scalar const & scaB
		)
	{
		return Scalar{ scaA.theData[0] * scaB.theData[0] };
	}

	//! (Scalar*Vector) product
	inline
	Vector
	operator*
		( Scalar const & scaA
		, Vector const & vecB
		)
	{
		return Vector
			{ scaA.theData[0] * vecB.theData[0]
			, scaA.theData[0] * vecB.theData[1]
			, scaA.theData[0] * vecB.theData[2]
			};
	}

	//! (Scalar*BiVector) product
	inline
	BiVector
	operator*
		( Scalar const & scaA
		, BiVector const & bivB
		)
	{
		return BiVector
			{ scaA.theData[0] * bivB.theData[0]
			, scaA.theData[0] * bivB.theData[1]
			, scaA.theData[0] * bivB.theData[2]
			};
	}

	//! (Scalar*TriVector) product
	inline
	TriVector
	operator*
		( Scalar const & scaA
		, TriVector const & triB
		)
	{
		return TriVector{ scaA.theData[0] * triB.theData[0] };
	}

	//! (Scalar*Spinor) product
	inline
	Spinor
	operator*
		( Scalar const & scaA
		, Spinor const & spinB
		)
	{
		return Spinor
			{ scaA.theData[0] * spinB.theSca.theData[0]
			, scaA.theData[0] * spinB.theBiv
			};
	}

	//! (Scalar*ImSpin) product
	inline
	ImSpin
	operator*
		( Scalar const & scaA
		, ImSpin const & imspB
		)
	{
		return ImSpin
			{ scaA.theData[0] * imspB.theVec
			, scaA.theData[0] * imspB.theTri.theData[0]
			};
	}

	//! (Scalar*MultiVector) product
	inline
	MultiVector
	operator*
		( Scalar const & scaA
		, MultiVector const & mvB
		)
	{
		return MultiVector
			{ Scalar{ scaA.theData[0] * mvB.theSca.theData[0] }
			, Vector{ scaA.theData[0] * mvB.theVec }
			, BiVector{ scaA.theData[0] * mvB.theBiv }
			, TriVector{ scaA.theData[0] * mvB.theTri.theData[0] }
			};
	}

	//
	// === Vector * QQQ
	//

	//! (Vector) result of (Vector*double) product
	inline
	Vector
	operator*
		( Vector const & vecA
		, double const & dubB
		)
	{
		return dubB * vecA;
	}

	//! (Vector) result of (Vector*Scalar) product
	inline
	Vector
	operator*
		( Vector const & vecA
		, Scalar const & scaB
		)
	{
		return scaB * vecA;
	}

	//! (Scalar+BiVector) result of (Vector*Vector)
	inline
	Spinor
	operator*
		( Vector const & vecA
		, Vector const & vecB
		)
	{
		Scalar const dot{ priv::prodComm(vecA.theData, vecB.theData) };
		BiVector const wedge{ priv::prodAnti(vecA.theData, vecB.theData) };
		return Spinor{ dot, wedge };
	}

	//! (Vector+TriVector) result of (Vector)*(BiVector)
	inline
	ImSpin
	operator*
		( Vector const & vecA
		, BiVector const & bivB
		)
	{
		// v*B = v.B + v^B = v.(-b*I) + v^B
		Vector const v1{ priv::prodAnti(vecA.theData, bivB.theData) };
		TriVector const t1{ priv::prodComm(vecA.theData, bivB.theData) };
		return ImSpin{ -v1, t1 };
	}

	//! (Bivector) result of (Vector*TriVector) - i.e. dual of a Vector
	inline
	BiVector
	operator*
		( Vector const & vecA
		, TriVector const & triB
		)
	{
		// v*T = v*I*s
		return BiVector
			{ triB.theData[0] * vecA.theData[0]
			, triB.theData[0] * vecA.theData[1]
			, triB.theData[0] * vecA.theData[2]
			};
	}

	//! (Vector+TriVector) result of (Vector)*(Scalar+BiVector)
	inline
	ImSpin
	operator*
		( Vector const & vecA
		, Spinor const & spinB
		)
	{
		Vector const v1{ spinB.theSca.theData[0] * vecA };
		ImSpin const i2{ vecA * spinB.theBiv };
		return ImSpin{ i2.theVec + v1, i2.theTri };
	}

	//! (Scalar+BiVector) result of (Vector)*(Vector+TriVector)
	inline
	Spinor
	operator*
		( Vector const & vecA
		, ImSpin const & imspB
		)
	{
		// vecA * triB
		Spinor const s1{ vecA * imspB.theVec };
		BiVector const b2{ vecA * imspB.theTri };
		return Spinor{ s1.theSca, s1.theBiv + b2 };
	}

	//! (MultiVector) result of (Vector)*(MultiVector)
	inline
	MultiVector
	operator*
		( Vector const & vecA
		, MultiVector const & mvB
		)
	{
		Vector const vec1{ vecA * mvB.theSca };
		BiVector const biv1{ vecA * mvB.theTri };
		Spinor const spin1{ vecA * mvB.theVec };
		ImSpin const imsp1{ vecA * mvB.theBiv };
		return MultiVector
			{ spin1.theSca
			, vec1 + imsp1.theVec
			, biv1 + spin1.theBiv
			, imsp1.theTri
			};
	}

	//
	// === BiVector * QQQ
	//

	//! BiVector scaled by scalar amount
	inline
	BiVector
	operator*
		( BiVector const & bivA
		, double const & dubB
		)
	{
		return dubB * bivA;
	}

	//! BiVector scaled by scalar amount
	inline
	BiVector
	operator*
		( BiVector const & bivA
		, Scalar const & scaB
		)
	{
		return scaB * bivA;
	}

	//! Imaginary spinor product of BiVector and Vector
	inline
	ImSpin
	operator*
		( BiVector const & bivA
		, Vector const & vecB
		)
	{
		// B*v = B.v + B^v = (-I*b).v + B^v
		Vector const anti{ priv::prodAnti(bivA.theData, vecB.theData) };
		TriVector const symm{ priv::prodComm(bivA.theData, vecB.theData) };
		return ImSpin{ -anti, symm };
	}

	//! Spinor product of BiVector and BiVector
	inline
	Spinor
	operator*
		( BiVector const & bivA
		, BiVector const & bivB
		)
	{
		Scalar const symm{ priv::prodComm(bivA.theData, bivB.theData) };
		BiVector const anti{ priv::prodAnti(bivA.theData, bivB.theData) };
		// note negation (e.g. A*B = I*a*I*b = I*I*a*b = -a*b)
		return Spinor{ -symm, -anti };
	}

	//! (Vector) dual of a BiVector
	inline
	Vector
	operator*
		( BiVector const & bivA
		, TriVector const & triB
		)
	{
		// V = B*T = (-Ib)*(Is)
		return Vector
			{ - triB.theData[0] * bivA.theData[0]
			, - triB.theData[0] * bivA.theData[1]
			, - triB.theData[0] * bivA.theData[2]
			};
	}

	//! (Spinor) product of (BiVector)*(Scalar+BiVector)
	inline
	Spinor
	operator*
		( BiVector const & bivA
		, Spinor const & spinB
		)
	{
		BiVector const biv1{ bivA * spinB.theSca };
		Spinor const spin1{ bivA * spinB.theBiv };
		return Spinor{ spin1.theSca, biv1 + spin1.theBiv };
	}

	//! (ImSpin) product of (BiVector)*(Vector+TriVector)
	inline
	ImSpin
	operator*
		( BiVector const & bivA
		, ImSpin const & imspB
		)
	{
		ImSpin const imsp1{ bivA * imspB.theVec };
		Vector const vec1{ bivA * imspB.theTri };
		return ImSpin{ imsp1.theVec + vec1, imsp1.theTri };
	}

	//! (MultiVector) product of (BiVector) * (MultiVector)
	inline
	MultiVector
	operator*
		( BiVector const & bivA
		, MultiVector const & mvB
		)
	{
		BiVector const & biv1{ bivA * mvB.theSca };
		ImSpin const & imsp1{ bivA * mvB.theVec };
		Spinor const & spin1{ bivA * mvB.theBiv };
		Vector const & vec1{ bivA * mvB.theTri };
		return MultiVector
			{ spin1.theSca
			, vec1 + imsp1.theVec
			, biv1 + spin1.theBiv
			, imsp1.theTri
			};
	}

	//
	// === TriVector * QQQ
	//

	//! (Trivector) dual of a Scalar (as double)
	inline
	TriVector
	operator*
		( TriVector const & triA
		, double const & dubB
		)
	{
		return TriVector{ dubB * triA.theData[0] };
	}


	//! (Trivector) dual of a Scalar
	inline
	TriVector
	operator*
		( TriVector const & triA
		, Scalar const & scaB
		)
	{
		// T = t*S = S*t
		return TriVector{ scaB.theData[0] * triA.theData[0] };
	}

	//! (Bivector) dual of a Vector
	inline
	BiVector
	operator*
		( TriVector const & triA
		, Vector const & vecB
		)
	{
		// B = t*v = v*t
		return vecB * triA;
	}

	//! (Bivector) dual of a BiVector
	inline
	Vector
	operator*
		( TriVector const & triA
		, BiVector const & bivB
		)
	{
		// V = t*B = B*t
		return bivB * triA;
	}

	//! (Scalar) dual of a TriVector
	inline
	Scalar
	operator*
		( TriVector const & triA
		, TriVector const & triB
		)
	{
		// S = T*T = -|T*T|
		// note negation
		return Scalar{ - triA.theData[0] * triB.theData[0] };
	}

	//! (ImSpin) dual of a Spinor
	inline
	ImSpin
	operator*
		( TriVector const & triA
		, Spinor const & spinB
		)
	{
		TriVector const t1{ triA * spinB.theSca };
		Vector const v2{ triA * spinB.theBiv };
		return ImSpin{ v2, t1 };
	}

	//! (Spinor) dual of a ImSpin
	inline
	Spinor
	operator*
		( TriVector const & triA
		, ImSpin const & imspB
		)
	{
		BiVector const b1{ triA * imspB.theVec };
		Scalar const s1{ triA * imspB.theTri };
		return Spinor{ s1, b1 };
	}

	//! (MultiVector) dual of MultiVector
	inline
	MultiVector
	operator*
		( TriVector const & triA
		, MultiVector const & mvB
		)
	{
		return MultiVector
			{ triA * mvB.theTri
			, triA * mvB.theBiv
			, triA * mvB.theVec
			, triA * mvB.theSca
			};
	}

	//
	// === Spinor * QQQ
	//

	//! (Spinor) product (Spinor*double)
	inline
	Spinor
	operator*
		( Spinor const & spinA
		, double const & dubB
		)
	{
		return Spinor{ dubB * spinA.theSca, dubB * spinA.theBiv };
	}

	//! (Spinor) product (Spinor*Scalar)
	inline
	Spinor
	operator*
		( Spinor const & spinA
		, Scalar const & scaB
		)
	{
		return Spinor
			{ scaB.theData[0] * spinA.theSca
			, scaB.theData[0] * spinA.theBiv
			};
	}

	//! (Vector+TriVector) result of (Scalar+BiVector)*(Vector)
	inline
	ImSpin
	operator*
		( Spinor const & spinA
		, Vector const & vecB
		)
	{
		// (Sca + Biv) * Vec
		// (ScaA * VecB) + (BivA * VecB)
		// (ScaA * VecB) + (BivA . VecB) + (BivA ^ VecB)
		// (ScaA * VecB) - I*(VecA . VecB) + (BivA ^ VecB)
		using priv::prodAnti;
		using priv::prodComm;
		Vector const v1{ spinA.theSca * vecB };
		Vector const v2{ prodAnti(spinA.theBiv.theData, vecB.theData) };
		TriVector const t1{ prodComm(spinA.theBiv.theData, vecB.theData) };
		// note negative to handle dual of biv.vec step
		return ImSpin{ v1 - v2, t1 };
	}

	//! (Spinor) results of (Scalar+BiVector)*(Spinor)
	inline
	Spinor
	operator*
		( Spinor const & spinA
		, BiVector const & bivB
		)
	{
		BiVector const biv1{ spinA.theSca * bivB };
		Spinor const spin1{ spinA.theBiv * bivB };
		return Spinor{ spin1.theSca, spin1.theBiv + biv1 };
	}

	//! (Vector+TriVector) results of (Scalar+BiVector)*(TriVector)
	inline
	ImSpin
	operator*
		( Spinor const & spinA
		, TriVector const & triB
		)
	{
		return ImSpin{ triB * spinA.theBiv, triB * spinA.theSca };
	}

	//! (Scalar+BiVector) result of (Scalar+BiVector)*(Scalar+BiVector)
	inline
	Spinor
	operator*
		( Spinor const & spinA
		, Spinor const & spinB
		)
	{
		// access individual grades of each factor
		double const & alpha = spinA.theSca.theData[0];
		BiVector const & bivA = spinA.theBiv;
		double const & beta = spinB.theSca.theData[0];
		BiVector const & bivB = spinB.theBiv;

		// Biv-Biv product commutative and anti-commutative constituents
		// Note sign change is implemented in combination below
		double const symmAB{ priv::prodComm(bivA.theData, bivB.theData) };
		BiVector const antiAB{ priv::prodAnti(bivA.theData, bivB.theData) };

		// Form scalar and bivector components of result
		// Note: include negative sign here (bivectors square to non-positive)
		Scalar const scaC{ alpha*beta - symmAB };
		BiVector const bivC{ alpha*bivB + beta*bivA - antiAB };

		return Spinor{ scaC, bivC };
	}

	//! (Vector+TriVector) result of (Scalar+BiVector)*(Vector+TriVector)
	inline
	ImSpin
	operator*
		( Spinor const & spinA
		, ImSpin const & imspB
		)
	{
		ImSpin const imsp1{ spinA.theSca.theData[0] * imspB };
		ImSpin const imsp2{ spinA.theBiv * imspB };
		return { imsp1 + imsp2 };
	}

	//! (MultiVector) product of (Spinor)*(MultiVector)
	inline
	MultiVector
	operator*
		( Spinor const & spinA
		, MultiVector const & mvB
		)
	{
		MultiVector const mv1{ spinA.theSca.theData[0] * mvB };
		MultiVector const mv2{ spinA.theBiv * mvB };
		return { mv1 + mv2 };
	}

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
	 * The implementation involved approximately 128 floating point
	 * operations (64 each multiplies and additions, 8 assignments).
	 * This may represent some overhead if working only with simple
	 * types (e.g. it is a wasteful way to implement Scalar*Scalar
	 * product). However, if either entity has a composite structure,
	 * then this one function call can provide reasonably efficient
	 * computation.
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
