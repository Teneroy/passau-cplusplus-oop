#include <iostream>

class Pair
{
protected:
    int first;
    int second;

public:
    Pair(int t, int u) : first(t), second(u) {}

    bool operator==(const Pair &rhs) const
    {
        return first == rhs.first && second == rhs.second;
    }

    friend std::ostream &operator<<(std::ostream &os, const Pair &rhs)
    {
        os << "(" << rhs.first << ", " << rhs.second << ")";
        return os;
    }

    Pair& operator=(const Pair& rhs) {
        if(this == &rhs) {
            return *this;
        }
        first = rhs.first;
        second = rhs.second;
        return *this;
    }
};

class Triple : public Pair
{
protected:
    int third;
public:
    Triple(int t, int u, int v) : Pair(t, u), third(v) {}

    Triple& operator=(const Pair& rhs) {
        Pair::operator=(rhs);
        third = 0;
        return *this;
    }

    Triple& operator=(const Triple& rhs) {
        if(this == &rhs) {
            return *this;
        }
        Pair::operator=(rhs);
        third = rhs.third;
        return *this;
    }

    friend std::ostream &operator<<(std::ostream &os, const Triple &rhs)
    {
        os << "(" << rhs.first << ", " << rhs.second << ", " << rhs.third << ")";
        return os;
    }
};

int main()
{
    // show a quick demo of class
    Pair p(1, 2);
    Pair p1(1, 2);
    std::cout << p << std::endl;
    Triple t1(2, 3, 3);
    Triple t2(1, 3, 3);
    t1 = p;
    std::cout << t1 << std::endl;
    t1 = t2;
    std::cout << t1 << std::endl;
    p1 = t1;
    std::cout << p1 << std::endl;
}