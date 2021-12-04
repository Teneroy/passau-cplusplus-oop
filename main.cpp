//
// Created by studone on 11/20/21.
//

#include <iostream>
#include "./question1/expr.h"
using namespace std;

int main() {
    string input;
    cout << "Input: ";
    getline(cin, input);
    ast::ASTNode * node = ast::BuildAST::build(input);
    cout << "S-expression: " << node -> str() << endl;
    cout << "Output: " << node -> evaluate() << endl;
    delete node;

    return 0;
}
