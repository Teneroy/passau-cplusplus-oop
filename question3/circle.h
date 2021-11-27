//
// Created by studone on 11/27/21.
//

#ifndef PASSAU_CPLUSPLUS_OOP_CIRCLE_H
#define PASSAU_CPLUSPLUS_OOP_CIRCLE_H

#include <cmath>
#include "shape.h"
#include "circumference.h"

class Circle : Shape, Circumference {
public:
    explicit Circle(double);
    double area() override;
    double circumference() override;
    double getRadius() const;
protected:
    double radius;
};


#endif //PASSAU_CPLUSPLUS_OOP_CIRCLE_H
