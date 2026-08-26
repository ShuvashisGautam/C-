#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    double billAmount;

    cout << "Enter total bill amount: ";
    cin >> billAmount;

    cout << "Formatted bill: "
         << setw(12) << setfill('*') << fixed << showpoint << setprecision(2)
         << billAmount << endl;

    return 0;
}
