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

std::string removeSpaces(const std::string& str)
{
    std::string s(str);
    int j = 0;
    int N = s.size();

    for (int i = 0; i < N; ++i) {
        if (s[i] != ' ') {
            s[j] = s[i];
            j++;
        }
    }

    s.resize(j);
    return s;
}

//
// output is a list of strings which map to tokens
//
void tokenize(const std::string& str, std::list<std::string>& tokens)
{
    std::string num;
    int N = str.size();

    for (int i = 0; i < N; ++i) {
        char c = str[i];
        if (isdigit(c)) {
            num += c;
        } else {
            if (!num.empty()) {
                tokens.push_back(num);
                num.clear();
            }
            std::string token;
            token += c;
            tokens.push_back(token);
        }
    }

    if (!num.empty()) {
        tokens.push_back(num);
        num.clear();
    }
}

int calculate(std::string s)
{
    Calculator calculator(s);
    return calculator.exp();
}

ASTNode * _calculate(std::string s)
{
    Calculator calculator(s);
    return calculator._exp();
}


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

    cout << BuildAST::build("23*20400*30*20*20")->str() << endl;
    //BuildAST::build("23*(300+4)+5*(2+(32*3))");
    //BuildAST::build("3*2+4*2+3");

    std::string expression;

    // "3+2*2" = 7
    // " 3/2 " = 1
    // " 3+5 / 2 " = 5

    // my code evalute this to 2, while it's expected to be 7
    //expression = "(1 + 22 + 2*(21 + 34)) * 3";
    //expression = "(1 + 22) * 3";
    //expression = "3*1+2*(3+7)";
    expression = "20*(7-1)/20";
    //expression = "9-7-1";
    //expression = "9-7-1";
    std::cout << expression << " -> "
              << calculate(expression) << std::endl;


    ASTNode * node = _calculate(expression);
    cout << expression << endl;
    cout << node -> str() << endl;
//    std::string s = removeSpaces(expression);
//    std::list<std::string> mTokens;
//    tokenize(s, mTokens);
//    cout << "" << endl;

    return 0;
}
