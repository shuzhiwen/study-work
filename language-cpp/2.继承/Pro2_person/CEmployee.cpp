#include "CEmployee.h"

#include <iostream>

using namespace std;

CEmployee::CEmployee(string name, string identity, bool gender, int age, string department,
                     double salary)
    : CPerson(name, identity, gender, age) {
    this->department = department;
    this->salary = salary;
}

CEmployee::~CEmployee() { department.clear(); }

void CEmployee::print() {
    CPerson::print();
    cout << "department: " << department << endl << "salary: " << salary << endl;
}