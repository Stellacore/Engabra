# test info

## Testing structure

### Test Environment

The test environment includes

	checks.hpp - functions used by individual test implementations.

### Test Naming

Tests are named as

	test_g3<group><name>

This facilitates use with CTest utility and its regular expression matching.

### Ranking Hierarchy

For tests that involve multiple fundamental types, tests are structured
based on the rand hierarchy below. Items lower in the hierarchy assume
that those above already exist and are covered by tests.  For example,
test for a binary combination of actions (e.g. multiplication, a cast,
etc.) between types A and B are implemented within test for B assuming
A occurs before B in the following list:

Type Ranking:

	Scalar
	Vector
	BiVector
	TriVector
	Spinor
	ImSpin
	ComPlex
	DirPlex
	MultiVector

For example, a binary operator for Spinor\*DirPlex (if implemented) belongs
in test with name test_g3<...>DirPlex (and not in test_g3<...>Spinor.

### Package

Overall project/package level tests

	test_g3engabra
	test_g3helloEngabra.cpp

### Types

Check basic construction and fundamental type methods.
Naming convention test_g3type_<>

	test_g3type_ctors - constructions for {ctor, default, zero, null}

	test_g3type_Scalar
	test_g3type_Vector
	test_g3type_BiVector
	test_g3type_TriVector
	test_g3type_Spinor
	test_g3type_ImSpin
	test_g3type_ComPlex
	test_g3type_DirPlex
	test_g3type_MultiVector

### Traits

	test_g3traits_all.cpp

### Validity

Check null pattern support (e.g. 'null<>' and 'isValid()').
Naming convention test_g3validity_<>

	test_g3validity_all

### Comparison

Check numeric value comparisons (e.g. 'nearlyEquals()').
Naming convention test_g3compare_<>

	test_g3compare_all

### Constants

Check defined constant values.
Naming convention test_g3const_<>

	test_g3const_all

### Casting

Check casting between various fundamental types.
Naming convention test_g3cast_<>

	test_g3cast_all

### Operator Overloading

#### Namespace promotion

Check code used to promote/publish namespace declarations for use in
standard namespace (e.g. operator<<(), operator+(), operator\*() etc )

	test_g3publish.cpp

#### Input/Output

Check overload operators for basic input and output (e.g. stream overloads)
Naming convention test_g3io_<>

	test_g3io_all

#### Unitary Operations

Check single argument operations (e.g. negation, reverse, oddverse, dirverse)
Naming convention test_g3opsUni_<>

	test_g3opsUni_all.cpp

#### Addition Operations

Check addition overload operators.
Naming convention test_g3opsAdd_<>

	test_g3opsAdd_Scalar
	test_g3opsAdd_Vector
	test_g3opsAdd_BiVector
	test_g3opsAdd_TriVector
	test_g3opsAdd_Spinor
	test_g3opsAdd_ImSpin
	test_g3opsAdd_ComPlex
	test_g3opsAdd_DirPlex
	test_g3opsAdd_MultiVector

#### Multiplication Operations

Check multiplication overload operators.
Naming convention test_g3opsMul_<>

Note that multiplication operators are implemented in the test code
associated with the highest ranking argument.

	test_g3opsMul_Scalar
	test_g3opsMul_Vector
	test_g3opsMul_BiVector
	test_g3opsMul_TriVector
	test_g3opsMul_Spinor
	test_g3opsMul_ImSpin
	test_g3opsMul_ComPlex
	test_g3opsMul_DirPlex
	test_g3opsMul_MultiVector

### Functions

Math functions for GA types (perhaps the most useful aspect of
the Engabra library)

#### Unary

	test_g3func_ga - geometric algebra functions
	test_g3func_G2 - specialized operations for G2(even) subalgebra
	test_g3func_mag - scalar magnitude functions
	test_g3func_amp - complex-like amplitude functions

#### Algebraic

	test_g3func_inv - algebraic inverses

#### Transcendental

	test_g3func_exp - exponentional function
	test_g3func_log - function inverse of exponentional function
	test_g3func_trig - trigonometric components (hyperbolic and standard)

#### Polar form

Amplitude/Argument style representations

	test_g3func_polar - polar form (amplitude/argument) decomposition

#### Powers and roots

General powers and roots of multivectors (exploits polar form)

	test_g3func_pow
	test_g3func_root


## ===================================

#### Convenience Functions - TODO/TBD if needed

	test_g3func_dot - inner products (lowest grade of pairwise products)
	test_g3func_wedge - outer products (highest grade of pairwise products)

## Status 2023.11.11 - TODO

The following need renaming (and factoring) to conform with above

	test_g3opsAdd.cpp
	test_g3opsMulAll.cpp
	test_g3opsMul.cpp

	test_g3func_amp.cpp
	test_g3func.cpp
	test_g3func_exp.cpp
	test_g3func_mag.cpp


