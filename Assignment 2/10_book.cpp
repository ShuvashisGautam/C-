#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    double price;

public:
    Book(string t, string a, double p) {
        title = t;
        author = a;
        price = p;
    }

    void applyDiscount(double percent) {
        price = price - (price * percent / 100);
    }

    void display() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Price: " << price << endl;
    }
};

int main() {
    Book book1("The Alchemist", "Paulo Coelho", 800);

    book1.applyDiscount(10);
    book1.display();

    return 0;
}
