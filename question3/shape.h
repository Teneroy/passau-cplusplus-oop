//
// Created by studone on 11/27/21.
//

#ifndef PASSAU_CPLUSPLUS_OOP_SHAPE_H
#define PASSAU_CPLUSPLUS_OOP_SHAPE_H

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() = 0;
};

#endif //PASSAU_CPLUSPLUS_OOP_SHAPE_H
