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

string BuildAST::nextStep(list<string> &tokens)
{
    string currentChar;
    tokens.pop_front();

    if (!tokens.empty()) {
        currentChar = tokens.front();
    } else {
        currentChar = std::string();
    }

    return currentChar;
}

ASTNode * BuildAST::expression(string &currentChar, list<string> &tokens)
{
    ASTNode * result = term(currentChar, tokens);
    while (currentChar == "+" || currentChar == "-") {
        if (currentChar == "+") {
            currentChar = nextStep(tokens);
            result = linkNodes(term(currentChar, tokens), result, new Operator('+'));
        }
        if (currentChar == "-") {
            currentChar = nextStep(tokens);
            result = linkNodes(term(currentChar, tokens), result, new Operator('-'));
        }
    }
    return result;
}

ASTNode * BuildAST::term(string &currentChar, list<string> &tokens)
{
    ASTNode * result = factor(currentChar, tokens);
    while (currentChar == "*" || currentChar == "/") {
        if (currentChar == "*") {
            currentChar = nextStep(tokens);
            result = linkNodes(factor(currentChar, tokens), result, new Operator('*'));
        }
        if (currentChar == "/") {
            currentChar = nextStep(tokens);
            result = linkNodes(factor(currentChar, tokens), result, new Operator('/'));
        }
    }
    return result;
}

ASTNode * BuildAST::factor(string &currentChar, list<string> &tokens)
{
    ASTNode * result;

    if (currentChar == "(") {
        currentChar = nextStep(tokens);
        result = expression(currentChar, tokens);
        currentChar = nextStep(tokens);
    } else {
        result = new Data(stoi(currentChar));
        currentChar = nextStep(tokens);
    }

    return result;
}

ASTNode *BuildAST::linkNodes(ASTNode * factor, ASTNode * node, ASTNode * action) {
    ASTNode * rightNode = new BlankNode(
            node,
            new BlankNode(factor, new Nil)
            );

    return new BlankNode(action, rightNode);
}
