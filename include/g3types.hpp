/*

MIT License

Copyright (c) 2021 Stellacore Corporation

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/


#ifndef engabra_g3types_INCL_
#define engabra_g3types_INCL_


#include <array>
#include <cstddef>

#include <cmath>
#include <limits>


namespace engabra
{

namespace g3
{

/*! \brief Namespace for definition of fundamental GA data types.
 *
 * The fundamental types are
 * \arg Scalar
 * \arg Vector
 *
 * Other blades are based on extensions of these fundamental types and
 * include:
 * \arg BiVector
 * \arg TriVector
 *
 * Particularly useful composites of the basic blade types include:
 * \arg Spinor
 * \arg ImSpinor
 * \arg Complex - TODO worth supporting? can use std::complex<double>
 * \arg MultiVector
 *
 * Note that MultiVector is the general element of the entire algebra.
 *
 */
namespace types
{

	//
	// Fundamentals (as unique structs to allow compiler type detection)
	//

	/*! \brief Fundamental scalar type - basically a wrapper for 'double' type.
	 *
	 * TODO- Engineering uses: quantities: mass, temperature, time, ...
	 *
	 * TODO- Geometric interpretation: a quantity that does not depend on space
	 *
	 * In geometric algebra (GA) terminology this class represents the 
	 * field of real value numbers over which the algebra is defined.
	 *
	 * In computer software terminology this class is effectively an
	 * alias for a 'double'.  The reason for having a separate, standalone
	 * wrapper class for scalar type (instead of using 'double' directly)
	 * is to support unambiguous type detection by the compiler. This allows
	 * the implementation to freely overload GA operators without concern
	 * of potentially interfering with external code structure (which may
	 * overload operations involving native times for some other purpose).
	 * E.g. the primary (only?) reason for this class is that it facilitates
	 * encapsulation of all GA operations separate from other code.
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
	 * 10.x+5.=7.
	 * x = inverse(10.) * (7.-5.)
	 */
	struct Scalar
	{
		//! Internal data store: Can also access element via operator[]().
		std::array<double, 1u> theData;

		/*! Subscript-style access to theData.
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
			return theData[ndx];
		}
	};

	/*! \brief Fundamental directed element of GA (in 3D)
	 *
	 * TODO - Engineering uses: relationships: displacements, forces, velocities
	 *
	 * TODO - Geometric interpretation: a quantity that defines the
	 * idea of (1D of) space
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

		/*! Subscript-style access to theData elements.
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
			return theData[ndx];
		}
	};

	/*! \brief Extension of orthogonal vector directions to planar element
	 *
	 * A bivector results from the extension of one vector along an
	 * independent vector direction, and also is the result of the
	 * product of two orthogonal vectors.
	 *
	 * TODO - Engineering uses: surfaces: angles, moments, rotations, ...
	 *
	 * TODO - Geometric interpretation: the idea of perpendicular
	 * (spatial orthogonality)
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
	 */
	struct BiVector
	{
		//! Internal data store: Can also access elements via operator[]().
		std::array<double, 3u> theData;

		/*! Subscript-style access to theData elements.
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
			return theData[ndx];
		}
	};

	/*! \brief Extension of vectors into volume element.
	 *
	 * A trivector results from the extension of a bivector along an
	 * independent vector direction, and are the result of the
	 * product of three orthogonal vectors.
	 *
	 * TODO - Engineering uses: volumes, duality relationships
	 * (e.g. surface normals)
	 *
	 * TODO - Geometric interpretation: the concept of volume - all of space
	 *
	 * TODO - Algebraically: wraparound (dual to scalars)
	 * - e.g. *ALL* of space (N-D together) acts like time - except neg square
	 *
	 * TODO - (e.g. geometrically associated with a section of a volume)
	 *
	 * In geometric algebra (GA), trivectors are an extension of bivectors
	 * along a vector direction. Trivectors may also be defined as the
	 * multiplicative product of three orthogonal vectors.
	 *
	 */
	struct TriVector
	{
		//! Internal data store: Can also access element via operator[]().
		std::array<double, 1u> theData;

		/*! Subscript-style access to theData.
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
			return theData[ndx];
		}
	};

	//
	// Useful composites
	//

	/*! \brief Conventional spinor - scalar and bivector grades.
	 *
	 *
	 */
	struct Spinor
	{
		Scalar theS; //!< Scalar grade part (acts like 'real' number)
		BiVector theB; //!< BiVector grade part (acts like 'imaginary plane')
	};

	/*! \brief Imaginary spinor - vector and trivector grades (dual to Spinor).
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
		Vector theV; //!< Vector grade part
		TriVector theT; //!< TriVector grade part
	};


} // [types]

// "Publish" these implementations into working engabra::g3 namespace

using types::Scalar;
using types::Vector;
using types::BiVector;
using types::TriVector;
using types::Spinor;
using types::ImSpin;


	//
	// Null/NaN values
	//

	//! Generic Not-A-Number for individual values
	constexpr double nan{ std::numeric_limits<double>::quiet_NaN() };

	//! Null instance for a type constructable from 'double'.
	template <typename Type>
	inline
	Type
	null
		()
	{
		return Type{ nan };
	}

	// null<Scalar> could be handled by default function
	//! Null value - specialization for Scalar
	template <> inline Scalar
	null<Scalar> () { return Scalar{ nan }; }

	//! Null value - specialization for Vector
	template <> inline Vector
	null<Vector> () { return Vector{ nan, nan, nan }; }

	//! Null value - specialization for BiVector
	template <> inline BiVector
	null<BiVector> () { return BiVector{ nan, nan, nan }; }

	// null<Tri> could be handled by default function
	//! Null value - specialization for TriVector
	template <> inline TriVector
	null<TriVector> () { return TriVector{ nan }; }

	//
	// Instance validity testing
	//

	//! True if dub is a reasonable value, e.g. is (! null)
	inline
	bool
	isValid
		( double const & dub
		)
	{
		bool okay{ (0. == dub) }; // allow zero as valid
		if (! okay)
		{
			// normal meaning NOT any of {zero, subnormal, infinite, NaN}
			okay = std::isnormal(dub);
		}
		return okay;
	}

	//! True if blade is not a null instancwe
	template <typename Blade>
	inline
	bool
	isValid
		( Blade const & blade
		)
	{
		return isValid(blade.theData[0]); // test only first element for nan
	}

	//! True if instance is not null - specialization for Spinor
	template <>
	inline
	bool
	isValid
		( Spinor const & spin
		)
	{
		return { isValid(spin.theS) && isValid(spin.theB) };
	}

	//! True if instance is not null - specialization for ImSpin
	template <>
	inline
	bool
	isValid
		( ImSpin const & imsp
		)
	{
		return { isValid(imsp.theV) && isValid(imsp.theT) };
	}

	//
	// Zero values
	//

	//! Zero value instance of Type constructable from 'double'.
	template <typename Type>
	constexpr
	Type
	zero
		()
	{
		return Type{ 0. };
	}

	// zero<Scalar> handled by default function

	//! Zero value - specialization for Vectors
	template <> constexpr Vector zero<Vector> () { return Vector{ 0., 0., 0. }; }

	//! Zero value - specialization for BiVectors
	template <> constexpr BiVector zero<BiVector> () { return BiVector{ 0., 0., 0. }; }

	// zero<TriVector> handled by default function


} // [g3]

} // [engabra]


#endif // engabra_g3types_INCL_
