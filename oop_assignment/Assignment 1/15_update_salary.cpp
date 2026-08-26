#include <iostream>
using namespace std;

void updateSalary(float *salary, float bonus) {
    *salary = *salary + bonus;
}

int main() {
    float salary, bonus;

    cout << "Enter salary: ";
    cin >> salary;

    cout << "Enter bonus: ";
    cin >> bonus;

    updateSalary(&salary, bonus);

    cout << "Updated salary = " << salary << endl;

    return 0;
}
