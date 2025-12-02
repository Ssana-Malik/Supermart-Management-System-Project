#include <iostream>
#include<iomanip>
using namespace std;

// ***** Structure of Product *****
// Represents a single product in an inventory
struct Product {
    string pro_name;
    int pro_id;
    int pro_quantity;
    float pro_price;
    Product* next;
    static int id;

    Product(string n, int q, float p) {
        pro_name = n;
        pro_quantity = q;
        pro_price = p;
        pro_id = id++;
        next = NULL;
    }
};
int Product::id = 1001;

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
Product* head = NULL;          	  // inventory list head
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

// ===================== Find Product in Inventory =====================
Product* findProduct(Product* head, string name){
	Product* temp = head;
	while(temp != NULL){
		if(temp->pro_name == name){
			return temp;
		}
		temp = temp->next;
	}
	return NULL;
}

// ===================== Manage Customer's Cart =====================

// Allows a customer to add products from inventory to their cart
void addToCart(Product*& inventoryHead, Customer*& cust){
	string name;
	int qty;
	while(true){
		cout << "\nEnter product name to add (or '0' to stop): ";
		cin >> name;
		if(name == "0"){
			break;
		}
		
		Product* prod = findProduct(inventoryHead, name);
		if(prod == NULL){
			cout<<"Product not found in inventory.\n";
			continue;
		}
		
		cout<<"Enter quantity: ";
		cin >> qty;
		if(prod->pro_quantity == 0){
			cout<<"Sorry, " << name << " is currently out of stock.\n";
			continue;
		}
		
		if(qty > prod->pro_quantity){
			cout << "Only " << prod->pro_quantity << " available. Do you want to add them? (y/n): ";
			char choice;
			cin >> choice;
			if(choice == 'y' || choice == 'Y'){
				qty = prod->pro_quantity;
			}else{
				continue;
			}	
		}
		
		prod->pro_quantity -= qty;
		CartItem* newItem = new CartItem(prod->pro_name, qty, prod->pro_price);
		if(cust->cartHead == NULL){
			cust->cartHead = newItem;
		}else{
			CartItem* temp = cust->cartHead;
			while(temp->next != NULL){
				temp = temp->next;
			}
			temp->next = newItem; 
		}
		
		cout << "Added to cart for Customer ID " << cust->custId << "!\n";
	}
}

// Removes an item from the customer's cart and updates inventory
void removeFromCart(Product*& inventoryHead, Customer*& cust){
	if(cust->cartHead == NULL){
		cout<<"Cart empty.\n";
		return;
	}
	
	string name;
	cout<<"Enter item to remove: ";
	cin >> name;
	
	CartItem* t = cust->cartHead;
	CartItem* p = NULL;
	
	while(t != NULL && t->name != name){
		p = t;
		t = t->next;
	}
	
	if(t == NULL){
		cout<<"Item not found.\n";
		return;
	}
	
	//add back to inventory
	Product* prod = findProduct(inventoryHead, name);
		if(prod != NULL){
			prod->pro_quantity += t->quantity;
		}
	
	// Remove item from cart
	if(p == NULL){
		cust->cartHead = t->next;
	}else{
		p->next = t->next;
	}
	
	delete t;
	cout << "Item removed from cart of Customer " << cust->custId << ".\n";
	
	// if cart is now empty, remove customer as well
	if(cust->cartHead == NULL){
        cout << "Cart is now empty. Removing Customer ID " << cust->custId << "...\n";
    
    // Find and remove the customer from the linked list
        Customer* temp = customerHead;
        Customer* prev = NULL;
        while (temp != NULL && temp != cust) {
            prev = temp;
            temp = temp->next;
        }
        
        if (temp != NULL) {
        	if(prev == NULL){      // head customer
        		customerHead = temp->next;
			}else{
				prev->next = temp->next;
			}
			
			delete temp;
        	cout << "Customer removed successfully.\n";
        }
    }
}

// Updates the quantity of an item in a customer's cart and adjusts inventory
void updateCart(Product*& inventoryHead, Customer*& cust){
	if(cust->cartHead == NULL){
		cout<<"Cart empty.\n";
		return;
	}
	
	string name;
	cout<<"Enter item to update: ";
	cin >> name;
	
	CartItem* t = cust->cartHead;
	while (t && t->name != name){
		t = t->next;
	}
	
	if(t == NULL){
		cout<<"Item not found.\n"; 
		return; 
	}
	
    int newQty; 
	cout<<"Enter new quantity: "; 
	cin >> newQty;
	
    Product* prod = findProduct(inventoryHead, name);
    if (prod == NULL){
		cout << "Product not found in inventory.\n";
		return; 
	}
	
    int diff = newQty - t->quantity;
    
    if(diff > 0){
    	if(diff > prod->pro_quantity){	
    	cout << "Only " << prod->pro_quantity << " more available. Take them? (y/n): ";
    	char c; 
		cin >> c;
	
		if(c == 'y' || c == 'Y'){
			diff = prod->pro_quantity;
		}else{
			return;
    	}
	}
	
	prod->pro_quantity -= diff;
	
	}else if(diff < 0){
		prod->pro_quantity += (-diff);
	}
	
	t->quantity = newQty;
    cout << "Cart updated for Customer " << cust->custId << ".\n";
}

// Displays all customers carts with their items, quantities, and prices
void displayAllCarts() {
    if (customerHead == NULL) { 
        cout << "No customers yet.\n"; 
        return; 
    }
    
    Customer* c = customerHead;
    bool anyDisplayed = false; // to check if at least one non-empty cart exists
	
	while(c){
		
		// skip customers whose cart is empty
        if(c->cartHead != NULL){
            anyDisplayed = true;
            cout << "\n========= Customer ID: " << c->custId << " =========\n";
            cout << left << setw(20) << "Item"
                 << left << setw(10) << "Qty"
                 << left << setw(10) << "Price" << endl;
            cout << "-------------------------------------\n";

            CartItem* it = c->cartHead;
            while(it){
                cout << left << setw(20) << it->name
                     << left << setw(10) << it->quantity
                     << left << setw(10) << it->price << endl;
                it = it->next;
            }

            cout << "-------------------------------------\n";
        }
        c = c->next;
    }

    // if no non-empty cart was found
    if(!anyDisplayed){
        cout << "\nNo customers with items in their carts.\n";
	}
}

//                        MAIN FUNCTION
int main() {
    int main_choice, choice;

    while(true){
        system("cls");
        cout<<"WELCOME TO SUPERMART MANAGEMENT SYSTEM\n\n";
        cout<<"******** MAIN MENU ********\n";
        cout<<"\n1. Manage Employee"<<endl;
        cout<<"2. Manage Inventory"<<endl;
        cout<<"3. Manage Customer/Cart"<<endl;
        cout<<"4. Billing Section"<<endl;
        cout<<"5. Exit"<<endl<<endl;
        cout<<"Choose option: ";
        cin>>main_choice;

        switch(main_choice){

		// ---------------- MANAGE CUSTOMER / CART ----------------
        case 3:
            while (true) {
                system("cls");
                cout << "______ Manage Customers / Carts ______\n";
                cout << "1. Add New Customer\n2. Add Item to Customer Cart\n3. Remove Item from Cart\n";
                cout << "4. Update Item in Cart\n5. Display All Customer Carts\n6. Go Back\n\n";
                cout << "Enter choice: "; 
				cin >> choice;

                int id; 
				Customer* cust;
				
                switch(choice){
                    case 1:
                        addCustomer(); 
						break;
						
                    case 2:
                        cout << "Enter Customer ID: "; 
						cin >> id;
                        cust = findCustomer(id);
                        if(cust != NULL){
							addToCart(head, cust); 
						}else{
							cout << "Customer not found.\n";
						}
                        break;
                        
                    case 3:
                        cout << "Enter Customer ID: "; 
						cin >> id;
                        cust = findCustomer(id);
                        if(cust != NULL){
							removeFromCart(head, cust); 
						}else{
							cout << "Customer not found.\n";
						}
                        break;
                        
                    case 4:
                        cout << "Enter Customer ID: "; 
						cin >> id;
                        cust = findCustomer(id);
                        if(cust != NULL){
							updateCart(head, cust); 
						}else{
							cout << "Customer not found.\n";
						}
                        break;
                        
                    case 5:
                        displayAllCarts(); 
						break;
						
                    case 6: 
                    	break;
                    	
                    default: 
					cout << "Invalid option.\n";
                }
                
                if(choice==6){
					break;
				}
				
                cout << "\nPress any key to continue..."; 
				getch();
            }
            break;

        	default:
            	cout << "Invalid option.\n";
        	}
		
    }
    return 0;
}



