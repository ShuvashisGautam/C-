#include <iostream>
using namespace std;

void swapValues(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}

int main() {
    int a, b;

    cout << "Enter two integers: ";
    cin >> a >> b;

    cout << "Before swapping: a = " << a << ", b = " << b << endl;

    swapValues(a, b);

    cout << "After swapping: a = " << a << ", b = " << b << endl;

    return 0;
}
