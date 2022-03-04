// Chapter 10 of C++ How to Program
// Debugging Problem (debugging10.cpp)

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

#include "animal.h"
#include "dog.h"
#include "lion.h"

void setHeightWeight(Animal*);

int main() {
    Dog* dog1 = new Dog(60, 120, "Fido");
    Lion* lion1 = new Lion(45, 300);

    setHeightWeight(lion1);
    setHeightWeight(dog1);

    return 0;

}  // end main

// function setHeightWeight definition
void setHeightWeight(Animal* a) {
    int height;
    int weight;

    a->print();
    cout << "Enter a new height (using standard units): ";
    cin >> height;
    a->setHeight(height);

    cout << "Enter a new weight (using standard units): ";
    cin >> weight;
    a->setWeight(weight);

    height = a->getHeight();
    weight = a->getWeight();

    cout << "Here are the new height and weight values:\n"
         << height << endl
         << weight << endl
         << endl;

}  // end function setHeightWeight

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