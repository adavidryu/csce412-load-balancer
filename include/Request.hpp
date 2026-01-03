#ifndef REQUEST_HPP
#define REQUEST_HPP

#include<iostream>
#include <string>
using namespace std;

struct Request {
    string ipIn;
    string ipOut;
    int processTime;
    char jobType;
};

#endif