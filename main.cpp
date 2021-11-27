//
// Created by studone on 11/20/21.
//

#include <iostream>
#include "./question3/circle.h"
#include "./question3/ellipse.h"
#include "./question3/square.h"
#include "./question3/triangle.h"

using namespace std;

//void rotate(int &a, int &b, int &c) {
//    int temp = a;
//    a = b;
//    b = c;
//    c = temp;
//}

int main() {
//    int a = 5, b = 7, c = 9;
//
//    cout << "Before rotation: a=" << a << ", b=" << b << ", c=" << c << endl;
//    rotate(a, b, c);
//    cout << "After rotation: a=" << a << ", b=" << b << ", c=" << c << endl;

    Circle circle(5);
    cout << "The area of a circle with the radius of " << circle.getRadius() << " is " << circle.area() << endl;
    cout << "The circumference of a circle with radius of " << circle.getRadius() << " is " << circle.circumference() << endl;

    Ellipse ellipse(2, 5);
    cout << "The area of an ellipse with semi-major of " << ellipse.getSemiMajor()
         << " and semi-minor of " << ellipse.getSemiMinor() << " is " << ellipse.area() << endl;

    Square square(5);
    cout << "The area of a square with side length of " << square.getSideLength() << " is " << square.area() << endl;
    cout << "The number of sides of a square is " << square.num_sides() << endl;

    Triangle triangle(2, 3, 4);
    cout << "The area of a triangle with sides of " << triangle.getSideA() << ", " << triangle.getSideB() << ", "
         << triangle.getSideC() << " is " << triangle.area() << endl;
    cout << "The number of sides of a triangle is " << triangle.num_sides() << endl;

    return 0;
}
