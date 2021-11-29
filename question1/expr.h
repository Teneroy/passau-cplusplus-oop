//
// Created by studone on 11/27/21.
//

#ifndef PASSAU_CPLUSPLUS_OOP_EXPR_H
#define PASSAU_CPLUSPLUS_OOP_EXPR_H
#include <string>
#include <iostream>

using namespace std;

class ASTNode {
public:
    virtual std::string str() = 0;
    virtual int evaluate() = 0;
};

class BlankNode : public ASTNode {
public:
    BlankNode(ASTNode *nodeLeft, ASTNode *nodeRight){
        left = nodeLeft;
        right = nodeRight;
    };
    std::string str() override {
        std::string result;
        result.append(left -> str());
        result.append(right -> str());
        return result;
    }
    int evaluate() override { return 0; }

protected:
    ASTNode *left;
    ASTNode *right;
};

class Operator : public ASTNode {
public:
    explicit Operator(char t) {
        type = t;
    };
    std::string str() override {
        std::string result = " (";
        result.append(type);
        return result;
    };
    int evaluate() override { return 0; }

private:
    std::basic_string<char> type;
};

class Data : public ASTNode {
public:
    explicit Data(int num) {
        number = num;
    };
    std::string str() override {
        std::string result;
        result.append(" ");
        result.append(std::to_string(number));
        return result;
    };
    int evaluate() override { return 0; }

private:
    int number;
};

class Nil : public ASTNode {
public:
    std::string str() override {
        return ")";
    };
    int evaluate() override {
        return 0.0;
    };
};

class BuildAST {
public:
    static ASTNode * build(std::string expr) {
//        cout << expr << endl;
//        cout << expr.find('*') << endl;
//        cout << expr.find('+') << endl;
//        cout << expr.find('(') << endl;
//        cout << expr.find(')') << endl;
//
//        int brPos = expr.find('(');
//
//
//        int start_exp = 0;
//        int stop_exp = 0;
//        int i = 0;
//        ASTNode * rootNode = nullptr;
//        ASTNode * leftExpression = nullptr;
//        ASTNode * rightExpression = nullptr;
//        ASTNode * curNode = nullptr;
//        string number;
//        for (char cur : expr) {
//            switch (cur) {
//                case '*':
//                    cout << "number: " << number << endl;
//                    number = "";
//                    if(leftExpression == nullptr) {
//                        leftExpression = new Data(stoi(number));
//                    }
//                    Operator * mult = new Operator('*');
//                    rootNode = new BlankNode(mult, new BlankNode(leftExpression, build()));
//                    break;
//                case '+':
//                    cout << "number: " << number << endl;
//                    number = "";
//                    break;
//            }
//
//            if (cur >= '0' && cur <= '9') {
//                number.append(1, cur);
//            }
//
//
//            i++;
//        }

        return evalGenerate(expr);
    }

private:
    static ASTNode * evalGenerate(string expr) {
        ASTNode * rootNode = nullptr;
        string number;
        for (int i = 0; i < expr.length(); i++) {
            if(expr.at(i) == '*') {
                ASTNode * mult = new Operator('*');
                ASTNode * data = new Data(stoi(number));
                ASTNode * rightNode = new BlankNode(data, evalGenerate(expr.substr(i + 1)));
                rootNode = new BlankNode(mult, rightNode);
                number = "";
                i = expr.length();
                continue;
            }

            if(expr.at(i) >= '0' && expr.at(i) <= '9') {
                number.append(1, expr.at(i));
            }
        }
        if(rootNode != nullptr) {
            return rootNode;
        }

        if(number.length() == 0) {
            return new Nil;
        }

        return new BlankNode(new Data(stoi(number)), new Nil);
    }
};


#endif //PASSAU_CPLUSPLUS_OOP_EXPR_H
