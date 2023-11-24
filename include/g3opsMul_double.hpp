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


#ifndef engabra_g3opsMul_double_INCL_
#define engabra_g3opsMul_double_INCL_

/*! \file
 * \brief Implementation of operator*() for double*{...}
 */
 /*
 * Example:
 * \snippet test_g3opsMul_double.cpp DoxyExample01
 *
 */


#include "g3type.hpp"


namespace engabra
{

namespace g3
{
	//
	// "Backward" rank order:
	// -- redirect to forward op+() functions (from files included above)
	//

	//
	// "Self-type" multiply
	//

	//Default: double * double -- via language

	//
	// "Forward" rank order:
	//

	/*! \brief Scalar from double * Scalar..
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_double.cpp DoxyExampleSca
	 */
	inline
	Scalar
	operator*
		( double const & dubA
		, Scalar const & scaB
		)
	{
		return Scalar{ dubA * scaB.theData[0] };
	}

	/*! \brief Vector from double * Vector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_double.cpp DoxyExampleVec
	 */
	inline
	Vector
	operator*
		( double const & dubA
		, Vector const & vecB
		)
	{
		return Vector
			{ dubA * vecB.theData[0]
			, dubA * vecB.theData[1]
			, dubA * vecB.theData[2]
			};
	}

	/*! \brief BiVector from double * BiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_double.cpp DoxyExampleBiv
	 */
	inline
	BiVector
	operator*
		( double const & dubA
		, BiVector const & bivB
		)
	{
		return BiVector
			{ dubA * bivB.theData[0]
			, dubA * bivB.theData[1]
			, dubA * bivB.theData[2]
			};
	}

	/*! \brief TriVector from double * TriVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_double.cpp DoxyExampleTri
	 */
	inline
	TriVector
	operator*
		( double const & dubA
		, TriVector const & triB
		)
	{
		return TriVector{ dubA * triB.theData[0] };
	}

	/*! \brief Spinor from double * Spinor.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_double.cpp DoxyExampleSpin
	 */
	inline
	Spinor
	operator*
		( double const & dubA
		, Spinor const & spinB
		)
	{
		return Spinor
			{ Scalar
				{ dubA * spinB.theSca.theData[0] }
			, BiVector
				{ dubA * spinB.theBiv.theData[0]
				, dubA * spinB.theBiv.theData[1]
				, dubA * spinB.theBiv.theData[2]
				}
			};
	}

	/*! \brief ImSpin from double * ImSpin.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_double.cpp DoxyExampleImsp
	 */
	inline
	ImSpin
	operator*
		( double const & dubA
		, ImSpin const & imspB
		)
	{
		return ImSpin
			{ Vector
				{ dubA * imspB.theVec.theData[0]
				, dubA * imspB.theVec.theData[1]
				, dubA * imspB.theVec.theData[2]
				}
			, TriVector
				{ dubA * imspB.theTri.theData[0] }
			};
	}

	/*! \brief ComPlex from double * ComPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_double.cpp DoxyExampleCplx
	 */
	inline
	ComPlex
	operator*
		( double const & dubA
		, ComPlex const & cplxB
		)
	{
		return ComPlex
			{ dubA * cplxB.theSca.theData[0]
			, dubA * cplxB.theTri.theData[0]
			};
	}

	/*! \brief DirPlex from double * DirPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_double.cpp DoxyExampleDplx
	 */
	inline
	DirPlex
	operator*
		( double const & dubA
		, DirPlex const & dplxB
		)
	{
		return DirPlex
			{ Vector
				{ dubA*dplxB.theVec.theData[0]
				, dubA*dplxB.theVec.theData[1]
				, dubA*dplxB.theVec.theData[2]
				}
			, BiVector
				{ dubA*dplxB.theBiv.theData[0]
				, dubA*dplxB.theBiv.theData[1]
				, dubA*dplxB.theBiv.theData[2]
				}
			};
	}

	/*! \brief MultiVector from double * MultiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_double.cpp DoxyExampleMvec
	 */
	inline
	MultiVector
	operator*
		( double const & dubA
		, MultiVector const & mvB
		)
	{
		return MultiVector
			{ Scalar
					{ dubA * mvB.theSca.theData[0] }
			, Vector
				{ dubA * mvB.theVec.theData[0]
				, dubA * mvB.theVec.theData[1]
				, dubA * mvB.theVec.theData[2]
				}
			, BiVector
				{ dubA * mvB.theBiv.theData[0]
				, dubA * mvB.theBiv.theData[1]
				, dubA * mvB.theBiv.theData[2]
				}
			, TriVector
				{ dubA * mvB.theTri.theData[0] }
			};
	}

	/*! \brief Type from double * Type.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_double.cpp DoxyExampleType
	 */


} // [g3]

} // [engabra]


#endif // engabra_g3opsMul_double_INCL_
