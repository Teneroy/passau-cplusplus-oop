#include "Course.h"


template <unsigned s, bool a_cond, bool b_cond, bool c_cond, bool d_cond, bool e_cond, bool f_cond>
struct GradeBase {};

template <unsigned s>
struct gradeProject : GradeBase<s, (s >= 90), (s >= 80 && s < 90), (s >= 70 && s < 80), (s >= 60 && s < 70), (s >= 50 && s < 60), (s < 50)> {};

template <unsigned s>
struct gradeWritten : GradeBase<s, (s >= 90), (s >= 80 && s < 90), (s >= 70 && s < 80), (s >= 55 && s < 70), (s >= 40 && s < 55), (s < 40)> {};

template <unsigned s, bool b_cond, bool c_cond, bool d_cond, bool e_cond, bool f_cond>
struct GradeBase<s, true, b_cond, c_cond, d_cond, e_cond, f_cond> {
    static constexpr char result = 'A';
};

template <unsigned s, bool c_cond, bool d_cond, bool e_cond, bool f_cond>
struct GradeBase<s, false, true, c_cond, d_cond, e_cond, f_cond> {
    static constexpr char result = 'B';
};

template <unsigned s, bool d_cond, bool e_cond, bool f_cond>
struct GradeBase<s, false, false, true, d_cond, e_cond, f_cond> {
    static constexpr char result = 'C';
};

template <unsigned s, bool e_cond, bool f_cond>
struct GradeBase<s, false, false, false, true, e_cond, f_cond> {
    static constexpr char result = 'D';
};

template <unsigned s, bool f_cond>
struct GradeBase<s, false, false, false, false, true, f_cond> {
    static constexpr char result = 'E';
};

template <unsigned s, bool f_cond>
struct GradeBase<s, false, false, false, false, false, f_cond> {
    static constexpr char result = 'F';
};

template <size_t I = 0, typename... Ts>
constexpr void precomputeGradeMap(std::map<Ts...>& map)
{
    if
    constexpr(I == 100)
    {
        return;
    }
    else {
        map.insert(std::make_pair(I, gradeProject<I>::result));
        precomputeGradeMap<I + 1>(map);
        return;
    }
}

template <size_t I = 0, typename... Ts>
constexpr void precomputeGradeMapWritten(std::map<Ts...>& map)
{
    if
    constexpr(I == 100)
    {
        return;
    }
    else {
        map.insert(std::make_pair(I, gradeWritten<I>::result));
        precomputeGradeMap<I + 1>(map);
        return;
    }
}

template <size_t I = 0, typename... Ts>
constexpr float calculateProject(std::tuple<Ts...> tup)
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
        return (std::get<I>(tup)/(sizeof...(Ts) - 1)) + calculateProject<I + 1>(tup);
    }
}

template <size_t I = 0, typename... Ts>
constexpr float calculateHybrid(std::tuple<Ts...> tup)
{
    if
    constexpr(I == sizeof...(Ts) - 1)
    {
        auto p = 0.4f*std::get<I>(tup);
        return p;
    }
    else {
        auto p = 0.6f*(std::get<I>(tup)/(sizeof...(Ts) - 1));
        return p + calculateHybrid<I + 1>(tup);
    }
}

template <size_t I = 0, typename... Ts>
constexpr float calculateWritten(std::tuple<Ts...> tup)
{
    if
    constexpr(I == sizeof...(Ts) - 1)
    {
        auto p = 0.7f*std::get<I>(tup);
        return p;
    }
    else {
        return 0.3f*std::get<I>(tup) + calculateWritten<I + 1>(tup);
    }
}

