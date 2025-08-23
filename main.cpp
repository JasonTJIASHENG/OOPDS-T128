/* Assignment Question 1
   Jason Tan Jia Sheng | 242UC244KW | jason.tan.jia@student.mmu.edu.my
   Nelson Ng Yaohan | 242UC2444H | nelson.ng.yaohan@student.mmu.edu.my
   Tan Park Zhong | 242UC244TW | tan.park.zhong@student.mmu.edu.my
*/

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// Bank Account class representing individual account data
class BankAccount {
private:
    string accountNumber;
    string customerName;
    double accountBalance;
    
public:
    //Constructor with default parameters(settle everything in 1 constructor)
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
    
    //Getter Methods (Encapsulation)
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
        cout << left << setw(20) << accountNumber << setw(20) << customerName << fixed << setprecision(2) << "$" << accountBalance << endl;
    }
};

// Node class for singly linked list
class BankAccountNode {
public:
    BankAccount account; //Account Data
    BankAccountNode* next; //Pointer to the next node
    
    //Constructor
    BankAccountNode(const BankAccount& acc) {
        account = acc;
        next = nullptr;
    }
    
    //Destructor
    ~BankAccountNode() {
        cout << "Account node for " << account.getAccountNumber() << " destroyed." << endl;
    }
};

// Bank Management System class using singly linked list
class BankManagementSystem {
private:
    BankAccountNode* head; //Head pointer to the next linked list
    
public:
    // This constructor is to initialize the empty list
    BankManagementSystem() {
        head = nullptr;
        cout << "Bank Management System initialized." << endl;
    }
    
    // This destructor is to clean up all the nodes
    ~BankManagementSystem() {
        cout << "\nCleaning up memory......" << endl;
        while(head != nullptr) {
            BankAccountNode* temp = head;
            head = head->next;
            delete temp; // Calls node destructor
        }
        cout << "Bank Management System destroyed." << endl;
    }
    
    // Method 1: Add a new account (prevent duplicates)
    bool createAccount(const string& accNum, const string& cusName, double initialBalance) {
        // Check for duplicate account number
        if(searchAccount(accNum) != nullptr) {
            cout << "Error: Account number " << accNum << " already exists!" << endl;
            return false;
        }
        
        // Validate initial balance
        if(initialBalance < 0) {
            cout << "Error: Initial balance cannot be negative!" << endl;
            return false;
        }
        
        // Create new account and node
        BankAccount newAccount(accNum, cusName, initialBalance);
        BankAccountNode* newNode = new BankAccountNode(newAccount);
        
        // Insert at the beginning of the list
        newNode->next = head;
        head = newNode;
        
        cout << "Account " << accNum << " created successfully!" << endl;
        return true;
    }
    
    // Method 2: Display all accounts
    void displayAllAccounts() const {
        if(head == nullptr) {
            cout << "No accounrs found in the system." << endl;
            return;
        }
        cout << "\n" << string(60, '=') << endl;
        cout << left << setw(20) << "Account Number" << setw(20) << "Customer Name" << "Account Balance" << endl;
        cout << string(60, '-') << endl;
        
        BankAccountNode* current = head;
        while(current != nullptr) {
            current->account.displayAmount();
            current = current->next;
        }
        cout << string(60, '=') << endl;
    }
    
    // Method 3: Search by account number
    BankAccountNode* searchAccount(const string& accNum) const {
        BankAccountNode* current = head;
        while(current != nullptr) {
            if(current->account.getAccountNumber() == accNum) {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Account not found
    }
    
    // Method 4: Deposit money
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
    
    // Method 5: Withdraw money
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
    
    // Method 6: Delete an account
    bool deleteAccount(const string& accNum) {
        if(head == nullptr) {
            cout << "Error: No accounts in the system!" << endl;
            return false;
        }
        
        // If the account to delete is the first node
        if(head->account.getAccountNumber() == accNum) {
            BankAccountNode* temp = head;
            head = head->next;
            cout << "Account " << accNum << " deleted successfully" << endl;
            delete temp;
            return true;
        }
        
        // Search for the account to delete
        BankAccountNode* current = head;
        while(current->next != nullptr && current->next->account.getAccountNumber() != accNum) {
            current = current->next;
        }
        
        if(current->next == nullptr) {
            cout << "Error: Account " << accNum << " not found!" << endl;
            return false;
        }
        
        // Delete the node
        BankAccountNode* temp = current->next;
        current->next = temp->next;
        cout << "Account " << accNum << " deleted successfully!" << endl;
        delete temp;  // Calls destructor
        return true;
    }
    
    // Method 7: Send Feedback or Report Issue
    void sendFeedback() const {
        cout << "\n" << string(50, '=') << endl;
        cout << "CUSTOMER FEEDBACK & ISSUE REPORTING SYSTEM" << endl;
        cout << string(50, '=') << endl;
        
        string accNum, name, feedbackType, message;
        
        // Get customer information
        cout << "Enter your Account Number (or press Enter to skip): ";
        getline(cin, accNum);
        
        if (!accNum.empty()) {
            // Verify if account exists
            BankAccountNode* accountNode = searchAccount(accNum);
            if (accountNode != nullptr) {
                name = accountNode->account.getCustomerName();
                cout << "Welcome, " << name << "!" << endl;
            } else {
                cout << "Account not found, but you can still submit feedback as a guest." << endl;
                cout << "Enter your Name: ";
                getline(cin, name);
            }
        } else {
            cout << "Enter your Name: ";
            getline(cin, name);
        }
        
        // Select feedback type
        cout << "\nSelect Feedback Type:" << endl;
        cout << "1. General Feedback" << endl;
        cout << "2. Service Complaint" << endl;
        cout << "3. Technical Issue" << endl;
        cout << "4. Feature Request" << endl;
        cout << "5. Account Issue" << endl;
        cout << "Enter your choice (1-5): ";
        
        int choice;
        while (!(cin >> choice) || choice < 1 || choice > 5) {
            cout << "Invalid input! Please enter a number between 1-5: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        cin.ignore(); // Clear newline
        
        // Map choice to feedback type
        switch (choice) {
            case 1: feedbackType = "General Feedback"; break;
            case 2: feedbackType = "Service Complaint"; break;
            case 3: feedbackType = "Technical Issue"; break;
            case 4: feedbackType = "Feature Request"; break;
            case 5: feedbackType = "Account Issue"; break;
        }
        
        // Get feedback message
        cout << "\nEnter your " << feedbackType << " (max 500 characters):" << endl;
        cout << "Message: ";
        getline(cin, message);
        
        if (message.empty()) {
            cout << "Error: Feedback message cannot be empty!" << endl;
            return;
        }
        
        // Display feedback summary
        cout << "\n" << string(50, '=') << endl;
        cout << "FEEDBACK SUBMITTED SUCCESSFULLY!" << endl;
        cout << string(50, '=') << endl;
        cout << "Feedback ID: FB" << rand() % 10000 + 1000 << endl;
        cout << "Date & Time: " << __DATE__ << " " << __TIME__ << endl;
        cout << "Customer: " << (name.empty() ? "Anonymous" : name) << endl;
        if (!accNum.empty()) {
            cout << "Account Number: " << accNum << endl;
        }
        cout << "Type: " << feedbackType << endl;
        cout << "Message: " << message << endl;
        cout << string(50, '=') << endl;
        cout << "\nThank you for your feedback!" << endl;
        cout << "Our customer service team will review your " << feedbackType << endl;
        cout << "and respond within 24-48 hours if a response is required." << endl;
        cout << "\nFor urgent issues, please call our hotline: 1-800-BANK-HELP" << endl;
    }
    
    // Display account details by account number
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

// Menu-driven interface functions
void displayMenu() {
    cout << "\n" << string(50, '=') << endl;
    cout << "BANK MANAGEMENT SYSTEM" << endl;
    cout << string(50, '=') << endl;
    cout << "1. Create New Account" << endl;
    cout << "2. Display All Accounts" << endl;
    cout << "3. Search Account By Account Number" << endl;
    cout << "4. Deposit Money" << endl;
    cout << "5. Withdraw Money" << endl;
    cout << "6. Delete Account" << endl;
    cout << "7. Send Feedback/Report Issue" << endl;
    cout << "8. Exit System" << endl;
    cout << "Enter your choice (1-8): ";
}

//Input validation
int getValidChoice() {
    int choice;
    while (!(cin >> choice) || choice < 1 || choice > 8) {
        cout << "Invalid input! Please enter a number between 1-8: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }
    cin.ignore(); // Clear the newline character
    return choice;
}

// Main function demonstrating the system
int main() {
    BankManagementSystem bank; //Create bank management system
    int choice;
    string accNum;
    string cusName;
    double amount;
    
    cout << "Welcome to the Bank Account Management System!" << endl;
    
    do {
        displayMenu();
        choice = getValidChoice();
        
        switch (choice) {
            case 1: { // Create New Account
                cout << "\nCREATE NEW ACCOUNT" << endl;
                cout << string(30, '-') << endl;
                cout << "Enter Account Number: ";
                getline(cin, accNum);
                cout << "Enter Customer Name: ";
                getline(cin, cusName);
                cout << "Enter Initial Balance: $";
                cin >> amount;
                cin.ignore();
                
                bank.createAccount(accNum, cusName, amount);
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
            
            case 7: { //Send Feedback/Report Issue
                bank.sendFeedback();
                break;
            }
            
            case 8: { // Exit System
                cout << "\nThank you for using Bank Account Management System!" << endl;
                cout << "See You Next Time!" << endl;
                cout << "Goodbye!" << endl;
                break;
            }
        }
        
        if (choice != 8) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
        
    } while (choice != 8);
    
    return 0; // Destructor will be automatically called here
