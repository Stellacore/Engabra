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
		Vector const v1
			{ spinB.theSca.theData[0] * vecA.theData[0]
			, spinB.theSca.theData[0] * vecA.theData[1]
			, spinB.theSca.theData[0] * vecA.theData[2]
			};
		Vector const v2
			{ priv::prodAnti(vecA.theData, spinB.theBiv.theData) };
		TriVector const t2
			{ priv::prodComm(vecA.theData, spinB.theBiv.theData) };
		return ImSpin{ -v2 + v1, t2 };
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
		Vector const & v1 = vecA;
		Vector const & v2 = imspB.theVec;
		TriVector const & t2 = imspB.theTri;
		// v1 * v2
		Scalar const sca_v1v2{ priv::prodComm(v1.theData, v2.theData) };
		BiVector const biv_v1v2{ priv::prodAnti(v1.theData, v2.theData) };
		// v1 * t2
		BiVector const biv_v1t2
			{ v1.theData[0] * t2.theData[0]
			, v1.theData[1] * t2.theData[0]
			, v1.theData[2] * t2.theData[0]
			};
		return Spinor
			{ sca_v1v2
			, BiVector
				{ biv_v1v2.theData[0] + biv_v1t2.theData[0]
				, biv_v1v2.theData[1] + biv_v1t2.theData[1]
				, biv_v1v2.theData[2] + biv_v1t2.theData[2]
				}
			};
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
			{ Vector
				{ vecA.theData[0] * mvB.theSca.theData[0]
				, vecA.theData[1] * mvB.theSca.theData[0]
				, vecA.theData[2] * mvB.theSca.theData[0]
				}
			, BiVector
				{ vecA.theData[0] * mvB.theTri.theData[0]
				, vecA.theData[1] * mvB.theTri.theData[0]
				, vecA.theData[2] * mvB.theTri.theData[0]
				}
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
		Vector const & v1 = vecA;
		Vector const & v2 = dplxB.theVec;
		BiVector const & b2 = dplxB.theBiv;
		// v1 * v2
		Scalar const sca_v1v2{ priv::prodComm(v1.theData, v2.theData) };
		BiVector const biv_v1v2{ priv::prodAnti(v1.theData, v2.theData) };
		// v1 * b2 = v1 * I*(-Ib2) // negation applied in return below
		Vector const vec_v1b2{ priv::prodAnti(v1.theData, b2.theData) };
		TriVector const tri_v1b2{ priv::prodComm(v1.theData, b2.theData) };
		return MultiVector
			{ sca_v1v2
			, -vec_v1b2
			, biv_v1v2
			, tri_v1b2
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
		Vector const vec1
			{ vecA.theData[0] * mvB.theSca.theData[0]
			, vecA.theData[1] * mvB.theSca.theData[0]
			, vecA.theData[2] * mvB.theSca.theData[0]
			};
		BiVector const biv1
			{ vecA.theData[0] * mvB.theTri.theData[0]
			, vecA.theData[1] * mvB.theTri.theData[0]
			, vecA.theData[2] * mvB.theTri.theData[0]
			};
		// vecA * mvB.theVec
		Spinor const spin1
			{ Scalar
				{ priv::prodComm(vecA.theData, mvB.theVec.theData) }
			, BiVector
				{ priv::prodAnti(vecA.theData, mvB.theVec.theData) }
			};
		// vecA * mvB.theBiv
		ImSpin const imsp1
			{ Vector // negation applied in return below)
				{ priv::prodAnti(vecA.theData, mvB.theBiv.theData) }
			, TriVector
				{ priv::prodComm(vecA.theData, mvB.theBiv.theData) }
			};
		return MultiVector
			{ spin1.theSca
			, vec1 + (-imsp1.theVec)
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
