#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    string name;
    double balance;

public:
    BankAccount(int accNum, string accHolder, double initialBalance) {
        accountNumber = accNum;
        name = accHolder;
        balance = initialBalance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    string getName() const {
        return name;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposit successful!\n";
        } else {
            cout << "Invalid deposit amount!\n";
        }
    }

    void withdraw(double amount) {
        if (amount <= balance && amount > 0) {
            balance -= amount;
            cout << "Withdrawal successful!\n";
        } else {
            cout << "Insufficient balance or invalid amount!\n";
        }
    }

    void display() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Account Holder: " << name << endl;
        cout << fixed << setprecision(2);
        cout << "Current Balance: $" << balance << endl;
    }
};

vector<BankAccount> accounts;

BankAccount* findAccount(int accNum) {
    for (auto& acc : accounts) {
        if (acc.getAccountNumber() == accNum)
            return &acc;
    }
    return nullptr;
}

void createAccount() {
    int accNum;
    string name;
    double initialBalance;

    cout << "Enter account number: ";
    cin >> accNum;
    cin.ignore(); // Clear buffer
    cout << "Enter account holder name: ";
    getline(cin, name);
    cout << "Enter initial balance: $";
    cin >> initialBalance;

    accounts.push_back(BankAccount(accNum, name, initialBalance));
    cout << "Account created successfully!\n\n";
}

void viewAccount() {
    int accNum;
    cout << "Enter account number to view: ";
    cin >> accNum;

    BankAccount* acc = findAccount(accNum);
    if (acc) {
        acc->display();
    } else {
        cout << "Account not found.\n";
    }
    cout << endl;
}

void depositToAccount() {
    int accNum;
    double amount;

    cout << "Enter account number to deposit into: ";
    cin >> accNum;
    BankAccount* acc = findAccount(accNum);

    if (acc) {
        cout << "Enter amount to deposit: $";
        cin >> amount;
        acc->deposit(amount);
    } else {
        cout << "Account not found.\n";
    }
    cout << endl;
}

void withdrawFromAccount() {
    int accNum;
    double amount;

    cout << "Enter account number to withdraw from: ";
    cin >> accNum;
    BankAccount* acc = findAccount(accNum);

    if (acc) {
        cout << "Enter amount to withdraw: $";
        cin >> amount;
        acc->withdraw(amount);
    } else {
        cout << "Account not found.\n";
    }
    cout << endl;
}

int main() {
    int choice;

    do {
        cout << "======= Bank Account Management =======\n";
        cout << "1. Create New Account\n";
        cout << "2. View Account Details\n";
        cout << "3. Deposit\n";
        cout << "4. Withdraw\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "---------------------------------------\n";

        switch (choice) {
            case 1: createAccount(); break;
            case 2: viewAccount(); break;
            case 3: depositToAccount(); break;
            case 4: withdrawFromAccount(); break;
            case 5: cout << "Thank you! Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n\n"; break;
        }

    } while (choice != 5);

    return 0;
}
