// 
// MIT License
// 
// Copyright (c) 2022 Stellacore Corporation
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


#ifndef engabra_g3validity_INCL_
#define engabra_g3validity_INCL_

/*! \file
\brief Types and functions for testing instance validity (e.g. null, isValid()).

Throughout the engabra implementation, special data values are used
to represent invalid or "null" entities.  For the GA entities based
on scalar values, the double value "NaN" is used to represent that the
instance is not valid.

To promote certainty over speed, the isValid() tests check all component
values in an entity (e.g. for Vector 3 tests are performed).

Individual null instances for the various engabra types are available
in include file g3const.hpp.

The use of the null values allows coding with a "null pattern
paradigm". (Cf. https://en.wikipedia.org/wiki/Null_object_pattern)

For example:
\snippet test_g3validity.cpp DoxyExample01

Note that, in engabra, instances need to be \a explicitly initialized
to null (for most engabra entities, default construction leaves the
contents UN-initialized).

All g3 types support this same pattern
\snippet test_g3validity.cpp DoxyExample02

*/


#include "g3const.hpp"
#include "g3traits.hpp"
#include "g3type.hpp"


namespace engabra
{

namespace g3
{

	//
	// Validity testing
	//

	/*! \brief True if dub is a reasonable value, e.g. is (! null)
	 * True if argument has a useful numeric value (zero or 'isnormal').
	 *
	 * Typical usage pattern is to initialize/deafult a value to null
	 * (via one of the templated functions), and then optionally assign a
	 * useful result (e.g. only if something succeeds). Latter, the
	 * validity of the value (e.g. success of assignment operation) can be
	 * evaluated by calling this function.
	 */
	inline
	bool
	isValid
		( double const & dub
		)
	{
		bool okay{ (0. == dub) }; // allow zero as valid
		if (! okay)
		{
			// normal meaning NOT any of {zero, subnormal, infinite, NaN}
			okay = std::isnormal(dub);
		}
		return okay;
	}

	//
	// isValid() templates for the various G3 types
	//

	//! True if all components of array are valid
	template <std::size_t Dim>
	inline
	bool
	isValid
		( std::array<double, Dim> const & data
		)
	{
		bool okay{ isValid(data[0]) };
		for (std::size_t ndx{1u} ; ndx < Dim ; ++ndx)
		{
			okay &= isValid(data[ndx]);
		}
		return okay;
	}

	//! True if blade (Scalar,Vector,BiVector,TriVector) is not a null instance
	template
		< typename Blade
		, std::enable_if_t< is::blade<Blade>::value, bool > = true
		>
	inline
	bool
	isValid
		( Blade const & blade
		)
	{
		return isValid(blade.theData[0]); // test only first element for nan
	}

	//! True if instance is not null - specialization for Spinor
	inline
	bool
	isValid
		( Spinor const & spin
		)
	{
		return { isValid(spin.theSca) && isValid(spin.theBiv) };
	}

	//! True if instance is not null - specialization for ImSpin
	inline
	bool
	isValid
		( ImSpin const & imsp
		)
	{
		return { isValid(imsp.theVec) && isValid(imsp.theTri) };
	}

	//! True if instance is not null - specialization for MultiVector
	inline
	bool
	isValid
		( MultiVector const & mv
		)
	{
		return
			{  isValid<Scalar>(mv.theSca)
			&& isValid<Vector>(mv.theVec)
			&& isValid<BiVector>(mv.theBiv)
			&& isValid<TriVector>(mv.theTri)
			};
	}

} // [g3]

} // [engabra]


#endif // engabra_g3validity_INCL_
