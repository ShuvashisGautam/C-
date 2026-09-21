#include <iostream>
#include <string>
using namespace std;

class BankAccount {
public:
    int accountNumber;
    string accountHolder;
    double balance;

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
    BankAccount account;

    account.accountNumber = 1001;
    account.accountHolder = "Bibesh Dhakal";
    account.balance = 5000;

    account.deposit(2000);
    account.withdraw(1500);
    account.deposit(1000);

    account.displayBalance();

    return 0;
}
