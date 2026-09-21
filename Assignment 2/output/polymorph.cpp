// cpp to understand the concept of polymorphism 
// Polymorphism is a feature of object-oriented programming that allows objects of different classes to be treated as objects of a common superclass. It enables a single interface to represent different underlying forms (data types).
#include <iostream>
using namespace std;
class shape{
    public:
    int getarea(){
        return -1;
    }
};

class Rectangle:
 public shape{
    int length;
    int breadth;
    public:
    Rectangle(int l, int b){
        length = l;
        breadth = b;
    }
    int getarea(){
        return length * breadth;
    }
};

int main(){
    Rectangle object(10, 5);
    cout << "Area of rectangle: " << object.getarea() << endl;
    return 0;
}