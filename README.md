
[//]: # (Comments Like this)

[MIT License](https://mit-license.org/)


# Engabra - ENGineering Geometric AlgeBRA
*A C++ Library enabling  __Practical__ engineering computation
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

Quick jump links to below:
* [Key Features](#Key-Features)
* [GA Data Types](#GA-Data-Types)
* [Getting Started](#Getting-Started)
* [Software Organization](#Software-Organization)
* [Basic Library Use](#Basic-Library-Use)
	* [Code Build Commands](#Code-Build-Commands)

### Examples

#### Transform positions, forces, and moments between coordinate frames

A an example, consider transforming a coordinate position (vector),
a force (vector) and a moment (bivector) that are expressed in a world
coordinate frame in order to obtain an expressions for the force and
moment now expressed in the coordinate frame of some specific structural
element.

```C++
// Here the using directive makes this code example more condensed and compact.
// Items with scope resolved by the using operator include:
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

## Key Features

The main utility/distinction of Engabra is that it has a very practical
focus for use in coding applications that provide real-world engineering
solutions.

#### _Practical_:

Structured and intended for real-world engineering type solutions.

* Focused on actual use (compared with experimentation or academic
explorations)

* All entities have direct physical interpretations and associations
(compared with e.g. various higher-dimensional conformal algebras used
in academic contexts)

* Dumb-simple-stupid class definitions and function operators generally
allow compiler to do type checking and produce easily interpretable
warnings and error messages.

* Uses explicit constructors and avoids implicit casting to avoid
potential confusing behaviors - keeps consuming code expression very
WYSIWYG.

* Engabra is an entirely stand-alone library. No other packages need be
installed to use it - other than C++ compiler (e.g. g++, clang, msvc)
and general development environment of course.

#### _Platforms and Environments_:

The code is portable C++ and should work fine on nearly any platform that
supports a modern standard C++ compiler.

* Code implementation is relatively 'vanilla' and standard so that
the library should build on nearly any (64-bit) device or platform.

	* Note: (as of 2023.Q1) implementation has only been built for
	environments using 64-bit double representations. It is unverified
	how/if compatible the implementation is with 32-bit double sizes.

* The CMake build process should allow compiling and packaging on a variety
of different operating systems, distributions and hardware platforms.

	* _Note_ that the descriptions herein and associated
	file/directory/command name conventions are consistent with a
	\*nix environment.  However, this should not be construed as any
	sort of limitation on the library, only that a \*nix environment
	was used to author many of the text files and descriptions.

#### _Natural Code Syntax_:

For the most part, the library is very easy and natural to use in consuming
code.

* There are no fancy templating expressions involved or required in the
consuming code (other than a few relatively natural use cases - e.g.
such as defining a few useful type instances such as "null<Vector>()"
or "zero<BiVector>()" and the like)

* There are NO strange operators to memorize.

	* Operator overloading only uses the obvious and standard operators
	(e.g. "\*" for multiplication, "+" for addition, etc).

	* For operations not standard to C++ syntax, clarifying function
	names are used (e.g. dot(), wedge(), reverse(), dual()}

	* Division ambiguity is avoid in favor of more explicit constructs
	involving element inverses. I.e. specifie either "inverse(vecA)*vecB" or
	"vecA*inverse(vecB)" according to whichever is actually intended.

#### _Performance_:

Engabra is very fast to use in practice.

* Fast to compile -- although templates are used heavily within the
_implementation_ of Engabra the instantiations are dirt simple so that
compiler can resolve and instantiate code very quickly. Note that, in
spite of the use of templates within the implementation, consuming code
is generally free from them - other than a few cases where using templates
could be expected for any library (mostly in customizing constant types)

* Fast run time -- The run time performance is quite good. Although there
are no special coding techniques used (and certainly no expectation for
special hardware), the implementation code makes copious use of 'const'
and 'inline' specifications so that compilers can optimize the implementation
code very well.

* Emphasizes 'const' paradigm to support better __compiler optimization__
as well as easier and more efficient use in multi-threaded applications.

	* NOTE: For runtime performance, be sure to compile with
	optimization enabled. This will remove many "inline" function
	implementations and optimize away many copy operations (that
	are present only for clarify of library implementation code).

#### _Limited Overrides_:

With numeric libraries, it is tempting to try to override all standard C++
math operations. However, this is not necessary for a functioning library
since many of the same results can often be expressed in alternative
manner.

For example, various comparision operators can always be expressed as
an appropriate combination of operator<() and logical operators (e.g.
"(a \> b)" can be coded easily as "(b \< a)".

A side benfit is that the code is generally easier to read because there
are fewer operators to distract thought, and resulting code patterns are
more standardized and uniform.

Operators (intentionally) not supported include:

* The increment and decrement pre/post-fix operators -- these are
primarily useful for integer type operations.  Although these could
perhaps be applied to scalar and pseudo-scalar (trivector) grades,
there's little algebraic benefit in doing so.

	operator++() -- use explicit "foo = foo + ..." instead;
	operator--() -- use explicit "foo = foo - ..." instead

* Division operators -- Given the non-commutative nature of GA (at least
for multiplictative operations, it's generally more clear to be explicit
what is meant. E.g.

	operator/() -- use combination of inverse() and multiplication - e.g.

	// one of these depending on specific intent
	result = numerator * inverse(denominator); // division from right
	result = inverse(denominator) * numerator; // division from left

	// for scalars, instead of "foo = bar / sca;" use something like
	foo = (1./sca) * bar;
	foo = inverse(sca) * bar;

* Compound assignment operators. Given modern compiler optimizaiton 
capabilities, these are often no more than a typing shortcut.

	operator+=() -- use "foo = foo + bar;" instead
	operator-=() -- use "foo = foo - bar;" instead
	operator*=() -- use "foo = foo * bar;" instead
	operator/=() -- use "foo = foo + inverse(bar);" instead


## GA Data Types

#### Fundamental Types

Fundamental Types: For detail refer to (doxygen-generated) reference
documentation for classes in file 'g3type.hpp'

* __double__ -- native C++ type (for convenience and performance where
constructing a class 'scalar' type is unnecessary). (In algebraic speak,
this is the "field" over which the 3D geometric algebra is defined).

* __Scalar__ -- (class wrapper around native double - that mirrors overall
Engabra conventions.  This is a classic single value (subscripts [0]) and of
grade 0.

* __Vector__ -- A (classic) vector (line like) with three components
(subscripts [0-2]) and of grade 1. Vectors are particularly suited for
expressing position relationships, forces, velocities and accelerations.

* __BiVector__ -- A bivector (plane like) with three components (subscripts
[0-2]) and of grade 2.  BiVectors are particularly suited for encoding
(directed 3-dimensional) angles, moments, and rotation operations in 3D space.

* __TriVector__ -- a trivector (volume like) with one component (subscript [0])
and of grade 3.

#### Common Composite Types

* __Spinor__ -- Member of the self-consistent and self-closed G2 sub-algebra.
Composed of a Scalar (.theSca member) and Bivector (.theBiv member). This 3D
spinor type is isomorphic with quaternions. (This type is often associated
with the product of two vectors). The individual components can also be
accessed via subscripts [0-3] in order Scalar then Vector components.

* __ImSpin__ -- An "imaginary spinor" type that is dual to
Spinor. Composed of a Vector (.theVec member) and TriVector (.theTri
member). This type is often associated with the product of three
vectors). Individual components can also be accessed via subscripts
[0-3] in order Vector then TriVector components.

* __MultiVector__ -- The most general element of the (3D) geometric
algebra.  Composed of a Scalar (.theSca member), a Vector (.theVec
member), a BiVector (.theBiv member), and a TriVector (.theTri
member). Note that any and all other types and general operations of the
entire algebra can be implemented entirely in terms of MultiVectors. The
components can also be accessed via subscripts [0-7] in order of Scalar,
Vector, BiVector, TriVector components.

	__NOTE__: If the library currently does not support some
	specialized type or combination of operations, you can always
	implement whatever you want simply by promoting types to
	MultiVectors, coding the operations with multivector operations
	and then accessing/extracting the appropriate grade portions of
	the results!!

#### Commutative and non-commutative decomposition types

* __Complex__: with Sca + Tri -- this complex type multiplicatively
commutes with all other types. This type has the same behavior as does
the standard library "std::complex\<double\>" type. This type can be 
constructed from (and cast to) std::complex.

* __DirPlex__: with Vec + Biv -- this "complex vector" type contains
the spatially directed grades (vector and bivector). In general,
multiplication with this type is non-commutative. The DirPlex type
provides a natural representation for describing electromagnetic fields
(with the vector representing the electric components, and bivector
representing the magnetic ones).

In general general 3D multivector can be decomposed as:

	Complex const complex{...}; // isomorphic with classic complex numbers
	Complex const dirplex{...}; // the physically directed grades (vec,biv)
	MultiVector const multi{ complex + dirplex };

In this representation, the "complex" type commutes with the dirplex typeC
commute. E.g. for this construction,

	MultiVector const comdir{ complex * dirplex };
	MultiVector const dircom{ complex * dirplex };

The instances "comdir" and "dircom" will be theoretically identical.

#### Relatively Unusual Composites (to be implemented as needed)

All operations associated with the following special types can be implemented
completely (albeit slightly less efficiently) using full g3::MultiVector
data types.

* __ParaVec__: with Sca + Vec -- used for some physics formulations

* __ImPara__: with Biv + Tri -- (dual to ParaVec)

* __NoScalar__: -- with Vec + Biv + Tri -- any need?

* __NoVector__: -- with Sca + Biv + Tri -- any need?

* __NoBiVector__: -- with Sca + Vec + Tri -- any need?

* __NoTriVector__: -- with Sca + Vec + Biv -- any need?


#### Grade Access

Compound entities have members of multiple grades (for example, a Spinor
is composed of a Scalar and a BiVector grade member). These constituent
grades may be accessed directly as member variables. The member variable
naming is consistent across all compound types.

	__theSca__: The scalar grade constituent member.
	__theVec__: The vector grade constituent member.
	__theBiv__: The bivector grade constituent member.
	__theTri__: The trivector grade constituent member.


#### Component Access

The individual components are accessible with the subscript operator:

* __operator[]()__: The indices start at zero and increase as follows:

	Scalar     : 0
	Vector     : 0, 1, 2
	BiVector   : 0, 1, 2
	TriVector  : 0
	Spinor     : (0), (1, 2, 3)
	ImSpinor   : (0, 1, 2), (3)
	MultiVector: (0), (1, 2, 3), (4, 5, 6), (7)


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

* __reverse()__: -- as expected, changes algebraic sign on imaginary-like
grade constituents (bivector and trivector grades). This is associated
with changing the order of multiplication between vector factors in
a product - i.e. what might be called a kind of "procedural inversion".

* __oddverse()__: -- changes algebraic sign on odd grade constituents
(vector and trivector grades) - (aka "Complex Conjugate"). This is
associated with reflecting all basis vectors through the origin - i.e.
"space inversion" or "geometric point involution".

* __dirverse()__: -- changes algebraic sign on directed grade constituents
(vector and bivector grades) - (aka "Clifford Conjugate") - i.e. what might
be called a kind of "direction involution".

* __dual()__: -- as expected, this returns the dual of it's argument. In
3D space, the dual type relationships include:

	* Scalar <-> TriVector
	* Vector <-> BiVector
	* Spinor <-> ImSpin


#### GA Functions

##### Null Value Paradigm Support

These are constexpr entities.

* __nan__: double value representing Not-A-Number (quiet_nan). This is used
to indicate null instances by populating members with nan values.

* __null()__: various constexpr functions that create "null" instances.

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

* __one()__: create various types instances with scalar grade value set to 1.

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
Scalar, Spinor, Complex, MultiVector.

* __sq()__ : Square of argument (i.e. arg\*arg)

* __cube()__: Cube of types (i.e. arg\*arg\*arg)

##### Magnitude and Direction

Blade magnitude and direction (direction only valid for non-zero blades)

* __magnitude()__: a native __double__ value representing the magnitude
of the argument (i.e. sqrt(magSq(arg))

* __magSq()__: a native __double__ value that is the square of the
magnitude of the argument (i.e. arg\*reverse(arg));

* __direction()__: for non-zero arguments, returns a unitary magnitude
instance of the same type as argument (i.e. arg/magnitude(arg))

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

Clone this repository to local system then follow [instructions
below](#Code-Build-Commands) to build, test, package and install (or
any some of those).

### Installation and basic use

Install: package

Utilize: include headers and link against library

### Using with other CMake projects

CMake: using cmake find and in other projects

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
	* cmake --build . --target all -j 16

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
@unknown{unknown,
author = {Josipovic, Miroslav},
year = {2015},
month = {09},
pages = {},
title = {Some remarks on Cl3 and Lorentz transformations},
doi = {10.13140/RG.2.1.3138.6088}
}
