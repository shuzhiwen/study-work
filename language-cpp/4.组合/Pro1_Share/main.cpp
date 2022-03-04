#include <iostream>

#include "share.h"

using namespace std;

int main() {
    share sp(new A());
    sp->n = 10;

    share sp2 = sp;
    cout << "sp2->n is :" << sp2->n << endl;
    return 0;
}
