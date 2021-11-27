//
// Created by studone on 11/27/21.
//

#include "ellipse.h"

Ellipse::Ellipse(double sMinor, double sMajor) : semiMinor{sMinor}, semiMajor{sMajor} {}

double Ellipse::area() {
    return M_PI * semiMajor * semiMinor;
}

double Ellipse::getSemiMinor() const {
    return semiMinor;
}

double Ellipse::getSemiMajor() const {
    return semiMajor;
}
