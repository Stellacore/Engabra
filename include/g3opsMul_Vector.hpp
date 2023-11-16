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


#ifndef engabra_g3opsMul_Vector_INCL_
#define engabra_g3opsMul_Vector_INCL_

/*! \file
 * \brief Implementation of operator*() for Vector*{...}
 */
 /*
 * Example:
 * \snippet test_g3opsMul_Vector.cpp DoxyExample01
 *
 */


#include "g3type.hpp"

#include "g3_private.hpp"
#include "g3opsAdd.hpp"
#include "g3opsUni.hpp"

#include "g3opsMul_double.hpp"
#include "g3opsMul_Scalar.hpp"


namespace engabra
{

namespace g3
{
	//
	// "Backward" rank order:
	// -- redirect to forward op+() functions (from files included above)
	//

	/*! \brief Vector from Vector * double.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Vector.cpp DoxyExampleDub
	 */
	inline
	Vector
	operator*
		( Vector const & vecA
		, double const & dubB
		)
	{
		return dubB * vecA;
	}

	/*! \brief Vector from Vector * Scalar.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Vector.cpp DoxyExampleSca
	 */
	inline
	Vector
	operator*
		( Vector const & vecA
		, Scalar const & scaB
		)
	{
		return scaB * vecA;
	}

	//
	// "Self-type" multiply
	//

	/*! \brief Spinor from Vector * Vector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Vector.cpp DoxyExampleVec
	 */
	inline
	Spinor
	operator*
		( Vector const & vecA
		, Vector const & vecB
		)
	{
		Scalar const dot{ priv::prodComm(vecA.theData, vecB.theData) };
		BiVector const wedge{ priv::prodAnti(vecA.theData, vecB.theData) };
		return Spinor{ dot, wedge };
	}

	//
	// "Forward" rank order:
	//

	/*! \brief ImSpin from Vector * BiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Vector.cpp DoxyExampleBiv
	 */
	inline
	ImSpin
	operator*
		( Vector const & vecA
		, BiVector const & bivB
		)
	{
		// v*B = v.B + v^B = v.(-b*I) + v^B
		Vector const v1{ priv::prodAnti(vecA.theData, bivB.theData) };
		TriVector const t1{ priv::prodComm(vecA.theData, bivB.theData) };
		return ImSpin{ -v1, t1 };
	}

	/*! \brief BiVector from Vector * TriVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Vector.cpp DoxyExampleTri
	 */
	inline
	BiVector
	operator*
		( Vector const & vecA
		, TriVector const & triB
		)
	{
		// v*T = v*I*s
		return BiVector
			{ triB.theData[0] * vecA.theData[0]
			, triB.theData[0] * vecA.theData[1]
			, triB.theData[0] * vecA.theData[2]
			};
	}

	/*! \brief ImSpin from Vector * Spinor.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Vector.cpp DoxyExampleSpin
	 */
	inline
	ImSpin
	operator*
		( Vector const & vecA
		, Spinor const & spinB
		)
	{
		Vector const v1{ spinB.theSca.theData[0] * vecA };
		ImSpin const i2{ vecA * spinB.theBiv };
		return ImSpin{ i2.theVec + v1, i2.theTri };
	}

	/*! \brief Spinor from Vector * ImSpin.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Vector.cpp DoxyExampleImsp
	 */
	inline
	Spinor
	operator*
		( Vector const & vecA
		, ImSpin const & imspB
		)
	{
		// vecA * triB
		Spinor const s1{ vecA * imspB.theVec };
		BiVector const b2{ vecA * imspB.theTri };
		return Spinor{ s1.theSca, s1.theBiv + b2 };
	}

	/*! \brief DirPlex from Vector * ComPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Vector.cpp DoxyExampleCplx
	 */
	inline
	DirPlex
	operator*
		( Vector const & vecA
		, ComPlex const & mvB
		)
	{
		return DirPlex
			{ vecA * mvB.theSca
			, vecA * mvB.theTri
			};
	}

	/*! \brief MultiVector from Vector * DirPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Vector.cpp DoxyExampleDplx
	 */
	inline
	MultiVector
	operator*
		( Vector const & vecA
		, DirPlex const & dplxB
		)
	{
		return MultiVector
			{ vecA * dplxB.theVec
			+ vecA * dplxB.theBiv
			};
	}


	/*! \brief MultiVector from Vector * MultiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Vector.cpp DoxyExampleMvec
	 */
	inline
	MultiVector
	operator*
		( Vector const & vecA
		, MultiVector const & mvB
		)
	{
		Vector const vec1{ vecA * mvB.theSca };
		BiVector const biv1{ vecA * mvB.theTri };
		Spinor const spin1{ vecA * mvB.theVec };
		ImSpin const imsp1{ vecA * mvB.theBiv };
		return MultiVector
			{ spin1.theSca
			, vec1 + imsp1.theVec
			, biv1 + spin1.theBiv
			, imsp1.theTri
			};
	}

	/*! \brief ResType from Vector * Type.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Vector.cpp DoxyExampleType
	 */


} // [g3]

} // [engabra]


#endif // engabra_g3opsMul_Vector_INCL_
