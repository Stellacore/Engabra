
# EnGAbra - Practical Geometric Algebra Computation for Engineering


EnGAbra - Engineering Geometric Algebra

namespace ega::
namespace Engabra::


## Good advice points

- What the project does
- Why the project is useful
- How users can get started with the project
- Where users can get help with your project
- Who maintains and contributes to the project

- a brief description of what your code does;
- instructions for installing your code;
- what other code needs to be installed for it to work;
- one or two examples of how to invoke your code;
- optionally: who wrote the code, how to cite it, and who to contact for help.
- One good example of a README file is
[here](https://github.com/github/markup/blob/master/README.md)



## Features

	- Graphics
		- need cool imagery on main page

	- Functional
		- not an experiment
		- not an academic exercise
		- ref example project (e.g. gravity bridge?)

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


## Tools

### Code Build Tools

- CMake : for build system generation

- Standard C++ compiler (e.g. g++, clang)

### Documentation

#### Code Reference Material

Doxygen : For generation of code reference documentation

#### General Algorithm and Math Descriptions

LyX : GUI interface for operating with LaTeX

- https://www.lyx.org/


LaTeX Figures

- tikZ : For drawing figures

	- https://www.tug.org/pracjourn/2007-1/mertz/mertz.pdf

	- https://www.overleaf.com/learn/latex/LaTeX_Graphics_using_TikZ%3A_A_Tutorial_for_Beginners_(Part_1)%E2%80%94Basic_Drawing

- tikz-3dplot : Extensions to tikz for drawing perspective 3D figures

	- https://ctan.math.washington.edu/tex-archive/graphics/pgf/contrib/tikz-3dplot/tikz-3dplot_documentation.pdf

	- https://tex.stackexchange.com/questions/534487/difference-between-usetikzlibrary3d-and-usepackagetikz-3dplot/534521#534521

	- https://ctan.org/pkg/tikz-3dplot

	- https://mirrors.concertpass.com/tex-archive/graphics/pgf/contrib/tikz-3dplot/tikz-3dplot_documentation.pdf


