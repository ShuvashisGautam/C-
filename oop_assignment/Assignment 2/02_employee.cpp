#include <iostream>
#include <string>
using namespace std;

class Employee {
public:
    string name;
    int employeeId;
    double salary;

    void display() {
        cout << "Name: " << name << endl;
        cout << "Employee ID: " << employeeId << endl;
        cout << "Salary: " << salary << endl;
        cout << endl;
    }
};

int main() {
    Employee e1, e2, e3;

    e1.name = "Ram";
    e1.employeeId = 101;
    e1.salary = 45000;

    e2.name = "Sita";
    e2.employeeId = 102;
    e2.salary = 52000;

    e3.name = "Hari";
    e3.employeeId = 103;
    e3.salary = 48000;

    e1.display();
    e2.display();
    e3.display();

    return 0;
}
