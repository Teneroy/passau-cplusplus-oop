//
// Created by studone on 11/27/21.
//

#include "expr.h"
#include <cctype>
#include <algorithm>

BlankNode::BlankNode(ASTNode *nodeLeft, ASTNode *nodeRight) {
    left = nodeLeft;
    right = nodeRight;
}

string BlankNode::str() {
    std::string result;
    result.append(left -> str());
    result.append(right -> str());
    return result;
}

int BlankNode::evaluate() {
    if(right -> getNodeType() == NIL) {
        return left -> evaluate();
    }
    auto * node = dynamic_cast<BlankNode*>(right);
    if(node == nullptr) {
        throw invalid_argument("Your ASTNode tree is not properly structured. It is recommended to use static method build in BuildAST");
    }
    switch (left -> getNodeType()) {
        case MULTIPLY:
            return node -> left -> evaluate() * node -> right -> evaluate();
        case DIVIDE:
            return node -> left -> evaluate() / node -> right -> evaluate();
        case PLUS:
            return node -> left -> evaluate() + node -> right -> evaluate();
        case MINUS:
            return node -> left -> evaluate() - node -> right -> evaluate();
    }
    throw invalid_argument("Your ASTNode tree is not properly structured. It is recommended to use static method build in BuildAST");
}

NodeType BlankNode::getNodeType() {
    return EMPTY;
}

Data::Data(int num) {
    number = num;
}

string Data::str() {
    std::string result;
    result.append(" ");
    result.append(to_string(number));
    return result;
}

int Data::evaluate() {
    return number;
}

NodeType Data::getNodeType() {
    return DATA;
}

std::string Nil::str() {
    return ")";
}

int Nil::evaluate() {
    return 0;
}

NodeType Nil::getNodeType() {
    return NIL;
}

string Minus::str() {
    return " (-";
}

int Minus::evaluate() {
    return 0;
}

NodeType Minus::getNodeType() {
    return MINUS;
}

string Divide::str() {
    return " (/";
}

int Divide::evaluate() {
    return 0;
}

NodeType Divide::getNodeType() {
    return DIVIDE;
}

string Plus::str() {
    return " (+";
}

int Plus::evaluate() {
    return 0;
}

NodeType Plus::getNodeType() {
    return PLUS;
}

string Multiply::str() {
    return " (*";
}

int Multiply::evaluate() {
    return 0;
}

NodeType Multiply::getNodeType() {
    return MULTIPLY;
}

ASTNode * BuildAST::build(const string& expr) {
    std::string s = expr;
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    std::list<std::string> tokens;
    tokenize(s, tokens);
    return expression(tokens.front(), tokens);
}

void BuildAST::tokenize(const string& str, list<string>& tokens)
{
    std::string num;
    for (char c : str) {
        if (isdigit(c)) {
            num.append(1, c);
            continue;
        }
        if (!num.empty()) {
            tokens.push_back(num);
            num.clear();
        }
        std::string token;
        token.append(1, c);
        tokens.push_back(token);
    }

    if (!num.empty()) {
        tokens.push_back(num);
        num.clear();
    }
}

string BuildAST::nextStep(list<string> &tokens)
{
    string currentToken;
    tokens.pop_front();
    if (!tokens.empty()) {
        currentToken = tokens.front();
    }
    return currentToken;
}

ASTNode * BuildAST::expression(string &currentToken, list<string> &tokens)
{
    ASTNode * result = term(currentToken, tokens);
    while (currentToken == "+" || currentToken == "-") {
        if (currentToken == "+") {
            currentToken = nextStep(tokens);
            result = linkNodes(term(currentToken, tokens), result, new Plus);
        }
        if (currentToken == "-") {
            currentToken = nextStep(tokens);
            result = linkNodes(term(currentToken, tokens), result, new Minus);
        }
    }
    return result;
}

ASTNode * BuildAST::term(string &currentToken, list<string> &tokens)
{
    ASTNode * result = factor(currentToken, tokens);
    while (currentToken == "*" || currentToken == "/") {
        if (currentToken == "*") {
            currentToken = nextStep(tokens);
            result = linkNodes(factor(currentToken, tokens), result, new Multiply);
        }
        if (currentToken == "/") {
            currentToken = nextStep(tokens);
            result = linkNodes(factor(currentToken, tokens), result, new Divide);
        }
    }
    return result;
}

ASTNode * BuildAST::factor(string &currentToken, list<string> &tokens)
{
    ASTNode * result;

    if (currentToken == "(") {
        currentToken = nextStep(tokens);
        result = expression(currentToken, tokens);
        currentToken = nextStep(tokens);
        return result;
    }
    result = new Data(stoi(currentToken));
    currentToken = nextStep(tokens);

    return result;
}

ASTNode *BuildAST::linkNodes(ASTNode * factor, ASTNode * node, ASTNode * action) {
    ASTNode * rightNode = new BlankNode(
            node,
            new BlankNode(factor, new Nil)
            );

    return new BlankNode(action, rightNode);
}