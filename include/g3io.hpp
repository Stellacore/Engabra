/*

MIT License

Copyright (c) 2021 Stellacore Corporation

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/


#ifndef engabra_g3io_INCL_
#define engabra_g3io_INCL_


#include "g3types.hpp"

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <sstream>


namespace engabra
{

namespace g3
{

//! Namespace for GA element input/ouput utilities and functions
namespace io
{
	/*! \brief Attributes for rudimentary numeric formatting.
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

		//! Format numbers with <sign><numDigLead>.<numDigFrac>.
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

		/*! Prepare stream to be suitable for inserting double next.
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
		prepareStream
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

	//! Use fmt formatter to prepare stream (calls fmt.prepareStream())
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::io::DoubleFormat const & fmt
		)
	{
		fmt.prepareStream(ostrm);
		return ostrm;
	}

	//
	// Formatting stream insertion functions
	//

	//! Put value to stream with nominal formatting
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

} // [io]
} // [g3]

} // [engabra]


//! Global i/o functions within anonymous namespace
namespace
{
	//! Put a scalar to stream - with some formatting
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::Scalar const & blade
		)
	{
		engabra::g3::io::put(ostrm, blade.theData);
		return ostrm;
	}

	//! Put a vector to stream - with some formatting
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::Vector const & blade
		)
	{
		engabra::g3::io::put(ostrm, blade.theData);
		return ostrm;
	}

	//! Put a bivector to stream - with some formatting
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::BiVector const & blade
		)
	{
		engabra::g3::io::put(ostrm, blade.theData);
		return ostrm;
	}

	//! Put a trivector to stream - with some formatting
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::TriVector const & blade
		)
	{
		engabra::g3::io::put(ostrm, blade.theData);
		return ostrm;
	}

	//! Put a spinor to stream - with some formatting
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::Spinor const & spin
		)
	{
		ostrm << spin.theS << " " << spin.theB;
		return ostrm;
	}

	//! Put a imaginary-spinor to stream - with some formatting
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::ImSpin const & imsp
		)
	{
		ostrm << imsp.theV << " " << imsp.theT;
		return ostrm;
	}

	/*
	std::ostream &
	operator<<
		( std::ostream & ostrm
		, engabra::g3::io::DoubleFormat const & fmt
		)
	{
		fmt.prepareStream(ostrm);
		return ostrm;
	}
	*/

} // [anon]

#endif // engabra_g3io_INCL_
