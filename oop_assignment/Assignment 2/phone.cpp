#include <iostream>
#include <string>
using namespace std;

class MobilePhone {
public:
    string brand;
    string model;
    double price;
    int storage;

    void displayDetails() {
        cout << "Brand: " << brand << endl;
        cout << "Model: " << model << endl;
        cout << "Price: " << price << endl;
        cout << "Storage: " << storage << " GB" << endl;
        cout << endl;
    }
};

int main() {
    MobilePhone phone1, phone2, phone3;

    phone1.brand = "Samsung";
    phone1.model = "Galaxy A15";
    phone1.price = 25000;
    phone1.storage = 128;

    phone2.brand = "Apple";
    phone2.model = "iPhone 13";
    phone2.price = 85000;
    phone2.storage = 128;

    phone3.brand = "Xiaomi";
    phone3.model = "Redmi Note 13";
    phone3.price = 30000;
    phone3.storage = 256;

    phone1.displayDetails();
    phone2.displayDetails();
    phone3.displayDetails();

    return 0;
}
