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


#ifndef engabra_g3consts_INCL_
#define engabra_g3consts_INCL_


#include <cmath>


namespace engabra
{

namespace g3
{

	//
	// Constants
	//

	//! Classic value of Pi (consistent with gnu math library)
	constexpr double pi{ 3.141592653589793 };
	//! Convenience mnemonic for Pi/2.
	constexpr double piHalf{ .5 * pi };
	//! Convenience mnemonic for Pi/4.
	constexpr double piQtr{ .5 * piHalf };

	//! Angle associated with a full turn (rotation returning to start) [rad]
	constexpr double turnFull{ 2.*pi };
	//! Angle associated with a half turn (pointing opposite direction) [rad]
	constexpr double turnHalf{ pi };
	//! Angle associated with quarter turn (pointing orthogonal direction) [rad]
	constexpr double turnQtr{ piHalf };

} // [g3]

} // [engabra]


#endif // engabra_g3consts_INCL_
