//
// Created by studone on 11/20/21.
//

#include <iostream>
#include <vector>
#include "./question1/expr.h"
using namespace std;

int main() {
    //string input = "1 - 2 - 3";
    //string input = "1+2-3";
  //  string input = "1-2+3-1";
    //string input = "1/4/3";
    //string input = "1/2*3-4";
    //string input = "1/2*3-4";
 //   cout << "Input: " << input << endl;
    //getline(cin, input);
//    ast::ASTNode * node = ast::BuildAST::build(input);
//    cout << "S-expression: " << node -> str() << endl;
//    cout << "Output: " << node -> evaluate() << endl;
//    delete node;

    std::vector<string> question = {
            "1+2+3",
            "1-2-3",
            "1*2*3",
            "1/4/3",
            "1+2-3",
            "1-2+3",
            "1/2*3-4",
            "1-2*3/4",
            "(1*(2-3)/5)*3-(3+42)-3-3",
            "1337",
            "115*(0-1)"
    };
    std::vector<string> answer = {
            "(+ (+ 1 2) 3)",
            "(- 1 (- 2 3))",
            "(* (* 1 2) 3)",
            "(/ 1 (/ 4 3))",
            "(- (+ 1 2) 3)",
            "(- 1 (+ 2 3))",
            "(- (* (/ 1 2) 3) 4)",
            "(- 1 (* 2 (/ 3 4)))",
            "(- (* (* 1 (/ (- 2 3) 5)) 3) (- (+ 3 42) (- 3 3)))",
            "1337",
            "(* 115 (- 0 1))"
    };

    int i = 0;
    for (const string& exp : question) {
        cout << "Input: " << exp << endl;
        ast::ASTNode * node = ast::BuildAST::build(exp);
        cout << "S-expression: " << node -> str() << endl;
        cout << "Expected expression: " << answer.at(i) << endl;
        cout << "Output: " << node -> evaluate() << endl;
        delete node;
        i++;
    }

    return 0;
}
