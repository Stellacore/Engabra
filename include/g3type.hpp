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


#ifndef engabra_g3type_INCL_
#define engabra_g3type_INCL_

/*! \file
\brief Fundamental types (dimension basis blades) for G3.

\b Types:

These are the fundamental types that describe the geometry of 3D space
and its component subspaces. Each of these is a pure blade (an entity
formed by the otter product of vectors).
\arg Scalar - a 0-Dimensional entity (numeric value). Abstractly speaking
	this is an outer product of zero vectors.
\arg Vector - a 1-Dimensional entity spanning a line and is the outer product
	of a single vector
\arg BiVector - a 2-Dimensional entity spanning a plane. This can be factored
	as the outer product of two (linearly independent) vectors. In 3D space
	BiVectors are dual to Vectors.
\arg TriVector - a 3-Dimensional entity spanning a volume and constructable
	as the outer product of three (linearly independent) vectors.
	TriVectors are the pseudoscalar of 3D space (i.e. dual to Scalars).

Composite entities include:
\arg Spinor - This is the geometric product of two vectors (aka "Rotor").
	It comprises a Scalar and a BiVector constituent parts.
\arg ImSpin - An "imaginary spinor" which is dual to Spinor. It comprises
	a Vector and a Trivector constituent parts.
\arg MultiVector - the most general type in the algebra is the full
multivector comprising (Scalar+Vector+BiVector+TriVector).

\b Constructions

The \b default constructions are fast but \b do \b NOT \b initialize
content values.
\snippet test_g3type.cpp DoxyExample01

Instances can be initialized to explicit null values (e.g. to
support the "null object" design pattern (ref. g3validity.hpp)
\snippet test_g3type.cpp DoxyExample02

Instances can be initialized to zero values (a single concept of 'zero'
applies to geometric algebra entities of all grades).
\snippet test_g3type.cpp DoxyExample03

Instances can be initialized with specific numeric values.
\snippet test_g3type.cpp DoxyExample04

Composite entities can also be constructed using constituent entities:
\snippet test_g3type.cpp DoxyExample05

\b Grade \b Selection

Each of the type structures contains member representing the individual
grades of which it is comprised. Grade selection is performed simply by
dereferencing these members. E.g. for compound (non-blade) entity, 
"SomeItem", the grade constituents are:
\arg SomeItem.theSca - Scalar grade == (SomeItem)_0
\arg SomeItem.theVec - Vector grade == (SomeItem)_1
\arg SomeItem.theBiv - BiVector grade == (SomeItem)_2
\arg SomeItem.theTri - TriVector grade == (SomeItem)_3

*/


#include <array>
#include <cstddef>

#include <cmath>
#include <limits>


namespace engabra
{

namespace g3
{

//! \brief Private functions used for internal implementation.
namespace priv
{
	//! Data value location returned for out-of-range references
	static
	constexpr double sGlobalNaN{ std::numeric_limits<double>::quiet_NaN() };
}

	//
	// Fundamentals (as unique structs to allow compiler type detection)
	//

	/*! \brief Fundamental amount-like type - mostly a wrapper of 'double' type
	 *
	 * Engineering uses: quantities such as mass, temperature, time, ...
	 *
	 * Geometric interpretation: a quantity or intensity that does not
	 * depend on directions of/in space.
	 *
	 * In geometric algebra (GA) terminology this class represents the 
	 * field of real value numbers over which the algebra is defined.
	 *
	 * In computer software terminology this class is effectively an
	 * alias for a 'double'.  The reason for having a separate, standalone
	 * wrapper class for scalar type (instead of using 'double' directly)
	 * is to support unambiguous type detection by the compiler. This allows
	 * the consuming code to freely overload GA operators without concern
	 * of potentially interfering with external code structure (which may
	 * overload operations involving native times for some other purpose).
	 * E.g. the primary (only?) reason for this class is that it facilitates
	 * encapsulation of all GA operations separate from other code.
	 *
	 * Scalars commute with all other entities of the algebra.
	 *
	 * A common appearance of scalar instances in GA is in association with
	 * the magnitude of various entities. If the other GA entities were
	 * absent, this type provides an implementation of "ordinary real algebra"
	 *
	 * TODO -- include from unit tests.
	 * Field type operations
	 * \arg Scalar const result
	 * 	{ Scalar{7.} * (Scalar{3.} + Scalar{5.}) }; // == Scalar{21.}
	 *
	 * Solving equations
	 * \arg 10.x+5.=7.  // via: x = inverse(10.) * (7.-5.)
	 */
	struct Scalar
	{
		//! Internal data store: Can also access element via operator[]().
		std::array<double, 1u> theData;

		/*! \brief Subscript-style access to theData.
		 *
		 * This is trivial for the 1-element array, but provides functional
		 * compatibility with other blade types.
		 *
		 * Only valid argument is ndx==0 (corresponding with e0 basis scalar).
		 */
		inline
		double const &
		operator[]
			( std::size_t const & ndx
			) const
		{
			if (ndx < 1u)
			{
				return theData[0];
			}
			else
			{
				return priv::sGlobalNaN;
			}
		}
	};

	/*! \brief Fundamental ray-like directed element of GA (in 3D)
	 *
	 * Engineering uses: positions, relationships between points, (lineal)
	 * directions, displacements, forces, velocities, etc.
	 *
	 * Geometric interpretation: an entity that defines the idea of
	 * line-like directions within 3D space. I.e. scalar multipliers of
	 * a vector entity all lie on a common line in space.
	 *
	 * In geometric algebra (GA), vectors are what extend the power of
	 * algebra to address "space". For engineering uses that are the focus
	 * of this package, the space of interest is a classic three-dimensional
	 * (3D) Euclidean space.
	 *
	 * TODO - 
	 * In the language of extensions, vectors extend the concept of a point
	 * attribute into space. The represent a one-dimensional element of space.
	 * The magnitude of the vector is how much of this dimension, and the
	 * direction is "which" 1D subspace is selected from full the full space.
	 * (e.g. geometrically associated with a section of a line)
	 *
	 * The principals and theory of GA are valid in any dimensional space.
	 * It is the code herein that is restricted to an implementation in
	 * the familiar 3D space of our ordinary (non-relativistic) world. This
	 * restrictive assumption allows providing a less complex library with
	 * a simpler syntax, and high performance implementation.
	 *
	 * Conceptually a vector represents a displacement in space - where
	 * is "that point in space" relative to "this point in space".
	 *
	 * The novelty, and great power, associated with GA (relative to
	 * ordinary real algebra) is associated with additional axioms that
	 * involve vectors. Specifically, GA extends algebra by including
	 * additional axioms:
	 *
	 * \arg The square of any vector is a scalar (which may be zero)
	 * \arg The product of two vectors has a scalar AND a bivector part
	 *
	 * These additional concepts allow expanding GA into an enormously
	 * rich and powerful mathematical system.
	 *
	 * The algebraic operations associated with Scalar class can now be
	 * extended to vectors. E.g.
	 *
	 * TODO -- include example from test code
	 * \arg Vector const result
	 * 	{ Vector{7.,6.,5.} * (Vector{3.,2.,1.} + Vector{5.,4.,3.}) };
	 * producing result same as
	 * \arg result{ Scalar{TODO} + BiVector{TODO,TODO,TODO} };
	 *
	 * Solving equation systems (after introducing rest of the algebra)
	 * a*x + S = R
	 * x = inverse(a) * (R - S) // with zero trivector part
	 *
	 */
	struct Vector
	{
		//! Internal data store: Can also access elements via operator[]().
		std::array<double, 3u> theData;

		/*! \brief Subscript-style access to theData elements.
		 *
		 * Valid arguments are ndx={0,1,2}. The coordinates correspond
		 * to unitary basis vector directions {e1,e2,e3}.
		 */
		inline
		double const &
		operator[]
			( std::size_t const & ndx
			) const
		{
			if (ndx < 3u)
			{
				return theData[ndx];
			}
			else
			{
				return priv::sGlobalNaN;
			}
		}
	};

	/*! \brief Fundamental plane-like entity (dual to Vector)
	 *
	 * Extension of orthogonal vector directions to planar element.
	 *
	 * A bivector results from the extension of one vector along an
	 * independent vector direction, and also is the result of the
	 * product of two orthogonal vectors.
	 *
	 * Engineering uses: angles, moments, surface facets, rotations.
	 *
	 * Geometric interpretation: an entity that encapsulates the ideas of
	 * plane-like directions in space. Scalar multiples of a BiVector are
	 * all coplanar to each other. As operators, multiplication involving
	 * BiVector factors is associated with (generalized) rotations.
	 *
	 * Example: Earth's equatorial plane can be represented as a
	 * bivector and the same bivector can be used in expressions
	 * for representing the rotation of Earth.  while keeping the
	 * direction of the equatorial plane constant in space.  In this
	 * case, the equatorial bivector is the eigen-bivector associated
	 * with rotation).
	 *
	 * Bivectors square to negative scalars.
	 *
	 * In geometric algebra (GA), bivectors are an extension of the concept
	 * of vector. Whereas a vector represents one dimension from the full
	 * space, a bivector represents two dimensions from within the full
	 * space (e.g. geometrically associated with a section of a plane)
	 *
	 * The specific relationship is that a bivector is formed by the
	 * multiplicative product of two orthogonal vectors. I.e. given two
	 * vectors that each represent a single one-dimensional direction and
	 * these two direction are completely independent, then the geometric
	 * product of these two vectors is a bivector that represents the
	 * plane containing both of the original vectors.
	 *
	 * \note The order of the components is associated with basis
	 * bivectors in the order: e23, e31, e12. E.g.
	 * \arg for "BiVector const foo{ 1., 2., 3. };",
	 * foo = foo[0]*e23 + foo[1]*e31 + foo[2]*e12
	 *
	 */
	struct BiVector
	{
		//! Internal data store: Can also access elements via operator[]().
		std::array<double, 3u> theData;

		/*! \brief Subscript-style access to theData elements.
		 *
		 * Valid arguments are ndx={0,1,2}. The coordinates correspond
		 * to unitary basis bivector directions {e21,e31,e12}
		 */
		inline
		double const &
		operator[]
			( std::size_t const & ndx
			) const
		{
			if (ndx < 3u)
			{
				return theData[ndx];
			}
			else
			{
				return priv::sGlobalNaN;
			}
		}
	};

	/*! \brief Fundamental volume-like element (dual to Scalar)
	 *
	 * A trivector results from the extension of a bivector along an
	 * independent vector direction, and are the result of the
	 * product of three orthogonal vectors.
	 *
	 * Engineering uses: volumes, duality relationships (e.g. between
	 * surface facet bivectors and surface normal vectors)
	 *
	 * Geometric interpretation: the concept of _directed_ volume. For
	 * this implementation (and in most GA frameworks) the trivector is
	 * associated with a "dextral" (aka "right handed") volume
	 * interpretation.
	 *
	 * In geometric algebra (GA), trivectors are an extension of bivectors
	 * along a vector direction. Trivectors may also be defined as the
	 * multiplicative product of three orthogonal vectors.
	 *
	 * The unit magnitude trivector 'I' is associated with the product
	 * of basis vectors, in cyclic order. E.g.
	 * \arg I = e1*e2*e3
	 *
	 * All trivectors are a scalar multiple of the unit trivector.
	 *
	 * Trivectors square to negative scalars.
	 *
	 * If 'S', 'V', 'B', 'T' are scalar, vector, bivector and trivector
	 * entities respectively, and all have the same magnitude, then
	 * duality relationship may be expressed in terms of unit trivector
	 * 'I' including:
	 * \arg T = I*S
	 * \arg B = I*V
	 * \arg V = -I*B
	 * \arg S = -I*T
	 *
	 * Trivectors commute with all other entities of the algebra.
	 *
	 */
	struct TriVector
	{
		//! Internal data store: Can also access element via operator[]().
		std::array<double, 1u> theData;

		/*! \brief Subscript-style access to theData.
		 *
		 * This is trivial for the 1-element array, but provides functional
		 * compatibility with other blade types.
		 *
		 * Only valid argument is ndx==0.
		 */
		inline
		double const &
		operator[]
			( std::size_t const & ndx
			) const
		{
			if (ndx < 1u)
			{
				return theData[0];
			}
			else
			{
				return priv::sGlobalNaN;
			}
		}
	};

	//
	// Useful composites
	//

	/*! \brief Conventional spinor (aka Rotor) - (Scalar + BiVector)
	 *
	 * Occurs, for example, in product of two vectors.
	 *
	 */
	struct Spinor
	{
		Scalar theSca; //!< Scalar grade part (acts like 'real' number)
		BiVector theBiv; //!< BiVector grade part (acts like 'imaginary plane')

		/*! \brief Subscript-style access to individual components
		 *
		 * Components are numbered sequentially e.g.
		 * \arg [0] - is scalar grade component
		 * \arg [1,2,3] - are the components of the bivector grade
		 *
		 * Valid argument values are ndx=={0, 1, 2, 3}
		 */
		inline
		double const &
		operator[]
			( std::size_t const & ndx
			) const
		{
			if (ndx < 1u)
			{
				return theSca.theData[0];
			}
			else
			if (ndx < 4u)
			{
				return theBiv.theData[ndx - 1u];
			}
			else
			{
				return priv::sGlobalNaN;
			}
		}
	};

	/*! \brief Imaginary spinor (Vector + TriVector) - is dual to Spinor.
	 *
	 * Occurs, for example, in product of three vectors.
	 *
	 * Although it is not much used directly, this composite type arises
	 * often during various intermediate computations (e.g. product of
	 * three vectors).
	 *
	 * This type is dual to Spinor. I.e. Spinor*e123 produces an ImSpin
	 *
	 */
	struct ImSpin
	{
		Vector theVec; //!< Vector grade part
		TriVector theTri; //!< TriVector grade part

		/*! \brief Subscript-style access to individual components
		 *
		 * Components are numbered sequentially e.g.
		 * \arg [0,1,2] - are the components of the vector grade
		 * \arg [3] - is trivector grade component
		 *
		 * Valid argument values are ndx=={0, 1, 2, 3}
		 */
		inline
		double const &
		operator[]
			( std::size_t const & ndx
			) const
		{
			if (ndx < 3u)
			{
				return theVec.theData[ndx];
			}
			else
			if (ndx < 4u)
			{
				return theTri.theData[0];
			}
			else
			{
				return priv::sGlobalNaN;
			}
		}
	};

	/*! \brief Full multivector for G3 (Scalar+Vector+Bivector+Trivector)
	 *
	 * MultiVector - This is the composition with one member representing
	 * each blade of the dimension. E.g. in 3D a MultiVector comprises Scalar,
	 * Vector, BiVector, and TriVector constituents.
	 *
	 * This is the most general entity in G3. Every operation involving
	 * other types can be expressed in terms of MultiVector operations.
	 * E.g. a Scalar is just MultiVector with zero vector, bivector, and
	 * trivector grades, and so on.
	 */
	struct MultiVector
	{
		// initialize to null by default
		Scalar theSca; //!< 0-Vector grade part
		Vector theVec; //!< 1-Vector grade part
		BiVector theBiv; //!< 2-Vector grade part
		TriVector theTri; //!< 3-Vector grade part

		//! Default construct a null instant (that is not isValid())
		MultiVector
			() = default;

		//! Value construction with constituent grades.
		inline
		explicit
		MultiVector
			( Scalar const & sca
			, Vector const & vec
			, BiVector const & biv
			, TriVector const & tri
			)
			: theSca{ sca }
			, theVec{ vec }
			, theBiv{ biv }
			, theTri{ tri }
		{ }

		//! Explicit construction from fundamental type.
		inline
		explicit
		MultiVector
			( double const & dub
			)
			: theSca{ dub }
			, theVec{ 0., 0., 0. }
			, theBiv{ 0., 0., 0. }
			, theTri{ 0. }
		{ }

		//! Explicit construction from fundamental type.
		inline
		explicit
		MultiVector
			( Scalar const & sca
			)
			: theSca{ sca }
			, theVec{ 0., 0., 0. }
			, theBiv{ 0., 0., 0. }
			, theTri{ 0. }
		{ }

		//! Explicit construction from fundamental type.
		inline
		explicit
		MultiVector
			( Vector const & vec
			)
			: theSca{ 0. }
			, theVec{ vec }
			, theBiv{ 0., 0., 0. }
			, theTri{ 0. }
		{ }

		//! Explicit construction from fundamental type.
		inline
		explicit
		MultiVector
			( BiVector const & biv
			)
			: theSca{ 0. }
			, theVec{ 0., 0., 0. }
			, theBiv{ biv }
			, theTri{ 0. }
		{ }

		//! Explicit construction from fundamental type.
		inline
		explicit
		MultiVector
			( TriVector const & tri
			)
			: theSca{ 0. }
			, theVec{ 0., 0., 0. }
			, theBiv{ 0., 0., 0. }
			, theTri{ tri }
		{ }

		//! Explicit construction from fundamental type.
		inline
		explicit
		MultiVector
			( Spinor const & spin
			)
			: theSca{ spin.theSca }
			, theVec{ 0., 0., 0. }
			, theBiv{ spin.theBiv }
			, theTri{ 0. }
		{ }

		//! Explicit construction from fundamental type.
		inline
		explicit
		MultiVector
			( ImSpin const & imsp
			)
			: theSca{ 0. }
			, theVec{ imsp.theVec }
			, theBiv{ 0., 0., 0. }
			, theTri{ imsp.theTri }
		{ }

		//! Construct by component values (very low level, not a typical usage)
		inline
		explicit
		MultiVector
			( double const & sca0
			, double const & vec0
			, double const & vec1
			, double const & vec2
			, double const & biv0
			, double const & biv1
			, double const & biv2
			, double const & tri0
			)
			: theSca{ sca0 }
			, theVec{ vec0, vec1, vec2 }
			, theBiv{ biv0, biv1, biv2 }
			, theTri{ tri0 }
		{ }

		/*! \brief Subscript-style access to theData elements.
		 *
		 * This is generally more for testing. For general use, it's
		 * typically more clear and convenient to work directly with
		 * the member instances (or more generally, with the multivector
		 * instance itself as a whole).
		 *
		 * Valid arguments are ndx={0,...,7}. The coordinates correspond
		 * to unitary basis directions {e0,e1,e2,e3,e21,e31,e12,e123}
		 */
		inline
		double const &
		operator[]
			( std::size_t const & ndx
			) const
		{
			if (ndx < 1u) // {0}
			{
				return theSca.theData[0];
			}
			else
			if (ndx < 4u) // {1,2,3}
			{
				return theVec.theData[ndx-1u]; // 0,1,2
			}
			else
			if (ndx < 7u) // {4,5,6}
			{
				return theBiv.theData[ndx-4u]; // 0,1,2
			}
			else // {7, ...}
			{
				return theTri.theData[0];
			}
		}

		/*! \brief Direct write access components by index.
		 *
		 * As with the const version of subscript access, this is
		 * more of a low-level mechanics method primarily useful only
		 * in special cases.
		 */
		inline
		double &
		operator[]
			( std::size_t const & ndx
			)
		{
			if (ndx < 1u) // {0}
			{
				return theSca.theData[0];
			}
			else
			if (ndx < 4u) // {1,2,3}
			{
				return theVec.theData[ndx-1u]; // 0,1,2
			}
			else
			if (ndx < 7u) // {4,5,6}
			{
				return theBiv.theData[ndx-4u]; // 0,1,2
			}
			else // {7, ...}
			{
				return theTri.theData[0];
			}
		}
	};

} // [g3]

} // [engabra]


#endif // engabra_g3type_INCL_
