#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>

struct Request {
    std::string ipIn;
    std::string ipOut;
    int processTime;
    char jobType;
    int id;
    int arrivalTick;
};

#endif