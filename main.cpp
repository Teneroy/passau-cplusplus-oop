#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <variant>
#include <any>
#include "./question1/utils.h"



int main() {
//    std::vector<int> a = {1,2,3,4,5};
//    std::vector<int> b = {6,7,8,9,10};
//    // get all odd numbers from a and b
//    auto c = unionAndFilterContainer(a,b, [](int x){return x%2==0;});
//    if (std::all_of(c.begin(), c.end(), [](auto x){ return x%2==0;}))
//        std::cout << "QUESTION 2 PASSED" << std::endl;
//    else
//        std::cout << "QUESTION 2 FAILED" << std::endl;
//
//    std::cout << std::endl;
//    constexpr unsigned v = Ackermann<0, 1>::value;
//    std::cout << v << std::endl;
//    std::cout << ackermann<1,2>() << std::endl;
//
//    int result = sum(1, 2, 3); //  6
//    std::cout << result << std::endl;

//    std::tuple<int, char, int, bool> t;
//    std::tuple<int, int, int, int> t2;
//    std::tuple<bool, bool, bool> t3;
//    t = std::make_tuple(1, 'a', 2, true);
//    t2 = std::make_tuple(1, 1, 1, 1);
//    t3 = std::make_tuple(true, true, true);
//    auto a = equalityU(t);
//    auto a1 = equalityU(t2);
//    auto a2 = equalityU(t3);
//    std::cout << a << std::endl;

    auto t = std::make_tuple(std::make_pair(3, 4), std::make_pair(4, 5), std::make_pair(4, 5), std::make_pair(5, 4));
    std::cout << matMulPossible(t) << std::endl;
}