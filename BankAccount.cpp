#include "BankAccount.h"

// Default constructor
BankAccount::BankAccount()
    : accountNumber(""), accountHolderName(""), balance(0.0) {}

// Parameterized constructor
BankAccount::BankAccount(const std::string& accNum, const std::string& holderName, double initialBalance)
    : accountNumber(accNum), accountHolderName(holderName), balance(initialBalance >= 0.0 ? initialBalance : 0.0) {}

// Accessor methods (Getters)
std::string BankAccount::getAccountNumber() const {
    return accountNumber;
}

std::string BankAccount::getAccountHolderName() const {
    return accountHolderName;
}

double BankAccount::getBalance() const {
    return balance;
}

// Mutator method (Setter)
void BankAccount::setAccountHolderName(const std::string& name) {
    accountHolderName = name;
}

// Member operations
void BankAccount::deposit(double amount) {
    if (amount > 0.0) {
        balance += amount;
    }
}

bool BankAccount::withdraw(double amount) {
    if (amount > 0.0 && amount <= balance) {
        balance -= amount;
        return true;
    }
    return false;
}
