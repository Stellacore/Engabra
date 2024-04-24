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


#ifndef engabra_g3opsMul_MultiVector_INCL_
#define engabra_g3opsMul_MultiVector_INCL_

/*! \file
 * \brief Implementation of operator*() for MultiVector*{...}
 */
 /*
 * Example:
 * \snippet test_g3opsMul_MultiVector.cpp DoxyExample01
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
#include "g3opsMul_DirPlex.hpp"


namespace engabra
{

namespace g3
{
	//
	// "Backward" rank order:
	// -- redirect to forward op+() functions (from files included above)
	//

	/*! \brief MultiVector from MultiVector * double.
	 *
	 * Example:
	 * \snippet test_g3opsMul_MultiVector.cpp DoxyExampleDub
	 */
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, double const dubB
		)
	{
		return MultiVector
			{ dubB * mvA.theSca
			, dubB * mvA.theVec
			, dubB * mvA.theBiv
			, dubB * mvA.theTri
			};
	}

	/*! \brief MultiVector from MultiVector * Scalar.
	 *
	 * Example:
	 * \snippet test_g3opsMul_MultiVector.cpp DoxyExampleSca
	 */
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, Scalar const scaB
		)
	{
		double const & dubB = scaB.theData[0];
		return MultiVector
			{ dubB * mvA.theSca
			, dubB * mvA.theVec
			, dubB * mvA.theBiv
			, dubB * mvA.theTri
			};
	}

	/*! \brief MultiVector from MultiVector * Vector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_MultiVector.cpp DoxyExampleVec
	 */
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, Vector const vecB
		)
	{
		Vector const vec1{ mvA.theSca * vecB };
		Spinor const spin1{ mvA.theVec * vecB };
		ImSpin const imsp1{ mvA.theBiv * vecB };
		BiVector const biv1{ mvA.theTri * vecB };
		return MultiVector
			{ spin1.theSca
			, vec1 + imsp1.theVec
			, biv1 + spin1.theBiv
			, imsp1.theTri
			};
	}

	/*! \brief MultiVector from MultiVector * BiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_MultiVector.cpp DoxyExampleBiv
	 */
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, BiVector const bivB
		)
	{
		BiVector const biv1{ mvA.theSca * bivB };
		ImSpin const imsp1{ mvA.theVec * bivB };
		Spinor const spin1{ mvA.theBiv * bivB };
		Vector const vec1{ mvA.theTri * bivB };
		return MultiVector
			{ spin1.theSca
			, imsp1.theVec + vec1
			, biv1 + spin1.theBiv
			, imsp1.theTri
			};
	}

	/*! \brief MultiVector from MultiVector * TriVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_MultiVector.cpp DoxyExampleTri
	 */
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, TriVector const triB
		)
	{
		TriVector const tri1{ mvA.theSca * triB };
		BiVector const biv1{ mvA.theVec * triB };
		Vector const vec1{ mvA.theBiv * triB };
		Scalar const sca1{ mvA.theTri * triB };
		return MultiVector{ sca1, vec1, biv1, tri1 };
	}

	/*! \brief MultiVector from MultiVector * Spinor.
	 *
	 * Example:
	 * \snippet test_g3opsMul_MultiVector.cpp DoxyExampleSpin
	 */
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, Spinor const spinB
		)
	{
		return MultiVector
			( mvA * spinB.theSca
			+ mvA * spinB.theBiv
			);
	}

	/*! \brief MultiVector from MultiVector * ImSpin.
	 *
	 * Example:
	 * \snippet test_g3opsMul_MultiVector.cpp DoxyExampleImsp
	 */
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, ImSpin const imspB
		)
	{
		return MultiVector
			( mvA * imspB.theVec
			+ mvA * imspB.theTri
			);
	}

	/*! \brief MultiVector from MultiVector * ComPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul_MultiVector.cpp DoxyExampleCplx
	 */
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, ComPlex const & cplxB
		)
	{
		return (cplxB * mvA); // commutative
	}

	/*! \brief MultiVector from MultiVector * DirPlex.
	 *
	 * Example:
	 * \snippet test_g3opsMul_MultiVector.cpp DoxyExampleDplx
	 */
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, DirPlex const & dplxB
		)
	{
		Spinor const spin1{ mvA.theVec * dplxB.theVec };
		ImSpin const imsp1{ mvA.theBiv * dplxB.theVec };
		ImSpin const imsp2{ mvA.theVec * dplxB.theBiv };
		Spinor const spin2{ mvA.theBiv * dplxB.theBiv };
		return MultiVector
			{ spin1.theSca + spin2.theSca
			, imsp1.theVec + imsp2.theVec
			+ (mvA.theSca * dplxB.theVec)
			+ (mvA.theTri * dplxB.theBiv)
			, spin1.theBiv + spin2.theBiv
			+ (mvA.theTri * dplxB.theVec)
			+ (mvA.theSca * dplxB.theBiv)
			, imsp1.theTri + imsp2.theTri
			};
	}


	//
	// "Self-type" multiply
	//

	/*! \brief MultiVector from MultiVector * MultiVector.
	 *
	 * Example:
	 * \snippet test_g3opsMul_MultiVector.cpp DoxyExampleMvec
	 *
	 * General MultiVector product (most general in 3D)
	 *
	 * This is the most general product of the algebra and represents
	 * a superset of all possible pairwise component operations.
	 *
	 * The implementation involves approximately 128 floating point
	 * operations (64 each multiplies and additions and 8 assignments).
	 * This may represent some overhead if working only with simple
	 * types (e.g. it is a wasteful way to implement Scalar*Scalar
	 * product). However, if either entity has a composite structure,
	 * then casting to/from MultiVector type and using this one
	 * function call usually still provides reasonably efficient
	 * computation for most applications (e.g. other than the most
	 * performance demanding ones).
	 */
	inline
	MultiVector
	operator*
		( MultiVector const & mvA
		, MultiVector const & mvB
		)
	{
		MultiVector result{};

		result.theSca.theData[0]
			   = ( mvA.theSca.theData[0] * mvB.theSca.theData[0]
				 + mvA.theVec.theData[0] * mvB.theVec.theData[0]
				 + mvA.theVec.theData[1] * mvB.theVec.theData[1]
				 + mvA.theVec.theData[2] * mvB.theVec.theData[2] )
			   - ( mvA.theBiv.theData[0] * mvB.theBiv.theData[0]
				 + mvA.theBiv.theData[1] * mvB.theBiv.theData[1]
				 + mvA.theBiv.theData[2] * mvB.theBiv.theData[2]
				 + mvA.theTri.theData[0] * mvB.theTri.theData[0] )
			   ;
		result.theVec.theData[0]
			   = ( mvA.theVec.theData[0] * mvB.theSca.theData[0]
				 + mvA.theSca.theData[0] * mvB.theVec.theData[0]
				 + mvA.theBiv.theData[2] * mvB.theVec.theData[1]
				 + mvA.theVec.theData[2] * mvB.theBiv.theData[1] )
			   - ( mvA.theBiv.theData[1] * mvB.theVec.theData[2]
				 + mvA.theTri.theData[0] * mvB.theBiv.theData[0]
				 + mvA.theVec.theData[1] * mvB.theBiv.theData[2]
				 + mvA.theBiv.theData[0] * mvB.theTri.theData[0] )
			   ;
		result.theVec.theData[1]
			   = ( mvA.theVec.theData[1] * mvB.theSca.theData[0]
				 + mvA.theSca.theData[0] * mvB.theVec.theData[1]
				 + mvA.theBiv.theData[0] * mvB.theVec.theData[2]
				 + mvA.theVec.theData[0] * mvB.theBiv.theData[2] )
			   - ( mvA.theBiv.theData[2] * mvB.theVec.theData[0]
				 + mvA.theVec.theData[2] * mvB.theBiv.theData[0]
				 + mvA.theTri.theData[0] * mvB.theBiv.theData[1]
				 + mvA.theBiv.theData[1] * mvB.theTri.theData[0] )
			   ;
		result.theVec.theData[2]
			   = ( mvA.theVec.theData[2] * mvB.theSca.theData[0]
				 + mvA.theBiv.theData[1] * mvB.theVec.theData[0]
				 + mvA.theSca.theData[0] * mvB.theVec.theData[2]
				 + mvA.theVec.theData[1] * mvB.theBiv.theData[0] )
			   - ( mvA.theBiv.theData[0] * mvB.theVec.theData[1]
				 + mvA.theVec.theData[0] * mvB.theBiv.theData[1]
				 + mvA.theTri.theData[0] * mvB.theBiv.theData[2]
				 + mvA.theBiv.theData[2] * mvB.theTri.theData[0] )
			   ;
		result.theBiv.theData[0]
			   = ( mvA.theBiv.theData[0] * mvB.theSca.theData[0]
				 + mvA.theTri.theData[0] * mvB.theVec.theData[0]
				 + mvA.theVec.theData[1] * mvB.theVec.theData[2]
				 + mvA.theSca.theData[0] * mvB.theBiv.theData[0]
				 + mvA.theBiv.theData[2] * mvB.theBiv.theData[1]
				 + mvA.theVec.theData[0] * mvB.theTri.theData[0] )
			   - ( mvA.theVec.theData[2] * mvB.theVec.theData[1]
				 + mvA.theBiv.theData[1] * mvB.theBiv.theData[2] )
			   ;
		result.theBiv.theData[1]
			   = ( mvA.theBiv.theData[1] * mvB.theSca.theData[0]
				 + mvA.theVec.theData[2] * mvB.theVec.theData[0]
				 + mvA.theTri.theData[0] * mvB.theVec.theData[1]
				 + mvA.theSca.theData[0] * mvB.theBiv.theData[1]
				 + mvA.theBiv.theData[0] * mvB.theBiv.theData[2]
				 + mvA.theVec.theData[1] * mvB.theTri.theData[0] )
			   - ( mvA.theVec.theData[0] * mvB.theVec.theData[2]
				 + mvA.theBiv.theData[2] * mvB.theBiv.theData[0] )
			   ;
		result.theBiv.theData[2]
			   = ( mvA.theBiv.theData[2] * mvB.theSca.theData[0]
				 + mvA.theVec.theData[0] * mvB.theVec.theData[1]
				 + mvA.theTri.theData[0] * mvB.theVec.theData[2]
				 + mvA.theBiv.theData[1] * mvB.theBiv.theData[0]
				 + mvA.theSca.theData[0] * mvB.theBiv.theData[2]
				 + mvA.theVec.theData[2] * mvB.theTri.theData[0] )
			   - ( mvA.theVec.theData[1] * mvB.theVec.theData[0]
				 + mvA.theBiv.theData[0] * mvB.theBiv.theData[1] )
			   ;
		result.theTri.theData[0]
			   = ( mvA.theTri.theData[0] * mvB.theSca.theData[0]
				 + mvA.theBiv.theData[0] * mvB.theVec.theData[0]
				 + mvA.theBiv.theData[1] * mvB.theVec.theData[1]
				 + mvA.theBiv.theData[2] * mvB.theVec.theData[2]
				 + mvA.theVec.theData[0] * mvB.theBiv.theData[0]
				 + mvA.theVec.theData[1] * mvB.theBiv.theData[1]
				 + mvA.theVec.theData[2] * mvB.theBiv.theData[2]
				 + mvA.theSca.theData[0] * mvB.theTri.theData[0] )
			   ;

		return result;
	}



	//
	// "Forward" rank order:
	//

	// NONE (MultiVector is highest ranking type)


	/*! \brief ZZ from MultiVector * Type.
	 *
	 * Example:
	 * \snippet test_g3opsMul_MultiVector.cpp DoxyExampleType
	 */


} // [g3]

} // [engabra]


#endif // engabra_g3opsMul_MultiVector_INCL_
