#include "String.h"

#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

String::String() {
    this->pt = NULL;
    // cout << "default init" << endl;
}

String::~String() {
    delete (this->pt);
    // cout << "destroy the class" << endl;
}

String::String(const char* str) {
    this->pt = new char[strlen(str) + 1];
    strcpy(this->pt, str);
    // cout << "common init" << endl;
}

String::String(const String& s) {
    this->pt = new char[strlen(s.pt) + 1];
    strcpy(this->pt, s.pt);
    // cout << "class init" << endl;
}

String& String::operator=(const String& s) {
    if (this->pt != NULL) {
        delete (this->pt);
    }

    this->pt = new char[strlen(s.pt) + 1];
    strcpy(this->pt, s.pt);
    return *this;
}

// 表示将s加到当前字符串中
void String::add(const String& s) {
    char* tmp = new char[strlen(this->pt) + 1];

    strcpy(tmp, this->pt);
    if (this->pt != NULL) {
        delete (this->pt);
    }

    this->pt = new char[strlen(s.pt) + strlen(this->pt) + 1];
    strcpy(this->pt, tmp);
    strcat(this->pt, s.pt);
    delete (tmp);
}

// 表示构造一个新字符串，内容为前字符串加上s，并返回该字符串对象
String String::add(const String& s) const {
    String* tmp = new String(*this);
    tmp->add(s);
    return *tmp;
}

void String::print() const { cout << this->pt << endl; }