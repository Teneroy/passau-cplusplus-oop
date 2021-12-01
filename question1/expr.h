//
// Created by studone on 11/27/21.
//

#ifndef PASSAU_CPLUSPLUS_OOP_EXPR_H
#define PASSAU_CPLUSPLUS_OOP_EXPR_H
#include <string>
#include <iostream>
#include <list>
#include <sstream>

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
    static ASTNode * build(const std::string& expr);

private:
    static void tokenize(const std::string& str, std::list<std::string>& tokens);
    static string _next(std::list<std::string>& _mTokens);
    static ASTNode * _exp(string &_mCurrent, list<string> &_mTokens);
    static ASTNode * _term(string &_mCurrent, list<string> &_mTokens);
    static ASTNode * _factor(string &_mCurrent, list<string> &_mTokens);
};

#endif //PASSAU_CPLUSPLUS_OOP_EXPR_H
