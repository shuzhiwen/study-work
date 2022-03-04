// Chapter 10 of C++ How to Program
// Debugging Problem (animal.cpp)

#include <iostream>
using std::cout;
using std::endl;

#include "animal.h"

// default constructor
Animal::Animal(int h, int w) {
    height = h;
    weight = w;

}  // end class Animal constructor

// function print definition
void Animal::print() const {
    cout << "This animal's height and weight are as follows:\n"
         << "Height: " << height << "\tWeight: " << weight << endl
         << endl;

}  // end function print

// return height
int Animal::getHeight() const { return height; }  // end function getHeight

// return weight
int Animal::getWeight() const { return weight; }  // end function getWeight

// function setHeight definition
void Animal::setHeight(int h) { height = h; }  // end function setHeight

// function setWeight definition
void Animal::setWeight(int w) { weight = w; }  // end function setWeight

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