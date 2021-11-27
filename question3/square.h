//
// Created by studone on 11/27/21.
//

#ifndef PASSAU_CPLUSPLUS_OOP_SQUARE_H
#define PASSAU_CPLUSPLUS_OOP_SQUARE_H

#include "shape.h"
#include "polygon.h"

class Square : Shape, Polygon {
public:
    explicit Square(double);
    double area() override;
    int num_sides() override;
    double getSideLength() const;
protected:
    double sideLength;
};


#endif //PASSAU_CPLUSPLUS_OOP_SQUARE_H
