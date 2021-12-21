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

Here's an example of basic null-pattern use.
\snippet test_g3validity.cpp DoxyExample01

All g3 types support this same pattern
\snippet test_g3validity.cpp DoxyExample02

*/


namespace engabra
{

namespace g3
{

	//
	// Null instances and validity testing
	//

	//! Generic Not-A-Number for individual values
	constexpr double nan{ std::numeric_limits<double>::quiet_NaN() };

	//! Null instance for any type constructable from 'double' argument.
	template <typename Type>
	inline
	Type
	null
		()
	{
		return Type{ nan };
	}

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
	// Null/NaN templates for the various G3 types
	//

	// null<Scalar> could be handled by default function
	//! Null value - specialization for Scalar
	template <> inline Scalar
	null<Scalar>
		()
	{
		return Scalar{ nan };
	}

	//! Null value - specialization for Vector
	template <> inline Vector
	null<Vector>
		()
	{
		return Vector{ nan, nan, nan };
	}

	//! Null value - specialization for BiVector
	template <> inline BiVector
	null<BiVector>
		()
	{
		return BiVector{ nan, nan, nan };
	}

	// null<Tri> could be handled by default function
	//! Null value - specialization for TriVector
	template <> inline TriVector
	null<TriVector>
		()
	{
		return TriVector{ nan };
	}

	//
	// isValid() templates for the various G3 types
	//

	//! True if blade is not a null instancwe
	template <typename Blade>
	inline
	bool
	isValid
		( Blade const & blade
		)
	{
		return isValid(blade.theData[0]); // test only first element for nan
	}

	//! True if instance is not null - specialization for Spinor
	template <>
	inline
	bool
	isValid
		( Spinor const & spin
		)
	{
		return { isValid(spin.theSca) && isValid(spin.theBiv) };
	}

	//! True if instance is not null - specialization for ImSpin
	template <>
	inline
	bool
	isValid
		( ImSpin const & imsp
		)
	{
		return { isValid(imsp.theVec) && isValid(imsp.theTri) };
	}

} // [g3]

} // [engabra]


#endif // engabra_g3validity_INCL_
