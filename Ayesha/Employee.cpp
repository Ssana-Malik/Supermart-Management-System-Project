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
