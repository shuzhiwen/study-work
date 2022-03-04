// Chapter 10 of C++ How to Program
// vehicle.h
#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>

using std::string;

// class Vehicle definition
class Vehicle {
   public:
    Vehicle(const int doors, const int cylinders, string color, double initialFuel,
            const int transmission);

    virtual void setColor(string color) = 0;
    virtual string getColor() const = 0;

    virtual void setFuelLevel(double amount) = 0;
    virtual double getFuelLevel() const = 0;

    virtual int getTransmissionType() const = 0;
    virtual int getNumberOfDoors() const = 0;
    virtual int getNumberOfCylinders() const = 0;

    virtual string getClassName() const = 0;

    /* Write prototype for pure virtual function horn */
    /* Write prototype for virtual function print     */
    virtual void horn() const = 0;
    virtual void print() const = 0;

   private:
    const int numberOfDoors;
    const int numberOfCylinders;
    string vehicleColor;
    double fuelLevel;
    const int transmissionType;

};  // end class Vehicle

#endif  // VEHICLE_H

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
