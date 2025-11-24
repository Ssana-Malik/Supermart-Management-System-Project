#include<iostream>
#include<iomanip>
#include <conio.h>

using namespace std;

//creating structure for items of billing section (Original items are not modified)
struct BillItem {
    string name;
    int quantity;
    float price;
    BillItem* next;

    BillItem(string n, int q, float p) {
        name = n;
        quantity = q;
        price = p;
        next = NULL;
    }
};

//BillNode stored in queue
struct BillNode {
    int customerId;
    BillItem* itemsHead; // linked list of purchased items
    float total;
    BillNode* next;

    BillNode(int cid, float t) {
        customerId = cid;
        total = t;
        itemsHead = NULL;
        next = NULL;
    }
};

// Queue pointers
BillNode* billFront = NULL;
BillNode* billRear = NULL;

// Enqueue a bill
void enqueueBill(BillNode* node){
    if(billRear == NULL){
        billFront = billRear = node;
    } else {
        billRear->next = node;
        billRear = node;
    }
}

// Dequeue a bill and return NULL if empty
BillNode* dequeueBill(){
    if(billFront == NULL) return NULL;
    BillNode* temp = billFront;
    billFront = billFront->next;
    if(billFront == NULL) billRear = NULL;
    temp->next = NULL;
    return temp;
}

// Print a single bill (receipt style)
void printBill(BillNode* bill){
    if(bill == NULL) return;
    cout << "========== SuperMart Receipt ==========" << endl;
    cout << "Customer ID: " << bill->customerId << endl;
    cout << left << setw(20) << "Item" << left << setw(10) << "Qty" << left << setw(10) << "Price" << left << setw(10) << "Subtotal" << endl;
    cout << "-----------------------------------------------" << endl;
    BillItem* it = bill->itemsHead;
    while(it){
        cout << left << setw(20) << it->name
             << left << setw(10) << it->quantity
             << left << setw(10) << it->price
             << left << setw(10) << (it->quantity * it->price) << endl;
        it = it->next;
    }
    cout << "-----------------------------------------------" << endl;
    cout << "Total: " << bill->total << endl;
    cout << "=========================================" << endl;
}

int main() {
    int main_choice, choice;

    while(true){
        system("cls");
        cout<<"WELCOME TO SUPERMART MANAGEMENT SYSTEM"<<endl<<endl;
        cout<<"******** MAIN MENU ********"<<endl<<endl;
        cout<<"1. Manage Employee"<<endl;
        cout<<"2. Manage Inventory"<<endl;
        cout<<"3. Manage Customer/Cart"<<endl;
        cout<<"4. Billing Section"<<endl;
        cout<<"5. Exit"<<endl<<endl;
        cout<<"Choose option: ";
        cin>>main_choice;

        switch(main_choice){

      
        // ************* BILLING SECTION MENU ************* 
        case 4:
            while(true){
                system("cls");
                cout << "******** Billing Section ********"<<endl;
                cout << "1. Generate Bill for Customer ID (enqueue)"<<endl;
                cout << "2. Process Next Bill (dequeue & print)"<<endl;
                cout << "3. Display Pending Bills"<<endl;
                cout << "4. Calculate Total Sales (pending)"<<endl;
                cout << "5. Go Back"<<endl;
                cout << "Enter choice: ";
                cin >> choice;
                
                if(choice == 1){
                   
                } else if(choice == 2){
                   
                } else if(choice == 3){
                   
                } else if(choice == 4){
                   
                } else if(choice == 5){
                    break;
                } else {
                    cout << "Invalid option.";
                }

                cout << "Press any key to continue..."; 
                getch();
            }
            break;

            
    }
    return 0;
}}

