#include <iostream>

#include "Complexd.h"

using namespace std;

int main() {
    Complexd a(1, 2);
    Complexd b(a);
    Complexd c;

    c = *(new Complexd(1, 1));
    cout << a << b << c;
    cout << (b + c) << (b - c) << (b * c) << (b / c);
}