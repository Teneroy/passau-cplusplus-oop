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
    return _exp(mTokens.front(), mTokens);
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

string BuildAST::_next(list<string> &_mTokens)
{
    string _mCurrent;
    _mTokens.pop_front();

    if (!_mTokens.empty()) {
        _mCurrent = _mTokens.front();
    } else {
        _mCurrent = std::string();
    }

    return _mCurrent;
}

ASTNode * BuildAST::_exp(string &_mCurrent, list<string> &_mTokens)
{
    ASTNode * result = _term(_mCurrent, _mTokens);
    while (_mCurrent == "+" || _mCurrent == "-") {
        if (_mCurrent == "+") {
            _mCurrent = _next(_mTokens);
            ASTNode * summator = _term(_mCurrent, _mTokens);
            summator = new BlankNode(summator, new Nil);
            result = new BlankNode(result, summator);
            result = new BlankNode(new Operator('+'), result);
        }
        if (_mCurrent == "-") {
            _mCurrent = _next(_mTokens);
            ASTNode * substractor = _term(_mCurrent, _mTokens);
            substractor = new BlankNode(substractor, new Nil);
            result = new BlankNode(result, substractor);
            result = new BlankNode(new Operator('-'), result);
        }
    }
    return result;
}

ASTNode * BuildAST::_term(string &_mCurrent, list<string> &_mTokens)
{
    ASTNode * result = _factor(_mCurrent, _mTokens);
    while (_mCurrent == "*" || _mCurrent == "/") {
        if (_mCurrent == "*") {
            _mCurrent = _next(_mTokens);
            ASTNode * multiplier = _factor(_mCurrent, _mTokens);
            multiplier = new BlankNode(multiplier, new Nil);
            result = new BlankNode(result, multiplier);
            result = new BlankNode(new Operator('*'), result);
        }
        if (_mCurrent == "/") {
            _mCurrent = _next(_mTokens);
            ASTNode * denominator = _factor(_mCurrent, _mTokens);
            denominator = new BlankNode(denominator, new Nil);
            result = new BlankNode(result, denominator);
            result = new BlankNode(new Operator('/'), result);
        }
    }
    return result;
}

ASTNode * BuildAST::_factor(string &_mCurrent, list<string> &_mTokens)
{
    ASTNode * result;

    if (_mCurrent == "(") {
        _mCurrent = _next(_mTokens);
        result = _exp(_mCurrent, _mTokens);
        _mCurrent = _next(_mTokens);
    } else {
        result = new Data(stoi(_mCurrent));
        _mCurrent = _next(_mTokens);
    }

    return result;
}