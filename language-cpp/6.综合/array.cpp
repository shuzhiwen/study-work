#include "array.h"

template <typename T>
int Array<T>::getSize() {
    return this->size;
}

template <typename T>
Array<T>::Array() {
    size = 0;
    arr = new T[size];
}

template <typename T>
Array<T>::Array(int size) {
    this->size = size;
    arr = new T[size];
}

template <typename T>
Array<T>::Array(const Array& other) {
    size = other.size;
    arr = new T[size];
    for (int i = 0; i < getSize(); i++) {
        arr[i] = other.arr[i];
    }
}

template <typename T>
Array<T>::Array(T a[], int n) {
    size = n;
    arr = new T[size];
    for (int i = 0; i < getSize(); i++) {
        arr[i] = a[i];
    }
}

template <typename T>
Array<T>::~Array() {
    size = 0;
    delete (arr);
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& rhs) {
    delete (arr);
    this->size = rhs.size;
    arr = new T[size];
    for (int i = 0; i < size; i++) {
        arr[i] = rhs.arr[i];
    }
}

template <typename T>
Array<T> Array<T>::operator+(const Array& rhs) const {
    Array tmp(rhs.size + this->size);
    for (int i = 0; i < rhs.size; i++) {
        tmp.arr[i] = rhs.arr[i];
    }
    for (int i = rhs.size; i < tmp.size; i++) {
        tmp.arr[i] = this->arr[i - rhs.size];
    }
    return tmp;
}

template <typename T>
T& Array<T>::operator[](int i) {
    if (i >= this->size) {
        throw "Index out of range !";
    } else {
        return arr[i];
    }
}

template <typename T>
const T& Array<T>::operator[](int i) const {
    if (i >= this->size) {
        throw "Index out of range !";
    } else {
        return arr[i];
    }
}

template <typename T>
Array<T>::operator T*() {
    return arr;
}

template <typename T>
void Array<T>::sort() {
    int maxIndex;
    for (int i = size - 1; i > 0; i--) {
        maxIndex = i;
        for (int j = 0; j < i; j++) {
            if (arr[j] > arr[maxIndex]) {
                maxIndex = j;
            }
        }
        T tmp = arr[i];
        arr[i] = arr[maxIndex];
        arr[maxIndex] = tmp;
    }
}

ostream& operator<<(ostream& out, const Array<int>& rhs) {
    for (int i = 0; i < rhs.size; i++) {
        out << rhs.arr[i] << ' ';
    }
    return out;
}

ostream& operator<<(ostream& out, const Array<double>& rhs) {
    for (int i = 0; i < rhs.size; i++) {
        out << rhs.arr[i] << ' ';
    }
    return out;
}