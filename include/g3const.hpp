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


#ifndef engabra_g3const_INCL_
#define engabra_g3const_INCL_

/*! \file
\brief Useful constants and entities (zero, unity, basis entities, etc).

\b Overview

General groups include:

\arg "zero values" - various entities that operate as zero (e.g. 0*x=0)

\arg "pi values" - numeric values representing various useful fractions
and multiples of 'pi'.

\arg "turning values" - often less confusing that pi fractions for
specifying physical angles E.g. full, half, quarter turns.

\arg "basis values" - a collection of mutually orthogonal unitary elements
(have magnitude of 1) that form the algebraic basis of G3 algebra
(ref below).

\b Basis \b Elements

The basis elements are:

\arg \b Scalar: \b e0 - scalar basis (this is the same as scalar value 1).

\arg \b Vector: \b e1,\b e2,\b e3 - collection of vectors spanning 3D space.
They are mutually orthogonal with dextral chirality in the sense that
the unit trivector (unit pseudo-scalar) is defined by cyclic orderings,
e1*e2*e3, e2*e3*e1, and e3*e1*e2. Individual elements square to 1
(e.g. e2*e2=1, etc). These bases vectors are often associated with "x",
"y", and "z" cartesian axes.

\arg \b BiVector: \b e23,\b e31,\b e12 - collection of bivectors spanning
3D space. They are mutually orthogonal with dextral chirality in the sense
that: e23*e31*e12 = e31*e12*e23 = e12*e23*e31 = 1. Individual elements
square to -1 (e.g. e31*e31=-1, etc). The ordering is consistent with
the duals of the vector basis (e.g. e23=dual(e1), etc.). These basis
bivectors are often associated with the "yz", "zx" and "xy" planes of
a Cartesian coordinate system.

\arg \b TriVector: \b e123 - unit trivector and pseudo-scalar of the
algebra which represents the magnitude and chirality of the unit volume
in 3D space. This is consistent with the triple product of basis vectors,
in any cyclic permutation (e.g. e123=e1*e2*e3, etc). This basis trivector
is often denoted with capital 'I' or 'J').

\note
Constant numeric values for representing "null" components (based on
numeric_limits quiet_NaN values) are contained in the g3validity.hpp
header file.

*/


#include "g3type.hpp"

#include <cmath>


namespace engabra
{

namespace g3
{

	//
	// Constants
	//

	//! Classic value of Pi (consistent with gnu math library)
	constexpr double pi{ 3.141592653589793 };
	//! Convenience mnemonic for Pi/2.
	constexpr double piHalf{ .5 * pi };
	//! Convenience mnemonic for Pi/4.
	constexpr double piQtr{ .5 * piHalf };

	//! Angle associated with a full turn (rotation returning to start) [rad]
	constexpr double turnFull{ 2.*pi };
	//! Angle associated with a half turn (pointing opposite direction) [rad]
	constexpr double turnHalf{ pi };
	//! Angle associated with quarter turn (pointing orthogonal direction) [rad]
	constexpr double turnQtr{ piHalf };

	//
	// Null instances
	//

	//! Generic Not-A-Number for individual values
	constexpr double nan{ std::numeric_limits<double>::quiet_NaN() };

	//! Null instance for any type constructable from 'double' argument.
	template <typename Type>
	inline
	constexpr
	Type
	null
		()
	{
		return Type{ nan };
	}

	//
	// Null/NaN templates for the various G3 types
	//

	// null<Scalar> handled by default function
	/*
	//! Null value - specialization for Scalar
	template <>
	inline
	constexpr
	Scalar
	null<Scalar>
		()
	{
		return Scalar{ nan };
	}
	*/

	//! Null value - specialization for Vector
	template <>
	inline
	constexpr
	Vector
	null<Vector>
		()
	{
		return Vector{ nan, nan, nan };
	}

	//! Null value - specialization for BiVector
	template <>
	inline
	constexpr
	BiVector
	null<BiVector>
		()
	{
		return BiVector{ nan, nan, nan };
	}

	// null<Tri> handled by default function
	/*
	//! Null value - specialization for TriVector
	template <>
	inline
	constexpr
	TriVector
	null<TriVector>
		()
	{
		return TriVector{ nan };
	}
	*/

	//! Null value - specialization for Spinor
	template <>
	inline
	constexpr
	Spinor
	null<Spinor>()
	{
		return Spinor{ null<Scalar>(), null<BiVector>() };
	}

	//! Null value - specialization for ImSpin
	template <>
	inline
	constexpr
	ImSpin
	null<ImSpin>()
	{
		return ImSpin{ null<Vector>(), null<TriVector>() };
	}

	//! Null value - specialization for ComPlex
	template <>  // NOTE: can't be const because of ctors
	inline
	ComPlex
	null<ComPlex>()
	{
		constexpr Scalar sca{ null<Scalar>() };
		constexpr TriVector tri{ null<TriVector>() };
		return ComPlex{ sca, tri };
	}

	//! Null value - specialization for DirPlex
	template <>
	inline
	constexpr
	DirPlex
	null<DirPlex>()
	{
		return DirPlex{ null<Vector>(), null<BiVector>() };
	}

	//
	// Zero values
	//

	//! Zero value instance of requested Type
	template <typename Type>
	inline
	constexpr
	Type
	zero
		()
	{
		return Type{ 0. };
	}

	/*
	// NOTE: Scalar handled by default template
	//! Zero as a Scalar instance
	template <>
	constexpr
	Scalar
	zero<Scalar>()
	{
		return Scalar{ 0. };
	}
	*/

	//! Zero as a Vector instance
	template <>
	inline
	constexpr
	Vector
	zero<Vector>()
	{
		return Vector{ 0., 0., 0. };
	}

	//! Zero as a BiVector instance
	template <>
	inline
	constexpr
	BiVector
	zero<BiVector>()
	{
		return BiVector{ 0., 0., 0. };
	}

	/*
	// NOTE: TriVector handled by default template
	//! Zero as a TriVector instance
	template <>
	inline
	constexpr
	TriVector
	zero<TriVector>()
	{
		return TriVector{ 0. };
	}
	*/

	//! Zero as a Spinor instance
	template <>
	inline
	constexpr
	Spinor
	zero<Spinor>()
	{
		return Spinor{ zero<Scalar>(), zero<BiVector>() };
	}

	//! Zero as a ImSpin instance
	template <>
	inline
	constexpr
	ImSpin
	zero<ImSpin>()
	{
		return ImSpin{ zero<Vector>(), zero<TriVector>() };
	}

	//! Zero as a ComPlex instance
	template <>
	inline
	constexpr
	ComPlex
	zero<ComPlex>()
	{
		return ComPlex{ zero<Scalar>(), zero<TriVector>() };
	}

	//! Zero as a DirPlex instance
	template <>
	inline
	constexpr
	DirPlex
	zero<DirPlex>()
	{
		return DirPlex{ zero<Vector>(), zero<BiVector>() };
	}

	//! Zero as a MultiVector instance
	template <>
	inline  // NOTE: can't be constexpr since MultiVector has ctors
	MultiVector
	zero<MultiVector>()
	{
		return MultiVector
			{ zero<Scalar>()
			, zero<Vector>()
			, zero<BiVector>()
			, zero<TriVector>()
			};
	}

	//
	// Unity/Identity Values
	//

	//! Unit value instance - standard types also Scalar, TriVector
	template <typename Type>
	inline
	constexpr
	Type
	one()
	{
		return Type{ 1 };
	}

	//! Unit value for vector is all zeros
	template<>
	inline
	constexpr
	Vector
	one<Vector>()
	{
		return Vector{ zero<Vector>() };
	}

	//! Unit value for bivector is all zeros
	template<>
	inline
	constexpr
	BiVector
	one<BiVector>()
	{
		return BiVector{ zero<BiVector>() };
	}

	//! Unit value (identity multiplier)
	template<>
	inline
	constexpr
	Spinor
	one<Spinor>()
	{
		return Spinor{ one<Scalar>(), zero<BiVector>() };
	}

	//! Unit value (identity multiplier)
	template<>
	inline
	MultiVector
	one<MultiVector>()
	{
		return MultiVector
			{ one<Scalar>()
			, zero<Vector>()
			, zero<BiVector>()
			, zero<TriVector>()
			};
	}

	//
	// Basis blades
	//

	// Scalar basis element - (unique)
	static Scalar const e0{ 1. }; //!< Magnitude [e.g. 'units' in use]

	// Vector basis elements - Mutually orthogonal, dextral and unitary
	static Vector const e1{ 1., 0., 0. }; //!< First direction [e.g. 'x' axis]
	static Vector const e2{ 0., 1., 0. }; //!< Second direction [e.g. 'y' axis]
	static Vector const e3{ 0., 0., 1. }; //!< Third direction [e.g. 'z' axis]

	// Bivector basis elements - Mutually orthogonal, dextral and unitary
	static BiVector const e23{ 1., 0., 0. }; //!< First plane [e.g. 'yz' plane]
	static BiVector const e31{ 0., 1., 0. }; //!< Second plane [e.g. 'zx' plane]
	static BiVector const e12{ 0., 0., 1. }; //!< Third plane [e.g. 'xy' plane]

	// Trivector basis element (unique in 3D)
	static TriVector const e123{ 1. }; //!< Volume [e.g. 'xyz' dextral cube]

} // [g3]

} // [engabra]


#endif // engabra_g3const_INCL_
