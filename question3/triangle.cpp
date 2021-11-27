//
// Created by studone on 11/27/21.
//

#include "triangle.h"

Triangle::Triangle(double a, double b, double c) : sideA{a}, sideB{b}, sideC{c} {}

double Triangle::area() {
    double semiPerimeter = (sideA + sideB + sideC) / 2;
    return sqrt(semiPerimeter * (semiPerimeter - sideA) * (semiPerimeter - sideB) * (semiPerimeter - sideC));
}

int Triangle::num_sides() {
    return 3;
}

double Triangle::getSideA() const {
    return sideA;
}

double Triangle::getSideB() const {
    return sideB;
}

double Triangle::getSideC() const {
    return sideC;
}
