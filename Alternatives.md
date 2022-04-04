
# Available/Alternative GA libraries


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


## Differentiators

	- use focus (not sciency or code trickery) - i.e. practical

	- non-confusing - simple, basic code that is easy to read/understand

		- no "new" operator overloading to learn (only basics op*, op+ etc used)

		- don't mess with the standard C++ environment

			- avoid special constructions, special syntax

			- allow common-sense constructions and syntax

		- no special compiler flags needed (other than normal optimization)

	- audience

		- assume familiarity with GA

		- e.g. discovered it, think it's cool,
			and want to use it on *REAL* project/app work.


### Resource lists

	- https://github.com/ga/awesome-geometric-algebra

### versor

	- http://wolftype.github.io/versor/devel/html/

	- On quick scan, looks reasonably good.

### gal

	- https://github.com/jeremyong/gal

	- Might be okay?
		"GAL is a realtime suitable C++17 library designed to
		be simultaneously competitive with and complementary to
		traditional methods for computing geometry (e.g. linear
		algebra, vector spaces, quaternions, dual quaternions). As
		the majority of its work is done at compile-time, the
		library is naturally "header-only" due to the implicit
		inlining requirements."

	- Benchmarks: https://www.jeremyong.com/gal/benchmarks/


