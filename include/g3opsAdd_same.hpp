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


#ifndef engabra_g3opsAdd_same_INCL_
#define engabra_g3opsAdd_same_INCL_

/*! \file
\brief Binary addition operators for like types.

\note All GA addition operations are fundamentally commutative
such that (A+B)=(B+A)

Example:
\snippet test_g3opsAdd_same.cpp DoxyExample01

*/


#include "g3type.hpp"
#include "g3_private.hpp"

#include <algorithm>
#include <numeric>


namespace engabra
{

namespace g3
{

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

	//! (ComPlex) result of (ComPlex) + (ComPlex)
	inline
	ComPlex
	operator+
		( ComPlex const & cplxA
		, ComPlex const & cplxB
		)
	{
		return ComPlex
			{ cplxA.theSca + cplxB.theSca
			, cplxA.theTri + cplxB.theTri
			};
	}

	//! (DirPlex) result of (DirPlex) + (DirPlex)
	inline
	DirPlex
	operator+
		( DirPlex const & dplxA
		, DirPlex const & dplxB
		)
	{
		return DirPlex
			{ dplxA.theVec + dplxB.theVec
			, dplxA.theBiv + dplxB.theBiv
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


} // [g3]

} // [engabra]


#endif // engabra_g3opsAdd_same_INCL_
