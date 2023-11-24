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


#ifndef engabra_g3opsMul_ComPlex_INCL_
#define engabra_g3opsMul_ComPlex_INCL_

/*! \file
 * \brief Implementation of operator*() for ComPlex*{...}
 */
 /*
 * Example:
 * \snippet test_g3opsMul_ComPlex.cpp DoxyExample01
 *
 */


#include "g3type.hpp"

#include "g3_private.hpp"

#include "g3opsAdd.hpp"
#include "g3opsSub.hpp"
#include "g3opsUni.hpp"

#include "g3opsMul_double.hpp"
#include "g3opsMul_Scalar.hpp"
#include "g3opsMul_Vector.hpp"
#include "g3opsMul_BiVector.hpp"
#include "g3opsMul_TriVector.hpp"
#include "g3opsMul_Spinor.hpp"
#include "g3opsMul_ImSpin.hpp"


namespace engabra
{

namespace g3
{
	//
	// "Backward" rank order:
	// -- redirect to forward op+() functions (from files included above)
	//

	/*! \brief ComPlex from ComPlex * double.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ComPlex.cpp DoxyExampleDub
	 */
	inline
	ComPlex
	operator*
		( ComPlex const & cplxA
		, double const & dubB
		)
	{
		return dubB * cplxA; // ComPlex type is commuting
	}

	/*! \brief ComPlex from ComPlex * Scalar.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ComPlex.cpp DoxyExampleSca
	 */
	inline
	ComPlex
	operator*
		( ComPlex const & cplxA
		, Scalar const & scaB
		)
	{
		return scaB * cplxA; // ComPlex type is commuting
	}

	/*! \brief DirPlex from ComPlex * Vector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ComPlex.cpp DoxyExampleVec
	 */
	inline
	DirPlex
	operator*
		( ComPlex const & cplxA
		, Vector const & vecB
		)
	{
		return vecB * cplxA; // ComPlex type is commuting
	}

	/*! \brief DirPlex from ComPlex * BiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ComPlex.cpp DoxyExampleBiv
	 */
	inline
	DirPlex
	operator*
		( ComPlex const & cplxA
		, BiVector const & bivB
		)
	{
		return bivB * cplxA; // ComPlex type is commuting
	}

	/*! \brief ComPlex from ComPlex * TriVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ComPlex.cpp DoxyExampleTri
	 */
	inline
	ComPlex
	operator*
		( ComPlex const & cplxA
		, TriVector const & triB
		)
	{
		return triB * cplxA; // ComPlex type is commuting
	}

	/*! \brief MultiVector from ComPlex * Spinor.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ComPlex.cpp DoxyExampleSpin
	 */
	inline
	MultiVector
	operator*
		( ComPlex const & cplxA
		, Spinor const & spinB
		)
	{
		return spinB * cplxA; // ComPlex type is commuting
	}

	/*! \brief MultiVector from ComPlex * ImSpin.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ComPlex.cpp DoxyExampleImsp
	 */
	inline
	MultiVector
	operator*
		( ComPlex const & cplxA
		, ImSpin const & imspB
		)
	{
		return imspB * cplxA; // ComPlex type is commuting
	}

	//
	// "Self-type" multiply
	//

	/*! \brief ComPlex from ComPlex * ComPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ComPlex.cpp DoxyExampleCplx
	 */
	inline
	ComPlex
	operator*
		( ComPlex const & cplxA
		, ComPlex const & cplxB
		)
	{
		return ComPlex // classic complex multiply
			{ Scalar
				{ cplxA.theSca.theData[0] * cplxB.theSca.theData[0]
				- cplxA.theTri.theData[0] * cplxB.theTri.theData[0]
				}
			, TriVector
			  	{ cplxA.theSca.theData[0] * cplxB.theTri.theData[0]
				+ cplxA.theTri.theData[0] * cplxB.theSca.theData[0]
				}
			};
	}

	//
	// "Forward" rank order:
	//

	/*! \brief DirPlex from ComPlex * DirPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ComPlex.cpp DoxyExampleDplx
	 */
	inline
	DirPlex
	operator*
		( ComPlex const & cplxA
		, DirPlex const & dplxB
		)
	{
		return DirPlex
		{ Vector
			{ cplxA.theSca * dplxB.theVec
			+ dplxB.theBiv * cplxA.theTri
			}
		, BiVector
			{ cplxA.theSca * dplxB.theBiv
			+ dplxB.theVec * cplxA.theTri
			}
		};
	}

	/*! \brief MultiVector from ComPlex * MultiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ComPlex.cpp DoxyExampleMvec
	 */
	inline
	MultiVector
	operator*
		( ComPlex const & cplxA
		, MultiVector const & mvecB
		)
	{
		return MultiVector
			{ cplxA.theSca * mvecB.theSca
			+ cplxA.theTri * mvecB.theTri
			, cplxA.theSca * mvecB.theVec
			+ mvecB.theBiv * cplxA.theTri
			, cplxA.theSca * mvecB.theBiv
			+ mvecB.theVec * cplxA.theTri
			, cplxA.theSca * mvecB.theTri
			+ mvecB.theSca * cplxA.theTri
			};
	}



	/*! \brief ZZ from ComPlex * Type.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ComPlex.cpp DoxyExampleType
	 */


} // [g3]

} // [engabra]


#endif // engabra_g3opsMul_ComPlex_INCL_
