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


#ifndef engabra_g3opsMul_TriVector_INCL_
#define engabra_g3opsMul_TriVector_INCL_

/*! \file
 * \brief Implementation of operator*() for TriVector*{...}
 */
 /*
 * Example:
 * \snippet test_g3opsMul_BiVector.cpp DoxyExample01
 *
 */


#include "g3type.hpp"

#include "g3_private.hpp"
#include "g3opsAdd.hpp"
#include "g3opsUni.hpp"

#include "g3opsMul_double.hpp"
#include "g3opsMul_Scalar.hpp"
#include "g3opsMul_Vector.hpp"
#include "g3opsMul_BiVector.hpp"


namespace engabra
{

namespace g3
{
	//
	// "Backward" rank order:
	// -- redirect to forward op+() functions (from files included above)
	//

	/*! \brief TriVector from TriVector * double.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_TriVector.cpp DoxyExampleDub
	 */
	inline
	TriVector
	operator*
		( TriVector const & triA
		, double const & dubB
		)
	{
		return TriVector{ dubB * triA.theData[0] };
	}

	/*! \brief TriVector from TriVector * Scalar.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_TriVector.cpp DoxyExampleSca
	 */
	inline
	TriVector
	operator*
		( TriVector const & triA
		, Scalar const & scaB
		)
	{
		// T = t*S = S*t
		return TriVector{ scaB.theData[0] * triA.theData[0] };
	}

	/*! \brief BiVector from TriVector * Vector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_TriVector.cpp DoxyExampleVec
	 */
	inline
	BiVector
	operator*
		( TriVector const & triA
		, Vector const & vecB
		)
	{
		// B = t*v = v*t
		return vecB * triA;
	}

	/*! \brief Vector from TriVector * BiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_TriVector.cpp DoxyExampleBiv
	 */
	inline
	Vector
	operator*
		( TriVector const & triA
		, BiVector const & bivB
		)
	{
		// V = t*B = B*t
		return bivB * triA;
	}

	//
	// "Self-type" multiply
	//

	/*! \brief Scalar from TriVector * TriVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_TriVector.cpp DoxyExampleTri
	 */
	inline
	Scalar
	operator*
		( TriVector const & triA
		, TriVector const & triB
		)
	{
		// S = T*T = -|T*T|
		// note negation
		return Scalar{ - triA.theData[0] * triB.theData[0] };
	}

	//
	// "Forward" rank order:
	//

	/*! \brief ImSpin from TriVector * Spinor.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_TriVector.cpp DoxyExampleSpin
	 */
	inline
	ImSpin
	operator*
		( TriVector const & triA
		, Spinor const & spinB
		)
	{
		TriVector const t1{ triA * spinB.theSca };
		Vector const v2{ triA * spinB.theBiv };
		return ImSpin{ v2, t1 };
	}

	/*! \brief Spinor from TriVector * ImSpin.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_TriVector.cpp DoxyExampleImsp
	 */
	inline
	Spinor
	operator*
		( TriVector const & triA
		, ImSpin const & imspB
		)
	{
		BiVector const b1{ triA * imspB.theVec };
		Scalar const s1{ triA * imspB.theTri };
		return Spinor{ s1, b1 };
	}

	/*! \brief ComPlex from TriVector * ComPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_TriVector.cpp DoxyExampleCplx
	 */
	inline
	ComPlex
	operator*
		( TriVector const & triA
		, ComPlex const & cplx
		)
	{
		return ComPlex
			{ triA * cplx.theTri
			, triA * cplx.theSca
			};
	}

	/*! \brief DirPlex from TriVector * DirPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_TriVector.cpp DoxyExampleDplx
	 */
	inline
	DirPlex
	operator*
		( TriVector const & triA
		, DirPlex const & dplx
		)
	{
		return DirPlex
			{ triA * dplx.theBiv
			, triA * dplx.theVec
			};
	}

	/*! \brief MultiVector from TriVector * MultiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_TriVector.cpp DoxyExampleMvec
	 */
	inline
	MultiVector
	operator*
		( TriVector const & triA
		, MultiVector const & mvB
		)
	{
		return MultiVector
			{ triA * mvB.theTri
			, triA * mvB.theBiv
			, triA * mvB.theVec
			, triA * mvB.theSca
			};
	}


	/*! \brief ResType from TriVector * Type.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_TriVector.cpp DoxyExampleType
	 */


} // [g3]

} // [engabra]


#endif // engabra_g3opsMul_TriVector_INCL_
