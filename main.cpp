//
// Created by studone on 11/20/21.
//

#include <iostream>
#include "./question1/expr.h"
using namespace std;

//void rotate(int &a, int &b, int &c) {
//    int temp = a;
//    a = b;
//    b = c;
//    c = temp;
//}

int main() {
    Operator plus('+');
    Operator mult('*');
    Data three(3);
    Data two(2);
    Data four(4);
    Nil nil;

//    BlankNode blankNode5(four, nil);
//    BlankNode blankNode4(three, blankNode5);
//    BlankNode blankNode3(plus, blankNode4);
//    BlankNode blankNode2(blankNode3, nil);
//    BlankNode blankNode1(two, blankNode2);
//    BlankNode blankNode(mult, blankNode1);
//    cout << blankNode.str() << endl;


//    char string[80] = "5*2-3*2";
//    // Make expression
//    auto * eptr = new Express(string);
//    // Parse it
//    eptr->parse();
//    // Solve the expression
//    cout << eptr->solve() << endl;

    cout << BuildAST::build("23*400")->str() << endl;
    //BuildAST::build("23*(300+4)+5*(2+(32*3))");
    //BuildAST::build("3*2+4*2+3");

    return 0;
}