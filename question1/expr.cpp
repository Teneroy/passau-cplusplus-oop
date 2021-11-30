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
            //result += _term();
            //... if (d_cast<summ>) { new BN }
            ASTNode * summator = _term();
            //if(dynamic_cast<Data*>(summator) != nullptr) { <--------------------
                summator = new BlankNode(summator, new Nil);
            //}                                              <--------------------
//            if(dynamic_cast<Data*>(result) != nullptr) {
//                result = new BlankNode(result, result);
//            }
            result = new BlankNode(result, summator);
            result = new BlankNode(new Operator('+'), result);
        }
        if (mCurrent == "-") {
            _next();
            //result -= _term();
            ASTNode * substractor = _term();
            //if(dynamic_cast<Data*>(substractor) != nullptr) { <--------------------
                substractor = new BlankNode(substractor, new Nil);
            //}                                                 <--------------------
//            if(dynamic_cast<Data*>(result) != nullptr) {
//                result = new BlankNode(result, result);
//            }
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
            //result *= _factor();
            ASTNode * multiplier = _factor();
   //         if(dynamic_cast<Data*>(multiplier) != nullptr) { <--------------------
                multiplier = new BlankNode(multiplier, new Nil);
     //       }                                                 <--------------------
//            if(dynamic_cast<Data*>(result) != nullptr) {
//                result = new BlankNode(result, multiplier);
//            }
            result = new BlankNode(result, multiplier);
            result = new BlankNode(new Operator('*'), result);
//            ASTNode * node = rootNode;
//            ASTNode * mult = new Operator('*');
//            rootNode = new BlankNode(mult, node);
        }
        if (mCurrent == "/") {
            _next();
            //
            // Could simply be:
            // result /= term();
            //
            // But we need to deal with divide by 0
            //
            ASTNode * denominator = _factor();
//            if (denominator != 0) {
//                result /= denominator;
//            } else {
//                result = 0;
//            }
            //if(dynamic_cast<Data*>(denominator) != nullptr) {     <--------------------
                denominator = new BlankNode(denominator, new Nil);
            //}                                                     <--------------------
//            if(dynamic_cast<Data*>(result) != nullptr) {
//                result = new BlankNode(result, denominator);
//            }
            result = new BlankNode(result, denominator);
            result = new BlankNode(new Operator('/'), result);
        }
    }
    return result;
}

ASTNode *
Calculator::_factor()
{
    ASTNode * result = nullptr;

    if (mCurrent == "(") {
        _next();
        result = _exp();
        //result = new BlankNode(result, new Nil);
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