//
// Created by studone on 11/20/21.
//

#include <iostream>
#include "./question1/expr.h"
using namespace std;

int main() {
    string expression;
    // my code evalute this to 2, while it's expected to be 7
    //expression = "(1 + 22 + 2*(21 + 34)) * 3";
    expression = "(1 + 22) * 3";
    //expression = "3*1+2*(3+7)";
    //expression = "20*(7-1)/20";
    //expression = "9-7-1";
    //expression = "9-7-1";
    std::cout << expression << std::endl;
    ASTNode * node = BuildAST::build(expression);
    cout << expression << endl;
    cout << node -> str() << endl;

    return 0;
}
