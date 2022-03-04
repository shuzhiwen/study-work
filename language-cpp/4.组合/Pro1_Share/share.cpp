#include "share.h"

#include <iostream>

share::share() { point = new A; }

share::share(A* p1) {
    point = new A;
    point->n = p1->n;
}

share::~share() {
    delete (point);
    std::cout << "begin to delete share" << std::endl;
}

share::share(share& t2) {
    this->point = t2.point;
    t2.point = nullptr;
}

share& share::operator=(share& t2) {
    this->point = t2.point;
    t2.point = nullptr;
    return *this;
}

A* share::operator->() { return point; }

A& share::operator*() { return *point; }