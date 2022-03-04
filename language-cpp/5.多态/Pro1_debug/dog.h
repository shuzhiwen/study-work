// Chapter 10 of C++ How to Program
// Debugging Problem (dog.h)

#ifndef DOG_H
#define DOG_H

#include "animal.h"

using namespace std;

// class Dog definition
class Dog : public Animal {
   public:
    Dog(int = 0, int = 0, string = "Toto");

    virtual void print() const;
    virtual int getHeight() const;
    virtual int getWeight() const;
    virtual void setHeight(int);
    virtual void setWeight(int);
    string getName() const;
    void setName(string);

   private:
    bool useMetric(string) const;
    string name;
    int metricHeight;
    int metricWeight;

};  // end class Dog

#endif  // DOG_H

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