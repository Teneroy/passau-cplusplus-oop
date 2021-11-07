#include <iostream>
using namespace std;

class Base {
protected:
    int d;
    int x;
public:
    Base() = default;
    int value() const { return 10; }
    ~Base() { cout << "Base deleted " ; }
};

class Derived1 : public Base {
protected:
    int y;
public:
    Derived1() = default;
    int value() const {
        return 10;
    }
    ~Derived1() { cout << "Derived1 deleted "; }
    int gety() const { return y; }
};

class Derived2 : public Base {
public:
    Derived2() = default;
    int value() const { return 17; }
    ~Derived2() { cout << "Derived2 deleted "; }
};

int main() {
    Base *p = new Base();
    Base *p1 = new Derived1();
    Derived1 *p2 = (Derived1*) new Base();
    cout << p2->gety() << endl;
    Base *p3 = new Derived2();
    cout << p->value() << endl;
    cout << p1->value() << endl;
    cout << p2->value() << endl;//L1
    cout << p3->value() << endl;

    Derived1 * d = new Derived1();
    cout << d -> value() << endl;
    delete d;

    delete p;
    delete p1;
    delete p2;
    delete p3;
}