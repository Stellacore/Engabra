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


#ifndef engabra_g3_INCL_
#define engabra_g3_INCL_

/*! \file
\brief Main package include file - incorporates other common includes.
*/


#include "g3compare.hpp"
#include "g3consts.hpp"
#include "g3types.hpp"
#include "g3func.hpp"
#include "g3io.hpp"
#include "g3ops.hpp"
#include "g3types.hpp"
#include "g3validity.hpp"



/*! Project enclosing namespace.
 *
 * Overall, "engabra" is the containing namespace for the project. The
 * three-dimensional geometric algebra (G3) which is the focus of this
 * project effort, is contained in the "g3" subordinate namespace. This
 * supports several common ways of utilizing the library. E.g.
 *
 * For a generic "token" in the namespace (e.g. class, func, constant, etc)
 *
 * Use of fully qualified names. This is should be fairly bullet-proof
 * with respect to potential external package name conflicts.
 * \snippet test_engabra.cpp DoxyExample01
 *
 * Use of implicit project name resolution.
 * This is frequently most convenient (unless 'g3' namespace conflict).
 * \snippet test_engabra.cpp DoxyExample02
 *
 * Use of fully implicit names resolution. Perhaps handy inside controlled
 * scopes - but there's a high risk of namespace conflicts with many of the
 * very common token names (e.g. Vector, zero, etc).
 * \snippet test_engabra.cpp DoxyExample03
 *
 * \snippet test_engabra.cpp DoxyExample04
 * And the most abbreviated form (e.g. inside small local scopes)
 * using namespace engabra::g3;
 * token
 *
 */
namespace engabra
{

//! Sub-namespace for geometric algebra in 3D space.
namespace g3
{
}

} // [engabra]


#endif // engabra_g3_INCL_
