#include <iostream>
using namespace std;

class Rectangle {
public:
    double length;
    double width;

    double calculateArea() {
        return length * width;
    }

    double calculatePerimeter() {
        return 2 * (length + width);
    }

    void display() {
        cout << "Length: " << length << endl;
        cout << "Width: " << width << endl;
        cout << "Area: " << calculateArea() << endl;
        cout << "Perimeter: " << calculatePerimeter() << endl;
    }
};

int main() {
    Rectangle r1;

    r1.length = 10;
    r1.width = 5;

    r1.display();

    return 0;
}
