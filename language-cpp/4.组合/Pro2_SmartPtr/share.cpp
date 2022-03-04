#include "share.h"

#include <iostream>

share::share() {
    point = new A;
    count = new int;
    *count = 1;
}

share::share(A* p1) {
    point = new A;
    point->n = p1->n;
    count = new int;
    *count = 1;
}

share::~share() {
    if (--(*count) == 0) {
        delete (point);
        delete (count);
        std::cout << "begin to delete share" << std::endl;
    }
}

share::share(share& t2) {
    this->point = t2.point;
    this->count = t2.count;
    ++(*count);
}

share& share::operator=(share& t2) {
    if (*count == 1) {
        this->~share();
    } else {
        --(*count);
    }
    this->point = t2.point;
    this->count = t2.count;
    ++(*count);
    return *this;
}

A* share::operator->() { return point; }

A& share::operator*() { return *point; }