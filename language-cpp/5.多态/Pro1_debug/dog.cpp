// Chapter 10 of C++ How to Program
// Debugging Problem (dog.cpp)

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include "dog.h"

using namespace std;

// default constructor
Dog::Dog(int h, int w, string n) : Animal(h, w) {
    setName(n);
    metricHeight = h * 2.5;
    metricWeight = w / 2.2;

}  // end class Dog constructor

// return name
string Dog::getName() const { return name; }  // end function getName

// function setName definition
void Dog::setName(string n) { name = n; }  // end function setName

// function print definition
void Dog::print() const {
    cout << "This animal is a dog, its name is: " << name << endl;
    Animal::print();

}  // end function print

void Dog::setHeight(int h) {
    Animal::setHeight(h);
    metricHeight = Animal::getHeight() * 2.5;
}

void Dog::setWeight(int w) {
    Animal::setWeight(w);
    metricWeight = Animal::getWeight() / 2.2;
}

// return height
int Dog::getHeight() const {
    if (useMetric("height"))
        return metricHeight;

    else
        return Animal::getHeight();

}  // end function print

// return weight
int Dog::getWeight() const {
    if (useMetric("weight"))
        return metricWeight;

    else
        return Animal::getWeight();

}  // end function getWeight
// function useMetric definition
bool Dog::useMetric(string type) const {
    int choice = 0;

    cout << "Which units would you like to see the " << type << " in? (Enter 1 or 2)\n"
         << "\t1. metric\n"
         << "\t2. standard\n";

    cin >> choice;

    if (choice == 1)
        return true;

    else
        return false;

}  // end function useMetric

/**************************************************************************
 * (C) Copyright 1992-2003 by Deitel & Associates, Inc. and Prentice      *
 * Hall. All Rights Reserved.                                             *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/