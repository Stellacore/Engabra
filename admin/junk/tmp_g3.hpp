
//
// MIT License
//
// Copyright (c) 2020 Stellacore Corporation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//


#ifndef g3_g3_INCL_
#define g3_g3_INCL_

/*! \file
\brief TODO #### - material to be factored into other files.
*/


#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numeric>
#include <sstream>
#include <utility>



//! Namespace
namespace g3_tmp
{
	//
	// Fundamentals (as classes to allow compiler type discrimination)
	//

	// TODO - maybe make a standalone document page for each type?

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
	// Type support
	//

	template <typename Type>
	struct is_blade : std::false_type
	{
	};
	template <> struct is_blade<Sca> : std::true_type {};
	template <> struct is_blade<Vec> : std::true_type {};
	template <> struct is_blade<Biv> : std::true_type {};
	template <> struct is_blade<Tri> : std::true_type {};

	//
	// Constants
	//

	static double const piQtr{ std::atan(1.) };
	static double const piHalf{ 2. * piQtr };
	static double const pi{ 2. * piHalf };

	static double const turnFull{ 2.*pi };
	static double const turnHalf{ pi };
	static double const turnQtr{ piHalf };

	//
	// Null/NaN values
	//

	constexpr double nan{ std::numeric_limits<double>::quiet_NaN() };

	template <typename Type>
	inline
	Type
	null
		()
	{
		return Type{ nan };
	}

	// template <> inline Sca null<Sca> () { return Sca{ nan }; }
	template <> inline Vec null<Vec> () { return Vec{ nan, nan, nan }; }
	template <> inline Biv null<Biv> () { return Biv{ nan, nan, nan }; }
	// template <> inline Tri null<Tri> () { return Tri{ nan }; }

	//! True if dub is a reasonable value - e.g. (! null)
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

	//
	// Useful composites
	//

	//! Conventional spinor - scalar and bivector grades
	struct Spinor
	{
		Sca theSca;
		Biv theBiv;
	};

	//! Imaginary spinor - vector and trivector grades
	struct ImSpin
	{
		Vec theVec;
		Tri theTri;
	};

	//! Display elements of array
	template <typename Type, std::size_t Dim>
	void
	put
		( std::ostream & ostrm
		, std::array<Type, Dim> const & elems
		)
	{
		std::ostringstream oss;
		constexpr std::size_t ndSign{ 1u };
		constexpr std::size_t ndInt{ 1u }; // should be arg?
		constexpr std::size_t ndDec{ 1u };
		constexpr std::size_t ndFrac{ 6u }; // should be arg?
		constexpr std::size_t ndSize{ ndSign + ndInt + ndDec + ndFrac };
		oss << std::fixed;
		oss << std::setprecision(ndFrac);
		for (double const & elem : elems)
		{
			oss << " " << std::setw(ndSize) << elem;
		}
		ostrm << oss.str();
	}


} // [g3_tmp]

//! Global/Anon i/o functions
namespace
{
	/*
	// needs some fancy template specialization logic (e.g. is_blade()?)
	template
		< typename Blade
		, typename = std::enable_if< g3::is_blade<Blade>::value::type >
		>
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, Blade const & blade
		)
	{
		ostrm << blade.theData;
		return ostrm;
	}
	*/

	std::ostream &
	operator<<
		( std::ostream & ostrm
		, g3::Sca const & blade
		)
	{
		g3::put(ostrm, blade.theData);
		return ostrm;
	}

	std::ostream &
	operator<<
		( std::ostream & ostrm
		, g3::Vec const & blade
		)
	{
		g3::put(ostrm, blade.theData);
		return ostrm;
	}

	std::ostream &
	operator<<
		( std::ostream & ostrm
		, g3::Biv const & blade
		)
	{
		g3::put(ostrm, blade.theData);
		return ostrm;
	}

	std::ostream &
	operator<<
		( std::ostream & ostrm
		, g3::Tri const & blade
		)
	{
		g3::put(ostrm, blade.theData);
		return ostrm;
	}

	std::ostream &
	operator<<
		( std::ostream & ostrm
		, g3::Spinor const & spin
		)
	{
		ostrm << spin.theSca << " " << spin.theBiv;
		return ostrm;
	}

	std::ostream &
	operator<<
		( std::ostream & ostrm
		, g3::ImSpin const & imsp
		)
	{
		ostrm << imsp.theVec << " " << imsp.theTri;
		return ostrm;
	}


} // [anon]

#endif // g3_g3_INCL_
