//
// Created by studone on 11/27/21.
//

#include "expr.h"

ast::BlankNode::BlankNode(ASTNode *nodeLeft, ASTNode *nodeRight) {
    left = nodeLeft;
    right = nodeRight;
}

string ast::BlankNode::str() {
    std::string result;
    result.append(left -> str());
    result.append(right -> str());
    return result;
}

int ast::BlankNode::evaluate() {
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

ast::NodeType ast::BlankNode::getNodeType() {
    return EMPTY;
}

ast::BlankNode::~BlankNode() {
    delete left;
    delete right;
}

ast::Data::Data(int num) {
    number = num;
}

string ast::Data::str() {
    std::string result;
    result.append(" ");
    result.append(to_string(number));
    return result;
}

int ast::Data::evaluate() {
    return number;
}

ast::NodeType ast::Data::getNodeType() {
    return DATA;
}

std::string ast::Nil::str() {
    return ")";
}

int ast::Nil::evaluate() {
    return 0;
}

ast::NodeType ast::Nil::getNodeType() {
    return NIL;
}

string ast::Minus::str() {
    return " (-";
}

int ast::Minus::evaluate() {
    return 0;
}

ast::NodeType ast::Minus::getNodeType() {
    return MINUS;
}

string ast::Divide::str() {
    return " (/";
}

int ast::Divide::evaluate() {
    return 0;
}

ast::NodeType ast::Divide::getNodeType() {
    return DIVIDE;
}

string ast::Plus::str() {
    return " (+";
}

int ast::Plus::evaluate() {
    return 0;
}

ast::NodeType ast::Plus::getNodeType() {
    return PLUS;
}

string ast::Multiply::str() {
    return " (*";
}

int ast::Multiply::evaluate() {
    return 0;
}

ast::NodeType ast::Multiply::getNodeType() {
    return MULTIPLY;
}

ast::ASTNode * ast::BuildAST::build(string expr) {
    expr.erase(std::remove_if(expr.begin(), expr.end(), ::isspace), expr.end());
    std::list<std::string> tokens;
    tokenize(expr, tokens);
    return expression(tokens.front(), tokens);
}

void ast::BuildAST::tokenize(const string& str, list<string>& tokens) {
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

string ast::BuildAST::nextStep(list<string> &tokens) {
    tokens.pop_front();
    if (!tokens.empty()) {
        return tokens.front();
    }
    return "";
}

ast::ASTNode * ast::BuildAST::expression(string &currentToken, list<string> &tokens) {
    ASTNode * result = term(currentToken, tokens);
    while (currentToken == "+" || currentToken == "-") {
        if (currentToken == "+") {
            currentToken = nextStep(tokens);
            result = linkNodes(term(currentToken, tokens), result, new Plus);
        }
        if (currentToken == "-") {
            currentToken = nextStep(tokens);
            result = linkNodes(expression(currentToken, tokens), result, new Minus);
        }
    }
    return result;
}

ast::ASTNode * ast::BuildAST::term(string &currentToken, list<string> &tokens) {
    ASTNode * result = div(currentToken, tokens);
    while (currentToken == "*") {
        currentToken = nextStep(tokens);
        result = linkNodes(div(currentToken, tokens), result, new Multiply);
    }
    return result;
}

ast::ASTNode * ast::BuildAST::div(string &currentToken, list<string> &tokens) {
    ASTNode * result = factor(currentToken, tokens);
    if (currentToken == "/") {
        currentToken = nextStep(tokens);
        result = linkNodes(div(currentToken, tokens), result, new Divide);
    }
    return result;
}

ast::ASTNode * ast::BuildAST::factor(string &currentToken, list<string> &tokens) {
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

ast::ASTNode * ast::BuildAST::linkNodes(ASTNode * factor, ASTNode * node, ASTNode * action) {
    ASTNode * rightNode = new BlankNode(
            node,
            new BlankNode(factor, new Nil)
            );

    return new BlankNode(action, rightNode);
}