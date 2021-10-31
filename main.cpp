#include <iostream>
#include <vector>
using namespace std;

vector<int> a() {
    vector<int> t {1, 2, 3};
    return t;
}

int main() {
    vector<int> x = a();
    cout << x.at(1) << endl;
    return 0;
}
