//
// Created by studone on 11/27/21.
//

#ifndef PASSAU_CPLUSPLUS_OOP_EXPR_H
#define PASSAU_CPLUSPLUS_OOP_EXPR_H
#include <string>
#include <iostream>
#include <list>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

namespace ast {

    enum NodeType {PLUS, MINUS, MULTIPLY, DIVIDE, DATA, NIL, EMPTY};

    class ASTNode {
    public:
        virtual ~ASTNode() = default;
        virtual string str() = 0;
        virtual int evaluate() = 0;
        virtual NodeType getNodeType() = 0;
    };

    class Multiply : public ASTNode {
    public:
        string str() override;
        int evaluate() override;
        NodeType getNodeType() override;
    };

    class Plus : public ASTNode {
    public:
        string str() override;
        int evaluate() override;
        NodeType getNodeType() override;
    };

    class Divide : public ASTNode {
    public:
        string str() override;
        int evaluate() override;
        NodeType getNodeType() override;
    };

    class Minus : public ASTNode {
    public:
        string str() override;
        int evaluate() override;
        NodeType getNodeType() override;
    };

    class Data : public ASTNode {
    public:
        explicit Data(int num);
        string str() override;
        int evaluate() override;
        NodeType getNodeType() override;

    private:
        int number;
    };

    class Nil : public ASTNode {
    public:
        string str() override;
        int evaluate() override;
        NodeType getNodeType() override;
    };

    class BlankNode : public ASTNode {
    public:
        BlankNode(ASTNode *nodeLeft, ASTNode *nodeRight);
        string str() override;
        int evaluate() override;
        NodeType getNodeType() override;
        ~BlankNode() override;

    protected:
        ASTNode *left;
        ASTNode *right;
    };

    class BuildAST {
    public:
        static ASTNode * build(string expr);

    private:
        static void tokenize(const string& str, list<string>& tokens);
        static string nextStep(list<string>& tokens);
        static ASTNode * expression(string &currentToken, list<string> &tokens);
        static ASTNode * term(string &currentToken, list<string> &tokens);
        static ASTNode * div(string &currentToken, list<string> &tokens);
        static ASTNode * factor(string &currentToken, list<string> &tokens);
        static ASTNode * linkNodes(ASTNode * factor, ASTNode * node, ASTNode * action);
    };

}

#endif //PASSAU_CPLUSPLUS_OOP_EXPR_H
