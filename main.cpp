#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include "BankAccount.h"

// Helper function (Clear invalid console input)
void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Helper function (Read trimmed/non-empty lines)
std::string getNonEmptyString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        // Trim check
        size_t first = value.find_first_not_of(" \t\r\n");
        if (first != std::string::npos) {
            size_t last = value.find_last_not_of(" \t\r\n");
            return value.substr(first, (last - first + 1));
        }
        std::cout << "Input cannot be empty. Please try again.\n";
    }
}

// Helper function (Read validated positive double/zero if allowZero=true))
double getValidDouble(const std::string& prompt, bool allowZero = false) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            if ((allowZero && value >= 0.0) || (!allowZero && value > 0.0)) {
                clearInputBuffer();
                return value;
            }
            std::cout << "Invalid amount. Value must be " 
                      << (allowZero ? "greater than or equal to 0.00" : "strictly greater than 0.00") 
                      << ".\n";
        } else {
            std::cout << "Invalid input. Please enter a numeric value.\n";
        }
        clearInputBuffer();
    }
}

// Helper function (Read validated integer menu choices)
int getValidInt(const std::string& prompt, int minVal, int maxVal) {
    int choice;
    while (true) {
        std::cout << prompt;
        if (std::cin >> choice) {
            if (choice >= minVal && choice <= maxVal) {
                clearInputBuffer();
                return choice;
            }
            std::cout << "Please select an option between " << minVal << " and " << maxVal << ".\n";
        } else {
            std::cout << "Invalid input. Please enter a valid number.\n";
        }
        clearInputBuffer();
    }
}

// Helper function (Search for account by account number)
int findAccountIndex(const std::vector<BankAccount>& accounts, const std::string& accNum) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].getAccountNumber() == accNum) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// Displays the formatted menu
void displayMenu() {
    std::cout << "\n=========================================\n";
    std::cout << "     BANK ACCOUNT MANAGEMENT SYSTEM      \n";
    std::cout << "=========================================\n";
    std::cout << " 1. Create New Account\n";
    std::cout << " 2. Deposit Funds\n";
    std::cout << " 3. Withdraw Funds\n";
    std::cout << " 4. View Account Details\n";
    std::cout << " 5. Update Account Holder Name\n";
    std::cout << " 6. Display All Accounts\n";
    std::cout << " 7. Exit\n";
    std::cout << "=========================================\n";
}

int main() {
    std::vector<BankAccount> accounts;
    bool running = true;

    // Set 2-decimal point precision for currency display
    std::cout << std::fixed << std::setprecision(2);

    while (running) {
        displayMenu();
        int choice = getValidInt("Enter your choice (1-7): ", 1, 7);
        std::cout << "\n";

        switch (choice) {
            case 1: { // Create New Account
                std::cout << "--- Create New Account ---\n";
                std::string accNum = getNonEmptyString("Enter Account Number: ");

                if (findAccountIndex(accounts, accNum) != -1) {
                    std::cout << "Error: An account with number '" << accNum << "' already exists.\n";
                    break;
                }

                std::string holderName = getNonEmptyString("Enter Account Holder Name: ");
                double initialBalance = getValidDouble("Enter Initial Deposit Amount ($): ", true);

                BankAccount newAccount(accNum, holderName, initialBalance);
                accounts.push_back(newAccount);

                std::cout << "\nSuccess: Account created for " << holderName 
                          << " (Account #" << accNum << ") with balance $" 
                          << initialBalance << ".\n";
                break;
            }

            case 2: { // Deposit Funds
                std::cout << "--- Deposit Funds ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts available. Please create an account first.\n";
                    break;
                }

                std::string accNum = getNonEmptyString("Enter Account Number: ");
                int index = findAccountIndex(accounts, accNum);

                if (index == -1) {
                    std::cout << "Error: Account #" << accNum << " not found.\n";
                    break;
                }

                double amount = getValidDouble("Enter Deposit Amount ($): ", false);
                accounts[index].deposit(amount);

                std::cout << "Success: Deposited $" << amount << " into account #" << accNum << ".\n";
                std::cout << "Updated Balance: $" << accounts[index].getBalance() << "\n";
                break;
            }

            case 3: { // Withdraw Funds
                std::cout << "--- Withdraw Funds ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts available. Please create an account first.\n";
                    break;
                }

                std::string accNum = getNonEmptyString("Enter Account Number: ");
                int index = findAccountIndex(accounts, accNum);

                if (index == -1) {
                    std::cout << "Error: Account #" << accNum << " not found.\n";
                    break;
                }

                std::cout << "Current Balance: $" << accounts[index].getBalance() << "\n";
                double amount = getValidDouble("Enter Withdrawal Amount ($): ", false);

                if (accounts[index].withdraw(amount)) {
                    std::cout << "Success: Withdrew $" << amount << " from account #" << accNum << ".\n";
                    std::cout << "Updated Balance: $" << accounts[index].getBalance() << "\n";
                } else {
                    std::cout << "Error: Withdrawal failed due to insufficient funds.\n";
                    std::cout << "Current Balance: $" << accounts[index].getBalance() << "\n";
                }
                break;
            }

            case 4: { // View Account Details
                std::cout << "--- View Account Details ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts available.\n";
                    break;
                }

                std::string accNum = getNonEmptyString("Enter Account Number: ");
                int index = findAccountIndex(accounts, accNum);

                if (index == -1) {
                    std::cout << "Error: Account #" << accNum << " not found.\n";
                    break;
                }

                std::cout << "\nAccount Details:\n";
                std::cout << "  Account Number : " << accounts[index].getAccountNumber() << "\n";
                std::cout << "  Holder Name    : " << accounts[index].getAccountHolderName() << "\n";
                std::cout << "  Balance        : $" << accounts[index].getBalance() << "\n";
                break;
            }

            case 5: { // Update Account Holder Name
                std::cout << "--- Update Account Holder Name ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts available.\n";
                    break;
                }

                std::string accNum = getNonEmptyString("Enter Account Number: ");
                int index = findAccountIndex(accounts, accNum);

                if (index == -1) {
                    std::cout << "Error: Account #" << accNum << " not found.\n";
                    break;
                }

                std::cout << "Current Holder Name: " << accounts[index].getAccountHolderName() << "\n";
                std::string newName = getNonEmptyString("Enter New Account Holder Name: ");
                accounts[index].setAccountHolderName(newName);

                std::cout << "Success: Holder name for account #" << accNum << " updated to '" << newName << "'.\n";
                break;
            }

            case 6: { // Display All Accounts
                std::cout << "--- All Accounts ---\n";
                if (accounts.empty()) {
                    std::cout << "No accounts registered yet.\n";
                    break;
                }

                std::cout << std::left << std::setw(6)  << "#" 
                          << std::setw(18) << "Account No." 
                          << std::setw(25) << "Account Holder" 
                          << std::right << std::setw(15) << "Balance ($)" << "\n";
                std::cout << std::string(64, '-') << "\n";

                for (size_t i = 0; i < accounts.size(); ++i) {
                    std::cout << std::left << std::setw(6)  << (i + 1)
                              << std::setw(18) << accounts[i].getAccountNumber()
                              << std::setw(25) << accounts[i].getAccountHolderName()
                              << std::right << std::setw(15) << accounts[i].getBalance() << "\n";
                }
                std::cout << std::string(64, '-') << "\n";
                std::cout << "Total Accounts: " << accounts.size() << "\n";
                break;
            }

            case 7: { // Exit
                std::cout << "Thank you for using the Bank Account Management System. Goodbye!\n";
                running = false;
                break;
            }
        }
    }

    return 0;
}
