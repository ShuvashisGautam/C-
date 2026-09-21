#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string name;
    int rollNo;
    string program;

public:
    Student(string n, int r, string p) {
        name = n;
        rollNo = r;
        program = p;
    }

    void display() {
        cout << "Name: " << name << endl;
        cout << "Roll No: " << rollNo << endl;
        cout << "Program: " << program << endl;
        cout << endl;
    }
};

int main() {
    Student s1("Bibesh Dhakal", 12, "Computer Science");
    Student s2("Aayush Sharma", 15, "BCA");

    s1.display();
    s2.display();

    return 0;
}
