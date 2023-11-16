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


#ifndef engabra_g3opsMul_Spinor_INCL_
#define engabra_g3opsMul_Spinor_INCL_

/*! \file
 * \brief Implementation of operator*() for Spinor*{...}
 */
 /*
 * Example:
 * \snippet test_g3opsMul_Spinor.cpp DoxyExample01
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


namespace engabra
{

namespace g3
{
	//
	// "Backward" rank order:
	// -- redirect to forward op+() functions (from files included above)
	//

	/*! \brief Spinor from Spinor * double.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Spinor.cpp DoxyExampleDub
	 */
	inline
	Spinor
	operator*
		( Spinor const & spinA
		, double const & dubB
		)
	{
		return Spinor{ dubB * spinA.theSca, dubB * spinA.theBiv };
	}

	/*! \brief Spinor from Spinor * Scalar.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Spinor.cpp DoxyExampleSca
	 */
	inline
	Spinor
	operator*
		( Spinor const & spinA
		, Scalar const & scaB
		)
	{
		return Spinor
			{ scaB.theData[0] * spinA.theSca
			, scaB.theData[0] * spinA.theBiv
			};
	}

	/*! \brief ImSpin from Spinor * Vector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Spinor.cpp DoxyExampleVec
	 */
	inline
	ImSpin
	operator*
		( Spinor const & spinA
		, Vector const & vecB
		)
	{
		// (Sca + Biv) * Vec
		// (ScaA * VecB) + (BivA * VecB)
		// (ScaA * VecB) + (BivA . VecB) + (BivA ^ VecB)
		// (ScaA * VecB) - I*(VecA . VecB) + (BivA ^ VecB)
		using priv::prodAnti;
		using priv::prodComm;
		Vector const v1{ spinA.theSca * vecB };
		Vector const v2{ prodAnti(spinA.theBiv.theData, vecB.theData) };
		TriVector const t1{ prodComm(spinA.theBiv.theData, vecB.theData) };
		// note negative to handle dual of biv.vec step
		return ImSpin{ v1 - v2, t1 };
	}

	/*! \brief Spinor from Spinor * BiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Spinor.cpp DoxyExampleBiv
	 */
	inline
	Spinor
	operator*
		( Spinor const & spinA
		, BiVector const & bivB
		)
	{
		BiVector const biv1{ spinA.theSca * bivB };
		Spinor const spin1{ spinA.theBiv * bivB };
		return Spinor{ spin1.theSca, spin1.theBiv + biv1 };
	}

	/*! \brief ImSpin from Spinor * TriVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Spinor.cpp DoxyExampleTri
	 */
	inline
	ImSpin
	operator*
		( Spinor const & spinA
		, TriVector const & triB
		)
	{
		return ImSpin{ triB * spinA.theBiv, triB * spinA.theSca };
	}

	//
	// "Self-type" multiply
	//

	/*! \brief Spinor from Spinor * Spinor.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Spinor.cpp DoxyExampleSpin
	 */
	inline
	Spinor
	operator*
		( Spinor const & spinA
		, Spinor const & spinB
		)
	{
		// access individual grades of each factor
		double const & alpha = spinA.theSca.theData[0];
		BiVector const & bivA = spinA.theBiv;
		double const & beta = spinB.theSca.theData[0];
		BiVector const & bivB = spinB.theBiv;

		// Biv-Biv product commutative and anti-commutative constituents
		// Note sign change is implemented in combination below
		double const symmAB{ priv::prodComm(bivA.theData, bivB.theData) };
		BiVector const antiAB{ priv::prodAnti(bivA.theData, bivB.theData) };

		// Form scalar and bivector components of result
		// Note: include negative sign here (bivectors square to non-positive)
		Scalar const scaC{ alpha*beta - symmAB };
		BiVector const bivC{ alpha*bivB + beta*bivA - antiAB };

		return Spinor{ scaC, bivC };
	}

	//
	// "Forward" rank order:
	//

	/*! \brief ImSpin from Spinor * ImSpin.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Spinor.cpp DoxyExampleImsp
	 */
	inline
	ImSpin
	operator*
		( Spinor const & spinA
		, ImSpin const & imspB
		)
	{
		ImSpin const imsp1{ spinA.theSca.theData[0] * imspB };
		ImSpin const imsp2{ spinA.theBiv * imspB };
		return { imsp1 + imsp2 };
	}

	/*! \brief MultiVector from Spinor * ComPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Spinor.cpp DoxyExampleCplx
	 */
	inline
	MultiVector
	operator*
		( Spinor const & spinA
		, ComPlex const & cplxB
		)
	{
		return MultiVector
			{ Scalar{ spinA.theSca.theData[0] * cplxB.theSca.theData[0] }
			, Vector{ spinA.theBiv * cplxB.theTri }
			, BiVector{ spinA.theBiv * cplxB.theSca.theData[0] }
			, TriVector{ spinA.theSca.theData[0] * cplxB.theTri }
			};
	}

	/*! \brief MultiVector from Spinor * DirPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Spinor.cpp DoxyExampleDplx
	 */
	inline
	MultiVector
	operator*
		( Spinor const & spinA
		, DirPlex const & dplxB
		)
	{
		Vector const vec{ spinA.theSca.theData[0] * dplxB.theVec };
		BiVector const biv{ spinA.theSca.theData[0] * dplxB.theBiv };
		ImSpin const imsp{ spinA.theBiv * dplxB.theVec };
		Spinor const spin{ spinA.theBiv * dplxB.theBiv };
		return MultiVector
			{ spin.theSca
			, vec + imsp.theVec
			, biv + spin.theBiv
			, imsp.theTri
			};
	}


	/*! \brief MultiVector from Spinor * MultiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Spinor.cpp DoxyExampleMvec
	 */
	inline
	MultiVector
	operator*
		( Spinor const & spinA
		, MultiVector const & mvB
		)
	{
		MultiVector const mv1{ spinA.theSca.theData[0] * mvB };
		MultiVector const mv2{ spinA.theBiv * mvB };
		return { mv1 + mv2 };
	}



	/*! \brief ZZ from Spinor * Type.
	 *
	 * Example:
	 * \snippet test_g3opsMul.hpp DoxyExampleData
	 * \snippet test_g3opsMul_Spinor.cpp DoxyExampleType
	 */


} // [g3]

} // [engabra]


#endif // engabra_g3opsMul_Spinor_INCL_
