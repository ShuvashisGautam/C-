#include <iostream>
#include <string>
using namespace std;

class Employee {
private:
    string name;
    int employeeId;
    double basicSalary;

public:
    Employee(string n, int id, double salary) {
        name = n;
        employeeId = id;
        basicSalary = salary;
    }

    double calculateAllowance() {
        return basicSalary * 0.20;
    }

    double calculateTax() {
        return basicSalary * 0.10;
    }

    double calculateNetSalary() {
        return basicSalary + calculateAllowance() - calculateTax();
    }

    void display() {
        cout << "Name: " << name << endl;
        cout << "Employee ID: " << employeeId << endl;
        cout << "Basic Salary: " << basicSalary << endl;
        cout << "Allowance: " << calculateAllowance() << endl;
        cout << "Tax: " << calculateTax() << endl;
        cout << "Net Salary: " << calculateNetSalary() << endl;
        cout << endl;
    }
};

int main() {
    Employee e1("Ram", 101, 50000);
    Employee e2("Sita", 102, 60000);

    e1.display();
    e2.display();

    return 0;
}
