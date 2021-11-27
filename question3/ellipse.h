//
// Created by studone on 11/27/21.
//

#ifndef PASSAU_CPLUSPLUS_OOP_ELLIPSE_H
#define PASSAU_CPLUSPLUS_OOP_ELLIPSE_H

#include <cmath>
#include "shape.h"

class Ellipse : Shape {
public:
    Ellipse(double, double);
    double area() override;
    double getSemiMinor() const;
    double getSemiMajor() const;
protected:
    double semiMinor, semiMajor;
};


#endif //PASSAU_CPLUSPLUS_OOP_ELLIPSE_H
