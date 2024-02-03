// 
// MIT License
// 
// Copyright (c) 2023 Stellacore Corporation
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


#ifndef engabra_test_g3opsMul_INCL_
#define engabra_test_g3opsMul_INCL_

/*! \file
\brief Contains data values useful for test code.

Example:
\snippet test_g3opsMul.cpp DoxyExampleData

*/


namespace engabra
{

namespace g3
{
	// test data
	namespace
	{
		// [DoxyExampleData]
		using namespace engabra::g3;

		// example data values
		// (test compound type are combination of these same blades)
		double const aDub{ 101. };
		double const bDub{ 103. };
		Scalar const aSca{  2. };
		Scalar const bSca{  3. };
		Vector const aVec{  5.,  7., 11. };
		Vector const bVec{ 13., 17., 19. };
		BiVector const aBiv{ 23., 29., 31. };
		BiVector const bBiv{ 37., 41., 43. };
		TriVector const aTri{ 47. };
		TriVector const bTri{ 53. };

			// [DoxyExampleData]

		// composite types reuse the blades above
		Spinor const aSpin{ aSca, aBiv };
		Spinor const bSpin{ bSca, bBiv };
		ImSpin const bImsp{ bVec, bTri };
		ImSpin const aImsp{ aVec, aTri };
		ComPlex const bCplx{ bSca, bTri };
		ComPlex const aCplx{ aSca, aTri };
		DirPlex const bDplx{ bVec, bBiv };
		DirPlex const aDplx{ aVec, aBiv };

		MultiVector const aMvec{ aSca, aVec, aBiv, aTri };
		MultiVector const bMvec{ bSca, bVec, bBiv, bTri };
	}

} // [g3]

} // [engabra]


#endif // engabra_test_g3opsMul_INCL_

