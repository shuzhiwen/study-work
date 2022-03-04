#include <string>

using namespace std;

class CPerson {
   public:
    CPerson(string, string, bool, int);
    ~CPerson();

    void print();

   private:
    string name;
    string identity;
    bool gender;  //'true' for male, 'false' for female
    int age;
};