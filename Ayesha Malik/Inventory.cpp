#include<iostream>
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
		cout<<"Invalid Position."<<endl<<endl;
		return;
	}
	
	Product* del = temp->next;
	cout<<"Deleting "<<del->pro_name<<" ....."<<endl;
	temp->next = del->next;
	delete del;
	cout<<"Deleted Successfully."<<endl<<endl;
}

int main{
}

