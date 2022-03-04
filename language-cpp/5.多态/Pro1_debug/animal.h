// Chapter 10 of C++ How to Program
// Debugging Problem (animal.h)

#ifndef ANIMAL_H
#define ANIMAL_H

// Note: class Animal is an abstract class
// class Animal definition
class Animal {
   public:
    Animal(int = 0, int = 0);

    virtual void setHeight(int) = 0;
    virtual int getHeight() const = 0;

    virtual void setWeight(int) = 0;
    virtual int getWeight() const = 0;

    virtual void print() const = 0;

   private:
    int height;
    int weight;

};  // end class Animal

#endif  // ANIMAL_H

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