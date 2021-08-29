
# engineeringGeoAlg - A Pragmatic Implementation of Geometric Algebra for Engineering


## Features

	- Simple
		- clean concrete classes for easy use
		- avoid annoying complex template notation for simple things
		- and fast compilation (avoid OVER use of templates)
		- clean software code separation of data and operations
			- avoids fancy overloading of operators,
			- uses clearly named/defined function calls instead of confusing
			- uses compile time type checking for operator consistency
			- explicit promotion of types (from operators, or from ctors)
				- avoids implicit conversions which can cause confusion
		- explicit implementation of functions
			- avoid template resolution and SFINAE confusion

	- High performance
		- fast compilation (restricted use of templates to sensible amount)
		- fast run time (reasonably efficient code)

	- Portable standard C++-17(?)

	- Lightweight - stand-alone implementation (no external libraries)

	- Modular - additional features are provided by additional modules
		egaBase - structures (blades and composities) and interactions
		egaMath - multiplications (e.g. 3D multiplication table implementation)
			egaFuncs - algebraic functions (e.g. exp(), log(), etc)
		egaRigid - e.g. rigid body (and conformal?) transformations
		egaIO - serializing and i/o support
		egaXyz


## Decisions

	- Naming: verbose vs. short
		- For structs (blades)
			- use a short regular pattern for efficiency
				(e.g. Sca, Vec, Biv, Tri)
			- provide aliases that can be used as longer descriptive names
				(e.g. Scalar, Vector, Bivector, Trivector)
		- For structs (composites)


## Alternatives

### Terathon Math Library

"C++ math library for 2D/3D/4D vector, matrix, quaternion, and geometric algebra."

	- https://github.com/EricLengyel/Terathon-Math-Library

### LGA

"A C++ library to do geometric and linear algebra."

	- https://github.com/mifortin/LGA

### ConstGA

Uses C++ constant expressions to do Geometric Algebra. Removes
all calculations that result in zeros at compile time.

	- https://github.com/RobinKa/ConstGA


