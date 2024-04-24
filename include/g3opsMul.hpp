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


#ifndef engabra_g3opsMul_INCL_
#define engabra_g3opsMul_INCL_

/*! \file
\brief Binary operators associated with multiplication actions.

\b Overview

This header file provides functions that overload operator*() for G3
type operations.

e.g.
\snippet test_g3opsMul.cpp DoxyExample01

All combinations of product pairs involving the explicit engabra::g3 types
are supported. The MultiVector*MultiVector product can be used to evaluate
the product of any arbitrary combination of "unusual" argument types.

Explicit product operator implementations include the products described
below. The following description (as well as code layout in this header
file) is organized by the type of the first argument, but operators are
provided for both argument orders of all explicit types.

\b Convenience

\arg (double * ...) -- overload multiplication by native type,
double. This is primarily for coding convenience. In theory the
g3::Scalar type provides this capability. However, in practices, it's
much easier and more efficient (mostly in terms of compilation times)
to type e.g. "17." instead of "Scalar{17.}"

\b Blades

\arg (Scalar * ...) -- increase (or decrease) the magnitude of other argument.

\arg (Vector * ...) -- provides geometric product with other argument.
Generally, this includes a inner product (contracted) grade and also an
outer product (extended) grade constituent for each grade constituent
in the other argument.

\arg (BiVector * ...) -- another geometric product. In G3, the bivector
is dual to vector. These products have "grade-splitting" geometric
properties similar to those of the product involving a vector operand.

\arg (TriVector * ...) -- in G3, trivectors are the pseudo-scalar of the
algebra and multiplication with a trivector is commutative. Multiplication
by the unit magnitude trivector produces an entity's dual.

\b Composites

\arg (Spinor * ...) -- multiplication by spinor types are commonly
encountered during evaluation of intermediate results (e.g. product of
three vectors, a*b*c, in which a*b produces a spinor that then multiplies
the third vector, c). Also, this is a particularly common multiplication
operation involved with rotations.

\arg (ImSpin * ...) -- another multiplication operator that often occurs
during evaluation of intermediate results. These products are dual to the
(Spinor*...) ones.

\arg (MultiVector * ...) -- multiplication operations with the most general
algebraic type entity. This can be used to evaluate multiplication products
of any pair of types. Ref note below.

\b Note/Generality

The (MultiVector*MultiVector) product is the most general
multiplication possible in the algebra. In practical terms, it can be used
to perform multiplication of any two "unusual" composite types that may
not have an explicit operator*() implemented here.

E.g. to evaluate something like
(scalar+trivector)*(vector+bivector+trivector), the two arguments can
first be used to construct two MultiVector entities, and then the general
case operator*(MultiVector,MultiVector) operation can be used to obtain
the result.  \snippet test_g3opsMul.cpp DoxyExample02

*/


//
// Implementation Note
// 
// NOTE: a number of the functions (in g3opsMul_....hpp) could be
// implemented with template code. However, that:
// - leads to confusion in maintaining the code
// - often produces extremely verbose error messages for consumers
// - adds extra compilation overhead to resolve alternatives
//

//
// A hierarchy of "Forward" combinations is used to organize
// implementation of the pair-wise multiplication functions.
//
// "Forward" (primary implementation) functions are implemented
// Forward argument order is "A(operator)B" where "A" is near
// the top of the hierarchy list below and "B" is (equal or)
// further down the list.
//
// "Backward" (secondary implementation) functions are implemented
// assuming the forward functions are available for use (as a option).
//
// The hierarchy order *defined* herein is:
// - double
// - Scalar
// - Vector
// - BiVector
// - TriVector
// - Spinor
// - ImSpin
// - ComPlex
// - DirPlex
// - MultiVector
//
// For example, (Vector\*DirPlex) is the "forward" implementation
// and (DirPlex\*Vector) is the "backward" implementation (that
// optionally may use the forward one).
//


#include "g3type.hpp"

#include "g3opsUni.hpp"

#include "g3_private.hpp"

#include "g3opsAdd_same.hpp"
#include "g3opsSub_same.hpp"

#include "g3opsMul_double.hpp"
#include "g3opsMul_Scalar.hpp"
#include "g3opsMul_Vector.hpp"
#include "g3opsMul_BiVector.hpp"
#include "g3opsMul_TriVector.hpp"
#include "g3opsMul_Spinor.hpp"
#include "g3opsMul_ImSpin.hpp"
#include "g3opsMul_ComPlex.hpp"
#include "g3opsMul_DirPlex.hpp"
#include "g3opsMul_MultiVector.hpp"

#include <algorithm>
#include <array>
#include <numeric>


namespace engabra
{

namespace g3
{

} // [g3]

} // [engabra]


#endif // engabra_g3opsMul_INCL_
