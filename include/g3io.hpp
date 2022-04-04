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


#ifndef engabra_g3io_INCL_
#define engabra_g3io_INCL_

/*! \file
\brief Provides I/O function support for G3 entities.

\b Overview

This file provides basic input/output operators for various engabra::g3
types. Unlike most engabra package functions, the stream operators,
operator<<() and operator>>() are declared in the global namespace so
that they can interact freely with the global streams environment. Other,
more custom, i/o utility functions are encapsulated in the engabra::g3::io
sub namespace.

\b Output

The stream output functions, operator<<(), produce text with a format
that is fairly reasonable for many practical and engineering type
applications in which numeric values are within a few orders magnitude
of unity.  For encoding numbers with more extreme value ranges, there are
several specific encoding functions in the g3::io subnamespace that
provide more general flexibility. These include:

\arg io::fixed() - provide string representation in fixed-format with
easy control over number of leading and trailing decimal digits. E.g.
useful for generating aligned and tabular data displays.

\arg io::enote() - provide string representation in (scientific) e-notation
with full numeric precision for 'double' value types. E.g. useful for
serializing data values for ascii file storage or transmittal.

\b Input

The stream input/extraction, operator>>(), functions support reading
various engabra::g3 types from standard library streams. These operators
are implemented to support the null pattern paradigm, so that extracted
values can also be evaluated for validity independent of stream status.

For example:
\snippet test_g3io.cpp DoxyExample01

\b Utilities

The g3::io::priv subnamespace provides utility functions primarily used for
package implementation.

*/


#include "g3traits.hpp"
#include "g3type.hpp"
#include "g3validity.hpp"

#include <algorithm>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>


namespace engabra
{

namespace g3
{

/*! \brief Support for input/output operations
 *
 * Includes several utilities mostly to support implementation and
 * testing. However, some of these may also be useful in applications
 * such as:
 *
 * \arg g3::io::fixed() - functions that provide string encoding
 * for various entities with easy control over number of leading and
 * trailing decimal digits.
 */
namespace io
{

namespace priv
{

	/*! \brief Holds attributes for rudimentary numeric formatting.
	 *
	 * This structure provides a means for formatting the various GA
	 * numeric values in a consistent manner.
	 *
	 * Since a good practice in quality computational work is to utilize
	 * normalized data, the default formatting values are configured to
	 * represent data with values on order magnitude of unity and to
	 * precision of about part in a million. Custom instances can be
	 * constructed to provide a modified format configuration.
	 */
	struct DoubleFormat
	{

		//! Number of digit places available before decimal (int part).
		std::size_t theNumDigLead{ 3u };
		//! Number of digit places available after the decimal (frac part)
		std::size_t theNumDigFrac{ 6u };

	private:

		//! Mnemonic for tracking sign spacing.
		static constexpr std::size_t theNumDigSign{ 1u };
		//! Mnemonic for tracking decimal spacing.
		static constexpr std::size_t theNumDigPoint{ 1u };

	public:

		//! Construct with nominally-sane default format configuration.
		DoubleFormat () = default;

		//! Format numbers with \<sign\>\<numDigLead\>.\<numDigFrac\>.
		inline
		explicit
		DoubleFormat
			( std::size_t const & numDigLead
				//!< Number of leading digits (between sign and point)
			, std::size_t const & numDigFrac
				//!< Number of trailing digits (after point)
			)
			: theNumDigLead{ numDigLead }
			, theNumDigFrac{ numDigFrac }
		{
		}

		//! Total width required for number (e.g. to use with std::setw())
		inline
		std::size_t
		fieldWide
			() const
		{
			return
				( theNumDigSign
				+ theNumDigLead
				+ theNumDigPoint
				+ theNumDigFrac
				);
		}

		/*! \brief Prepare stream to be suitable for inserting double next.
		 *
		 * E.g.
		 * \code
		 * std::cout << DoubleFormat(2u, 4u) << (1./3.);
		 * \endcode
		 *
		 * \sa engabra::g3::io::operator<<()
		 */
		inline
		void
		prepareFixed
			( std::ostream & ostrm
			) const
		{
			ostrm
				<< " "   // force a leading space
				<< std::fixed
				<< std::setprecision(theNumDigFrac)
				<< std::setw(fieldWide())
				;
		}

	}; // DoubleFormat

	/*! \brief Prepare stream to be suitable for inserting eNotation string
	 *
	 * E.g. to configure std::cout to print next number in e-notation
	 * with 12 digits after decimal point.
	 * \code
	 * prepareEnote(std::cout, 12u);
	 * \endcode
	 *
	 * \sa engabra::g3::io::operator<<()
	 */
	inline
	void
	prepareEnote
		( std::ostream & ostrm
		, std::size_t const & numDigits = 15u
		/*< Default value is
		 about right for IEEE-754 double (give or take
		 a bit). E.g. 1 before and 15 after is 16 decimal
		 digits (vs theoretical number of digits at 15.95)
		 */
		)
	{
		// sign, leading, point, rest
		std::size_t const numField{ 1u + 1u + 1u + numDigits };
		ostrm
			<< " "   // force a leading space
			<< std::scientific
			<< std::setprecision(numDigits)
			<< std::setw(numField)
			;
	}

	//! Local use formatter to prepare streams (calls fmt.prepareFixed())
	inline
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, DoubleFormat const & fmt
		)
	{
		fmt.prepareFixed(ostrm);
		return ostrm;
	}

	//
	// Formatting stream insertion functions
	//

	//! Put value to stream with nominal formatting
	inline
	void
	put
		( std::ostream & ostrm
		, double const & value
		, DoubleFormat const & fmt = {}
		)
	{
		// using engabra::g3::io::operator<<() for fmt
		ostrm << fmt << value;
	}

	//! Display elements of array
	template <typename Type, std::size_t Dim>
	inline
	void
	put
		( std::ostream & ostrm
		, std::array<Type, Dim> const & elems
		, DoubleFormat const & fmt = {}
		)
	{
		std::ostringstream oss;
		for (double const & elem : elems)
		{
			// using engabra::g3::io::operator<<() for fmt
			oss << fmt << elem;
		}
		ostrm << oss.str();
	}

	//
	// Stream handling utilities
	//

	//! True if previous string operation(s) succeeded and isValid(value)
	inline
	bool
	isInputOkay
		( std::istream & istrm
		, double const & value
		)
	{
		return
			(  (! istrm.fail())
			&& isValid(value)
			);
	}

} // [priv]

	//
	// Fixed-Format String encodings for various entities
	//

	//! Conversion to string with requested leading and trailing digits.
	inline
	std::string
	fixed
		( double const & dub
		, std::size_t const & digBefore = 3u
		, std::size_t const & digAfter = 6u
		)
	{
		std::stringstream oss;
		g3::io::priv::DoubleFormat const fmt{ digBefore, digAfter };
		oss << fmt << dub;
		return oss.str();
	}

	//! Fixed format string with requested leading and trailing digits.
	template
		< typename Blade
		, std::enable_if_t< is::blade<Blade>::value, bool > = true
		>
	inline
	std::string
	fixed
		( Blade const & blade
		, std::size_t const & digBefore = 3u
		, std::size_t const & digAfter = 6u
		)
	{
		std::stringstream oss;

		for (std::size_t ndx{0u} ; ndx < blade.theData.size() ; ++ndx)
		{
			// spaces are handled by fixed()
			oss << fixed(blade[ndx], digBefore, digAfter);
		}
		return oss.str();
	}

	//! Fixed format string specialization for Spinor
	inline
	std::string
	fixed
		( Spinor const & spin
		, std::size_t const & digBefore = 3u
		, std::size_t const & digAfter = 6u
		)
	{
		std::stringstream oss;
		oss
			<< fixed<Scalar>(spin.theSca, digBefore, digAfter)
			<< "  "
			<< fixed<BiVector>(spin.theBiv, digBefore, digAfter)
			;
		return oss.str();
	}

	//! Fixed format string specialization for ImSpin
	inline
	std::string
	fixed
		( ImSpin const & imsp
		, std::size_t const & digBefore = 3u
		, std::size_t const & digAfter = 6u
		)
	{
		std::stringstream oss;
		oss
			<< fixed<Vector>(imsp.theVec, digBefore, digAfter)
			<< "  "
			<< fixed<TriVector>(imsp.theTri, digBefore, digAfter)
			;
		return oss.str();
	}

	//! Fixed format string specialization for MultiVector
	inline
	std::string
	fixed
		( MultiVector const & mv
		, std::size_t const & digBefore = 3u
		, std::size_t const & digAfter = 6u
		)
	{
		std::stringstream oss;
		oss
			<< fixed<Scalar>(mv.theSca, digBefore, digAfter)
			<< "  "
			<< fixed<Vector>(mv.theVec, digBefore, digAfter)
			<< "  "
			<< fixed<BiVector>(mv.theBiv, digBefore, digAfter)
			<< "  "
			<< fixed<TriVector>(mv.theTri, digBefore, digAfter)
			;
		return oss.str();
	}

	//
	// E-Notation String encodings for various entities
	//

	//! Conversion to string with full IEEE-754 'double' precision
	inline
	std::string
	enote
		( double const & dub
		, std::size_t const & digAfter = 15u
		)
	{
		std::stringstream oss;
		priv::prepareEnote(oss, digAfter);
		oss << dub;
		return oss.str();
	}

	//! Conversion to string with full IEEE-754 'double' precision
	template
		< typename Blade
		, std::enable_if_t< is::blade<Blade>::value, bool > = true
		>
	inline
	std::string
	enote
		( Blade const & blade
		, std::size_t const & digAfter = 15u
		)
	{
		std::stringstream oss;
		for (std::size_t ndx{0u} ; ndx < blade.theData.size() ; ++ndx)
		{
			if (0u < ndx)
			{
				oss << " ";
			}
			priv::prepareEnote(oss, digAfter);
			oss << blade[ndx];
		}
		return oss.str();
	}

	//! Conversion to string with full IEEE-754 'double' precision
	inline
	std::string
	enote
		( Spinor const & spin
		, std::size_t const & digAfter = 15u
		)
	{
		std::stringstream oss;
		oss
			<< enote<Scalar>(spin.theSca, digAfter)
			<< "  "
			<< enote<BiVector>(spin.theBiv, digAfter)
			;
		return oss.str();
	}

	//! Conversion to string with full IEEE-754 'double' precision
	inline
	std::string
	enote
		( ImSpin const & imsp
		, std::size_t const & digAfter = 15u
		)
	{
		std::stringstream oss;
		oss
			<< enote<Vector>(imsp.theVec, digAfter)
			<< "  "
			<< enote<TriVector>(imsp.theTri, digAfter)
			;
		return oss.str();
	}

	//! Conversion to string with full IEEE-754 'double' precision
	inline
	std::string
	enote
		( MultiVector const & mv
		, std::size_t const & digAfter = 15u
		)
	{
		std::stringstream oss;
		oss
			<< enote<Scalar>(mv.theSca, digAfter)
			<< "  "
			<< enote<Vector>(mv.theVec, digAfter)
			<< "  "
			<< enote<BiVector>(mv.theBiv, digAfter)
			<< "  "
			<< enote<TriVector>(mv.theTri, digAfter)
			;
		return oss.str();
	}

} // [io]

} // [g3]

} // [engabra]


//! Global i/o functions within anonymous namespace
namespace
{
	//
	// Output operators
	//

	//! Put a scalar to stream - with some formatting
	inline
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::Scalar const & blade
		)
	{
		engabra::g3::io::priv::put(ostrm, blade.theData);
		return ostrm;
	}

	//! Put a vector to stream - with some formatting
	inline
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::Vector const & blade
		)
	{
		engabra::g3::io::priv::put(ostrm, blade.theData);
		return ostrm;
	}

	//! Put a bivector to stream - with some formatting
	inline
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::BiVector const & blade
		)
	{
		engabra::g3::io::priv::put(ostrm, blade.theData);
		return ostrm;
	}

	//! Put a trivector to stream - with some formatting
	inline
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::TriVector const & blade
		)
	{
		engabra::g3::io::priv::put(ostrm, blade.theData);
		return ostrm;
	}

	//! Put a spinor to stream - with some formatting
	inline
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::Spinor const & spin
		)
	{
		ostrm << spin.theSca << " " << spin.theBiv;
		return ostrm;
	}

	//! Put a imaginary-spinor to stream - with some formatting
	inline
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::ImSpin const & imsp
		)
	{
		ostrm << imsp.theVec << " " << imsp.theTri;
		return ostrm;
	}

	//! Put a full multivector to stream - with some formatting
	inline
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::MultiVector const & mv
		)
	{
		ostrm
			<< mv.theSca
			<< " " << mv.theVec
			<< " " << mv.theBiv
			<< " " << mv.theTri
			;
		return ostrm;
	}

	//
	// Input (extraction) operators
	//

	/*! \brief Extract individual data array elements from input stream.
	 *
	 * Checks that stream operations are successful and that each extracted
	 * data value is valid.
	 */
	template <std::size_t Dim>
	inline
	std::istream &
	operator>>
		( std::istream & istrm
		, std::array<double, Dim> & data
		)
	{
		using engabra::g3::io::priv::isInputOkay;

		istrm >> data[0];
		bool okay{ isInputOkay(istrm, data[0]) };
		for (std::size_t ndx{1u}
			; okay && (ndx < Dim) ; ++ndx)
		{
			istrm >> data[ndx];
			okay = isInputOkay(istrm, data[ndx]);
		}
		if (! okay) // if anything went wrong...
		{
			// place all null data into entire return instance
			std::fill(data.begin(), data.end(), engabra::g3::nan);
		}
		return istrm;
	}

	//! Extract stream data into a Blade
	template
		< typename Blade
		, std::enable_if_t< engabra::g3::is::blade<Blade>::value, bool> = true
		>
	inline
	std::istream &
	operator>>
		( std::istream & istrm
		, Blade & blade
		)
	{
		istrm >> blade.theData; // includes validity checking of elements
		return istrm;
	}

	//! Specialization of extraction operator for Spinor
	inline
	std::istream &
	operator>>
		( std::istream & istrm
		, engabra::g3::Spinor & spin
		)
	{
		// includes validity checking of elements
		istrm >> spin.theSca.theData;
		istrm >> spin.theBiv.theData;
		return istrm;
	}

	//! Specialization of extraction operator for ImSpin
	inline
	std::istream &
	operator>>
		( std::istream & istrm
		, engabra::g3::ImSpin & imsp
		)
	{
		// includes validity checking of elements
		istrm >> imsp.theVec.theData;
		istrm >> imsp.theTri.theData;
		return istrm;
	}

	//! Specialization of extraction operator for MultiVector
	inline
	std::istream &
	operator>>
		( std::istream & istrm
		, engabra::g3::MultiVector & mv
		)
	{
		// includes validity checking of elements
		istrm >> mv.theSca.theData;
		istrm >> mv.theVec.theData;
		istrm >> mv.theBiv.theData;
		istrm >> mv.theTri.theData;
		return istrm;
	}


} // [anon]

#endif // engabra_g3io_INCL_
