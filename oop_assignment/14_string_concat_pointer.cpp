#include <iostream>
using namespace std;

int main() {
    char first[200];
    char second[100];
    char *p;
    char *q;

    cout << "Enter first string: ";
    cin.getline(first, 200);

    cout << "Enter second string: ";
    cin.getline(second, 100);

    p = first;
    while (*p != '\0') {
        p++;
    }

    q = second;
    while (*q != '\0') {
        *p = *q;
        p++;
        q++;
    }

    *p = '\0';

    cout << "Concatenated string = " << first << endl;

    return 0;
}
