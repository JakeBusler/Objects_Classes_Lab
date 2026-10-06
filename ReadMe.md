# BankAccount Class

A C++ class for representing and managing bank accounts within a banking management system.

## Data Dictionary

| Attribute | Data Type | Description |
|-----------|-----------|-------------|
| `accountNumber` | `std::string` | Unique identifier for the bank account. |
| `accountHolderName` | `std::string` | Full name of the account holder. |
| `balance` | `double` | Current monetary balance in the account. |

## Methods List

| Method Signature | Return Type | Description |
|------------------|-------------|-------------|
| `BankAccount()` | (Constructor) | Default constructor initializing empty account attributes and a 0.00 balance. |
| `BankAccount(const std::string& accNum, const std::string& holderName, double initialBalance)` | (Constructor) | Parameterized constructor initializing account number, holder name, and starting balance. |
| `getAccountNumber() const` | `std::string` | Returns the account number. |
| `getAccountHolderName() const` | `std::string` | Returns the account holder's name. |
| `getBalance() const` | `double` | Returns the current account balance. |
| `setAccountHolderName(const std::string& name)` | `void` | Updates the account holder's name. |
| `deposit(double amount)` | `void` | Adds funds to the account if the deposit amount is positive. |
| `withdraw(double amount)` | `bool` | Deducts funds if the amount is positive and sufficient funds exist; returns `true` if successful, or `false` on insufficient funds. |
