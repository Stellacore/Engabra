
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
namespace g3
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
	// Zero values
	//

	//! Zero value instance of requested Type
	template <typename Type>
	constexpr
	Type
	zero
		()
	{
		return Type{ 0. };
	}

	// template <> constexpr Sca zero<Sca> () { return Sca{ 0. }; }
	template <> constexpr Vec zero<Vec> () { return Vec{ 0., 0., 0. }; }
	template <> constexpr Biv zero<Biv> () { return Biv{ 0., 0., 0. }; }
	// template <> constexpr Tri zero<Tri> () { return Tri{ 0. }; }


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

	//
	// Basis blades
	//

	// Scalar basis element - (unique)
	static Sca const e0{ 1. }; //!< Magnitude [e.g. 'units' in use]

	// Vector basis elements - Mutually orthogonal, dextral and unitary
	static Vec const e1{ 1., 0., 0. }; //!< First direction [e.g. 'x' axis]
	static Vec const e2{ 0., 1., 0. }; //!< Second direction [e.g. 'y' axis]
	static Vec const e3{ 0., 0., 1. }; //!< Third direction [e.g. 'z' axis]

	// Bivector basis elements - Mutually orthogonal, dextral and unitary
	static Biv const e23{ 1., 0., 0. }; //!< First plane [e.g. 'yz' plane]
	static Biv const e31{ 0., 1., 0. }; //!< Second plane [e.g. 'zx' plane]
	static Biv const e12{ 0., 0., 1. }; //!< Third plane [e.g. 'xy' plane]

	// Trivector basis element (unique in 3D)
	static Tri const e123{ 1. }; //!< Volume [e.g. 'xyz' dextral cube]

	//
	// Unitary operations
	//

	//! Unitary negation
	template <typename Blade>
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

	// reverse instances for each blade type
	inline Sca reverse (Sca const & blade) { return blade; }
	inline Vec reverse (Vec const & blade) { return blade; }
	inline Biv reverse (Biv const & blade) { return -blade; }
	inline Tri reverse (Tri const & blade) { return -blade; }

	// reverse instances for composites types
	inline Spinor reverse (Spinor const & spin)
		{ return Spinor{spin.theSca, -spin.theBiv}; }
	inline ImSpin reverse (ImSpin const & imsp)
		{ return ImSpin{imsp.theVec, -imsp.theTri}; }

	//
	// Basic operations
	//

	//! Element-by-element operation (A (op) B)
	template <typename Blade, typename Func>
	inline
	Blade
	binaryElementByElement
		( Blade const & bladeA
		, Blade const & bladeB
		, Func const & op
		)
	{
		Blade outBlade{}; // okay uninitialized, each element is filled
		std::transform
			( std::cbegin(bladeA.theData)
			, std::cend(bladeA.theData)
			, std::cbegin(bladeB.theData)
			, std::begin(outBlade.theData)
			, op
			);
		return outBlade;
	}

	//! Addition of two blades (A+B)
	template <typename Blade>
	inline
	Blade
	operator+
		( Blade const & bladeA
		, Blade const & bladeB
		)
	{
		return binaryElementByElement
			( bladeA
			, bladeB
			, [] (double const & elemA, double const & elemB)
				{ return elemA+elemB; }
			);
	}

	//! Subtraction of two blades (A-B)
	template <typename Blade>
	inline
	Blade
	operator-
		( Blade const & bladeA
		, Blade const & bladeB
		)
	{
		return binaryElementByElement
			( bladeA
			, bladeB
			, [] (double const & elemA, double const & elemB)
				{ return elemA-elemB; }
			);
	}

	//! Double multiplication
	template <typename Blade>
	inline
	Blade
	operator*
		( double const & dub
		, Blade const & anyBlade
		)
	{
		Blade outBlade{}; // okay uninitialized, each element is filled
		std::transform
			( std::cbegin(anyBlade.theData)
			, std::cend(anyBlade.theData)
			, std::begin(outBlade.theData)
			, [& dub] (double const & elem) { return dub*elem; }
			);
		return outBlade;
	}

	//! Double multiplication
	template <typename Blade>
	inline
	Blade
	operator*
		( g3::Sca const & sca
		, Blade const & anyBlade
		)
	{
		double const & dub = sca.theData[0];
		return dub * anyBlade;
	}


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

	//
	// Duals (in 3D)
	//

	inline
	Tri
	operator*
		( Sca const & anySca
		, Tri const & tri
		)
	{
		// T = I*S = S*I
		double const & dub = tri.theData[0];
		return Tri{ (dub * anySca).theData };
		// return Tri{ anySca.theData[0] * tri.theData[0] };
	}

	inline
	Biv
	operator*
		( Vec const & anyVec
		, Tri const & tri
		)
	{
		// B = I*V = V*I
		double const & dub = tri.theData[0];
		return Biv{ (dub * anyVec).theData };
	}

	inline
	Vec
	operator*
		( Biv const & anyBiv
		, Tri const & tri
		)
	{
		// V = -I*B = -B*I
		double const & dub = tri.theData[0];
		// note negation
		return Vec{ (-dub * anyBiv).theData };
	}

	inline
	Sca
	operator*
		( Tri const & anyTri
		, Tri const & tri
		)
	{
		// S = T*T = -|T*T|
		double const & dub = tri.theData[0];
		// note negation
		return Sca{ (-dub * anyTri).theData };
	}

	inline
	ImSpin
	operator*
		( Tri const & tri
		, Spinor const & spin
		)
	{
		Tri const t1{ spin.theSca * tri };
		Vec const v1{ spin.theBiv * tri };
		return ImSpin{ v1, t1 };
	}

	inline
	Spinor
	operator*
		( Tri const & tri
		, ImSpin const & imsp
		)
	{
		Biv const b1{ imsp.theVec * tri };
		Sca const s1{ imsp.theTri * tri };
		return Spinor{ s1, b1 };
	}

	// Duals in reverse order
	inline Tri operator* (Tri const & tri, Sca const & anySca)
		{ return anySca*tri; }
	inline Biv operator* (Tri const & tri, Vec const & anyVec)
		{ return anyVec*tri; }
	inline Vec operator* (Tri const & tri, Biv const & anyBiv)
		{ return anyBiv*tri; }
	inline ImSpin operator* (Spinor const & anySpin, Tri const & tri )
		{ return tri*anySpin; }
	inline Spinor operator* (ImSpin const & anyImsp, Tri const & tri )
		{ return tri*anyImsp; }

	//
	// Math functions
	//

	//! Squared magnitude
	template <typename Blade>
	inline
	double
	magSq
		( Blade const & blade
		)
	{
		return prodComm(blade.theData, blade.theData);
	}

	//! Magnitude of blade
	template <typename Blade>
	inline
	double
	magnitude
		( Blade const & blade
		)
	{
		return std::sqrt(magSq(blade));
	}

	//! Decompose arbitrary blade into magnitude and direction interpretations
	template <typename Blade>
	inline
	std::pair<double, Blade>
	magDirFrom
		( Blade const & blade
		)
	{
		double const mag{ magnitude(blade) };
		Blade dir{ null<Blade>() };
		if (0. != mag)
		{
			dir = (1./mag) * blade;
		}
		return {mag, dir};
	}

	//! Exponential of a bivector
	inline
	Spinor
	exp
		( Biv const & spinAngle
		)
	{
		Spinor spin{ 1., zero<Biv>() }; // zero angle default result
		std::pair<double, Biv> const magdir{ magDirFrom(spinAngle) };
		double const & mag = magdir.first;
		Biv const & dir = magdir.second;
		if (isValid(dir)) // zero angle direction undefined - return default
		{
			spin = Spinor{ std::cos(mag), std::sin(mag)*dir };
		}
		return spin;
	}

	//
	// Composite operations
	//

	//! (Vec+Tri) result of (Vec)*(Biv)
	inline
	ImSpin
	operator*
		( Vec const & vec
		, Biv const & biv
		)
	{
		
		Vec const v1{ prodAnti(biv.theData, vec.theData) };
		Tri const t1{ prodComm(biv.theData, vec.theData) };
		return ImSpin{ v1, t1 };
	}

	//! (Vec+Tri) result of (vec)*(sca+biv)
	inline
	ImSpin
	operator*
		( Vec const & vec
		, Spinor const & spin
		)
	{
		Vec const v1{ spin.theSca * vec };
		Vec const v2{ prodAnti(vec.theData, spin.theBiv.theData) };
		Tri const t1{ prodComm(vec.theData, spin.theBiv.theData) };
		return ImSpin{ v1 + v2, t1 };
	}

	//! (Vec+Tri) result of (sca+biv)*(vec)
	inline
	ImSpin
	operator*
		( Spinor const & spin
		, Vec const & vec
		)
	{
		Vec const v1{ spin.theSca * vec };
		Vec const v2{ prodAnti(spin.theBiv.theData, vec.theData) };
		Tri const t1{ prodComm(spin.theBiv.theData, vec.theData) };
		return ImSpin{ v1 + v2, t1 };
	}

	//! (Vec+Tri) result of (vec+tri)*(sca+biv)
	inline
	ImSpin
	operator*
		( ImSpin const & imsp
		, Spinor const & spin
		)
	{
		ImSpin const i1{ imsp.theVec * spin };
		ImSpin const i2{ imsp.theTri * spin };
		return ImSpin{ (i1.theVec + i2.theVec), (i1.theTri + i2.theTri) };
	}

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


} // [g3]

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
