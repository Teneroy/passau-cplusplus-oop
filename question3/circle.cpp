//
// Created by studone on 11/27/21.
//

#include "circle.h"

Circle::Circle(double r) : radius{r} {}

double Circle::area() {
    return M_PI * radius * radius;
}

double Circle::circumference() {
    return 2 * M_PI * radius;
}

double Circle::getRadius() const {
    return radius;
}
