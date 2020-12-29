#pragma once
#include <exception>
#include <string>

class WrongMove : public std::exception {
    const std::string msg {"This move is forbidden! Check if parameters are incorrect or this field is busy!"};

public:
    const char * what() const noexcept override {
        return msg.c_str();
    }
};