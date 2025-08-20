#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string customerName;
    double accountBalance;
    
public:
    //Constructor with default parameters
    BankAccount(int accNum = 0, string cusName = "", double accBal = 0.0) {
        accountNumber = accNum;
        customerName = cusName;
        accountBalance = accBal;
    }
    
    //Setter Methods
    void setAccountNumber(int accNum) {
        accountNumber = accNum;
    }
    
    void setCustomerName(string cusName) {
        customerName = cusName;
    }
    
    void setAccountBalance(double accBal) {
        accountBalance = accBal;
    }
    
    //Getter Methods
    int getAccountNumber() {
        return accountNumber;
    }
    
    int getCustomerName() {
        return customerName;
    }
    
    int getAccountBalance() {
        return accountBalance;
    }
    
    //Deposit method with balance validation
    bool deposit(double amount) {
        if(amount > 0) {
            accountBalance = accountBalance + amount;
            return true;
        } else {
            return false;
        }
    }
    
    //Withdraw method with balance validation
    bool withdraw(double amount) {
        if(amount > 0 && amount <= accountBalance ) {
            accountBalance = accountBalance - amount;
            return true;
        } else {
            return false;
        }
    }
    
    //Display Account Information
    void displayAmount() {
        cout << left << setw(15) << accountNumber << setw() << customerName << fixed << setprecision(20) << "$" << accountBalance << endl;
    }
};

void displayMenu() {
    cout << "\n" << string(50, '=') << endl;
    cout << "BANK MANAGEMENT SYSTEM" << endl;
    cout << string(50, '=') << endl;
    cout << "1. Add New Account" << endl;
    cout << "2. Display All Accounts" << endl;
    cout << "3. Search Account By Account Number" << endl;
    cout << "4. Deposit Money" << endl;
    cout << "5. Withdraw Money" << endl;
    cout << "6. Delete An Account" << endl;
    cout << "7. Exit System" << endl;
    cout << "Enter your choice (1-7): ";
}

//Input validation
int getValidChoice() {
    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 7) {
        cout << "Invalid input! Please enter a number between 1-7: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore(); // Clear the newline character
    return choice;
}

int main() {
    int choice;
    string accNum, name;
    double amount;
    
    cout << "Welcome to the Bank Account Management System!" << endl;
    
    do {
        displayMenu();
        choice = getValidChoice();
        
        switch (choice) {
            case 1: { // Add New Account
                cout << "\nADD NEW ACCOUNT" << endl;
                cout << string(30, '-') << endl;
                cout << "Enter Account Number: ";
                getline(cin, accNum);
                cout << "Enter Customer Name: ";
                getline(cin, name);
                cout << "Enter Initial Balance: $";
                cin >> amount;
                cin.ignore();
                
                bank.addAccount(accNum, name, amount);
                break;
            }
            
            case 2: { // Display All Accounts
                bank.displayAllAccounts();
                break;
            }
            
            case 3: { // Search Account
                cout << "\nSEARCH ACCOUNT" << endl;
                cout << string(30, '-') << endl;
                cout << "Enter Account Number: ";
                getline(cin, accNum);
                
                bank.displayAccountDetails(accNum);
                break;
            }
            
            case 4: { // Deposit Money
                cout << "\nDEPOSIT MONEY" << endl;
                cout << string(30, '-') << endl;
                cout << "Enter Account Number: ";
                getline(cin, accNum);
                cout << "Enter Deposit Amount: $";
                cin >> amount;
                cin.ignore();
                
                bank.deposit(accNum, amount);
                break;
            }
            
            case 5: { // Withdraw Money
                cout << "\nWITHDRAW MONEY" << endl;
                cout << string(30, '-') << endl;
                cout << "Enter Account Number: ";
                getline(cin, accNum);
                cout << "Enter Withdrawal Amount: $";
                cin >> amount;
                cin.ignore();
                
                bank.withdraw(accNum, amount);
                break;
            }
            
            case 6: { // Delete Account
                cout << "\nDELETE ACCOUNT" << endl;
                cout << string(30, '-') << endl;
                cout << "Enter Account Number to Delete: ";
                getline(cin, accNum);
                
                char confirm;
                cout << "Are you sure you want to delete this account? (y/n): ";
                cin >> confirm;
                cin.ignore();
                
                if (confirm == 'y' || confirm == 'Y') {
                    bank.deleteAccount(accNum);
                } else {
                    cout << "Account deletion cancelled." << endl;
                }
                break;
            }
            
            case 7: { // Exit System
                cout << "\nThank you for using Bank Account Management System!" << endl;
                cout << "Goodbye!" << endl;
                break;
            }
        }
        
        if (choice != 7) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        
    } while (choice != 7);
    
    return 0;
}
