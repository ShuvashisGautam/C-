#include <iostream>
using namespace std;

namespace Metric {
    double kilometersToMeters(double kilometers) {
        return kilometers * 1000;
    }
}

namespace Imperial {
    double milesToFeet(double miles) {
        return miles * 5280;
    }
}

int main() {
    double kilometers, miles;

    cout << "Enter distance in kilometers: ";
    cin >> kilometers;

    cout << "Enter distance in miles: ";
    cin >> miles;

    cout << kilometers << " kilometers = "
         << Metric::kilometersToMeters(kilometers) << " meters" << endl;

    cout << miles << " miles = "
         << Imperial::milesToFeet(miles) << " feet" << endl;

    return 0;
}
