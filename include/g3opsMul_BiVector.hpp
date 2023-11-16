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


#ifndef engabra_g3opsMul_BiVector_INCL_
#define engabra_g3opsMul_BiVector_INCL_

/*! \file
 * \brief Implementation of operator*() for BiVector*{...}
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


namespace engabra
{

namespace g3
{
	//
	// "Backward" rank order:
	// -- redirect to forward op+() functions (from files included above)
	//

	/*! \brief BiVector from BiVector * double.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_BiVector.cpp DoxyExampleDub
	 */
	inline
	BiVector
	operator*
		( BiVector const & bivA
		, double const & dubB
		)
	{
		return dubB * bivA;
	}

	/*! \brief BiVector from BiVector * Scalar.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_BiVector.cpp DoxyExampleSca
	 */
	inline
	BiVector
	operator*
		( BiVector const & bivA
		, Scalar const & scaB
		)
	{
		return scaB * bivA;
	}

	/*! \brief ImSpin from BiVector * Vector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_BiVector.cpp DoxyExampleVec
	 */
	inline
	ImSpin
	operator*
		( BiVector const & bivA
		, Vector const & vecB
		)
	{
		// B*v = B.v + B^v = (-I*b).v + B^v
		Vector const anti{ priv::prodAnti(bivA.theData, vecB.theData) };
		TriVector const symm{ priv::prodComm(bivA.theData, vecB.theData) };
		return ImSpin{ -anti, symm };
	}

	//
	// "Self-type" multiply
	//

	/*! \brief Spinor from BiVector * BiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_BiVector.cpp DoxyExampleBiv
	 */
	inline
	Spinor
	operator*
		( BiVector const & bivA
		, BiVector const & bivB
		)
	{
		Scalar const symm{ priv::prodComm(bivA.theData, bivB.theData) };
		BiVector const anti{ priv::prodAnti(bivA.theData, bivB.theData) };
		// note negation (e.g. A*B = I*a*I*b = I*I*a*b = -a*b)
		return Spinor{ -symm, -anti };
	}

	//
	// "Forward" rank order:
	//

	/*! \brief Vector from BiVector * TriVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_BiVector.cpp DoxyExampleTri
	 */
	inline
	Vector
	operator*
		( BiVector const & bivA
		, TriVector const & triB
		)
	{
		// V = B*T = (-Ib)*(Is)
		return Vector
			{ - triB.theData[0] * bivA.theData[0]
			, - triB.theData[0] * bivA.theData[1]
			, - triB.theData[0] * bivA.theData[2]
			};
	}

	/*! \brief Spinor from BiVector * Spinor.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_BiVector.cpp DoxyExampleSpin
	 */
	inline
	Spinor
	operator*
		( BiVector const & bivA
		, Spinor const & spinB
		)
	{
		BiVector const biv1{ bivA * spinB.theSca };
		Spinor const spin1{ bivA * spinB.theBiv };
		return Spinor{ spin1.theSca, biv1 + spin1.theBiv };
	}

	/*! \brief ImSpin from BiVector * ImSpin.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_BiVector.cpp DoxyExampleImsp
	 */
	inline
	ImSpin
	operator*
		( BiVector const & bivA
		, ImSpin const & imspB
		)
	{
		ImSpin const imsp1{ bivA * imspB.theVec };
		Vector const vec1{ bivA * imspB.theTri };
		return ImSpin{ imsp1.theVec + vec1, imsp1.theTri };
	}

	/*! \brief DirPlex from BiVector * ComPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_BiVector.cpp DoxyExampleCplx
	 */
	inline
	DirPlex
	operator*
		( BiVector const & bivA
		, ComPlex const & mvB
		)
	{
		return DirPlex
			{ bivA * mvB.theTri
			, bivA * mvB.theSca
			};
	}

	/*! \brief MultiVector from BiVector * DirPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_BiVector.cpp DoxyExampleDplx
	 */
	inline
	MultiVector
	operator*
		( BiVector const & bivA
		, DirPlex const & dplxB
		)
	{
		return MultiVector
			{ bivA * dplxB.theVec
			+ bivA * dplxB.theBiv
			};
	}

	/*! \brief MultiVector from BiVector * MultiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_BiVector.cpp DoxyExampleMvec
	 */
	inline
	MultiVector
	operator*
		( BiVector const & bivA
		, MultiVector const & mvB
		)
	{
		BiVector const & biv1{ bivA * mvB.theSca };
		ImSpin const & imsp1{ bivA * mvB.theVec };
		Spinor const & spin1{ bivA * mvB.theBiv };
		Vector const & vec1{ bivA * mvB.theTri };
		return MultiVector
			{ spin1.theSca
			, vec1 + imsp1.theVec
			, biv1 + spin1.theBiv
			, imsp1.theTri
			};
	}


	/*! \brief ResType from BiVector * Type.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_BiVector.cpp DoxyExampleType
	 */


} // [g3]

} // [engabra]


#endif // engabra_g3opsMul_BiVector_INCL_
