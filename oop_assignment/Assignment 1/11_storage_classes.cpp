#include <iostream>
using namespace std;

int globalCount = 0;

void trackFunctionCalls() {
    int automaticCount = 0;
    static int staticCount = 0;

    automaticCount++;
    staticCount++;
    globalCount++;

    cout << "Automatic local count = " << automaticCount << endl;
    cout << "Static local count = " << staticCount << endl;
    cout << "Global count = " << globalCount << endl;
    cout << endl;
}

int main() {
    cout << "First function call:" << endl;
    trackFunctionCalls();

    cout << "Second function call:" << endl;
    trackFunctionCalls();

    cout << "Third function call:" << endl;
    trackFunctionCalls();

    return 0;
}
