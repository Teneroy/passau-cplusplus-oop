//
// Created by studone on 11/27/21.
//

#ifndef PASSAU_CPLUSPLUS_OOP_POLYGON_H
#define PASSAU_CPLUSPLUS_OOP_POLYGON_H


class Polygon {
public:
    virtual ~Polygon() = default;
    virtual int num_sides() = 0;
};


#endif //PASSAU_CPLUSPLUS_OOP_POLYGON_H
