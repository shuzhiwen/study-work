#include "CPerson.h"

#include <iostream>

using namespace std;

CPerson::CPerson(string name, string identity, bool gender, int age) {
    this->name = name;
    this->identity = identity;
    this->gender = gender;
    this->age = age;
}

CPerson::~CPerson() {
    name.clear();
    identity.clear();
}

void CPerson::print() {
    cout << "name: " << name << endl
         << "identity: " << identity << endl
         << "gender: " << (gender ? "male" : "female") << endl
         << "age: " << age << endl;
}