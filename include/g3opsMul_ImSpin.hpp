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


#ifndef engabra_g3opsMul_ImSpin_INCL_
#define engabra_g3opsMul_ImSpin_INCL_

/*! \file
 * \brief Implementation of operator*() for ImSpin*{...}
 */
 /*
 * Example:
 * \snippet test_g3opsMul_ImSpin.cpp DoxyExample01
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


namespace engabra
{

namespace g3
{
	//
	// "Backward" rank order:
	// -- redirect to forward op+() functions (from files included above)
	//

	/*! \brief ImSpin from ImSpin * double.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ImSpin.cpp DoxyExampleDub
	 */
	inline
	ImSpin
	operator*
		( ImSpin const & imspA
		, double const & dubB
		)
	{
		return ImSpin{ dubB * imspA.theVec, dubB * imspA.theTri };
	}

	/*! \brief ImSpin from ImSpin * Scalar.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ImSpin.cpp DoxyExampleSca
	 */
	inline
	ImSpin
	operator*
		( ImSpin const & imspA
		, Scalar const & scaB
		)
	{
		double const & dubB = scaB.theData[0];
		return ImSpin{ dubB * imspA.theVec, dubB * imspA.theTri };
	}

	/*! \brief Spinor from ImSpin * Vector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ImSpin.cpp DoxyExampleVec
	 */
	inline
	Spinor
	operator*
		( ImSpin const & imspA
		, Vector const & vecB
		)
	{
		// a.b + a^b + A*b
		Spinor const spinAB{ imspA.theVec * vecB };
		BiVector const bivAB{ imspA.theTri * vecB };
		return Spinor{ spinAB.theSca, spinAB.theBiv + bivAB };
	}

	/*! \brief ImSpin from ImSpin * BiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ImSpin.cpp DoxyExampleBiv
	 */
	inline
	ImSpin
	operator*
		( ImSpin const & imspA
		, BiVector const & bivB
		)
	{
		ImSpin const imsp1{ imspA.theVec * bivB };
		Vector const vec1{ imspA.theTri * bivB };
		return { imsp1.theVec + vec1, imsp1.theTri };
	}

	/*! \brief Spinor from ImSpin * TriVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ImSpin.cpp DoxyExampleTri
	 */
	//! (Scalar+BiVector) result of (Vector+TriVector)*(TriVector) - ImSpin dual
	inline
	Spinor
	operator*
		( ImSpin const & imspA
		, TriVector const & triB
		)
	{
		return triB*imspA;
	}

	/*! \brief ImSpin from ImSpin * Spinor.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ImSpin.cpp DoxyExampleSpin
	 */
	inline
	ImSpin
	operator*
		( ImSpin const & imspA
		, Spinor const & spinB
		)
	{
		ImSpin const imsp1{ imspA.theVec * spinB };
		ImSpin const imsp2{ imspA.theTri * spinB };
		return ImSpin{ imsp1 + imsp2 };
	}

	//
	// "Self-type" multiply
	//

	/*! \brief Spinor from ImSpin * ImSpin.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ImSpin.cpp DoxyExampleImsp
	 */
	inline
	Spinor
	operator*
		( ImSpin const & imspA
		, ImSpin const & imspB
		)
	{
		Spinor const spin1{ imspA.theVec * imspB };
		Spinor const spin2{ imspA.theTri * imspB };
		return Spinor{ spin1 + spin2 };
	}

	//
	// "Forward" rank order:
	//

	/*! \brief MultiVector from ImSpin * ComPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ImSpin.cpp DoxyExampleCplx
	 */
	inline
	MultiVector
	operator*
		( ImSpin const & imspA
		, ComPlex const & cplxB
		)
	{
		return MultiVector
			{ imspA.theTri * cplxB.theTri
			, imspA.theVec * cplxB.theSca
			, imspA.theVec * cplxB.theTri
			, imspA.theTri * cplxB.theSca
			};
	}

	/*! \brief MultiVector from ImSpin * DirPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ImSpin.cpp DoxyExampleDplx
	 */
	inline
	MultiVector
	operator*
		( ImSpin const & imspA
		, DirPlex const & dplxB
		)
	{
		Spinor const spin{ imspA.theVec * dplxB.theVec };
		ImSpin const imsp{ imspA.theVec * dplxB.theBiv };
		return MultiVector
			{ spin.theSca
			, imsp.theVec + (imspA.theTri * dplxB.theBiv)
			, spin.theBiv + (imspA.theTri * dplxB.theVec)
			, imsp.theTri
			};
	}

	/*! \brief MultiVector from ImSpin * MultiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ImSpin.cpp DoxyExampleMvec
	 */
	inline
	MultiVector
	operator*
		( ImSpin const & imspA
		, MultiVector const & mvB
		)
	{
		return MultiVector
			{ imspA.theVec * mvB
			+ imspA.theTri * mvB
			};
	}

	/*! \brief ZZ from ImSpin * Type.
	 *
	 * Example:
	 * \snippet test_g3opsMul_ImSpin.cpp DoxyExampleType
	 */


} // [g3]

} // [engabra]


#endif // engabra_g3opsMul_ImSpin_INCL_
