//
// Created by studone on 11/27/21.
//

#include "square.h"

Square::Square(double s) : sideLength{s} {}

double Square::area() {
    return sideLength * sideLength;
}

int Square::num_sides() {
    return 4;
}

double Square::getSideLength() const {
    return sideLength;
}

