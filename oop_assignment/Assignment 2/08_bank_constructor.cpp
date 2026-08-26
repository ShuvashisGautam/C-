#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string accountHolder;
    double balance;

public:
    BankAccount(int number, string holder, double amount) {
        accountNumber = number;
        accountHolder = holder;
        balance = amount;
    }

    void deposit(double amount) {
        balance = balance + amount;
    }

    void withdraw(double amount) {
        if (amount <= balance) {
            balance = balance - amount;
        } else {
            cout << "Not enough balance." << endl;
        }
    }

    void displayBalance() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << accountHolder << endl;
        cout << "Balance: " << balance << endl;
    }
};

int main() {
    BankAccount account(2001, "Bibesh Dhakal", 10000);

    account.deposit(3000);
    account.withdraw(2500);
    account.deposit(1500);

    account.displayBalance();

    return 0;
}
