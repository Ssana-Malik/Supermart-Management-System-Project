#include<iostream>
#include<iomanip>
#include<conio.h>
using namespace std;

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
int Employee::id = 2001; // starting id for employees
void addEmployee(Employee*& head, string name, string role, int salary){
    // Createing new employee node dynamically
    Employee* emp = new Employee(name, role, salary);
    //If list is empty new employee becomes first node
    if(head == NULL){
        head = emp;
        cout<<"Added Successfully."<<endl<<endl;
        return;
    }
    //Otherwise traverse to the last node in the list
    Employee* temp = head;
    while(temp->next != NULL){
        temp = temp->next;
    }
    //Attach new employee at the end
    temp->next = emp;
    cout<<"Added Successfully."<<endl<<endl;
}
void deleteEmployee(Employee*& head, string name){
    //Check if list is empty
    if(head == NULL){
        cout<<"No Employee in the record."<<endl<<endl;
        return;
    }
    //Check if the employee to delete is the first one (head)
    if(head->emp_name == name){
        Employee* temp = head;             // store head
        cout<<"Deleting "<<head->emp_name<<" ....."<<endl;
        head = head->next;                 // move head forward
        delete temp;                        // delete old head
        cout<<"Deleted Successfully."<<endl<<endl;
        return;
    }
    //Traverse to find the employee just before the one we want to delete
    Employee* temp = head;
    while(temp->next != NULL && temp->next->emp_name != name){
        temp = temp->next;
    }
    //If we reached end not found
    if(temp->next == NULL){
        cout<<"Employee not found."<<endl<<endl;
        return;
    }
    //Delete the employee node
    Employee* del = temp->next;
    cout<<"Deleting "<<del->emp_name<<" ....."<<endl;
    temp->next = del->next;   // unlink the node
    delete del;               // free memory
    cout<<"Deleted Successfully."<<endl<<endl;
}
