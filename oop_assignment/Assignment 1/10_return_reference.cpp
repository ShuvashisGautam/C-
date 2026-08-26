#include <iostream>
using namespace std;

int &maxRef(int &x, int &y) {
    if (x >= y) {
        return x;
    }
    return y;
}

int main() {
    int a = 25;
    int b = 40;

    cout << "Before assignment: a = " << a << ", b = " << b << endl;

    maxRef(a, b) = 100;

    cout << "After assignment: a = " << a << ", b = " << b << endl;

    return 0;
}
