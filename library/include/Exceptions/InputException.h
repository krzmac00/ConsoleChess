#ifndef SZACHY_INPUTEXCEPTION_H
#define SZACHY_INPUTEXCEPTION_H

#include <exception>
#include <string>

class InputException : public std::exception {
    std::string message;
public:
    InputException(std::string msg);
    const char * what() const noexcept override;
};

#endif //SZACHY_INPUTEXCEPTION_H
