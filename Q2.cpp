/* Assignment Question 2
   Jason Tan Jia Sheng | 242UC244KW | jason.tan.jia@student.mmu.edu.my
   Nelson Ng Yaohan    | 242UC2444H | nelson.ng.yaohan@student.mmu.edu.my
   Tan Park Zhong      | 242UC244TW | tan.park.zhong@student.mmu.edu.my
*/
#include <iostream>
#include <string>
using namespace std;

// Array-based Queue Class for shipping items
class Queue
{
private:
    int front, rear;
    int MAX_SIZE;
    string *items;

public:
    // Constructor
    Queue(int size = 100)
    {
        MAX_SIZE = size;
        items = new string[MAX_SIZE];
        front = -1;
        rear = -1;
    }

    // Destructor
    ~Queue()
    {
        delete[] items;
    }

    // Check if queue is empty
    bool isEmpty()
    {
        return (front == -1 && rear == -1);
    }

    // Check if queue is full
    bool isFull()
    {
        return ((rear + 1) % MAX_SIZE == front);
    }

    // Add item to queue (enqueue)
    void enqueue(string item)
    {
        if (isFull())
        {
            cout << "Error: Shipping queue is full. Cannot add more items.\n";
            return;
        }

        if (isEmpty())
        {
            front = 0;
            rear = 0;
        }
        else
        {
            rear = (rear + 1) % MAX_SIZE;
        }

        items[rear] = item;
    }

    // Remove item from queue (dequeue)
    string dequeue()
    {
        if (isEmpty())
        {
            return ""; // Return empty string for empty queue
        }

        string item = items[front];

        if (front == rear)
        {
            // Only one item in queue
            front = -1;
            rear = -1;
        }
        else
        {
            front = (front + 1) % MAX_SIZE;
        }

        return item;
    }

    // Peek at front item (next to ship)
    string peek()
    {
        if (isEmpty())
        {
            return ""; // Return empty string for empty queue
        }
        return items[front];
    }

    // Display all items in shipping queue
    void displayAll(){
        if(isEmpty()){
            cout << "Shipping queue is empty\n";
            return;
        }
    cout << "Items in shipping queue:\n";
    int i = front;
    while (true){
        cout << "- " << items[i] << endl;
        if (i == rear)
        break;
        i = (i+1) % MAX_SIZE;
    }
  }
};

// Array-based Stack Class handling incoming items

class Stack
{
private:
    int top;
    int MAX_SIZE;
    string *items;

public:
    // Constructor
    Stack(int size = 100)
    {
        MAX_SIZE = size;
        items = new string[MAX_SIZE];
        top = -1; // Empty Stack because we start counting from 0
    }

    // Destructor
    ~Stack()
    {
        delete[] items;
    }

    // Check if stack is empty
    bool isEmpty()
    {
        return (top == -1);
    }

    // Check if stack is full
    bool isFull()
    {
        return (top == MAX_SIZE - 1);
    }

    // Push item onto stack
    void push(string item)
    {
        if (isFull())
        {
            cout << "Error: Inventory is full. Cannot add items.\n";
            return;
        }
        items[++top] = item;
        cout << "Item \"" << item << "\" added to inventory.\n";
    }

    // Pop item from stack
    string pop()
    {
        if (isEmpty())
        {
            cout << "Error: No items in inventory to process.\n";
            return "";
        }
        return items[top--];
    }

    // Peek at top item (latest item)
    string peek()
    {
        if (isEmpty())
        {
            cout << "No incoming items\n";
            return "";
        }
        return items[top];
    }
    
    // Display all items in inventory
    void displayAll(){
        if(isEmpty()){
            cout << "Error: No items in inventory to process.\n";
            return;
        }
        cout << "All inventory items:\n";
        for(int i = top; i >=0; i--)
        {
            cout << "- " << items[i] << endl;
        }
    }
};

Queue shippingQueue; // Global shipping queue instance
Queue shippedItems(100); // To track shipped items

// Main program
int main()
{
    Stack inventory(100); // stack for incoming items
    int choice;
    string item;

    do
    {
        cout << "\n" << string(50, '=') << endl;
        cout << "     WAREHOUSE INVENTORY & SHIPPING SYSTEM" << endl;
        cout << string(50, '=') << endl;
        cout << "1. Add Incoming Item\n";
        cout << "2. Process Incoming Item\n";
        cout << "3. Ship Item\n";
        cout << "4. View Last Incoming Item\n";
        cout << "5. View Next Shipment\n";
        cout << "6. Show All Inventory Items\n";
        cout << "7. Show All Shipping Items\n";
        cout << "8. Show All Shipped Items\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        if (!(cin >> choice)) {
          cin.clear();            // clear error state
          cin.ignore(1000, '\n'); // removes bad input
          cout << "Invalid input. Please enter a number between 1 and 9." << endl;
          continue;               // restart loop
        }
        cin.ignore(1000, '\n'); 

        switch (choice)
        {
        case 1:
            cout << "Enter item name: ";
            getline(cin, item);
            inventory.push(item);
            break;

        case 2:
        {
            // Pop from stack (simulate processing)
            string processed = inventory.pop();
            if (processed != "")
                shippingQueue.enqueue(processed); // Add to shipping queue
            cout << "Processed \"" << processed
                 << "\" and added to shipping queue." << endl;

            break;
        }

        case 3:
        {
            string itemToShip = shippingQueue.dequeue();
            if (itemToShip != "")
            {
                cout << "Shipping item: " << itemToShip << endl;
                shippedItems.enqueue(itemToShip); // to store shipped history
            }
            else
            {
                cout << "No items to ship." << endl;
            }
            break;
        }

        case 4:
        {
            string last = inventory.peek();
            if (last != "")
                cout << "Last incoming item: " << last << endl;
            break;
        }

        case 5:
        {
            string next = shippingQueue.peek();
            if (next != "")
            {
                cout << "Next item to ship: " << next << endl;
            }
            else
            {
                cout << "No items in shipping queue." << endl;
            }
            break;
        }

        case 6:
            inventory.displayAll();         // Display all items in inventory
            break;

        case 7:
            shippingQueue.displayAll();     // Display all items in shipping queue
            break; 

        case 8:
            shippedItems.displayAll();      // Display all completed shipping
            break;

        case 9:
            cout << "Exiting..." << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 9);

    return 0;
}