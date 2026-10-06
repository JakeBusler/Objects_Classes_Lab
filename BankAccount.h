#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>

class BankAccount {
private:
    std::string accountNumber;
    std::string accountHolderName;
    double balance;

public:
    // Constructors
    BankAccount();
    BankAccount(const std::string& accNum, const std::string& holderName, double initialBalance);

    // Accessors (Getters)
    std::string getAccountNumber() const;
    std::string getAccountHolderName() const;
    double getBalance() const;

    // Mutator (Setter)
    void setAccountHolderName(const std::string& name);

    // Operations
    void deposit(double amount);
    bool withdraw(double amount);
};

#endif // BANKACCOUNT_H
