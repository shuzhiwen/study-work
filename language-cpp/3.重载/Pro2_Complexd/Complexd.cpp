#include "Complexd.h"

Complexd::Complexd(double real, double imag) {
    this->real = real;
    this->imag = imag;
}

Complexd::Complexd(const Complexd &other) {
    this->real = other.real;
    this->imag = other.imag;
}

Complexd &Complexd::operator=(const Complexd &other) {
    real = other.real;
    imag = other.imag;
    return *this;
}

Complexd Complexd::operator+(const Complexd &other) {
    Complexd tmp;
    tmp.real = this->real + other.real;
    tmp.imag = this->imag + other.imag;
    return tmp;
}

Complexd Complexd::operator-(const Complexd &other) {
    Complexd tmp;
    tmp.real = this->real - other.real;
    tmp.imag = this->imag - other.imag;
    return tmp;
}

Complexd Complexd::operator*(const Complexd &other) {
    Complexd tmp;
    tmp.real = this->real * other.real - this->imag * other.imag;
    tmp.imag = this->real * other.imag + this->imag * other.real;
    return tmp;
}

Complexd Complexd::operator/(const Complexd &other) {
    Complexd tmp;
    double down = other.imag * other.imag + other.real * other.real;
    tmp.real = (this->real * other.real + this->imag * other.imag) / down;
    tmp.imag = (this->imag * other.real - this->real * other.imag) / down;
    return tmp;
}

ostream &operator>>(ostream &in, const Complexd &other) { return in >> other.real >> other.imag; }

ostream &operator<<(ostream &out, const Complexd &other) {
    return out << other.real << '\t' << other.imag << "i" << endl;
}