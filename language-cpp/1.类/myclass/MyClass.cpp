#include "MyClass.h"

#include <iostream>

using namespace std;

MyClass::MyClass() : pi(3.1415926) {
    number++;
    // cout << "default init" << endl;
}

MyClass::MyClass(string name) : pi(3.1415926), name(name) {
    number++;
    // cout << "common init" << endl;
}

MyClass::~MyClass() {
    // cout << "destroy the class" << endl;
}

MyClass::MyClass(const MyClass& s) : pi(s.pi), name(s.name) {
    number++;
    // cout << "class init" << endl;
}

MyClass& MyClass::operator=(const MyClass& s) {
    this->name = s.name;
    return *this;
}

void MyClass::print() const {
    cout << "name: " << name << endl;
    cout << "number: " << number << endl;
    cout << "pi: " << pi << endl;
}

int MyClass::getNumber() { return number; }