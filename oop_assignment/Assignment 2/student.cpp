#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int rollNo;
    string program;

    void display() {
        cout << "Name: " << name << endl;
        cout << "Roll No: " << rollNo << endl;
        cout << "Program: " << program << endl;
    }
};

int main() {
    Student s1;

    s1.name = "Bibesh Dhakal";
    s1.rollNo = 12;
    s1.program = "Computer Science";

    s1.display();

    return 0;
}
