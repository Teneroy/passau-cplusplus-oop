//
// Created by studone on 11/27/21.
//

#include "expr.h"

Calculator::Calculator(const std::string& expression)
{
    std::string s = removeSpaces(expression);
    // std::cout << s << std::endl;

    tokenize(s, mTokens);

    // std::list<std::string>::iterator it, itEnd;
    // for (it = mTokens.begin(); it != mTokens.end(); ++it) {
    //     std::cout << *it << " ";
    // }
    // std::cout << std::endl;

    mCurrent = mTokens.front();
}

void
Calculator::next()
{
    mTokens.pop_front();

    if (!mTokens.empty()) {
        mCurrent = mTokens.front();
    } else {
        mCurrent = std::string();
    }
}

int
Calculator::exp()
{
    int result = term();
    while (mCurrent == "+" || mCurrent == "-") {
        if (mCurrent == "+") {
            next();
            result += term();
        }
        if (mCurrent == "-") {
            next();
            result -= term();
        }
    }
    return result;
}

int
Calculator::term()
{
    int result = factor();
    while (mCurrent == "*" || mCurrent == "/") {
        if (mCurrent == "*") {
            next();
            result *= factor();
//            ASTNode * node = rootNode;
//            ASTNode * mult = new Operator('*');
//            rootNode = new BlankNode(mult, node);
        }
        if (mCurrent == "/") {
            next();
            //
            // Could simply be:
            // result /= term();
            //
            // But we need to deal with divide by 0
            //
            int denominator = factor();
            if (denominator != 0) {
                result /= denominator;
            } else {
                result = 0;
            }
        }
    }
    return result;
}

int
Calculator::factor()
{
    int result;

    if (mCurrent == "(") {
        next();
        result = exp();
        next();
    } else {
        result = toInt(mCurrent);
        next();
    }

    return result;
}

int
Calculator::toInt(const std::string& s)
{
    std::stringstream ss;
    ss << s;
    int x;
    ss >> x;
    return x;
}


//__________________________


void
Calculator::_next()
{
    mTokens.pop_front();

    if (!mTokens.empty()) {
        mCurrent = mTokens.front();
    } else {
        mCurrent = std::string();
    }
}

ASTNode *
Calculator::_exp()
{
    ASTNode * result = _term();
    while (mCurrent == "+" || mCurrent == "-") {
        if (mCurrent == "+") {
            _next();
            ASTNode * summator = _term();
            summator = new BlankNode(summator, new Nil);
            result = new BlankNode(result, summator);
            result = new BlankNode(new Operator('+'), result);
        }
        if (mCurrent == "-") {
            _next();
            ASTNode * substractor = _term();
            substractor = new BlankNode(substractor, new Nil);
            result = new BlankNode(result, substractor);
            result = new BlankNode(new Operator('-'), result);
        }
    }
    return result;
}

ASTNode *
Calculator::_term()
{
    ASTNode * result = _factor();
    while (mCurrent == "*" || mCurrent == "/") {
        if (mCurrent == "*") {
            _next();
            ASTNode * multiplier = _factor();
            multiplier = new BlankNode(multiplier, new Nil);
            result = new BlankNode(result, multiplier);
            result = new BlankNode(new Operator('*'), result);
        }
        if (mCurrent == "/") {
            _next();
            ASTNode * denominator = _factor();
            denominator = new BlankNode(denominator, new Nil);
            result = new BlankNode(result, denominator);
            result = new BlankNode(new Operator('/'), result);
        }
    }
    return result;
}

ASTNode *
Calculator::_factor()
{
    ASTNode * result;

    if (mCurrent == "(") {
        _next();
        result = _exp();
        _next();
    } else {
        result = new Data(_toInt(mCurrent));
        _next();
    }

    return result;
}

int
Calculator::_toInt(const std::string& s)
{
    std::stringstream ss;
    ss << s;
    int x;
    ss >> x;
    return x;
}