#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string customerName;
    double accountBalance;
    
public:
    //Constructor with default parameters
    BankAccount(string accNum = "", string cusName = "", double accBal = 0.0) {
        accountNumber = accNum;
        customerName = cusName;
        accountBalance = accBal;
    }
    
    //Setter Methods
    void setAccountNumber(string accNum) {
        accountNumber = accNum;
    }
    
    void setCustomerName(string cusName) {
        customerName = cusName;
    }
    
    void setAccountBalance(double accBal) {
        accountBalance = accBal;
    }
    
    //Getter Methods
    string getAccountNumber() const {
        return accountNumber;
    }
    
    string getCustomerName() const {
        return customerName;
    }
    
    double getAccountBalance() const {
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
    void displayAmount() const {
        cout << left << setw(15) << accountNumber << setw(20) << customerName << fixed << setprecision(2) << "$" << accountBalance << endl;
    }
};

class BankAccountNode {
public:
    BankAccount account;
    BankAccountNode* next;
    
    BankAccountNode(const BankAccount& acc) {
        account = acc;
        next = nullptr;
    }
    
    ~BankAccountNode() {
        cout << "Account node for " << account.getAccountNumber() << " destroyed." << endl;
    }
};

class BankManagementSystem {
private:
    BankAccountNode* head;
    
public:
    BankManagementSystem() {
        head = nullptr;
        cout << "Bank Management System initialized." << endl;
    }
    
    ~BankManagementSystem() {
        cout << "\nCleaning up memory......" << endl;
        while(head != nullptr) {
            BankAccountNode* temp = head;
            head = head->next;
            delete temp;
        }
        cout << "Bank Management System destroyed." << endl;
    }
    
    bool addAccount(const string& accNum, const string& cusName, double initialBalance) {
        if(searchAccount(accNum) != nullptr) {
            cout << "Error: Account number " << accNum << " already exists!" << endl;
            return false;
        }
        
        if(initialBalance < 0) {
            cout << "Error: Initial balance cannot be negative!" << endl;
            return false;
        }
        
        BankAccount newAccount(accNum, cusName, initialBalance);
        BankAccountNode* newNode = new BankAccountNode(newAccount);
        
        newNode->next = head;
        head = newNode;
        
        cout << "Account " << accNum << " added successfully!" << endl;
        return true;
    }
    
    void displayAllAccounts(const string& accNum, const string& cusName, double accBal) const {
        if(head == nullptr) {
            cout << "No accounrs found in the system." << endl;
            return;
        }
        cout << "\n" << string(60, '=') << endl;
        cout << left << setw(20) << "Account Number" << setw(20) << "Customer Name" << "Account Balance" << endl;
        cout << string(60, '-') << endl;
        cout << left << setw(20) << accNum << setw(20) << cusName << accBal << endl;
    }
    
    BankAccountNode* searchAccount(const string& accNum) const {
        BankAccountNode* current = head;
        while(current != nullptr) {
            if(current->account.getAccountNumber() == accNum) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }
    
    bool deposit(const string& accNum, double amount) {
        BankAccountNode* accountNode = searchAccount(accNum);
        if(accountNode == nullptr) {
            cout << "Error: Account " << accNum << " not found!" << endl;
            return false;
        }
        
        if(accountNode->account.deposit(amount)) {
            cout << "Successfully deposited $" << fixed << setprecision(2) << amount << " to account " << accNum << endl;
            cout << "New balance: $" << accountNode->account.getAccountBalance() << endl;
            return true;
        } else {
            cout << "Error: Invalid deposit amount!" << endl;
            return false;
        }
    }
    
    bool withdraw(const string& accNum, double amount) {
        BankAccountNode* accountNode = searchAccount(accNum);
        if(accountNode == nullptr) {
            cout << "Error: Account " << accNum << " not found!" << endl;
            return false;
        }
        
        if(accountNode->account.withdraw(amount)) {
            cout << "Successfully withdrew $" << fixed << setprecision(2) << amount << " from account " << accNum << endl;
            cout << "New balance: $" << accountNode->account.getAccountBalance() << endl;
            return true;
        } else {
            cout << "Error: Insufficient balance or invalid amount!" << endl;
            return false;
        }
    }
    
    bool deleteAccount(const string& accNum) {
        if(head == nullptr) {
            cout << "Error: No accounts in the system!" << endl;
            return false;
        }
        
        if(head->account.getAccountNumber() == accNum) {
            BankAccountNode* temp = head;
            head = head->next;
            cout << "Account " << accNum << " deleted successfully" << endl;
            delete temp;
            return true;
        }
        
        BankAccountNode* current = head;
        while(current->next != nullptr && current->next->account.getAccountNumber() != accNum) {
            current = current->next;
        }
        
        if(current->next == nullptr) {
            cout << "Error: Account " << accNum << " not found!" << endl;
            return false;
        }
        
        BankAccountNode* temp = current->next;
        current->next = temp->next;
        cout << "Account " << accNum << " deleted successfully!" << endl;
        delete temp;  // Calls destructor
        return true;
    }
    
    void displayAccountDetails(const string& accNum) const {
        BankAccountNode* accountNode = searchAccount(accNum);
        if(accountNode != nullptr) {
            cout << "\nAccount Details:" << endl;
            cout << string(40, '-') << endl;
            cout << "Account Number: " << accountNode->account.getAccountNumber() << endl;
            cout << "Customer Name: " << accountNode->account.getCustomerName() << endl;
            cout << "Account Balance: $" << fixed << setprecision(2)
                 << accountNode->account.getAccountBalance() << endl;
            cout << string(40, '-') << endl;
        } else {
            cout << "Account " << accNum << " not found!" << endl;
        }
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
    BankManagementSystem bank;
    int choice;
    string accNum;
    string cusName;
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
                getline(cin, cusName);
                cout << "Enter Initial Balance: $";
                cin >> amount;
                cin.ignore();
                
                bank.addAccount(accNum, cusName, amount);
                break;
            }
            
            case 2: { // Display All Accounts
                bank.displayAllAccounts(const string& accNum, const string& cusName, double accBal);
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
