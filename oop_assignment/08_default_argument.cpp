#include <iostream>
using namespace std;

double amountCalc(double principal, double time, double rate = 3.5) {
    return principal + (principal * time * rate / 100);
}

int main() {
    double principal, time, rate;

    cout << "Enter principal and time in years: ";
    cin >> principal >> time;

    cout << "Amount using default rate 3.5% = "
         << amountCalc(principal, time) << endl;

    cout << "Enter custom rate: ";
    cin >> rate;

    cout << "Amount using custom rate = "
         << amountCalc(principal, time, rate) << endl;

    return 0;
}
