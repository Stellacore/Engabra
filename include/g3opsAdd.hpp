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


#ifndef engabra_g3opsAdd_INCL_
#define engabra_g3opsAdd_INCL_

/*! \file
\brief Binary operators associated with additive processes.

Example:
\snippet test_g3opsAdd.cpp DoxyExample01

*/


#include "g3const.hpp"
#include "g3traits.hpp"
#include "g3type.hpp"

#include <algorithm>
#include <numeric>


namespace engabra
{

namespace g3
{

namespace priv
{

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

} // [add]

	//
	// Addition of similar types
	//

	//! Addition of two blades (A+B)
	template
		< typename Blade
		, std::enable_if_t< is::blade<Blade>::value, bool> = true
		>
	inline
	Blade
	operator+
		( Blade const & bladeA
		, Blade const & bladeB
		)
	{
		return priv::binaryElementByElement
			( bladeA
			, bladeB
			, [] (double const & elemA, double const & elemB)
				{ return elemA+elemB; }
			);
	}


	//
	// Addition operators
	//


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

	//! (ImSpin) result of (ImSpin) + (ImSpin)
	inline
	ImSpin
	operator+
		( ImSpin const & imspA
		, ImSpin const & imspB
		)
	{
		return ImSpin
			{ imspA.theVec + imspB.theVec
			, imspA.theTri + imspB.theTri
			};
	}

	//! Uncommon combination, so promote result to MultiVector.
	inline
	MultiVector
	operator+
		( MultiVector const & mvA
		, MultiVector const & mvB
		)
	{
		return MultiVector
			{ mvA.theSca + mvB.theSca
			, mvA.theVec + mvB.theVec
			, mvA.theBiv + mvB.theBiv
			, mvA.theTri + mvB.theTri
			};
	}

	//
	// Subtraction operators
	//

	//! Subtraction of two blades (A-B)
	template
		< typename Blade
		, std::enable_if_t< is::blade<Blade>::value, bool> = true
		>
	inline
	Blade
	operator-
		( Blade const & bladeA
		, Blade const & bladeB
		)
	{
		return priv::binaryElementByElement
			( bladeA
			, bladeB
			, [] (double const & elemA, double const & elemB)
				{ return elemA-elemB; }
			);
	}

	//! Subtraction (Spinor) result of (Spinor) - (Spinor)
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

	//! Subtraction (ImSpin) result of (ImSpin) - (ImSpin)
	inline
	ImSpin
	operator-
		( ImSpin const & imspA
		, ImSpin const & imspB
		)
	{
		return ImSpin
			{ imspA.theVec - imspB.theVec
			, imspA.theTri - imspB.theTri
			};
	}

	//! Subtraction (MultiVector) result of (MultiVector) - (MultiVector)
	inline
	MultiVector
	operator-
		( MultiVector const & mvA
		, MultiVector const & mvB
		)
	{
		return MultiVector
			{ mvA.theSca - mvB.theSca
			, mvA.theVec - mvB.theVec
			, mvA.theBiv - mvB.theBiv
			, mvA.theTri - mvB.theTri
			};
	}

	//
	// Addition of composite types
	//

/*
	//! Uncommon combination, so promote result to MultiVector.
	inline
	MultiVector
	operator+
		( Scalar const & sca
		, Vector const & vec
		)
	{
		return MultiVector{ sca, vec, zero<BiVector>(), zero<TriVector>() };
	}
*/

	//! Uncommon combination, so promote result to MultiVector.
	inline
	Spinor
	operator+
		( Scalar const & sca
		, BiVector const & biv
		)
	{
		return Spinor{ sca, biv };
	}
//		return MultiVector{ sca, zero<Vector>(), zero<TriVector>() };


} // [g3]

} // [engabra]


#endif // engabra_g3opsAdd_INCL_
