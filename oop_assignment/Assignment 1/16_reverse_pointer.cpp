#include <iostream>
using namespace std;

int main() {
    int numbers[5];

    cout << "Enter 5 integers:" << endl;
    for (int i = 0; i < 5; i++) {
        cin >> numbers[i];
    }

    int *ptr = numbers + 4;

    cout << "Reverse order:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << *ptr << " ";
        ptr--;
    }

    cout << endl;

    return 0;
}
