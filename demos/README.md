
# The /demo directory contains various demonstrations and examples

Example solving real world problems with Engabra code constructs.

## General Organization

Demonstration Source Code

- DemoXYZ.cpp : contains source code

Demonstration Descriptions (using [Lyx](www.lyx.org) with document
class "Paper (Standard Class)").

- DemoXYZ.lyx : describes configuration algorithm and mathematics

- DemoXYZ_nn.tex : figures for DemoXYZ.lyx



## Demonstrations

### Rigid Body Attitude - Simple Example

This example illustrates the use of Engabra to represent the attitude
(aka pose, orientation) of a rigid body and to transform the expression
of vector locations between the body coordinate frame and reference
coordinate frame.

- DemoRigidBodyAttitude.cpp


This example illustrates the use of Engabra to represent the angular attitude
(aka pose, orientation) of a rigid body. The attitude representation is
used to transform vector coordinate values between the body coordinate
frame and the external reference frame.


The body of interest is a flat rectangular block. Although, the body
size and shape are irrelevant for this demo. To aid in interpretation of
figures and data the body is drawn with proportions that similar to a
smart phone.

Body is assumed to be at an attitude specified by angle "A". (Note that
this is a bivector with three numeric components and therefore completely
specifies the complete attitude of the body in 3D space - the three bivector
components provide values for the 3 dof of physical attitude).

In the demo program, several vectors are defined in the reference coordinate
frame. The expressions of these vectors are transformed into expressions
in the body frame (such as would be observed by on-board strap-down sensors).

To illustrate the reference transformation, vectors representing the edges
of the body are transformed into expressions in the reference frame.

The transformed vectors are used to compute the height of each corner of
the body relative to it's starting reference plane.



## TODO Demonstration Ideas

### Attitude Determination - From Two Reference Directions (Gravity and Mag)


This example computes the attitude of a rigid body (wrt a reference frame)
by using a pair of vector directions that are observed in the body frame
and are known in the reference frame.

The two reference directions used are those of resistance to gravity
(e.g. 'up') and local ambient magnetic field (e.g. about 40-deg above
horizontal for these example data).

Reference frame directions are observed with body in reference position.
These same quantities are observed again with the body at a attitude of
interest.

Dir.1: Acceleration resisting gravity (i.e. upward acceleration)

Dir.2: Magnetic field vector (i.e. local Earth magnetic field direction near
40-deg N latitude)


TODO - Use as example of "aligner" object/functor?



### Non-Commutative Rotation Illustration

Rotation operations are non-commutative. This means that two rotations
performed in succession will produce different results depending on the
order in which the rotations are performed.

- DemoRotationOrder.cpp

This demo ... TODO



