#include <iostream>

#include "MyClass.h"

using namespace std;

int MyClass::number = 0;

int main() {
    MyClass mc1;
    MyClass mc2("zhang");

    mc1 = mc2;  // 表示将s2赋值给s1
    cout << MyClass::getNumber() << endl;

    MyClass mc3(mc2);
    // mc3.print();

    const MyClass mc4("li");
    mc4.print();
    cout << MyClass::getNumber() << endl;

    MyClass* pm = new MyClass[6];
    cout << MyClass::getNumber() << endl;

    if (nullptr != pm) {
        delete[] pm;
        pm = nullptr;
    }
}
