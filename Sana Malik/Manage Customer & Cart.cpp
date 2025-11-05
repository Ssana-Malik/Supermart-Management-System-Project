#include <iostream>
using namespace std;

// ***** Structure of CartItem *****
// Represents a single item in a customer's cart.
struct CartItem {
    string name;
    int quantity;
    float price;
    CartItem* next;

    CartItem(string n, int q, float p) {
        name = n;
        quantity = q;
        price = p;
        next = NULL;
    }
};

// ***** Structure of Customer *****
// Represents a customer with a unique ID and their cart items.
struct Customer {
    int custId;
    CartItem* cartHead;
    Customer* next;

    Customer(int id) {
        custId = id;
        cartHead = NULL;
        next = NULL;
    }
};

// ***** Global Head and Variable *****
// Points to the first customer in the list and tracks the next customer ID.
Customer* customerHead = NULL;   // Head of the customer linked list
int nextCustId = 1;              // Counter for assigning unique customer IDs


// ===================== Manage Customer =====================

// Creates a new customer, assigns a unique ID, and adds them to the list.
Customer* addCustomer() {
    Customer* newCust = new Customer(nextCustId++); // Post-increment: assign then increase
    if (customerHead == NULL) {
        customerHead = newCust;
    } else {
        Customer* temp = customerHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newCust; 
    }
    cout << "New Customer created. Customer ID: " << newCust->custId << endl;
    return newCust; // Returns pointer for later access to their cart or data
}

// Finds a customer by ID in the customer list.
Customer* findCustomer(int id) {
    Customer* temp = customerHead;
    while (temp != NULL) {
        if (temp->custId == id) {
            return temp;
        }
        temp = temp->next; 
    }
    return NULL;
}

