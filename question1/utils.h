//
// Created by studone on 1/16/22.
//

#ifndef PASSAU_CPLUSPLUS_OOP_UTILS_H
#define PASSAU_CPLUSPLUS_OOP_UTILS_H

#include <algorithm>
#include <iostream>
#include <vector>


/* Task 1 */
template <unsigned m, unsigned n, bool cond, bool cond2>
struct AckermannBase {};

template <unsigned m, unsigned n>
struct Ackermann : AckermannBase<m, n, (m == 0), (n == 0)> {};

template <unsigned m, unsigned n>
struct AckermannBase<m, n, false, true> : Ackermann<m - 1, 1> {};

template <unsigned m, unsigned n>
struct AckermannBase<m, n, false, false> : Ackermann<m - 1, Ackermann<m, n - 1>::value> {};

template <unsigned m, unsigned n, bool cond2>
struct AckermannBase<m, n, true, cond2> {
    static const unsigned value = n + 1;
};

template <unsigned m, unsigned n>
unsigned ackermann() {
    return Ackermann<m, n>::value;
}


/* Task 2 */
template <class Container, typename Function>
Container unionAndFilterContainer(Container& a, Container& b, Function f) {
    Container cont;
    auto unionContainer = [](Container& iterCont, Container& resultCont, Function cond) {
        for (auto elem : iterCont) {
            if(!cond(elem)) {
                continue;
            }
            resultCont.push_back(elem);
        }
        return resultCont;
    };
    cont = unionContainer(a, cont, f);
    cont = unionContainer(b, cont, f);
    return cont;
}

/* Task 3 */

template <size_t index, class Op, class... Ts>
constexpr auto fold(Op op, const std::tuple<Ts...>& t) {
    if constexpr(index == sizeof...(Ts) - 1) {
        return std::get<index>(t);
    } else {
        return op(std::get<index>(t), fold<1 + index>(op, t));
    }
}

template <class Op, typename A, typename B>
constexpr auto performe(Op op, A a, B b) {
    return op(a, b);
}

template <typename ... Ts>
constexpr auto equalityU(std::tuple<Ts...> const & t1)  {
    bool equals = true;
    fold<0>(
            [&equals](auto a, auto b) {
                if(typeid(a) != typeid(b)) {
                    equals = false;
                    return b;
                }
                auto val = performe(std::equal_to<>{}, a, b);
                if(val == false) {
                    equals = false;
                }
                return b;
            },
            t1);
    return equals;
}


/* Task 4 */

template <size_t I = 1, typename... Ts>
constexpr bool matMulPossible(std::tuple<Ts...> tup)
{
    // If we have iterated through all elements
    if
    constexpr(I >= sizeof...(Ts))
    {
        // Last case, if nothing is left to
        // iterate, then exit the function
        return true;
    }
    else {
        auto p1 = std::get<I - 1>(tup);
        auto p2 = std::get<I>(tup);
        if(std::get<1>(p1) != std::get<0>(p2)) {
            return false;
        }
        return matMulPossible<I + 2>(tup);
    }
}

#endif //PASSAU_CPLUSPLUS_OOP_UTILS_H
