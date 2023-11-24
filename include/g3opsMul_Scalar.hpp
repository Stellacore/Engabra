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


#ifndef engabra_g3opsMul_Scalar_INCL_
#define engabra_g3opsMul_Scalar_INCL_

/*! \file
 * \brief Implementation of operator*() for Scalar*{...}
 */
 /*
 * Example:
 * \snippet test_g3opsMul_Scalar.cpp DoxyExample01
 *
 */


#include "g3type.hpp"

#include "g3opsMul_double.hpp"


namespace engabra
{

namespace g3
{
	//
	// "Backward" rank order:
	// -- redirect to forward op+() functions (from files included above)
	//

	/*! \brief Scalar from Scalar * double.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Scalar.cpp DoxyExampleDub
	 */
	inline
	Scalar
	operator*
		( Scalar const & scaA
		, double const & dubB
		)
	{
		return dubB * scaA;
	}

	//
	// "Self-type" multiply
	//

	/*! \brief Scalar from Scalar * Scalar.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Scalar.cpp DoxyExampleSca
	 */
	inline
	Scalar
	operator*
		( Scalar const & scaA
		, Scalar const & scaB
		)
	{
		return Scalar{ scaA.theData[0] * scaB.theData[0] };
	}

	//
	// "Forward" rank order:
	//

	/*! \brief Vector from Scalar * Vector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Scalar.cpp DoxyExampleVec
	 */
	inline
	Vector
	operator*
		( Scalar const & scaA
		, Vector const & vecB
		)
	{
		return Vector
			{ scaA.theData[0] * vecB.theData[0]
			, scaA.theData[0] * vecB.theData[1]
			, scaA.theData[0] * vecB.theData[2]
			};
	}

	/*! \brief BiVector from Scalar * BiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Scalar.cpp DoxyExampleBiv
	 */
	inline
	BiVector
	operator*
		( Scalar const & scaA
		, BiVector const & bivB
		)
	{
		return BiVector
			{ scaA.theData[0] * bivB.theData[0]
			, scaA.theData[0] * bivB.theData[1]
			, scaA.theData[0] * bivB.theData[2]
			};
	}

	/*! \brief TriVector from Scalar * TriVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Scalar.cpp DoxyExampleTri
	 */
	inline
	TriVector
	operator*
		( Scalar const & scaA
		, TriVector const & triB
		)
	{
		return TriVector{ scaA.theData[0] * triB.theData[0] };
	}

	/*! \brief Spinor from Scalar * Spinor.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Scalar.cpp DoxyExampleSpin
	 */
	inline
	Spinor
	operator*
		( Scalar const & scaA
		, Spinor const & spinB
		)
	{
		return Spinor
			{ Scalar
				{ scaA.theData[0] * spinB.theSca.theData[0] }
			, BiVector
				{ scaA.theData[0] * spinB.theBiv.theData[0]
				, scaA.theData[0] * spinB.theBiv.theData[1]
				, scaA.theData[0] * spinB.theBiv.theData[2]
				}
			};
	}

	/*! \brief ImSpin from Scalar * ImSpin.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Scalar.cpp DoxyExampleImsp
	 */
	inline
	ImSpin
	operator*
		( Scalar const & scaA
		, ImSpin const & imspB
		)
	{
		return ImSpin
			{ Vector
				{ scaA.theData[0] * imspB.theVec.theData[0]
				, scaA.theData[0] * imspB.theVec.theData[1]
				, scaA.theData[0] * imspB.theVec.theData[2]
				}
			, TriVector
				{ scaA.theData[0] * imspB.theTri.theData[0] }
			};
	}

	/*! \brief ComPlex from Scalar * ComPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Scalar.cpp DoxyExampleCplx
	 */
	inline
	ComPlex
	operator*
		( Scalar const & scaA
		, ComPlex const & cplxB
		)
	{
		return ComPlex
			{ scaA.theData[0] * cplxB.theSca.theData[0]
			, scaA.theData[0] * cplxB.theTri.theData[0]
			};
	}

	/*! \brief DirPlex from Scalar * DirPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Scalar.cpp DoxyExampleDplx
	 */
	inline
	DirPlex
	operator*
		( Scalar const & scaA
		, DirPlex const & dplxB
		)
	{
		return DirPlex
			{ Vector
				{ scaA.theData[0] * dplxB.theVec.theData[0]
				, scaA.theData[0] * dplxB.theVec.theData[1]
				, scaA.theData[0] * dplxB.theVec.theData[2]
				}
			, BiVector
				{ scaA.theData[0] * dplxB.theBiv.theData[0]
				, scaA.theData[0] * dplxB.theBiv.theData[1]
				, scaA.theData[0] * dplxB.theBiv.theData[2]
				}
			};
	}

	/*! \brief MultiVector from Scalar * MultiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Scalar.cpp DoxyExampleMvec
	 */
	inline
	MultiVector
	operator*
		( Scalar const & scaA
		, MultiVector const & mvB
		)
	{
		return MultiVector
			{ Scalar
				{ scaA.theData[0] * mvB.theSca.theData[0] }
			, Vector
				{ scaA.theData[0] * mvB.theVec.theData[0]
				, scaA.theData[0] * mvB.theVec.theData[1]
				, scaA.theData[0] * mvB.theVec.theData[2]
				}
			, BiVector
				{ scaA.theData[0] * mvB.theBiv.theData[0]
				, scaA.theData[0] * mvB.theBiv.theData[1]
				, scaA.theData[0] * mvB.theBiv.theData[2]
				}
			, TriVector
				{ scaA.theData[0] * mvB.theTri.theData[0] }
			};
	}

	/*! \brief Scalar from Scalar * Type.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Scalar.cpp DoxyExampleType
	 */


} // [g3]

} // [engabra]


#endif // engabra_g3opsMul_Scalar_INCL_
