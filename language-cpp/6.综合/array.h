#pragma once

#include <iostream>

using namespace std;

template <typename T>
class Array {
    friend ostream& operator<<(ostream& out, const Array<int>& rhs);
    friend ostream& operator<<(ostream& out, const Array<double>& rhs);

   private:
    int size;
    T* arr;

   public:
    int getSize();
    Array();  //
    Array(int size);
    Array(const Array& other);
    Array(T[], int n);
    ~Array();
    Array& operator=(const Array& rhs);
    Array operator+(const Array& rhs) const;  // append
    T& operator[](int i);                     // allow read and write
    const T& operator[](int n) const;         // readonly
    operator T*();                            // 将动态数组对象转换为类型T *
    void sort();
};

template class Array<int>;
template class Array<double>;