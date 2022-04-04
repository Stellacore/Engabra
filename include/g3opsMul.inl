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


#ifndef engabra_g3opsMulinl_INCL_
#define engabra_g3opsMulinl_INCL_

/*! \file
\brief Contains definitions for g3opsMul.hpp with more lengthy implementations.

*/


namespace engabra
{

namespace g3
{

inline
MultiVector
operator*
	( MultiVector const & mvA
	, MultiVector const & mvB
	)
{
	MultiVector result{};

	result.theSca.theData[0]
		   = ( mvA.theSca.theData[0] * mvB.theSca.theData[0]
			 + mvA.theVec.theData[0] * mvB.theVec.theData[0]
			 + mvA.theVec.theData[1] * mvB.theVec.theData[1]
			 + mvA.theVec.theData[2] * mvB.theVec.theData[2] )
		   - ( mvA.theBiv.theData[0] * mvB.theBiv.theData[0]
			 + mvA.theBiv.theData[1] * mvB.theBiv.theData[1]
			 + mvA.theBiv.theData[2] * mvB.theBiv.theData[2]
			 + mvA.theTri.theData[0] * mvB.theTri.theData[0] )
		   ;
	result.theVec.theData[0]
		   = ( mvA.theVec.theData[0] * mvB.theSca.theData[0]
			 + mvA.theSca.theData[0] * mvB.theVec.theData[0]
			 + mvA.theBiv.theData[2] * mvB.theVec.theData[1]
			 + mvA.theVec.theData[2] * mvB.theBiv.theData[1] )
		   - ( mvA.theBiv.theData[1] * mvB.theVec.theData[2]
			 + mvA.theTri.theData[0] * mvB.theBiv.theData[0]
			 + mvA.theVec.theData[1] * mvB.theBiv.theData[2]
			 + mvA.theBiv.theData[0] * mvB.theTri.theData[0] )
		   ;
	result.theVec.theData[1]
		   = ( mvA.theVec.theData[1] * mvB.theSca.theData[0]
			 + mvA.theSca.theData[0] * mvB.theVec.theData[1]
			 + mvA.theBiv.theData[0] * mvB.theVec.theData[2]
			 + mvA.theVec.theData[0] * mvB.theBiv.theData[2] )
		   - ( mvA.theBiv.theData[2] * mvB.theVec.theData[0]
			 + mvA.theVec.theData[2] * mvB.theBiv.theData[0]
			 + mvA.theTri.theData[0] * mvB.theBiv.theData[1]
			 + mvA.theBiv.theData[1] * mvB.theTri.theData[0] )
		   ;
	result.theVec.theData[2]
		   = ( mvA.theVec.theData[2] * mvB.theSca.theData[0]
			 + mvA.theBiv.theData[1] * mvB.theVec.theData[0]
			 + mvA.theSca.theData[0] * mvB.theVec.theData[2]
			 + mvA.theVec.theData[1] * mvB.theBiv.theData[0] )
		   - ( mvA.theBiv.theData[0] * mvB.theVec.theData[1]
			 + mvA.theVec.theData[0] * mvB.theBiv.theData[1]
			 + mvA.theTri.theData[0] * mvB.theBiv.theData[2]
			 + mvA.theBiv.theData[2] * mvB.theTri.theData[0] )
		   ;
	result.theBiv.theData[0]
		   = ( mvA.theBiv.theData[0] * mvB.theSca.theData[0]
			 + mvA.theTri.theData[0] * mvB.theVec.theData[0]
			 + mvA.theVec.theData[1] * mvB.theVec.theData[2]
			 + mvA.theSca.theData[0] * mvB.theBiv.theData[0]
			 + mvA.theBiv.theData[2] * mvB.theBiv.theData[1]
			 + mvA.theVec.theData[0] * mvB.theTri.theData[0] )
		   - ( mvA.theVec.theData[2] * mvB.theVec.theData[1]
			 + mvA.theBiv.theData[1] * mvB.theBiv.theData[2] )
		   ;
	result.theBiv.theData[1]
		   = ( mvA.theBiv.theData[1] * mvB.theSca.theData[0]
			 + mvA.theVec.theData[2] * mvB.theVec.theData[0]
			 + mvA.theTri.theData[0] * mvB.theVec.theData[1]
			 + mvA.theSca.theData[0] * mvB.theBiv.theData[1]
			 + mvA.theBiv.theData[0] * mvB.theBiv.theData[2]
			 + mvA.theVec.theData[1] * mvB.theTri.theData[0] )
		   - ( mvA.theVec.theData[0] * mvB.theVec.theData[2]
			 + mvA.theBiv.theData[2] * mvB.theBiv.theData[0] )
		   ;
	result.theBiv.theData[2]
		   = ( mvA.theBiv.theData[2] * mvB.theSca.theData[0]
			 + mvA.theVec.theData[0] * mvB.theVec.theData[1]
			 + mvA.theTri.theData[0] * mvB.theVec.theData[2]
			 + mvA.theBiv.theData[1] * mvB.theBiv.theData[0]
			 + mvA.theSca.theData[0] * mvB.theBiv.theData[2]
			 + mvA.theVec.theData[2] * mvB.theTri.theData[0] )
		   - ( mvA.theVec.theData[1] * mvB.theVec.theData[0]
			 + mvA.theBiv.theData[0] * mvB.theBiv.theData[1] )
		   ;
	result.theTri.theData[0]
		   = ( mvA.theTri.theData[0] * mvB.theSca.theData[0]
			 + mvA.theBiv.theData[0] * mvB.theVec.theData[0]
			 + mvA.theBiv.theData[1] * mvB.theVec.theData[1]
			 + mvA.theBiv.theData[2] * mvB.theVec.theData[2]
			 + mvA.theVec.theData[0] * mvB.theBiv.theData[0]
			 + mvA.theVec.theData[1] * mvB.theBiv.theData[1]
			 + mvA.theVec.theData[2] * mvB.theBiv.theData[2]
			 + mvA.theSca.theData[0] * mvB.theTri.theData[0] )
		   ;

	return result;
}

} // [g3]

} // [engabra]


#endif // engabra_g3opsMulinl_INCL_
