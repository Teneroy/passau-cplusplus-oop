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
    return 0;
}

Data::Data(int num) {
    number = num;
}

string Data::str() {
    std::string result;
    result.append(" ");
    result.append(std::to_string(number));
    return result;
}

int Data::evaluate() {
    return 0;
}

std::string Nil::str() {
    return ")";
}

int Nil::evaluate() {
    return 0;
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
            result = linkNodes(term(currentToken, tokens), result, new Operator('+'));
        }
        if (currentToken == "-") {
            currentToken = nextStep(tokens);
            result = linkNodes(term(currentToken, tokens), result, new Operator('-'));
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
            result = linkNodes(factor(currentToken, tokens), result, new Operator('*'));
        }
        if (currentToken == "/") {
            currentToken = nextStep(tokens);
            result = linkNodes(factor(currentToken, tokens), result, new Operator('/'));
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
