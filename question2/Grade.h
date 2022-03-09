#include "Course.h"

template <size_t I = 0, typename... Ts>
constexpr float gradeProject(std::tuple<Ts...> tup)
{
    if
    constexpr(I == sizeof...(Ts) - 1)
    {
        return 0;
    }
    else {
        auto p1 = std::get<I>(tup);
        auto p2 = std::get<I + 1>(tup);
        if(p1 < p2) {
            std::get<I>(tup) = p2;
            std::get<I + 1>(tup) = p1;
        }
        return (std::get<I>(tup)/(sizeof...(Ts) - 1)) + sum<I + 1>(tup);
    }
}
