#include "CPerson.h"

class CEmployee : public CPerson {
   public:
    CEmployee(string, string, bool, int, string, double);
    ~CEmployee();

    void print();

   private:
    string department;
    double salary;
};