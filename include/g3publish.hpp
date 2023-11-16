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


#ifndef engabra_g3publish_INCL_
#define engabra_g3publish_INCL_

/*! \file
\brief Including this file promotes namespaces declarations.

\b Overview

Low level functions are defined within project sub namespaces. However,
it is typically convenient to have many of these available at more global
scope. E.g. instead of needing to write, for example,
\code
	using engabra::g3::operator+; // binary addition
	using engabra::g3::operator-; // unary negation
	engabra::g3::Vector const vecC{ vecA + (-vecB) };
\endcode
It is desirable to express this simply as e.g.
\code
	engabra::g3::Vector const vecC{ vecA + (-vecB) };
\endcode
With the operators resolved within the global scope.

Including this file provides "using" declarations (similar to lines in
the first example above) that enable expressing code as in the second
case.

\b Use

Include this file (ref note below)
\snippet test_g3publish_all.cpp DoxyExample01
After the "publication" all operators are available in global namespace.
\snippet test_g3publish_all.cpp DoxyExample02

\note The publish behavior is incoporated into the library by default
(i.e. g3publish.hpp in included by engabra.hpp). Therefore, it is more
exact to say that "to avoid having engabra functions in global namespace
do include the various g3*.hpp files explicitly rather than including the
default engabra.hpp include file.  The various 'using' directives within
this file are contained within an anonymous namespace so including this
file affects only a single compilation unit.

\note The I/O overload functions are always defined at global scope
in order to interact with std::streams.

*/


#include "g3opsAdd_same.hpp"
#include "g3opsSub_same.hpp"

#include "g3opsMul.hpp"
#include "g3opsUni.hpp"


namespace
{
	//
	// Unitary overloads
	//
	using engabra::g3::operator-;

	//
	// Binary overloads
	//
	using engabra::g3::operator+;
	using engabra::g3::operator*;


} // [annon]


#endif // engabra_g3publish_INCL_
