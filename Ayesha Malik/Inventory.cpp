#include<iostream>
#include <iomanip>
#include<conio.h>

using namespace std;

struct Product{
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

void insertion(Product*& head,string n,int quan, float pr){
	Product* product = new Product(n,quan,pr);
	
	if(head == NULL){
		head = product;
		return;
	}
	Product* temp = head;
	while(temp->next!=NULL){
		temp = temp->next;
	}
	temp->next = product;
	
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
		return;
	}
	
	Product* temp = head;
    while(temp->next != NULL && temp->next->pro_name != name){
    	temp = temp->next;
	}
	
	if(temp->next == NULL){
		cout<<"Product not found."<<endl<<endl;
		return;
	}
	
	Product* del = temp->next;
	cout<<"Deleting "<<del->pro_name<<" ....."<<endl;
	temp->next = del->next;
	delete del;
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
int main{
	Product* head = NULL;
	int main_choice,choice;
	string p_name;
	int p_quantity;
	float p_price;
	
	while(true){
		system("cls");
		cout<<"WELCOME TO SUPERMART MANAGEMNET SYSTEM"<<endl<<endl;
		cout<<"***** MENU *****"<<endl;
		cout<<"\n1. Manage Employee"<<endl;
		cout<<"2. Manage Inventory"<<endl;
		cout<<"3. Manage Customer"<<endl;
		cout<<"4. Billing Section"<<endl;
		cout<<"5. Exit"<<endl<<endl;
		
		cout<<"Choose from the above options: ";
		cin>>main_choice;
		
		switch(main_choice){
			
			case 2:
				while(true){
					system("cls");
					cout<<"______ Manage Inventory ______"<<endl<<endl;
					cout<<"***** MENU *****"<<endl;
					cout<<"\n1. Add Items"<<endl;
					cout<<"2. Delete Items"<<endl;
					cout<<"3. Update Items"<<endl;
					cout<<"4. Display All Items"<<endl;
					cout<<"5. Go back"<<endl<<endl;
		
					cout<<"Choose from the above options: ";
					cin>>choice;
		
				switch(choice){
					case 1:
						cout<<"Enter name of product: ";
						cin>>p_name;
						cout<<"Enter qunatity of product: ";
						cin>>p_quantity;
						cout<<"Enter price of product: ";
						cin>>p_price;
						insertion(head,p_name,p_quantity,p_price);
						break;
				
					case 2:
						cout<<"Enter name of product you want to delete: ";
						cin>>p_name;
						deletion(head,p_name);
						break;
			
					case 3:
						cout<<"Enter name of product you want to update: ";
						cin>>p_name;
						update(head,p_name);
						break;
				
					case 4:
						display(head);
						break;		
				
					case 5:
						break;	
				
					default:
						cout<<"Incorrect Option."<<endl;
				}
				
				if(choice==5){
					break;
				}
				cout<<"Press any key to continue "<<endl;
				getch();
		}
		break;
	}
}
	return 0;
}
