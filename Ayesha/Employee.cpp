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
// Function to update an employee's role and salary using their name
void updateEmployee(Employee*& head, string name) {
    // If the list is empty, there is nothing to update
    if (head == NULL) {
        cout << "No Employee in the record." << endl << endl;
        return;
    }
    // Search for the employee by name
    Employee* temp = head;
    while (temp != NULL && temp->emp_name != name) {
        temp = temp->next;
    }
    // If employee with given name is not found
    if (temp == NULL) {
        cout << "Employee not found." << endl << endl;
        return;
    }
    // Employee found
    cout << "Employee found." << endl << endl;
    // Take updated details from the user
    string role;
    int salary;
    cout << "Enter new Role: ";
    cin >> role;
    cout << "Enter new Salary: ";
    cin >> salary;
    cout << endl;
    // Update the employee's record
    temp->emp_role = role;
    temp->emp_salary = salary;
    cout << "Updated Successfully." << endl << endl;
}
// Function to display all employee records
void displayEmployee(Employee* head) {
    // If the list is empty, display message
    if (head == NULL) {
        cout << "No Employee in the record." << endl << endl;
        return;
    }
    // Display table header
    cout << "List of Employees:" << endl << endl;
    cout << "===================================================================================" << endl;
    cout << left << setw(20) << "Employee Id";
    cout << left << setw(20) << "Name";
    cout << left << setw(20) << "Role";
    cout << left << setw(20) << "Salary";
    cout << endl;
    cout << "===================================================================================" << endl;
    // Traverse the linked list and display each employee record
    Employee* temp = head;
    while (temp != NULL) {
        cout << left << setw(20) << temp->emp_id;
        cout << left << setw(20) << temp->emp_name;
        cout << left << setw(20) << temp->emp_role;
        cout << left << setw(20) << temp->emp_salary;
        cout << endl;
        temp = temp->next;  // Move to the next node
    }
    cout << "===================================================================================" << endl;
}
int main(){
    Employee* head = NULL; // employee list head
    int main_choice, choice;
    string name, role;
    int salary;
    while(true){
        system("cls");
        cout<<"WELCOME TO SUPERMART MANAGEMENT SYSTEM"<<endl<<endl;
        cout<<"***** MENU *****"<<endl;
        cout<<"\n1. Manage Employee"<<endl;
        cout<<"2. Manage Inventory"<<endl;
        cout<<"3. Manage Customer"<<endl;
        cout<<"4. Billing Section"<<endl;
        cout<<"5. Exit"<<endl<<endl;
        cout<<"Choose from the above options: ";
        cin>>main_choice;
        switch(main_choice){
            case 1:
                while(true){
                    system("cls");
                    cout<<"______ Manage Employee ______"<<endl<<endl;
                    cout<<"***** MENU *****"<<endl;
                    cout<<"\n1. Add Employee"<<endl;
                    cout<<"2. Delete Employee"<<endl;
                    cout<<"3. Update Employee"<<endl;
                    cout<<"4. Display All Employees"<<endl;
                    cout<<"5. Go back"<<endl<<endl;

                    cout<<"Choose from the above options: ";
                    cin>>choice;
