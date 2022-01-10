//
// Created by studone on 12/21/21.
//

#include "safeint.h"
#include <iostream>

SafeInt::SafeInt(const SafeInt& obj) {
    this->value = obj.value;
}

std::ostream &operator<<(std::ostream &os, const SafeInt &val) {
    return os << val.value;
}

SafeInt operator+(const SafeInt &val1, const SafeInt &val2) {
    if (val1.value >= 0 && val2.value >= 0 && val1.value > std::numeric_limits<int>::max() - val2.value)
        throw std::overflow_error("Sum operation would cause integer overflow");

    if (val1.value < 0 && val2.value < 0  && val1.value < std::numeric_limits<int>::min() - val2.value)
        throw std::overflow_error("Sum operation would cause integer underflow");

    return {val1.value + val2.value};
}

SafeInt operator-(const SafeInt &val1, const SafeInt &val2) {
    if (val1.value < 0 && val2.value >= 0 && val1.value < std::numeric_limits<int>::min() + val2.value)
        throw std::overflow_error("Minus operation would cause integer underflow");

    return {val1.value - val2.value};
}

SafeInt operator*(const SafeInt &val1, const SafeInt &val2) {
    int result = val1.value * val2.value;
    if(val1.value != 0 && val2.value != 0 && val1.value != result / val2.value) {
        if(val1.value < 0 && val2.value < 0 || val1.value > 0 && val2.value > 0) {
            throw std::overflow_error("Multiplication operator would cause integer overflow");
        } else {
            throw std::overflow_error("Multiplication operator would cause integer underflow");
        }
    }
    return {val1.value * val2.value};
}

SafeInt &SafeInt::operator++() {
    if(value > 0 && (value + 1) < 0)
        throw std::overflow_error("Increment operation would cause integer overflow");
    ++value;
    return *this;
}

int SafeInt::operator()() const {
    return this -> value;
}


int main() {
    SafeInt s1(5);
    SafeInt s2(10);
    SafeInt s3 = s1 + s2;
    std::cout << "s1 + s2 = " << s3 << std::endl;
    s3 = s1 - s2;
    std::cout << "s1 - s2 = " << s3 << std::endl;
    s3 = s1 * s2;
    std::cout << "s1 * s2 = " << s3() << std::endl;
    ++s3;
    std::cout << "++s3 = " << s3() << std::endl;
    return 0;
}
