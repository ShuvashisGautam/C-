#include <cmath>
#include <iostream>
using namespace std;

float area(float radius) {
    const float pi = 3.14159f;
    return pi * radius * radius;
}

int area(int length, int breadth) {
    return length * breadth;
}

float area(float a, float b, float c) {
    float s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

int main() {
    float radius, side1, side2, side3;
    int length, breadth;

    cout << "Enter radius of circle: ";
    cin >> radius;
    cout << "Area of circle = " << area(radius) << endl;

    cout << "Enter length and breadth of rectangle: ";
    cin >> length >> breadth;
    cout << "Area of rectangle = " << area(length, breadth) << endl;

    cout << "Enter three sides of triangle: ";
    cin >> side1 >> side2 >> side3;
    cout << "Area of triangle = " << area(side1, side2, side3) << endl;

    return 0;
}
