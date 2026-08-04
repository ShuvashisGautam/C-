#include <iostream>
using namespace std;

int main() {
    int number = 50;
    int *ptr = &number;
    int **doublePtr = &ptr;

    cout << "Using variable:" << endl;
    cout << "Address = " << &number << ", Value = " << number << endl;

    cout << "Using pointer:" << endl;
    cout << "Address = " << ptr << ", Value = " << *ptr << endl;

    cout << "Using double pointer:" << endl;
    cout << "Address = " << *doublePtr << ", Value = " << **doublePtr << endl;

    return 0;
}
