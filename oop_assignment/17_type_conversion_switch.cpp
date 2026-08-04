#include <iostream>
using namespace std;

int main() {
    float floatValue;
    int implicitValue;
    int choice;

    cout << "Enter a floating-point number: ";
    cin >> floatValue;

    implicitValue = floatValue;

    cout << "\n1. Perform explicit cast using static_cast<int>" << endl;
    cout << "2. View value after implicit conversion" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int explicitValue = static_cast<int>(floatValue);
            cout << "Explicitly cast value = " << explicitValue << endl;
            break;
        }
        case 2:
            cout << "Implicitly converted value = " << implicitValue << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
    }

    cout << "Fractional part is removed when float is converted to int." << endl;

    return 0;
}
