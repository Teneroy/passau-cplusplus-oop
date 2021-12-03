//
// Created by studone on 11/27/21.
//

#include "expr.h"
#include <cctype>
#include <algorithm>

ASTNode * BuildAST::build(const std::string& expr) {
    std::string s = expr;
    s.erase(std::remove_if(s.begin(), s.end(), ::isspace), s.end());
    std::list<std::string> mTokens;
    tokenize(s, mTokens);
    return expression(mTokens.front(), mTokens);
}

void BuildAST::tokenize(const std::string& str, std::list<std::string>& tokens)
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
