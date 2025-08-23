/* Assignment Question 2
   Jason Tan Jia Sheng | 242UC244KW | jason.tan.jia@student.mmu.edu.my
   Nelson Ng Yaohan    | 242UC2444H | nelson.ng.yaohan@student.mmu.edu.my
   Tan Park Zhong      | 242UC244TW | tan.park.zhong@student.mmu.edu.my
*/
#include <iostream>
using namespace std;

// Array-based Stack Class handling incoming items

class Stack{
private:
    int top;
    int MAX_SIZE;
    string *items;

public:
   // Constructor
   Stack(int size = 100) {
    MAX_SIZE = size;
    items = new string[MAX_SIZE];
    top = -1;  // Empty Stack because we start counting from 0
   }

   // Destructor
   ~Stack(){
    delete[] items;
   }

   // Check if stack is empty
   bool isEmpty(){
    return (top == -1);
   }

   // Check if stack is full
   bool isFull(){
    return (top == MAX_SIZE - 1);
   }

   // Push item onto stack
   void push(string item) {
    if(isFull()) {
        cout << "Error: Inventory is full. Cannot add items.\n";
        return;
    }
     items[++top] = item;
     cout << "Item \"" << item << "\" added to inventory.\n";
  }

  // Pop item from stack
  string pop(){
    if (isEmpty()) {
        cout << "Error: No items in inventory to process.\n";
        return "";
    }
    return items[top--];
  }
  
  // Peek at top item (latest item)
  string peek() {
    if(isEmpty()){
        cout << "No incoming items\n";
        return "";
    }
    return items[top];
  }
};

// Main program
int main(){
    Stack inventory(100);   // stack for incoming items
    int choice;
    string item;

    do {
        cout << "\n1. Add Incoming Item\n";
        cout << "2. Process Incoming Item\n";
        cout << "3. Ship Item\n";
        cout << "4. View Last Incoming Item\n";
        cout << "5. View Next Shipment\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // to clear buffer for getline

        switch(choice) {
            case 1:
              cout << "Enter item name: ";
              getline(cin, item);
              inventory.push(item);
              break;
             
             
            case 2: {
                // Pop from stack (simulate processing)
                string processed = inventory.pop();
                if (processed != "")
                    cout << "Processed \"" << processed
                         << "\" and added to shipping queue." << endl;
                break;
            }

            case 3:
                cout << "Shipping item: (Queue not implemented yet)" << endl;          // Queue
                break;

            case 4: {
                string last = inventory.peek();
                if (last != "")
                    cout << "Last incoming item: " << last << endl;                   // Peek from stack (check latest item)
                break;
            }

            case 5:
                cout << "Next item to ship: (Queue not implemented yet)" << endl;     // Queue
                break;

            case 6:
                cout << "Exiting..." << endl;
                break;

            default:
                cout << "Invalid choice. Try again." << endl;  // If exceeds 6 it will show error
        }

    }  while (choice != 6); // Repeats menu as long the choice is not 6
   return 0;
