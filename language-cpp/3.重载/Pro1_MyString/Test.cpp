#include <cstring>
#include <iostream>

#include "MyString.h"

using namespace std;

int main() {
    MyString s1("hello");
    MyString s2(s1);
    MyString s3;

    s3 = s1 + s2;
    cout << s1 << s2;
    cout << s3;

    return 0;
}