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


#ifndef g3_g3ops_INCL_
#define g3_g3ops_INCL_


#include "g3.h"


namespace g3
{
	// TODO - maybe rename this file g3mult.h ?

	//
	// Multiplications (like types)
	//

	//! (Sca) result of (Sca) * (Sca)
	inline
	Sca
	operator*
		( Sca const & scaA
		, Sca const & scaB
		)
	{
		return Sca{ scaA.theData[0] * scaB.theData[0] };
	}

	//! (Sca+Biv) result of (Vec) * (Vec)
	inline
	Spinor
	operator*
		( Vec const & vecA
		, Vec const & vecB
		)
	{
		Sca const dot{ prodComm(vecA.theData, vecB.theData) };
		Biv const wedge{ prodAnti(vecA.theData, vecB.theData) };
		return Spinor{ dot, wedge };
	}

	//! (Sca+Biv) result of (Sca+Biv) * (Sca+Biv)
	inline
	Spinor
	operator*
		( Spinor const & spinA
		, Spinor const & spinB
		)
	{
		// access individual grades of each factor
		double const & alpha = spinA.theSca.theData[0];
		Biv const & bivA = spinA.theBiv;
		double const & beta = spinB.theSca.theData[0];
		Biv const & bivB = spinB.theBiv;

		// Biv-Biv product commutative and anti-commutative constituents
		// Note sign change is implemented in combination below
		double const symmAB{ prodComm(bivA.theData, bivB.theData) };
		Biv const antiAB{ prodAnti(bivA.theData, bivB.theData) };

		// Form scalar and bivector components of result
		// Note: include negative sign here (bivectors square to non-positive)
		Sca const scaC{ alpha*beta - symmAB };
		Biv const bivC{ alpha*bivB + beta*bivA - antiAB };

		return Spinor{ scaC, bivC };
	}

} // [g3]

#endif // g3_g3ops_INCL_
