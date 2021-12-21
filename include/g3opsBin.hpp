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


#ifndef g3_g3opsBin_INCL_
#define g3_g3opsBin_INCL_

/*! \file
\brief Operator overload methods for G3 math operations (*,+,etc.).

*/


#include "g3types.hpp"


#include <algorithm>
#include <numeric>


namespace engabra
{

namespace g3
{
	// TODO - maybe rename this file g3mult.h ?

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

	//! Specialization - Subtraction of two spinors
	inline
	Spinor
	operator-
		( Spinor const & spinA
		, Spinor const & spinB
		)
	{
		return Spinor
			{ spinA.theSca - spinB.theSca
			, spinA.theBiv - spinB.theBiv
			};
	}

	//! (Spinor) result of (Spinor) + (Spinor)
	inline
	Spinor
	operator+
		( Spinor const & spinA
		, Spinor const & spinB
		)
	{
		return Spinor
			{ spinA.theSca + spinB.theSca
			, spinA.theBiv + spinB.theBiv
			};
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

	//! Double multiplication - specialized to Spinor
	template <>
	inline
	Spinor
	operator*
		( double const & dub
		, Spinor const & spin
		)
	{
		return Spinor{ dub*spin.theSca, dub*spin.theBiv };
	}

	//! Double multiplication
	template <typename Blade>
	inline
	Blade
	operator*
		( Scalar const & sca
		, Blade const & anyBlade
		)
	{
		double const & dub = sca.theData[0];
		return dub * anyBlade;
	}

	//
	// Multiplications (like types)
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

	//! (Scalar) result of (Scalar) * (Scalar)
	inline
	Scalar
	operator*
		( Scalar const & scaA
		, Scalar const & scaB
		)
	{
		return Scalar{ scaA.theData[0] * scaB.theData[0] };
	}

	//! (Scalar+BiVector) result of (Vector) * (Vector)
	inline
	Spinor
	operator*
		( Vector const & vecA
		, Vector const & vecB
		)
	{
		Scalar const dot{ prodComm(vecA.theData, vecB.theData) };
		BiVector const wedge{ prodAnti(vecA.theData, vecB.theData) };
		return Spinor{ dot, wedge };
	}

	//! (Scalar+BiVector) result of (Scalar+BiVector) * (Scalar+BiVector)
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
		double const symmAB{ prodComm(bivA.theData, bivB.theData) };
		BiVector const antiAB{ prodAnti(bivA.theData, bivB.theData) };

		// Form scalar and bivector components of result
		// Note: include negative sign here (bivectors square to non-positive)
		Scalar const scaC{ alpha*beta - symmAB };
		BiVector const bivC{ alpha*bivB + beta*bivA - antiAB };

		return Spinor{ scaC, bivC };
	}

	//
	// Duals (in 3D)
	//

	//! (Trivector) dual of a Scalar
	inline
	TriVector
	operator*
		( TriVector const & tri
		, Scalar const & anySca
		)
	{
		// T = I*S = S*I
		double const & dub = tri.theData[0];
		return TriVector{ (dub * anySca).theData };
		// return TriVector{ anySca.theData[0] * tri.theData[0] };
	}

	//! (Bivector) dual of a Vector
	inline
	BiVector
	operator*
		( TriVector const & tri
		, Vector const & anyVec
		)
	{
		// B = I*V = V*I
		double const & dub = tri.theData[0];
		return BiVector{ (dub * anyVec).theData };
	}

	//! (Vector) dual of a BiVector
	inline
	Vector
	operator*
		( TriVector const & tri
		, BiVector const & anyBiv
		)
	{
		// V = -I*B = -B*I
		double const & dub = tri.theData[0];
		// note negation
		return Vector{ (-dub * anyBiv).theData };
	}

	//! (Scalar) dual of a TriVector
	inline
	Scalar
	operator*
		( TriVector const & tri
		, TriVector const & anyTri
		)
	{
		// S = T*T = -|T*T|
		double const & dub = tri.theData[0];
		// note negation
		return Scalar{ (-dub * anyTri).theData };
	}

	//! (ImSpin) dual of a Spinor
	inline
	ImSpin
	operator*
		( TriVector const & tri
		, Spinor const & spin
		)
	{
		TriVector const t1{ tri * spin.theSca };
		Vector const v1{ tri * spin.theBiv };
		return ImSpin{ v1, t1 };
	}

	//! (Spinor) dual of an ImSpin
	inline
	Spinor
	operator*
		( TriVector const & tri
		, ImSpin const & imsp
		)
	{
		BiVector const b1{ tri * imsp.theVec };
		Scalar const s1{ tri * imsp.theTri };
		return Spinor{ s1, b1 };
	}

	// Duals in reverse order
	//! Specialization TriVector dual of Scalar in reverse order
	inline TriVector operator* (Scalar const & anySca, TriVector const & tri)
		{ return anySca*tri; }
	//! Specialization BiVector dual of Vector in reverse order
	inline BiVector operator* (Vector const & anyVec, TriVector const & tri)
		{ return anyVec*tri; }
	//! Specialization Vector dual of BiVector in reverse order
	inline Vector operator* (BiVector const & anyBiv, TriVector const & tri)
		{ return anyBiv*tri; }
	//! Specialization ImSpin dual of Spinor in reverse order
	inline ImSpin operator* (Spinor const & anySpin, TriVector const & tri )
		{ return tri*anySpin; }
	//! Specialization Spinor dual of ImSpin in reverse order
	inline Spinor operator* (ImSpin const & anyImsp, TriVector const & tri )
		{ return tri*anyImsp; }


	//
	// Composite operations
	//

	//! (Vector+TriVector) result of (Vector)*(BiVector)
	inline
	ImSpin
	operator*
		( Vector const & vec
		, BiVector const & biv
		)
	{
		Vector const v1{ prodAnti(biv.theData, vec.theData) };
		TriVector const t1{ prodComm(biv.theData, vec.theData) };
		return ImSpin{ v1, t1 };
	}

	//! (Vector+TriVector) result of (Vector)*(Scalar+BiVector)
	inline
	ImSpin
	operator*
		( Vector const & vec
		, Spinor const & spin
		)
	{
		Vector const v1{ spin.theSca * vec };
		Vector const v2{ prodAnti(vec.theData, spin.theBiv.theData) };
		TriVector const t1{ prodComm(vec.theData, spin.theBiv.theData) };
		return ImSpin{ v1 + v2, t1 };
	}

	//! (Vector+TriVector) result of (Scalar+BiVector)*(Vector)
	inline
	ImSpin
	operator*
		( Spinor const & spin
		, Vector const & vec
		)
	{
		Vector const v1{ spin.theSca * vec };
		Vector const v2{ prodAnti(spin.theBiv.theData, vec.theData) };
		TriVector const t1{ prodComm(spin.theBiv.theData, vec.theData) };
		return ImSpin{ v1 + v2, t1 };
	}

	//! (Vector+TriVector) result of (Vector+TriVector)*(Scalar+BiVector)
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

} // [g3]

} // [engabra]

#endif // g3_g3opsBin_INCL_
