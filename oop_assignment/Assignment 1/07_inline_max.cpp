#include <iostream>
using namespace std;

inline int maximum(int a, int b, int c) {
    if (a >= b && a >= c) {
        return a;
    }
    if (b >= a && b >= c) {
        return b;
    }
    return c;
}

int main() {
    // An inline function asks the compiler to replace the function call with
    // the function body. This can reduce function call overhead for small functions.
    // A normal function usually has call and return overhead during execution.
    cout << "Maximum of 10, 20, 30 = " << maximum(10, 20, 30) << endl;
    cout << "Maximum of 45, 12, 30 = " << maximum(45, 12, 30) << endl;
    cout << "Maximum of 7, 99, 31 = " << maximum(7, 99, 31) << endl;

    return 0;
}
