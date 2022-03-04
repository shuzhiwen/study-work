#include <iostream>

#include "CEmployee.h"

using namespace std;

int main() {
    string name, id, department;
    int sex, age;
    float salary;
    cout << "input employee's name,id,sex(0:women,1:man),age,department,salary:\n";
    cin >> name >> id >> sex >> age >> department >> salary;
    CEmployee employee1(name, id, sex, age, department, salary);
    employee1.print();
    return 0;
}
