//
// Created by studone on 11/20/21.
//

#include <iostream>
#include "./question1/expr.h"
using namespace std;

int main() {
    string input;
//    cout << "Input: ";
//    getline(cin, input);
    input = "2 + 3 * 20 + (2 - 1)";
    ASTNode * node = BuildAST::build(input);
    cout << "S-expression: " << node -> str() << endl;
    cout << "Output: " << node -> evaluate() << endl;
    delete node;

    return 0;
}
