#include <string>

using namespace std;

class MyClass {
    const double pi;
    static int number;
    string name;

   public:
    MyClass();
    MyClass(string name);
    ~MyClass();
    MyClass(const MyClass& s);
    MyClass& operator=(const MyClass& s);

    void print() const;
    static int getNumber();
};
