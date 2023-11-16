
[//]: # (Comments Like this)

[MIT License](https://mit-license.org/)


# Engabra - ENGineering Geometric AlgeBRA
*A C++ Library enabling  __practical__ engineering computation
with Geometric Algebra in 3D space.*

## Introduction

Engabra is lightweight C++ library that supports performing practical
Engineering computation, modeling, analysis, and simulation in 3D space
with no other software dependencies.


The main emphasis is on _practical utility_ (not theoretical abstraction
<<<<<<< HEAD
nor education, nor experimentation - as is the case for many GA software
libraries).  The fundamental idea behind engabra is that the library be
useful for real world computation, modeling and simulation.
=======
nor education, nor experimentation - as is the case for many available
GA software libraries).  The fundamental idea behind Engabra is that
the library is useful for real world computation, modeling and simulation.
>>>>>>> d698e59 (README.md - title intro tweaking, improved many descriptions in types and operations)

The focus on 3D space allows providing relationships and operations that
may not be available in other dimensions. For example splitting multivectors
into the sum of ComPlex and DirPlex values and using these to implement
generalized inversion operations as well as other functions that may not
be defined in higher dimensional spaces (e.g. circular trigonometric
functions, logarithms of vectors).


Quick jump links to below:
* [Key Features](#Key-Features)
* [GA Data Types](#GA-Data-Types)
* [Getting Started](#Getting-Started)
* [Software Organization](#Software-Organization)
* [Basic Library Use](#Basic-Library-Use)
	* [Code Build Commands](#Code-Build-Commands)

## Key Features

The main utility/distinction of Engabra is that it has a very practical
focus for use in coding applications that provide real-world engineering
solutions - in contrast to a mathematically interesting one. Engabra is
meant for use in real-world software development. It focus on ease of
use, practicality, and performance - from perspective of developer as well
as applications.

#### _Practical_:

The types and functions are structured and intended for real-world
engineering type solutions.

* Focused on actual use (compared with experimentation or academic
explorations)

* All entities have direct physical interpretations and associations
(compared with e.g. various higher-dimensional conformal algebras used
in academic contexts)

* Dumb-simple-stupid class definitions and function operators generally
allow compiler to do type checking and produce easily interpretable
warnings and error messages.

* In some places, this means there are concrete implementations of
overloaded functions, but this is preferable to having complex, confusing
and error prone templating syntaxes.

* Utilizes explicit constructors and mitigates implicit casting to avoid
potential confusing behaviors - keeps consuming code expression very
WYSIWYG.

* Engabra is an entirely stand-alone library. No other packages need be
installed to use it - other than C++ compiler (e.g. g++, clang, msvc)
and general development tools of course.

#### _Platforms and Environments_:

The code is standard C++ and should work fine on nearly any platform that
supports a modern C++ standard compiler (C++17 or later).

* Code implementation is relatively 'vanilla' and simple (e.g. no use of
fancy optimizations or 'tricks'). The library should build on nearly any
(64-bit) device or platform.

	* Note: (as of 2023.Q1) implementation has only been built for
	environments using 64-bit double representations. It is unverified
	how/if compatible the implementation is with 32-bit double sizes.

* The CMake build process supports compiling and packaging on a wide
variety of different operating systems, distributions and hardware
platforms.

	* _Note_ the descriptions herein and associated
	file/directory/command name conventions are consistent with a
	\*nix environment.  However, this should not be construed as any
	sort of limitation on the library, only that a \*nix environment
	was used to author many of the text files and descriptions.

#### _Natural Code Syntax_:

For the most part, the library is very easy and natural to utilize in
consuming code.

* There are no complex templating expressions involved or required in the
consuming code (other than a few relatively natural use cases - e.g.
such as defining useful generic type instances like "null<Vector>()"
or "zero<BiVector>()" and a few other natural/typical template usage)

* There are NO strange operators to memorize.

	* Operator overloading only uses the obvious and standard operators
	(e.g. "\*" for multiplication, "+" for addition, etc).

	* For operations not standard to C++ syntax, explicit function
	names are used (e.g. dot(), wedge(), reverse(), dual()}

	* Division ambiguity is avoid in favor of more explicit constructs
	involving element inverses. I.e. there is no support for the "/"
	operator. Instead, multivector "quotients" are supported with
	explicit and specific operations via the inverse function. E.g.
	"inverse(vecA)*vecB" or "vecA*inverse(vecB)" according to
	whichever is actually intended.

#### _Performance_:

Engabra is fast to use in practice.

* Fast to compile -- although templates are used heavily within internal
_implementation_ of Engabra the instantiations are very simple so that
compiler can resolve and instantiate code very quickly. Note that,
in spite of the use of templates within the implementation, consuming
code is generally insulated from them - other than a few cases where
using templates could be expected for any library (mostly in customizing
constant types)

* Fast run time -- The run time performance is quite good. Although
there are no particularly special coding techniques used (and certainly
no expectation for special hardware capabilities), the implementation
code makes copious use of 'const' and 'inline' specifications so that
compilers can optimize the code very well.

* Emphasizes 'const' paradigm to support better __compiler optimization__
as well as easier and more efficient use in multi-threaded applications.

	* NOTE: For runtime performance, be sure to compile with
	optimization enabled. This will remove many "inline" function
	implementations and optimize away many copy operations (that
	are present only for clarify of library implementation code).

#### _Limited Overrides_:

With numeric libraries, it is tempting to try to override all standard C++
math operations. However, this is not necessary for useable library
since many of the same results can often be expressed in alternative
manner.

For example, various comparison operators can always be expressed as
an appropriate combination of operator<() and logical operators (e.g.
"(a \> b)" can be coded easily as "(b \< a)".  This may require a small
adaptation in style and habits.

A side benefit is that consuming code is frequently easier to read
because there are fewer operators, and the resulting code patterns tend
to be more standardized and uniform.

Operators (intentionally) not supported include:

* The increment and decrement pre/post-fix operators -- these are
primarily useful for integer type operations.  Although these could
perhaps be applied to scalar and pseudo-scalar (trivector) grades,
there's little algebraic benefit in doing so.

	operator++() : use explicit "foo = foo + ..." instead;
	operator--() : use explicit "foo = foo - ..." instead

* Division operators -- Given the non-commutative nature of GA (at least
for multiplicative operations, it's generally more clear to be explicit
what is meant. E.g.

	operator/() -- use combination of inverse() and multiplication - e.g.

	// one of these depending on specific intent
	result = numerator * inverse(denominator); // division from right
	result = inverse(denominator) * numerator; // division from left

	// for scalars, instead of "foo = bar / sca;" use something like
	foo = (1./sca) * bar;
	foo = inverse(sca) * bar;

* Compound assignment operators. Given modern compiler optimization
capabilities, the "in-place" operators often provide more of a typing
shortcut than any performance difference. For GA types, there is the
additional concern that multiplication and "division" do not generally
commute, and there are no variants such as a hypothetical "operator=\*()"
or "operator=/()" to address this, which would be potentially confusing
in any case. Instead utilize explicit "operate then assign" syntax such
as:

	operator+=() -- use "foo = foo + bar;"
	operator-=() -- use "foo = foo - bar;"
	operator*=() -- use "foo = foo * bar;", "foo = bar * foo;"
	operator/=() -- use "foo = foo * inverse(bar)", "foo = inverse(bar) * foo;"


### Examples

#### Transform positions, forces, and moments between coordinate frames

As an example Engabra use, the following provides an example of
accomplishing fairly general coordinate transformation operations. It
illustrates instantiation of various types as well as interacting
with rigid body attitude using both sequential and simultaneous angle
conventions.

Consider transforming a coordinate position (vector), a force (vector)
and a moment (bivector) that are expressed with respect to some 'world'
reference coordinate frame in order to obtain an expressions for the force
and moment in the coordinate frame of some specific structural element.

```C++
// Here the using directive makes this code snippet condensed and compact.
// Items having scope resolved by the using operator include:
// - the main data types (Vector, Bivector, Spinor, ...)
// - useful constants including
//   -- basis vectors {e1, e2, e3}
//   -- basis bivectors {e23, e31, e12}
//   -- pi (also piHalf, piQtr, ...)
// - functions (e.g. exp(), logG2(), ...)
using namespace engabra::g3;

// starting information expressed in (W)orld space (assumed known)
Vector const posInW{ 10., 20., 30. };  // some position in world
Vector const forceInW{ -9.81 * e3 };  // e.g. force downward (-e3)
BiVector const momentInW{ 5. * e12 }; // e.g. moment in XY-plane (e12)

// location and attitude of structure in world frame
// generally this would be from some source, design, or calculation
Vector const locSwrtW{ 100., 200. 300. }; // location in world
// specify structure attitude as ordered sequence of Azim/Elev/Roll angles
BiVector const angAzim{ .01234 * pi * e12 }; // e.g. azimuth angle of structure
BiVector const angElev{ .23456 * pi * e23 }; // e.g. elevation angle rotation
BiVector const angRoll{ .34567 * pi * e31 }; // e.g. roll angle rotation
Spinor const spinSwrtW  // "spinor" rotation operator (like a quaternion) 
	{ exp(.5*angRoll) * exp(.5*angElev) * exp(.5*angAzim) };
BiVector const ang3D // 3D angle associated with azim/elev/roll sequence
	{ 2.*logG2(spinSwrtW).theBiv }; // pick BiVector from logG2() spinor

// position, force and moment expressed in (S)tructure element frame
Vector const posInS // canonical rigid body transformation formula
	{ spinSwrtW * (posInW - locSwrtW) * reverse(spinSwrtW) };
// force and moment only need to be rotated
Vector const forceInS{ spinSwrtW * forceInW * reverse(spinSwrtW) };
BiVector const momentInS{ spinSwrtW * momentInW * reverse(spinSwrtW) };

// report result
std::cout << "position in structure frame: " << posInS << std::endl;
std::cout << "   force in structure frame: " << forceInS << std::endl;
std::cout << "  moment in structure frame: " << momentInS << std::endl;
std::cout << "structure attitude 3D angle: " << ang3D << std::endl;
```

#### Integration of (e.g. MEMS) rotation rate sensor

```C++
// TODO - add example here
```

## GA Data Types

Fundamental Types: For detail refer to (doxygen-generated) reference
documentation for classes in file 'g3type.hpp'

#### Underlying Data Field

* __double__ -- native C++ type (for convenience and performance where
constructing a class 'scalar' type is unnecessary). (In algebraic speak,
this is the "field" over which the 3D geometric algebra is defined).

	* TODO/TBD - is this used in 'using' or 'typedef' somewhere? What
	about using library with other types - e.g. 'float' ?

#### Fundamental Types - Blades

* __Scalar__ -- This is mostly a class wrapper around native type in
order to provide consistency with Engabra conventions. This has a single
value (supports subscripting but has only single component [0]) and is
of grade 0. Scalars generally quantities, or "how much" of something,
and also represent magnitudes of other elements.

* __Vector__ -- A (classic) vector (line like) with three components
(subscripts [0-2]) and of grade 1. Vectors are particularly suited for
expressing position relationships, forces, velocities and accelerations.

* __BiVector__ -- A bivector (plane like) with three components (subscripts
[0-2]) and of grade 2.  BiVectors are particularly suited for encoding
directed, planar concepts - including angles, moments, and rotation
operations in 3D space. Bivectors square to non-positive values and
often act like a pure "imaginary" number, but with a planar direction
encoded within them as well.

* __TriVector__ -- a trivector (volume like) with one component (subscript [0])
and of grade 3. Trivectors square to non-positive values and provide a
directionless pure-imaginary number.

#### Most General Type

* __MultiVector__ -- This is the most general element of the (3D)
geometric algebra.  Comprised of a Scalar (.theSca member), a Vector
(.theVec member), a BiVector (.theBiv member), and a TriVector (.theTri
member). Note that any and all other types and general operations of the
entire algebra (and this library) can be implemented entirely in terms
of MultiVectors. The components can also be accessed via subscripts
[0-7] in order of Scalar([0]), Vector([1-3]), BiVector([4-6]),
TriVector([7]) components.

	__NOTE__: If/where the library currently does not support some
	specialized type or combination of operations, you always
	have the option to implement whatever you want in terms of
	multivector operations by first promoting the available types to
	MultiVectors, coding the operations with multivector operations
	and then casting or accessing/extracting the appropriate grade
	portions of the results!!

#### Common Composite Types

Aside from the general MultiVector composition, there are several
more simple composite types that are particularly useful for certain
applications.

* __Spinor__ -- Member of the G2 sub-algebra. The Spinor type is comprised
of a Scalar (.theSca member) and Bivector (.theBiv member). This 3D
spinor type is isomorphic with quaternions. (This type is often associated
with the product of two vectors). The individual components can also be
accessed via subscripts [0-3] with [0] accessing the Scalar and [1-3]
accessing the Vector components.

* __ImSpin__ -- An "imaginary spinor" type that is dual to Spinor.
It is comprised of a Vector (.theVec member) and TriVector (.theTri
member). This type is often associated with the product of three
vectors). Individual components can also be accessed via subscripts
[0-3] with [0-2] accessing the Vector components and [3] accessing
the TriVector component.

#### Commutative and non-commutative decomposition types

* __ComPlex__: with Sca + Tri -- this complex type multiplicatively
commutes with all other types. This type has the same behavior as does
the standard library "std::complex\<double\>" type and can be 
constructed from, and cast to, std::complex.

* __DirPlex__: with Vec + Biv -- this "complex vector" type comprises
the spatially directed grades, vector and bivector. In general,
multiplication with this type is non-commutative.

In general, an arbitrary multivector in 3D space, can be expressed
(or decomposed) in terms of the sum of commuting ComPlex type and
directed DirPlex type. E.g.

	// isomorphic with classic complex numbers
	ComPlex const complex{ someMulti.theSca, someMulti.theTri };

	// the physically directed grades (vec,biv)
	DirPlex const dirplex{ someMulti.theVec, someMulti.theBiv };

	// together ComPlex and DirPlex types comprise a full multivector
	MultiVector const multi{ complex + dirplex };

#### Relatively Unusual Composites (to be implemented as needed)

The following are less commonly utilized types - and are unsupported
in the current Engabra implementation.

All operations associated with these special types can be implemented
completely (albeit slightly less efficiently) by casting to g3::MultiVector
type.

* __ParaVec__: with Sca + Vec -- used for some physics formulations

* __ImPara__: with Biv + Tri -- (dual to ParaVec)

* __NoSca__: -- with Vec + Biv + Tri -- any need?

* __NoVec__: -- with Sca + Biv + Tri -- any need?

* __NoBiv__: -- with Sca + Vec + Tri -- any need?

* __NoTri__: -- with Sca + Vec + Biv -- any need?

In general, the most noticeable restriction of not having these types is
encountered when summing different types in an expression. E.g. something
like:

	MultiVector const foo{ aScalar + aVector + aBivector + aTriVector };

Is a seemingly natural expression. However, the compiler interprets this
from left to right and first tries to produce a ParaVec result
containing the scalar and vector grade quantities. This is followed by
attempting to generate a NoTri type by adding that temporary ParaVec
type to the bivector argument, and so on.

A workaround for this case is to either reorder the additions to produce
an addition order that involves only supported types, e.g.

	
	// temporaries are first a ComPlex and DirPlex type that are
	// then added together to produce a MultiVector
	MultiVector const foo
		{ (aScalar + aTriVector) // a ComPlex temporary
		+ (aVector + aBivector) // a DirPlex temporary
		};

or to cast to MultiVector type first, e.g.

	MultiVector const expMvec
		{ MultiVector(aSca)
		+ MultiVector(aVec)
		+ MultiVector(aBiv)
		+ MultiVector(aTri)
		}; 

Note that these coding inconveniences disappear as more of the special types
are implemented.

#### Grade Access

Compound entities have members of multiple grades (for example, a Spinor
is composed of a Scalar and a BiVector grade member). These constituent
grades may be accessed directly with the associated member variables. The
member variable naming is consistent across all compound types.

	__theSca__: The scalar grade constituent member.
	__theVec__: The vector grade constituent member.
	__theBiv__: The bivector grade constituent member.
	__theTri__: The trivector grade constituent member.

From one perspective these provide the blade decomposition of a general
MultiVector. I.e.

* MultiVector = Scalar + Vector + BiVector + TriVector

	* The Scalar part is most frequently associated with the magnitude
	(size, strength) of quantities and other elements in the algebra,
	e.g. length of vector, size of an angle, etc.

	* The Vector part is probably the single type most heavily used
	for engineering applications.

	* The BiVector part is probably most useful to engineering
	applications for representing angles in 3D space and describing
	the (eqatorial) plane of rotation.

	* The TriVector part is probably not used much on its own for
	engineering applications, but when combined with the Scalar part,
	provides the rich capabilities of the "complex" number system
	used to describe waves, and oscillations.

The compound types can be considered as different partitioning of af
general MultiVector

* MultiVector = Spinor + ImSpin

	* The Spinor part is generally the most useful since these types
	are intimately connected with rotation operations and describing
	the attitude of components and structures. This has great utility
	in practice.

	* The ImSpin type is often associated with intermediate data
	types that occur during GA operations. Frequently it arises in
	the context of the product of three Vector entities.

* MultiVector = ComPlex + DirPlex

	* This partition is particuarly useful for separating the
	multiplicatively commutative portions from a multivector and is
	particuarly important for defining and implementing many of the
	algebraic functions within this library.

	* The ComPlex type is compatible with std::complex<double>.
	One of the common uses of this type is for electrical circuit
	and modeling vibration and oscillation of structures.

	* The DirPlex items is a bit unusual. It has application in
	physics for representing electro magnetic fields, but is perhaps
	not that useful for engineering applications.


#### Component Access

The individual components of all types are accessible with the
subscript operator.

* __operator[]()__: The indices start at zero and increase as follows:

	Scalar     : 0
	Vector     : 0, 1, 2
	BiVector   : 0, 1, 2
	TriVector  : 0
	Spinor     : (0), (1, 2, 3)
	ImSpinor   : (0, 1, 2), (3)
	MultiVector: (0), (1, 2, 3), (4, 5, 6), (7)
	ComPlex    : (0), (1)
	DirPlex    : (0, 1, 2), (3, 4, 5)


## GA Entity Operations

#### GA Entity Input/Output

String formatting:

* __fixed()__: return a string "fixed point" representation of entity
value. Optional arguments allow specifying number of digits encoded both
before and after the decimal point.

* __enote()__: return a string representation using "E-notation" for
representing the numeric values.

Instance insert/extract:

* __operator<<()__: insertion (output) operator for basic GA types.

* __operator>>()__: extraction (input) operator for basic GA types.

#### Special GA Operations

Notes on Terminology: Some of the unitary operations of geometric algebra
are associated with rather ambiguous names. For example, does "conjugate"
mean the "complex conjugate" or does it mean the very different "Clifford
conjugate".  To avoid confusion, a couple functions are given novel names
that should help remove any ambiguity. I.e. the following self-descriptive
functions provide various grade sign changing operations:

* __reverse()__: -- Product permutation operation: Changes algebraic
sign on imaginary-like grade constituents (bivector and trivector
grades). This is associated with changing the order of multiplication
between vector factors in a product - i.e. what might be called a kind of
"procedural inversion".

* __oddverse()__: -- Space involution operation: changes algebraic sign
on odd grade constituents (vector and trivector grades) - (aka "Complex
Conjugate"). This is associated with reflecting all basis vectors through
the origin - i.e.  "space inversion" or "geometric point involution".

* __dirverse()__: -- Composite involution operation: changes algebraic
sign on directed grade constituents (vector and bivector grades) - (aka
"Clifford Conjugate") - i.e. what might be called a kind of "direction
involution".

* __dual()__: -- Operator that interchanges "Real" and "Imaginary"
properties: This returns the result of multiplying its argument
by the unit magnitude imaginary TriVector. The operation provides
the mathematical dual of its argument. In 3D space, the dual type
relationships include:

	* Scalar <-> TriVector
	* Vector <-> BiVector
	* Spinor <-> ImSpin
	* ComPlex <-> ComPlex  (but with 'real' and 'imaginary' roles exchanged
	* DirPlex <-> DirPlex  (but with Vector and BiVector roles exchanged


#### GA Functions

##### Null Value Paradigm Support

These are constexpr entities.

* __nan__: double value representing Not-A-Number (quiet_NaN). This is used
to indicate null instances by populating members with nan values.

* __null()__: various constexpr functions that create "null" instances.

	* TODO/TBD note template use

These involve run-time evaluation:

* __isValid()__: test if an item is not a null instance.  Additional
specialized comparisons include:

	* __bothAreValid()__: conjunction (&&) of isValid() called on each
	argument.


##### Basis Vectors

These are constexpr entities.

* __e0__: unitary basis entity for scalar type

* __e1__, __e2__, __e3__: unitary basis entities for vector type

* __e23__, __e31__, __e12__: unitary basis entities for bivector type

* __e123__: unitary basis entity for trivector type

##### Special Numeric Values

These are constexpr entities/functions.

* __zero()__: create zero instances of various types

	* TODO/TBD note template use

* __one()__: create various types instances with scalar grade value set to 1.

	* TODO/TBD note template use

* Useful _double_ type (radian) angle values

	* __pi__, __piHalf__, __piQtr__: respective fractions of pi

	* __turnFull__, __turnHalf__, __turnQtr__: fractions of pi associated with
	turning motions.

##### Comparision Support

These involve runtime evaluation.

* __nearlyEquals()__: generally useful comparison if two (reasonably
normalized) data values are "same enough" within practical tolerances
(allowing for reasonable amount of computation noise). Additional
specialized comparisons available include:

	* __isSmallAbs()__: has a absolute value within tolerance near zero
	* __isSmallAbsDiff()__: two values are within isSmallAbs() of each other
	* __nearlyEqualsAbs()__: two values are same within absolute tolerance
	* __nearlyEqualsRel()__: two values are same within relative tolerance

* __operator==()__: comparisions for bit-wise identical values.

##### Convenience functions

These are for types in __closed subalgebras__. This includes types:
Scalar, Spinor, Complex, and MultiVector.

* __sq()__ : Square of argument (i.e. arg\*arg)

* __cube()__: Cube of types (i.e. arg\*arg\*arg)

##### Magnitude and Direction

Blade magnitude and direction (direction only valid for non-zero blades)

* Magnitude - This is a real (Scalar) type that is always non-negative and
represents the "size" or "strength" of an entity.  In GA, the magnitude
(aka "norm"): (associated with the square root of the scalar part of
the product of an entity and its reverse):

	* __magnitude()__: a native __double__ value representing the
	magnitude of the argument (i.e. sqrt(magSq(arg))

	* __magSq()__: a native __double__ value that is the square of
	the magnitude of the argument (i.e. arg\*reverse(arg));

* Amplitude - This is a ComPlex type that has a rather abstract
interpretation. Its main use is in defining an inverse of other types.

	NOTE: Amplitude (as used here) is only defined for Geometric Algebras
	over spatial dimensions of size three (as the case here) or less. The
	amplitude may not exist in all cases.

	* TODO - Amplitude is one component of polar form.

	* __amplitude()__: a ComPlex quantity that 

		TODO ...

* Direction - Decomposition of 

	* TODO - Direction is one component of polar form.

	* __direction()__: for non-zero arguments, returns a unitary magnitude
	instance of the same type as argument (i.e. arg/magnitude(arg))

		TODO... should this be in terms of amplitude?

* Polar Form - Decomposition of general multivector into
Amplitude and (TODO??) Direction

	* __pairMagDirFrom()__: returns both magnitude and direction of argument
	(i.e. std::pair\<magnitude(arg), direction(arg)\>). This saves a couple
	computation operations in the fiarly common case when both are needed.


##### Unitary Operators

* __operator-()__: unary negation: changes sign on all grades (sca,vec,biv,tri)

* __reverse()__: -- changes algebraic sign on imaginary-like grades (biv,tri)

* __oddverse()__: -- changes algebraic sign on odd grades (vec,tri)

* __dirverse()__: -- changes algebraic sign on directed grades (vec,biv)

* __dual()__: -- this returns the dual of it's argument:

	* dual(sca) =  e123\*sca (is a TriVector)
	* dual(vec) =  e123\*vec (is a BiVector)
	* dual(biv) = -e123\*biv (is a Vector)
	* dual(tri) = -e123\*tri (is a Scalar)


##### Binary Operators

* __operator+()__: binary addition of two items.

	All operations are supported with both arguments of same time.
	TODO - implement support for mixed type combinations

* __operator-()__: binary "subtraction" of two items.

* __operator\*()__: binary multiplication of two items. In large part,
these operations provide the "magic" of Geometric Algebra in providing
extension and contraction of grades during the multiplication process.

	All operations are supported with both arguments of same time.
	Most commonly used mixed type operations are supported.
	TODO - implement support for ALL mixed type combinations


##### Algebraic Inverse

* __inverse()__: multiplicative inverse of non-zero (and non-idempotent)
blades (i.e. reverse(arg)/magSq(arg)).

	Inverse is supported for all types that are a product of zero or
	more vector factors. This includes the fundamental types (S,V,B,T)
	as well as Spinor, ImSpinor.
	TODO - implement more general support


##### Trancendental Functions

The implementation of the following functions is based in large part on the
descriptions of [Chappell, et.al., PLoS]

* __exp()__: exponential function (current Q1'23 for BiVectors and Spinors)

	Current support includes argument types: Spinor (of which BiVector
	and Scalar are special cases with one grade constituent being zero).
	TODO - implement more general support

* __logG2()__: logarithm for members of G2 sub-algebra (Spinors)

	Current support includes argument types: Spinor (of which BiVector
	and Scalar are special cases with one grade constituent being zero).
	TODO - implement more general support

* __sqrtG2()__: square root for members of G2 sub-algebra (Spinors)

	Current support includes argument types: Spinor (of which BiVector
	and Scalar are special cases with one grade constituent being zero).
	TODO - implement more general support

* __solutionOfLinear()__: solve linear multivector equation of form "AX+XB=C"


## Template Support Functions

To support internal implementation and perhaps some advanced uses of
the library code, there are several functions available that can aid
writing template code (ref g3traits.hpp). These include the following

In the "is" sub-namespace (within engabra::g3::is::)

* __is::blade()__: Evaluates to true if argument is a blade (pure Scalar,
Vector, BiVector, or TriVector type).


## Getting Started

### Clone, Build and Install

Clone this repository to local system then use the [CMake](www.cmake.org)
to package or install - e.g. using the
[example commands below](#Code-Build-Commands)

### Using installed package within another CMake project

If you have a code project that is also using CMake, you can request
cmake to automatically include Engabra by doing the following.

In the SomeProject/CMakeLists.txt file include:

	# Use CMake command to locate and attach Engabra package
	find_package(Engabra REQUIRED NO_MODULE)
	# Informational messages to confirm status and report version ID
	message(Engabra Found: ${Engabra_FOUND})
	message(Engabra Version: ${Engabra_VERSION})

	# Include Engabra in target build - e.g.
	target_link_libraries(
		${SomeTarget}
		PRIVATE
			Engabra::Engabra
		)

### Getting Help

TBD


## Software Organization

Code is implemented in standard C++ (C++11? 17?). The library and distribution
packages can be built with the CMake utility. The reference documentation is
created with [Doxygen](https://www.doxygen.nl/) as part of the cmake build
process.

Tools for building the library:

* C++ compiler (standard C++17 or later) - e.g. gcc, clang, msvc

* [CMake](https://cmake.org/) utilties (cmake, ctest, cpack) (v3.13 or later)

* [Doxygen](https://www.doxygen.nl/) utility

### Directory Structure

Relative to top engabra directory, the directory structure includes
several subdirectories:

* ./include -- library main source code

	* ./include/Engabra -- main include file with which to access library.

* ./src -- currently (2023.03) not used (is header only project)

* ./tests -- project test programs (integrated with 'CTest')

* ./cmake -- contains source files used in the CMake generator system

* ./doc -- files and information used for Doxygen document production

* ./demos -- a few simple demonstration programs for reference which
can be [Compiling Demo Programs](#Compiling-Demo-Programs) compiled as
described below).

	* ./helloEngabra -- example of include, namespaces and basic types

### Header File Structure

The following summarizes the organization of header files for the Engabra
library. The majority of library code is implemented as inline definitions
within these headers.

Detail on the contents of each can be found in the (doxygen-generated)
reference documentation. This reference documentation is created as part
of the library build and installation process. Ref section
[Reference Documentation](#Reference-Documentation)

#### Overall Access

* __engabra__ -- for matter of style (has "#include "engabra.hpp")

* __engabra.hpp__ -- includes the headers listed below

#### Implementation and Reference Documentation Organization

Fundamentals:  (included by top level include, but useful names to know
for accessing the reference documentation.

* __g3type.hpp__ -- defines fundamental types

* __g3const.hpp__ -- useful constants (e.g. basis entities, zero<>,
null<>, pi, etc)

* __g3compare.hpp__ -- functions for comparing numeric values

* __g3validity.hpp__ -- functions for checking validity (supporting the
null object paradigm)

Fundamental algebraic operations.

* __g3ops.hpp__ -- includes all other g3ops\* files in one place

* __g3opsUni.hpp__ -- unitary operations (e.g. reverse, negation, duals, etc)

* __g3opsAdd.hpp__ -- addition operators e.g. op+() and op-() for various types

* __g3opsMul.hpp__ -- multiplication operators (e.g. op\*() for various types)

Input output support functions

* __g3io.hpp__ -- string formatting, op<<(), op>>() overloads, etc

General algebraic functions

* __g3func.hpp__ -- math functions (e.g. exponentials, logarithms, roots, etc)

Advanced utilities

* __g3traits.hpp__ -- constructs useful for advanced template constructions

Internal implementation:

* g3publish.hpp -- declarations to promote various function declarations
for use in global namespace.


## Basic Library Use

### Namespaces

* engabra - overall containing namespace

* engabra::g3 - sub space for 3D geometric operations. An often convenient
coding technique is to employ the 'using' directive to shorten the namespace
resolution (unless you have another 'g3' namespace).

E.g. as in

```C++
engabra::g3::Vector const aVec{ 1., 2., 3. };
// or
using namespace engabra;
g3::Vector const aVec{ 1., 2., 3. };
// or
using namespace engabra::g3;
Vector const aVec{ 1., 2., 3. };
```

### Implementation Key Concepts

#### Null Object Paradigm Support

The library uses and supports a null object pattern paradigm. E.g.

```C++
using namespace engabra;
// construct a null instance
g3::Vector const aNullVec{ g3::null<Vector>() };
// after which guarantees (false == g3::isValid(aNullVec))
// check validity of return value (assuming someFunction supports null paradigm)
g3::Vector const someVec{ someFunction() };
if (g3::isValid(someVec))
{
	// okay to use someVec (it's not null)
}
```

#### Default Initialization (None)

Default initializations follow C++ convention for initialization of
aggregate types - e.g. no initialization can be assumed.

```C++
engabra::g3::Vector const vecUnInitialized;
```

Note that this is of limited use in light of the emphasis on use of
const as described in the next section. I.e. in general, all entities
should be initialized explicitly (to values, by function return, using a
'null' or 'zero' type template) - otherwise, it's generally good to delay
(or eliminate) instantiating an instance until there's something with
which to initialize it.

#### Emphasis on 'const' Instances

The library implementation makes copious use of 'const' to support
high performance (and what many people consider good coding practice).
The use of 'const' data instances is encouraged to the extent that this
is assumed in place of supporting self-modifying types.

Therefore, the library does _not_ have support for self modifying
operators like "\*=", "++", etc.  Instead, in place of updating an entity
in place, simply create a new instance at will and discard the old one.

```C++
using namespace engabra;
g3::Vector const beforeVec{ someInitFunction() };
g3::Vector const afterVec{ beforeVec + g3::Vector{1., 2., 3.} };
```

In general, this is not a problem for higher level applications. Compiler
optimization for modern compilers is typically sufficiently advanced that
there are virtually no (speed or space) performance penalties in expressing
source code with the extra construction/destruction.

## Features


## Tools

### Code Build Commands
Engabra uses the [CMake build system generator utility](https://cmake.org/).

Clone Example:

	$ cd /repos  # or wherever, '/repos' is used as example here
	$ git clone https://github.com/Stellacore/engabra.git

Build Example:

	$ # -- Compile everything (including doxygen documentation)
	$ mkdir <someBuildDir> && cd <someBuildDir>
	$ cmake  \
		-DCMAKE_BUILD_TYPE=Release \
		-DCMAKE_INSTALL_PREFIX=/tmpLocal/ \
		-DCMAKE_PREFIX_PATH=/tmpLocal/ \
		/repos/engabra
	$ cmake --build . --target all -j `nproc`
	$ # -- Run library unit tests
	$ ctest -j `nproc`
	$ # -- Create distribution packages
	$ cpack
	$ # -- Installation
	$ dpkg --contents ./Engabra*
	$ sudo apt-get install ./Engabra-0.1.0-Linux.deb   # Install
	$ sudo apt-get remove engabra   # Remove

### Compiling Demo Programs
	* cmake --build . --target all -j `nproc`

Assuming that Engabra is cloned to /repos/engabra, then

	$ mkdir <someBuildDir> && cd <someBuildDir>
	$ cmake  \
		-DCMAKE_BUILD_TYPE=Release \
		/repos/engabra/demos
	$ make -j `nproc`
	$ # -- Run individual programs as desired (relative to build dir) e.g.
	$ ./demos/helloEngabra

### Reference Documentation

Provided "doxygen" tool is available, library reference documentation
(on classes, files, functions, and more) is generated automatically
during the cmake build process described in section [Code Build
Commands](#Code-Build-Commands).

After building system (with cmake), point browser to:

	<cmakeBuildDir>/doc/html/index.html

After installation of the package documents are found in appropriate system
install locations. E.g. on linux systems, often in:

	<installPath>/share/doc/engabra/html/index.html

## References

* Chappell JM, Iqbal A, Gunn LJ, Abbott D (2015) Functions of Multivector
Variables. PLoS ONE 10(3): e0116943. doi:10.1371/journal.pone.0116943,
[(at journals.plos.org)](https://journals.plos.org/plosone/article/file?id=10.1371/journal.pone.0116943&type=printable)

* Chappell JM, Iqbal A, Abbott D (2015), "Geometric Algebra: A natural
representation of three-space", arXiv:1101.3619v3 [physics.hist-ph]
16 Apr 2015, [(at arXiv)](https://arxiv.org/pdf/1101.3619v3.pdf)

* Chappell JM, Hartnett JG, Iannella N, Iqbal A and Abbott D (2016)
Time As a Geometric Property of Space.
Front. Phys. 4:44.
doi: 10.3389/fphy.2016.00044
[(at Frontiers in Physics)](https://www.frontiersin.org/articles/10.3389/fphy.2016.00044/full)

* Chappell,... "Deriving time from the geometry of space"
https://arxiv.org/pdf/1501.04857v2.pdf

* Chappell,... "A new description of space and time using Clifford multivectors"
https://arxiv.org/pdf/1205.5195.pdf

* https://www.researchgate.net/publication/281948670_Some_remarks_on_Cl3_and_Lorentz_transformations

	% veterinary faculty guy 
	unknown{unknown,
	author = {Josipovic, Miroslav},
	year = {2015},
	month = {09},
	pages = {},
	title = {Some remarks on Cl3 and Lorentz transformations},
	doi = {10.13140/RG.2.1.3138.6088}
	}
