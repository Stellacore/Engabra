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

//
// Program to demonstrate basic Engabra data types
//

/*! \file
\brief Example of fundamental and composite type construction and output.
*/

/*

Example:
\snippet test_g3NS.cpp DoxyExample01

*/


#include <Engabra>  // top-level include provides full basic functionality

namespace
{
	//! Illustrate construction and display of fundamental types
	void
	showFundamentalTypes
		()
	{
		using namespace engabra; // saves typing locally

		// Scalar type generally interacts nicely with doubles
		double const dub{ 100.1 };  // all components are of this type
		g3::Scalar const sca{ dub };  // basically wrapper around double type

		// Vector is the enabling new type that extends the scalar algebra
		g3::Vector const vec{ 100.1, 100.2, 100.3 }; // classic 3D vector

		// High grade multivectors associated with extensions of vectors
		g3::BiVector const biv{ 200.1, 200.2, 200.3 }; // directed plane element
		g3::TriVector const tri{ 300.1 }; // directed volume element

		// show types - using op<<() overloading
		std::cout << "\nBasic Types\n";
		std::cout << "dub: " << dub << std::endl;
		std::cout << "sca: " << sca << std::endl;
		std::cout << "vec: " << vec << std::endl;
		std::cout << "biv: " << biv << std::endl;
		std::cout << "tri: " << tri << std::endl;
	}

	//! Illustrate construction and display of composite data types
	void
	showCompositeTypes
		()
	{
		using namespace engabra;

		// use two vectors to generate various composite relationships
		g3::Vector const vecA{ 2., 3., 5. };
		g3::Vector const vecB{ 11., 13., 17. };

		// A classic (albeit non-unitary) spinor
		// (with scalar and bivector grades)
		g3::Spinor const spinAB{ vecA * vecB};

		// An "imaginary spinor" dual to classic spinorA
		// (with vector and trivector grades)
		g3::ImSpin const imspAB{ g3::dual(spinAB) };

		// A complete (3D multivector) - with all four grades
		// To avoid working with a combinatorial explosion of addition and
		// multiplication operations, for unusual combinations of elements
		// such as:
		// g3::MultiVector const multiOrig{ spinAB + imspAB };
		//
		// You can cast the component elements to multivectors and perform
		// general operations with full multivector operations. This involves
		// dragging along a few unnecessary operations with zero-valued
		// components. However, this is needed only for unusual combinations
		// and the small cost here is offset be keeping the library
		// implementation and compile times shorter. For "common unusual"
		// situations, the library can be extended by adding appropriate
		// op+() and op*() methods where needed.
		//
		g3::MultiVector const multiOrig
			{ g3::MultiVector(spinAB) + g3::MultiVector(imspAB) };

		// Access grades within a full multivector by member entities.
		// All composites have two or more of members named
		// as ".the{Sca,Vev,Biv,Tri}" members
		g3::MultiVector const multiCopy
			{  multiOrig.theSca  // .theSca is a g3::Scalar
			,  multiOrig.theVec  // .theVec is a g3::Vector
			,  multiOrig.theBiv  // .theBiv is a g3::BiVector
			,  multiOrig.theTri  // .theTri is a g3::TriVector
			};

		// display contents via operator<<() overloading
		// The op<<() are defined in top level anonymous namespaces
		std::cout << "\nComposite Types\n";
		std::cout << "spinAB: " << spinAB << std::endl;
		std::cout << "imspAB: " << imspAB << std::endl;
		std::cout << "multiOrig: " << multiOrig << std::endl;
		std::cout << "multiCopy: " << multiCopy << std::endl;
	}

}

int
main
	()
{
	showFundamentalTypes();
	showCompositeTypes();
}

