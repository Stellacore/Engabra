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


#ifndef engabra_g3opsMul_DirPlex_INCL_
#define engabra_g3opsMul_DirPlex_INCL_

/*! \file
 * \brief Implementation of operator*() for DirPlex*{...}
 */
 /*
 * Example:
 * \snippet test_g3opsMul_DirPlex.cpp DoxyExample01
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
#include "g3opsMul_ComPlex.hpp"


namespace engabra
{

namespace g3
{
	//
	// "Backward" rank order:
	// -- redirect to forward op+() functions (from files included above)
	//

	/*! \brief DirPlex from DirPlex * double.
	 *
	 * Example:
	 * \snippet test_g3opsMul_DirPlex.cpp DoxyExampleDub
	 */
	inline
	DirPlex
	operator*
		( DirPlex const & dplxA
		, double const & dubB
		)
	{
		return { dubB * dplxA }; // commutative
	}

	/*! \brief DirPlex from DirPlex * Scalar.
	 *
	 * Example:
	 * \snippet test_g3opsMul_DirPlex.cpp DoxyExampleSca
	 */
	inline
	DirPlex
	operator*
		( DirPlex const & dplxA
		, Scalar const & scaB
		)
	{
		return { scaB * dplxA }; // commutative
	}

	/*! \brief MultiVector from DirPlex * Vector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_DirPlex.cpp DoxyExampleVec
	 */
	inline
	MultiVector
	operator*
		( DirPlex const & dplxA
		, Vector const & vecB
		)
	{
		Spinor const spin{ dplxA.theVec * vecB };
		ImSpin const imspRev{ vecB * reverse(dplxA.theBiv) };
		ImSpin const imsp{ reverse(imspRev) };
		return MultiVector
			{ spin.theSca
			, imsp.theVec
			, spin.theBiv
			, imsp.theTri
			};
	}

	/*! \brief MultiVector from DirPlex * BiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_DirPlex.cpp DoxyExampleBiv
	 */
	inline
	MultiVector
	operator*
		( DirPlex const & dplxA
		, BiVector const & bivB
		)
	{
		ImSpin const imsp{ dplxA.theVec * bivB };
		Spinor const spinRev{ reverse(bivB) * reverse(dplxA.theBiv) };
		Spinor const spin{ reverse(spinRev) };
		return MultiVector
			{ spin.theSca
			, imsp.theVec
			, spin.theBiv
			, imsp.theTri
			};
	}

	/*! \brief DirPlex from DirPlex * TriVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_DirPlex.cpp DoxyExampleTri
	 */
	inline
	DirPlex
	operator*
		( DirPlex const & dplxA
		, TriVector const & triB
		)
	{
		return DirPlex
			{ dplxA.theBiv * triB
			, dplxA.theVec * triB
			};
	}

	/*! \brief MultiVector from DirPlex * Spinor.
	 *
	 * Example:
	 * \snippet test_g3opsMul_DirPlex.cpp DoxyExampleSpin
	 */
	inline
	MultiVector
	operator*
		( DirPlex const & dplxA
		, Spinor const & spinB
		)
	{
		ImSpin const imsp{ dplxA.theVec * spinB.theBiv };
		Spinor const spin{ dplxA.theBiv * spinB.theBiv };
		return MultiVector
			{ spin.theSca
			, imsp.theVec + (spinB.theSca * dplxA.theVec)
			, spin.theBiv + (spinB.theSca * dplxA.theBiv)
			, imsp.theTri
			};
	}

	/*! \brief MultiVector from DirPlex * ImSpin.
	 *
	 * Example:
	 * \snippet test_g3opsMul_DirPlex.cpp DoxyExampleImsp
	 */
	inline
	MultiVector
	operator*
		( DirPlex const & dplxA
		, ImSpin const & imspB
		)
	{
		Spinor const spin{ dplxA.theVec * imspB.theVec };
		ImSpin const imsp{ dplxA.theBiv * imspB.theVec };
		return MultiVector
			{ spin.theSca
			, imsp.theVec + (dplxA.theBiv * imspB.theTri)
			, spin.theBiv + (dplxA.theVec * imspB.theTri)
			, imsp.theTri
			};
	}

	/*! \brief DirPlex from DirPlex * ComPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul_DirPlex.cpp DoxyExampleCplx
	 */
	inline
	DirPlex
	operator*
		( DirPlex const & dplxA
		, ComPlex const & cplxB
		)
	{
		return DirPlex
			{ cplxB.theSca * dplxA.theVec
			+ dplxA.theBiv * cplxB.theTri
			, cplxB.theSca * dplxA.theBiv
			+ dplxA.theVec * cplxB.theTri
			};
	}

	//
	// "Self-type" multiply
	//

	/*! \brief MultiVector from DirPlex * DirPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul_DirPlex.cpp DoxyExampleDplx
	 */
	inline
	MultiVector
	operator*
		( DirPlex const & dplxA
		, DirPlex const & dplxB
		)
	{
		Spinor const spin1{ dplxA.theVec * dplxB.theVec };
		ImSpin const imsp1{ dplxA.theBiv * dplxB.theVec };
		ImSpin const imsp2{ dplxA.theVec * dplxB.theBiv };
		Spinor const spin2{ dplxA.theBiv * dplxB.theBiv };
		return MultiVector
			{ spin1.theSca + spin2.theSca
			, imsp1.theVec + imsp2.theVec
			, spin1.theBiv + spin2.theBiv
			, imsp1.theTri + imsp2.theTri
			};
	}

	//
	// "Forward" rank order:
	//

	/*! \brief MultiVector from DirPlex * MultiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_DirPlex.cpp DoxyExampleMvec
	 */
	inline
	MultiVector
	operator*
		( DirPlex const & dplxA
		, MultiVector const & mvecB
		)
	{
		Spinor const spin1{ dplxA.theVec * mvecB.theVec };
		ImSpin const imsp1{ dplxA.theVec * mvecB.theBiv };
		Spinor const spin2{ dplxA.theBiv * mvecB.theBiv };
		ImSpin const imsp2Rev{ mvecB.theVec * reverse(dplxA.theBiv) };
		ImSpin const imsp2{ reverse(imsp2Rev) };
		return MultiVector
			{ spin1.theSca + spin2.theSca
			, imsp1.theVec + imsp2.theVec
			+ (mvecB.theSca * dplxA.theVec)
			+ (dplxA.theBiv * mvecB.theTri)
			, spin1.theBiv + spin2.theBiv
			+ (dplxA.theVec * mvecB.theTri)
			+ (mvecB.theSca * dplxA.theBiv)
			, imsp1.theTri + imsp2.theTri
			};
	}


	/*! \brief ZZ from DirPlex * Type.
	 *
	 * Example:
	 * \snippet test_g3opsMul_DirPlex.cpp DoxyExampleType
	 */


} // [g3]

} // [engabra]


#endif // engabra_g3opsMul_DirPlex_INCL_
