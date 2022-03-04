#include "array.h"

int main() {
    int data1[3] = {1, 2, 3};
    double data2[5] = {1.1, 2.2, 3.3, 4.4, 5.5};

    Array<int> a(data1, 3);
    Array<double> b(data2, 5);
    Array<int> aa(a);
    Array<double> bb(b);

    cout << a << endl;
    cout << aa << endl;
    cout << b << endl;
    cout << bb << endl;

    Array<int> aaa;
    aaa = a + aa;
    Array<double> bbb(5);
    bbb = b + bb;

    cout << aaa << endl;
    cout << bbb << endl;

    aaa.sort();
    bbb.sort();

    cout << aaa << endl;
    cout << bbb << endl;
}