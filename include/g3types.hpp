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


namespace engabra
{

namespace g3
{
namespace types
{

	//
	// Fundamentals (as unique structs to allow compiler type detection)
	//

	/*! A scalar type
	 *
* Engineering uses: quantities: mass, temperature, time, ...
*
* Geometric interpretation: a quantity that does not depend on space
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
	 * \arg Sca const result{ Sca{7.} * (Sca{3.} + Sca{5.}) }; // == Sca{21.}
	 *
	 * Solving equations
	 * 10.x+5.=7.
	 * x = inverse(10.) * (7.-5.)
	 */
	struct Sca
	{
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

	/*! A vector type (in 3D)
	 *
* Engineering uses: relationships: displacements, forces, velocities
*
* Geometric interpretation: a quantity that defines the idea of (1D of) space
*
	 * In geometric algebra (GA), vectors are what extend the power of
	 * algebra to address "space". For engineering uses that are the focus
	 * of this package, the space of interest is a classic three-dimensional
	 * (3D) Euclidean space.
	 *
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
	 * The algebraic operations associated with Sca class can now be
	 * extended to vectors. E.g.
	 *
	 * TODO -- include example from test code
	 * \arg Vec const result{ Vec{7.,6.,5.} * (Vec{3.,2.,1.} + Vec{5.,4.,3.}) };
	 * producing result same as
	 * \arg result{ Sca{TODO} + Biv{TODO,TODO,TODO} };
	 *
	 * Solving equation systems (after introducing rest of the algebra)
	 * a*x + S = R
	 * x = inverse(a) * (R - S) // with zero trivector part
	 *
	 */
	struct Vec
	{
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

	/*! A BiVector type (in 3D)
	 *
* Engineering uses: surfaces: angles, moments, rotations, ...
*
* Geometric interpretation: the idea of perpendicular (spatial orthogonality)
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
	struct Biv
	{
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

	/*! A Trivector type (in 3D. For 3D, this is the pseudo-scalar)
	 *
* Engineering uses: volumes, duality relationships (e.g. surface normals)
*
* Geometric interpretation: the concept of volume - all of space
*
* Algebraically: wraparound (dual to scalars)
* - e.g. *ALL* of space (N-D together) acts like time - except neg square
*
* (e.g. geometrically associated with a section of a volume)
*
	 * In geometric algebra (GA), trivectors are an extension of bivectors
	 * along a vector direction. Trivectors may also be defined as the
	 * multiplicative product of three orthogonal vectors.
	 *
	 */
	struct Tri
	{
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

	//! Conventional spinor - scalar and bivector grades
	struct Spinor
	{
		Sca theSca; //!< Scalar grade part (acts like 'real' number)
		Biv theBiv; //!< BiVector grade part (acts like 'imaginary plane')
	};

	/*! Imaginary spinor - vector and trivector grades (dual to Spinor).
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
		Vec theVec; //!< Vector grade part
		Tri theTri; //!< TriVector grade part
	};

} // [types]

using types::Sca;
using types::Vec;
using types::Biv;
using types::Tri;
using types::Spinor;
using types::ImSpin;

} // [g3]

} // [engabra]


#endif // engabra_g3types_INCL_
