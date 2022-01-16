//
// Created by studone on 12/21/21.
//

#ifndef PASSAU_CPLUSPLUS_OOP_SAFEINT_H
#define PASSAU_CPLUSPLUS_OOP_SAFEINT_H


#include <stdexcept>
#include <limits>

class SafeInt {
private:
    int value;
public:
    SafeInt(int value) : value(value) {};
    SafeInt(const SafeInt& obj);
    friend std::ostream& operator << (std::ostream& os, const SafeInt& val);
    friend SafeInt operator + (const SafeInt& val1, const SafeInt& val2);
    friend SafeInt operator - (const SafeInt& val1, const SafeInt& val2);
    friend SafeInt operator * (const SafeInt& val1, const SafeInt& val2);
    SafeInt& operator++();
    int operator()() const;
};


#endif //PASSAU_CPLUSPLUS_OOP_SAFEINT_H
