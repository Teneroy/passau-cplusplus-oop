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
    BlankNode(ASTNode *nodeLeft, ASTNode *nodeRight);
    std::string str() override;
    int evaluate() override;

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
    explicit Data(int num);
    std::string str() override;
    int evaluate() override;

private:
    int number;
};

class Nil : public ASTNode {
public:
    std::string str() override;
    int evaluate() override;
};


class BuildAST {
public:
    static ASTNode * build(const std::string& expr);

private:
    static void tokenize(const std::string& str, std::list<std::string>& tokens);
    static string nextStep(std::list<std::string>& tokens);
    static ASTNode * expression(string &currentToken, list<string> &tokens);
    static ASTNode * term(string &currentToken, list<string> &tokens);
    static ASTNode * factor(string &currentToken, list<string> &tokens);
    static ASTNode * linkNodes(ASTNode * factor, ASTNode * node, ASTNode * action);
};

#endif //PASSAU_CPLUSPLUS_OOP_EXPR_H
