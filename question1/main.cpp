#include "utils.h"

int main() {
    std::vector<int> a = {1,2,3,4,5};
    std::vector<int> b = {6,7,8,9,10};
    // get all odd numbers from a and b
    auto c = unionAndFilterContainer(a,b, [](int x){return x%2==0;});
    if (std::all_of(c.begin(), c.end(), [](auto x){ return x%2==0;}))
        std::cout << "QUESTION 2 PASSED" << std::endl;
    else
        std::cout << "QUESTION 2 FAILED" << std::endl;

    std::cout << std::endl;
    std::cout << ackermann<1,2>::result << std::endl;

    std::tuple<int, char> t1;
    std::tuple<int, int, int, int> t2;
    std::tuple<int, int, int, bool> t3;
    t1 = std::make_tuple(65, 'A');
    t2 = std::make_tuple(1, 1, 1, 1);
    t3 = std::make_tuple(1, 1, 1, false);
    std::cout << "t1's parameters: " << equalityU(t1) << std::endl;
    std::cout << "t2's parameters: " << equalityU(t2) << std::endl;
    std::cout << "t3's parameters: " << equalityU(t3) << std::endl;

    auto matrix_tuple = std::make_tuple(std::make_pair(3, 4), std::make_pair(4, 5), std::make_pair(4, 5), std::make_pair(5, 4));
    std::cout << matMulPossible(matrix_tuple) << std::endl;
}