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

enum NodeType {PLUS, MINUS, MULTIPLY, DIVIDE, DATA, NIL, EMPTY};

class ASTNode {
public:
    virtual std::string str() = 0;
    virtual int evaluate() = 0;
    virtual NodeType getNodeType() = 0;
};

class Multiply : public ASTNode {
public:
    std::string str() override { return " (*"; };
    int evaluate() override { return 0; }
    NodeType getNodeType() override { return MULTIPLY; }
};

class Plus : public ASTNode {
public:
    std::string str() override { return " (+"; };
    int evaluate() override { return 0; }
    NodeType getNodeType() override { return PLUS; }
};

class Divide : public ASTNode {
public:
    std::string str() override { return " (/"; };
    int evaluate() override { return 0; }
    NodeType getNodeType() override { return DIVIDE; }
};

class Minus : public ASTNode {
public:
    std::string str() override { return " (-"; };
    int evaluate() override { return 0; }
    NodeType getNodeType() override { return MINUS; }
};

class Data : public ASTNode {
public:
    explicit Data(int num);
    std::string str() override;
    int evaluate() override;
    NodeType getNodeType() override { return DATA; }

private:
    int number;
};

class Nil : public ASTNode {
public:
    std::string str() override;
    int evaluate() override;
    NodeType getNodeType() override { return NIL; }
};

class BlankNode : public ASTNode {
public:
    BlankNode(ASTNode *nodeLeft, ASTNode *nodeRight);
    std::string str() override;
    int evaluate() override;
    NodeType getNodeType() override { return EMPTY; }

protected:
    ASTNode *left;
    ASTNode *right;
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
