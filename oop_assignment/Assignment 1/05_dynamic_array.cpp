#include <iostream>
using namespace std;

int main() {
    int size;
    int sum = 0;

    cout << "Enter number of elements: ";
    cin >> size;

    if (size <= 0) {
        cout << "Size must be positive." << endl;
        return 1;
    }

    int *numbers = new int[size];

    cout << "Enter " << size << " integers:" << endl;
    for (int i = 0; i < size; i++) {
        cin >> numbers[i];
        sum += numbers[i];
    }

    double average = static_cast<double>(sum) / size;

    cout << "Sum = " << sum << endl;
    cout << "Average = " << average << endl;

    delete[] numbers;
    numbers = nullptr;

    return 0;
}
