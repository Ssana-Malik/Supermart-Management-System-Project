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
BillNode* processedBillsHead = NULL;


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

// Print a single bill 
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
// Generate bill for a given customer pointer: copies their cart into a bill, enqueues it, and clears customer's cart
void generateBillForCustomer(Customer* cust){
    if(cust == NULL){
        cout << "Customer not found." << endl;
        return;
    }
    if(cust->cartHead == NULL){
        cout << "Customer cart is empty. Cannot generate bill." << endl;
        return;
    }

    // Calculate total and create bill node
    float total = 0.0f;
    CartItem* cIt = cust->cartHead;
    BillNode* bill = new BillNode(cust->custId, 0.0f);
    BillItem* lastBillItem = NULL;

    while(cIt){
        float subtotal = cIt->quantity * cIt->price;
        total += subtotal;
        BillItem* bItem = new BillItem(cIt->name, cIt->quantity, cIt->price);
        if(bill->itemsHead == NULL){
            bill->itemsHead = bItem;
            lastBillItem = bItem;
        } else {
            lastBillItem->next = bItem;
            lastBillItem = bItem;
        }
        cIt = cIt->next;
    }

    bill->total = total;

    // Enqueue the bill
    enqueueBill(bill);
    cout << "Bill generated and added to billing queue for Customer "<<endl << cust->custId << ".";

    // After generating bill, remove customer from customer list and free their cart items
    // Find and remove customer
    Customer* temp = customerHead;
    Customer* prev = NULL;
    while(temp != NULL && temp != cust){
        prev = temp;
        temp = temp->next;
    }
    if(temp != NULL){
        if(prev == NULL){
            customerHead = temp->next;
        } else {
            prev->next = temp->next;
        }
        // free cart items
        CartItem* ci = temp->cartHead;
        while(ci){
            CartItem* toDel = ci;
            ci = ci->next;
            delete toDel;
        }
        delete temp;
    }
}




// Display pending bills in the queue 
void displayPendingBills(){
    if(billFront == NULL){
        cout << "No pending bills in queue." << endl;
        return;
    }
    cout << "Pending Bills:"<<endl;
    BillNode* temp = billFront;
    while(temp){
        cout << "Customer ID: " << temp->customerId  << endl;
        temp = temp->next;
    }
}

// Process next bill in queue
void processNextBill(){
    BillNode* bill = dequeueBill();
    if(bill == NULL){
        cout << "No bills to process." << endl;
        return;
    }

    printBill(bill);

    // Save this bill into processed bills list
    bill->next = processedBillsHead;
    processedBillsHead = bill;

    // Do NOT delete items here (otherwise totals break)
}
// Calculate total sales by iteracting through billing queue
float calculateTotalSales(){
    float sum = 0.0f;

    // Add totals from pending bills
    BillNode* temp = billFront;
    while(temp != NULL){
        sum += temp->total;
        temp = temp->next;
    }

    // Add totals from processed bills
    BillNode* p = processedBillsHead;
    while(p != NULL){
        sum += p->total;
        p = p->next;
    }

    return sum;
}

// Show complete sales of the day with customer-wise detail
void showSalesOfTheDay() {
    cout << "\n====== TOTAL SALES OF THE DAY ======\n";

    BillNode* temp;

    // 1) First show pending bills in queue
    temp = billFront;
    cout << "\n--- Pending Bills ---\n";
    if(temp == NULL) cout << "No pending bills.\n";
    while(temp) {
        cout << "\nCustomer ID: " << temp->customerId << endl;
        BillItem* it = temp->itemsHead;
        while(it) {
            cout << "  " << it->name  
	       << " | Qty: " << it->quantity 
                 << " | Price: " << it->price 
                 << " | Subtotal: " << it->price * it->quantity << endl;
            it = it->next;
        }
        cout << "Total: " << temp->total << endl;
        temp = temp->next;
    }

    // 2) Show processed bills
    temp = processedBillsHead;
    cout << "\n--- Processed Bills ---\n";
    if(temp == NULL) cout << "No processed bills.\n";
    while(temp) {
        cout << "\nCustomer ID: " << temp->customerId << endl;
        BillItem* it = temp->itemsHead;
        while(it) {
            cout << "  Item:  " << it->name    << "   "
	       << " |    Qty:  " << it->quantity<< "   "
                 << " |    Price:  " << it->price   << "   " 
                 << " |    Subtotal:  " << it->price * it->quantity << endl;
            it = it->next;
        }
        cout << "Total: " << temp->total << endl;
        temp = temp->next;
    }

    cout << "\n=====================================\n";
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
                cout << "1. Generate Bill for Customer ID "<<endl;
                cout << "2. Process  Bill "<<endl;
                cout << "3. Display Pending Bills"<<endl;
                cout << "4. Calculate Total Sales"<<endl;
                cout << "5. Show total sales of the day"<<endl;
                cout << "6. Go Back"<<endl;
                cout << "Enter choice: ";
                cin >> choice;
                
              if(choice == 1){
                    int cid;
                    cout << "Enter Customer ID to generate bill: ";
                    cin >> cid;
                    Customer* c = findCustomer(cid);
                    generateBillForCustomer(c);
                } else if(choice == 2){
                    processNextBill();
                } else if(choice == 3){
                    displayPendingBills();
                } else if(choice == 4){
                    float total = calculateTotalSales();
                    cout << "Total sales (pending bills) = " << total << endl;
                } 
			  else if(choice == 6){
    showSalesOfTheDay();
}
else if(choice == 6){
                    break;
		           }  else{
                    cout << "Invalid option.";
                }

                cout << "Press any key to continue..."; 
                getch();
            }
            break;
            
    }
    return 0;
    }}





