#include <iostream>
using namespace std;

int main() {
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    if (n <= 0) {
        cout << "Size must be positive." << endl;
        return 1;
    }

    int *arr = new int[n];

    cout << "Enter " << n << " integers:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> *(arr + i);
    }

    int largest = *arr;
    int smallest = *arr;

    for (int i = 1; i < n; i++) {
        if (*(arr + i) > largest) {
            largest = *(arr + i);
        }
        if (*(arr + i) < smallest) {
            smallest = *(arr + i);
        }
    }

    cout << "Largest = " << largest << endl;
    cout << "Smallest = " << smallest << endl;

    delete[] arr;
    arr = nullptr;

    return 0;
}
