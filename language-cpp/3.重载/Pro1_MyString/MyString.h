#include <cstdlib>
#include <iostream>

using namespace std;

class MyString {
    friend ostream &operator<<(ostream &out, const MyString &other);

   public:
    MyString(const char *str = NULL);
    MyString(const MyString &other);
    ~MyString(void);
    MyString &operator=(const MyString &other);
    MyString operator+(const MyString &other);
    char &operator[](int i);

   private:
    char *m_data;
};
