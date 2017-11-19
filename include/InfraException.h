//
// Created by mz on 18/11/17.
//
#ifndef FILE_SERVER_INFRAEXCEPTION_H
#define FILE_SERVER_INFRAEXCEPTION_H


#include <stdexcept>

using namespace std;

class InfraException : public runtime_error{

public:
    explicit InfraException(const string &__arg) : runtime_error(__arg) {}

};


#endif //FILE_SERVER_INFRAEXCEPTION_H
