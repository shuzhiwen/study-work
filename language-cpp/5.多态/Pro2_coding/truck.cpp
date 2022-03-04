// Chapter 10 of C++ How to Program
// truck.cpp
#include <iostream>

using std::cout;

#include "truck.h"

// constructor
Truck::Truck(double fuel) : Vehicle(2, 1, "black", fuel, 8) {
    cargo = false;

}  // end class Truck constructor

// function hasCargo definition
bool Truck::hasCargo() const { return cargo; }  // end function hasCargo

// function setCargo definition
void Truck::setCargo(bool cargoValue) { cargo = cargoValue; }  // end function setCargo

// function print definition
void Truck::print() const {
    Vehicle::print();

    if (cargo)
        cout << "\tThe truck is currently carrying cargo.\n";

    else
        cout << "\tThe truck is currently not carrying cargo.\n";

    cout << "\tclass name: " << getClassName() << "\n";

}  // end function print

// function horn definition
void Truck::horn() const { cout << "HOOOONK!"; }  // end function horn

// return class name
string Truck::getClassName() const { return "Truck"; }  // end function getClassName

void Truck::setColor(string color) { Vehicle::setColor(color); }

string Truck::getColor() const { return Vehicle::getColor(); }

void Truck::setFuelLevel(double amount) { Vehicle::setFuelLevel(amount); }

double Truck::getFuelLevel() const { return Vehicle::getFuelLevel(); }

int Truck::getTransmissionType() const { return Vehicle::getTransmissionType(); }

int Truck::getNumberOfDoors() const { return Vehicle::getNumberOfDoors(); }

int Truck::getNumberOfCylinders() const { return Vehicle::getNumberOfCylinders(); }

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
