#include<iostream>
#include<iomanip>
#include <conio.h>
#include<fstream>
using namespace std;

// ***** Structure of Employee *****
struct Employee {
    string emp_name;
    string emp_role;
    int emp_id;
    int emp_salary;
    Employee* next;
    static int id; //for auto id assigning

    Employee(string n, string r, int s) {
        emp_name = n;
        emp_role = r;
        emp_salary = s;
        emp_id = id++;
        next = NULL;
    }
};

// ***** Structure of Product *****
// Represents a single product in an inventory
struct Product{
    string pro_name;
    int pro_id;
    int pro_quantity;
    float pro_price;
    Product* next;
    static int id;

    Product(string n, int q, float p){
        pro_name = n;
        pro_quantity = q;
        pro_price = p;
        pro_id = id++;
        next = NULL;
    }
};

// ***** Structure of CartItem *****
// Represents a single item in a customer's cart.
struct CartItem{
    string name;
    int quantity;
    float price;
    CartItem* next;

    CartItem(string n, int q, float p){
        name = n;
        quantity = q;
        price = p;
        next = NULL;
    }
};


// ***** Structure of Customer *****
// Represents a customer with a unique ID and their cart items.
struct Customer{
    int custId;
    CartItem* cartHead;
    Customer* next;

    Customer(int id){
        custId = id;
        cartHead = NULL;
        next = NULL;
    }
};

// ***** Structure of Bill *****
struct BillItem {
    string name;
    int quantity;
    float price;
    BillItem* next;

    BillItem(string n, int q, float p){
        name = n;
        quantity = q;
        price = p;
        next = NULL;
    }
};

//BillNode stored in queue
struct BillNode{
    int customerId;
    BillItem* itemsHead; // linked list of purchased items
    float total;
    BillNode* next;

    BillNode(int cid, float t){
        customerId = cid;
        total = t;
        itemsHead = NULL;
        next = NULL;
    }
};

// ***** Global Head and Variable *****
int Employee::id = 2001;
int Product::id = 1001;

Employee* empHead = NULL;  		   // Global Head for Employee List
Product* head = NULL;          	  // inventory list head
Customer* customerHead = NULL;   // Head of the customer linked list
BillNode* billFront = NULL;       
BillNode* billRear = NULL;
BillNode* processedBillsHead = NULL;

int nextCustId = 1;             // Counter for assigning unique customer IDs

// ===================== Manage Employee =====================
// -------- FILE HANDLING FUNCTIONS --------
void saveEmployeesToFile(){
    ofstream file("employees.txt");
    Employee* temp = empHead;
    
    while(temp != NULL){
        file << temp->emp_id << endl;
        file << temp->emp_name << endl;
        file << temp->emp_role << endl;
        file << temp->emp_salary << endl;
        temp = temp->next;
    }
    file.close();
}

void loadEmployeesFromFile() {
    ifstream file("employees.txt");
	if(!file){
    	return;
	}

    string name, role;
    int id, salary;
    Employee::id = 2001; // reset static id

    while(file >> id){
        file.ignore(); // skip newline
        getline(file, name);
        getline(file, role);
        file >> salary;
        file.ignore();

        Employee* emp = new Employee(name, role, salary);
        emp->emp_id = id; // keep original id

        if(Employee::id <= id) Employee::id = id + 1;

        if(empHead == NULL){
            empHead = emp;
        } else {
            Employee* temp = empHead;
            while(temp->next != NULL) temp = temp->next;
            temp->next = emp;
        }
    }

    file.close();
}

// -------- EMPLOYEE OPERATIONS --------
void addEmployee(string name, string role, int salary){
    Employee* emp = new Employee(name, role, salary);

    if(empHead == NULL){
        empHead = emp;
    } else {
        Employee* temp = empHead;
        while(temp->next != NULL) temp = temp->next;
        temp->next = emp;
    }

    cout << "Added Successfully. Employee ID: " << emp->emp_id << endl << endl;
    saveEmployeesToFile();
}

void deleteEmployee(string name){
    if(empHead == NULL){
        cout << "No Employee in the record." << endl << endl;
        return;
    }

    if(empHead->emp_name == name){
        Employee* temp = empHead;
        cout << "Deleting " << empHead->emp_name << " ....." << endl;
        empHead = empHead->next;
        delete temp;
        cout << "Deleted Successfully." << endl << endl;
        saveEmployeesToFile();
        return;
    }

    Employee* temp = empHead;
    while(temp->next != NULL && temp->next->emp_name != name){
        temp = temp->next;
    }

    if(temp->next == NULL){
        cout << "Employee not found." << endl << endl;
        return;
    }

    Employee* del = temp->next;
    cout << "Deleting " << del->emp_name << " ....." << endl;
    temp->next = del->next;
    delete del;
    cout << "Deleted Successfully." << endl << endl;
    saveEmployeesToFile();
}

void updateEmployee(string name){
    if(empHead == NULL){
        cout << "No Employee in the record." << endl << endl;
        return;
    }

    Employee* temp = empHead;
    while(temp != NULL && temp->emp_name != name){
        temp = temp->next;
    }

    if(temp == NULL){
        cout << "Employee not found." << endl << endl;
        return;
    }

    cout << "Employee found." << endl << endl;

    string role;
    int salary;

    cin.ignore(1000, '\n'); // clear buffer
    cout << "Enter new Role: ";
    getline(cin, role);
    cout << "Enter new Salary: ";
    cin >> salary;
    cout << endl;

    temp->emp_role = role;
    temp->emp_salary = salary;

    cout << "Updated Successfully." << endl << endl;
    saveEmployeesToFile();
}

void displayEmployee(){
    if(empHead == NULL){
        cout << "No Employee in the record." << endl << endl;
        return;
    }

    cout << "List of Employees:" << endl << endl;
    cout << "===================================================================================" << endl;
    cout << left << setw(20) << "Employee Id";
    cout << left << setw(20) << "Name";
    cout << left << setw(20) << "Role";
    cout << left << setw(20) << "Salary";
    cout << endl;
    cout << "===================================================================================" << endl;

    Employee* temp = empHead;
    while(temp != NULL){
        cout << left << setw(20) << temp->emp_id;
        cout << left << setw(20) << temp->emp_name;
        cout << left << setw(20) << temp->emp_role;
        cout << left << setw(20) << temp->emp_salary;
        cout << endl;
        temp = temp->next;
    }
    cout << "===================================================================================" << endl;
}

// ===================== Manage Inventory =====================
void saveFile(Product* product){
	ofstream outFile("Inventory.txt",ios::app);           // append(app) add new things at the end of the file. Without earsing the prvious data
	
	if(!outFile){
		cout<<"Error: Could not open file."<<endl;
		return;
	}
	
	outFile<<product->pro_id<<"  ";
	outFile<<product->pro_name<<"  ";
	outFile<<product->pro_price<<"  ";
	outFile<<product->pro_quantity<<endl;
	outFile.close();
}

void rewriteFile(Product* head){
	ofstream outFile("Inventory.txt",ios::trunc);             //Truncate(trunc) Use for rewriting. It will rewrite the whole file according to the new contents
	
	if(!outFile){
		cout<<"Error: Could not open file."<<endl;
		return;
	}
	
	Product* temp = head;
	while(temp != NULL){
		outFile<<temp->pro_id<<"  ";
        outFile<<temp->pro_name<<"  ";
        outFile<<temp->pro_price<<"  ";
        outFile<<temp->pro_quantity<<endl;
        temp = temp->next;
	}
	
	outFile.close();
}

// Using the loadFile function to premanently stores the items in the file. 
void loadFile(Product*& head){
	ifstream outFile("Inventory.txt");
	
	if(!outFile){
		cout<<"Error: Could not open file."<<endl;
		return;
	}
	
	string name;
    int id, quantity;
    float price;

    Product::id = 1001;  
    
    while(outFile>>id>>name>>price>>quantity){      // Reads the info. The loop will continue until all the data is read
        Product* newPro = new Product(name, quantity, price);  // Creating new linked list from this read data
        newPro->pro_id = id;

        if(head == NULL){
		 	head = newPro;
		}
		
        else{
            Product* temp = head;
            while (temp->next != NULL){
				temp = temp->next;
			}
            temp->next = newPro;
        }

        if(id >= Product::id){
            Product::id = id + 1;
    	}
    }
    outFile.close();
}

void insertion(Product*& head,string n,int quan, float pr){
	Product* product = new Product(n,quan,pr);
	
	if(head == NULL){
		head = product;
		saveFile(product); 
		cout<<"Added Successfully."<<endl<<endl;
		return;
	}
	
	Product* temp = head;
	while(temp->next!=NULL){
		temp = temp->next;
	}
	temp->next = product;
	
	saveFile(product);
	cout<<"Added Successfully."<<endl<<endl;
}

void deletion(Product*& head,string name){
	if(head == NULL){
		cout<<"No product in the inventory."<<endl<<endl;
		return;
	}
	
	if(head->pro_name == name){
		Product* temp = head;
		cout<<"Deleting "<<head->pro_name<<" ....."<<endl;
		head = head->next;
		delete temp;
		cout<<"Deleted Successfully."<<endl<<endl;
		rewriteFile(head);
		return;
	}
	
	Product* temp = head;
    while(temp->next != NULL && temp->next->pro_name != name){
    	temp = temp->next;
	}
	
	if(temp->next == NULL){
		cout<<"Product not found"<<endl<<endl;
		return;
	}
	
	Product* del = temp->next;
	cout<<"Deleting "<<del->pro_name<<" ....."<<endl;
	temp->next = del->next;
	delete del;
	rewriteFile(head);
	cout<<"Deleted Successfully."<<endl<<endl;
}

void update(Product*& head, string name){
	if(head == NULL){
		cout<<"No product in the inventory."<<endl<<endl;
		return;
	}
	
	Product* temp = head;
	while(temp != NULL && temp->pro_name != name){
		temp = temp->next;
	}
	
	if(temp == NULL){
		cout<<"Product not found."<<endl<<endl;
		return;
	}
	
	cout<<"Product found."<<endl<<endl;
	cout<<"Enter new details below: "<<endl;
	
	string new_stat;
    float price;
    int quan;
    
    cout<<"Enter new Quantity: ";
    cin>>quan;
    
    cout<<"Enter new Price: ";
    cin>>price;
    cout<<endl<<endl;
    
    temp->pro_quantity = quan;
    temp->pro_price = price;
    
    cout<<"Updated Successfully."<<endl<<endl;
    rewriteFile(head);
}

void display(Product* head){
	if(head == NULL){
		cout<<"No product in the inventory."<<endl<<endl;
		return;
	}
	
	cout<<"List of product is follow: "<<endl<<endl;
	cout<<"==================================================================================="<<endl;
	cout<<left<<setw(20)<<"Product Id";
    cout<<left<<setw(20)<<"Name";
    cout<<left<<setw(20)<<"Price";
    cout<<left<<setw(20)<<"Qunatity";
	cout<<left<<endl;
	cout<<"==================================================================================="<<endl;
	
	Product* temp = head;
    while (temp != NULL) {
        cout<<left<<setw(20)<<temp->pro_id;
        cout<<left<<setw(20)<<temp->pro_name;
        cout<<left<<setw(20)<<temp->pro_price;
        cout<<left<<setw(20)<<temp->pro_quantity;
        cout<<left<<endl;
        temp = temp->next;
    }
    cout<<"==================================================================================="<<endl;
}

// ===================== Manage Customer =====================
// Creates a new customer, assigns a unique ID, and adds them to the list.
Customer* addCustomer(){
    Customer* newCust = new Customer(nextCustId++); // Post-increment: assign then increase
    
	if(customerHead == NULL){
        customerHead = newCust;
    }else{
        Customer* temp = customerHead;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newCust; 
    }
    
    cout << "New Customer created. Customer ID: " << newCust->custId << endl;
    return newCust; // Returns pointer for later access to their cart or data
}

// Finds a customer by ID in the customer list.
Customer* findCustomer(int id){
    Customer* temp = customerHead;
    while(temp != NULL){
        if(temp->custId == id){
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
	while (t != NULL && t->name != name){
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
void displayAllCarts(){
    if (customerHead == NULL){ 
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


// ===================== Manage Billing section ===================
// Enqueue a bill
void enqueueBill(BillNode* node){
    if(billRear == NULL){
        billFront = billRear = node;
    }else{
        billRear->next = node;
        billRear = node;
    }
}

// Dequeue a bill and return NULL if empty
BillNode* dequeueBill(){
    if(billFront == NULL){
    	return NULL;
	}
	
    BillNode* temp = billFront;
    billFront = billFront->next;
    if(billFront == NULL){
    	billRear = NULL;
	}
    temp->next = NULL;
    return temp;
}

// Print a single bill 
void printBill(BillNode* bill){
    if(bill == NULL){
    	return;
	}
	
    cout << "========== SuperMart Receipt ==========" << endl;
    cout << "Customer ID: " << bill->customerId << endl;
    cout << left << setw(20) << "Item" 
		 << left << setw(10) << "Qty" 
		 << left << setw(10) << "Price" 
		 << left << setw(10) << "Subtotal" << endl;
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
        }else{
            lastBillItem->next = bItem;
            lastBillItem = bItem;
        }
        cIt = cIt->next;
    }

    bill->total = total;

    // Enqueue the bill
    enqueueBill(bill);
    cout << "Bill generated and added to billing queue for Customer " << cust->custId << "."<<endl;

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
        }else{
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
        while(it){
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
    if(temp == NULL){
    	cout << "No processed bills.\n";
	}
	
    while(temp){
        cout << "\nCustomer ID: " << temp->customerId << endl;
        BillItem* it = temp->itemsHead;
        cout<< "Item             Quantity     Price      Total"<<endl;
        while(it){
    		cout << left << setw(20) << it->name        // Item name column (20 chars)
         		 << left << setw(10) << it->quantity    // Quantity column (10 chars)
         		 << left << setw(10) << it->price       // Price column (10 chars)
         		 << left << setw(15) << (it->quantity * it->price)  // Subtotal
         		 << endl;

    		it = it->next;
		}

        cout << "Total: " << temp->total << endl;
        temp = temp->next;
    }

    cout << "\n=====================================\n";
}

// ================================================================
//                        MAIN FUNCTION
// ================================================================
int main(){
    int main_choice, choice;
    loadEmployeesFromFile(); // load employees at start
    Product* head = NULL;
	loadFile(head);
	string name, role;
    int salary;
	
    while(true){
        system("cls");
        cout<<"WELCOME TO SUPERMART MANAGEMENT SYSTEM\n\n";
        cout<<"1. Manage Employee\n";
        cout<<"2. Manage Inventory\n";
        cout<<"3. Manage Customer/Cart\n";
        cout<<"4. Billing Section\n";
        cout<<"5. Exit\n\n";
        cout<<"Enter option: ";
        cin>>main_choice;

        switch(main_choice){

		// ---------------- MANAGE EMPLOYEE ----------------
		case 1:
    		while(true){
        		system("cls");
        		cout<<"______ Manage Employee ______\n\n";
        		cout<<"1. Add Employee\n";
        		cout<<"2. Delete Employee\n";
        		cout<<"3. Update Employee\n";
        		cout<<"4. Display All Employees\n";
        		cout<<"5. Go Back\n\n";
        		cout<<"Enter choice: ";
        		cin>>choice;

        		string name, role;
        		int salary;

        		switch(choice){
            	 case 1: {
                    cin.ignore(1000, '\n'); // clear buffer
                    cout << "Enter Employee Name: ";
                    getline(cin, name);
                	cout << "Enter Employee Role: ";
                    getline(cin, role);
                    cout << "Enter Employee Salary: ";
                	cin >> salary;
                 	addEmployee(name, role, salary);
                    break;
                }
                case 2:
                    cin.ignore(1000, '\n'); // clear buffer
                    cout << "Enter Employee Name to Delete: ";
             		getline(cin, name);
                    deleteEmployee(name);
                    break;
                
				case 3:
                    cin.ignore(1000, '\n'); // clear buffer
                	cout << "Enter Employee Name to Update: ";
    				getline(cin, name);
                    updateEmployee(name);
                	break;
                
				case 4:
                    displayEmployee();
                    break;
            	
				case 5:
                	break;

            	default:
                	cout<<"Invalid option.\n";
        		}

        		if(choice == 5){
        			break;
				}

        		cout<<"Press any key to continue...";
        		getch();	
    		}	
    	break;
    	
 		// ---------------- MANAGE INVENTORY ----------------
        case 2:
            while(true){
                system("cls");
                cout << "______ Manage Inventory ______\n";
                cout << "\n1. Add Items"<<endl;
				cout<<"2. Delete Items"<<endl;
				cout<<"3. Update Items"<<endl;
				cout<<"4. Display Items"<<endl;
				cout<<"5. Go Back"<<endl<<endl;
                cout << "Enter choice: "; 
				cin>>choice;
				
				string p_name; 
				int p_quantity; 
				float p_price;
				
                switch(choice){
                    case 1:
                        cout<<"Enter product name: "; 
						cin>>p_name;
                        cout<<"Enter quantity: "; 
						cin>>p_quantity;
                        cout<<"Enter price: "; 
						cin>>p_price;
                        insertion(head, p_name, p_quantity, p_price); 
						break;
						
                    case 2:
                        cout<<"Enter product name to delete: "; 
						cin>>p_name;
                        deletion(head, p_name); 
						break;
						
                    case 3:
                        cout<<"Enter product name to update: "; 
						cin>>p_name;
                        update(head, p_name); 
						break;
						
                    case 4:
                        display(head); 
						break;
						
                    case 5: 
						break;
					
                    default: 
						cout<<"Invalid option.\n";
                }
                
                if(choice==5){
					break;
				}
				
                cout << "\nPress any key to continue..."; 
				getch();
            }   
        break;

        // ---------------- MANAGE CUSTOMER / CART ----------------
        case 3:
            while (true) {
                system("cls");
               	cout << "______ Manage Customers / Carts ______\n";
               	cout << "1. Add New Customer" <<endl;
				cout << "2. Add Item to Customer Cart" <<endl;
				cout << "3. Remove Item from Cart" <<endl;
               	cout << "4. Update Item in Cart" <<endl;
				cout << "5. Display All Customer Carts" <<endl;
				cout << "6. Go Back\n\n";
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
        
		// ---------------- MANAGE bills ---------------- 
            
        case 4:
            while(true){
                system("cls");
                cout << "******** Billing Section ********"<<endl;
                cout << "1. Generate Bill for Customer "<<endl;
                cout << "2. Process Next Bill "<<endl;
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
                }else if(choice == 2){
                    processNextBill();
                }else if(choice == 3){
                    displayPendingBills();
                }else if(choice == 4){
                    float total = calculateTotalSales();
                    cout << "Total sales = " << total << endl;
                }else if(choice == 5){
                            showSalesOfTheDay();
                }else if(choice == 6){
                    break;
		        }else{
                    cout << "Invalid option.";
                }

                cout << "Press any key to continue..."; 
                getch();
            }
        break;
        
        // ---------------- EXIT ----------------
        case 5:
            cout << "Thank you for using the system!\n";
            return 0;

        default:
            cout << "Invalid option.\n";
        }
        
        if(main_choice == 5){
        	break;
		}     
    }
    
    return 0;
}
