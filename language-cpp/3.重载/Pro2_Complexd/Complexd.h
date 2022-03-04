#include <cstdlib>
#include <iostream>

using namespace std;

class Complexd {
    friend ostream &operator>>(ostream &in, const Complexd &other);
    friend ostream &operator<<(ostream &out, const Complexd &other);

   public:
    Complexd(double real = 0, double imag = 0);
    Complexd(const Complexd &other);
    Complexd &operator=(const Complexd &other);
    Complexd operator+(const Complexd &other);
    Complexd operator-(const Complexd &other);
    Complexd operator*(const Complexd &other);
    Complexd operator/(const Complexd &other);

   private:
    double real;
    double imag;
};