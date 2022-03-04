#include <iostream>

#include "share.h"

using namespace std;

int main() {
    share sp(new A());
    sp->n = 10;
    cout << "sp->n is :" << sp->n << endl;
    share sp2(sp);
    sp2->n = 20;
    cout << "sp2->n is :" << sp2->n << endl;
    share sp3(new A());
    sp3->n = 30;
    sp = sp3;
    cout << "sp->n is :" << sp->n << endl;
    A a;
    a = *sp2;
    cout << "a.n is :" << a.n << endl;
    return 0;
}
