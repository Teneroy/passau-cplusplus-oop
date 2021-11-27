//
// Created by studone on 11/27/21.
//

#ifndef PASSAU_CPLUSPLUS_OOP_TRIANGLE_H
#define PASSAU_CPLUSPLUS_OOP_TRIANGLE_H

#include <cmath>
#include "shape.h"
#include "polygon.h"

class Triangle : Shape, Polygon {
public:
    Triangle(double, double, double);
    double area() override;
    int num_sides() override;
    double getSideA() const;
    double getSideB() const;
    double getSideC() const;
protected:
    double sideA, sideB, sideC;
};


#endif //PASSAU_CPLUSPLUS_OOP_TRIANGLE_H
