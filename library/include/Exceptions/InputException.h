#ifndef SZACHY_INPUTEXCEPTION_H
#define SZACHY_INPUTEXCEPTION_H

#include <exception>

class InputException : public std::exception {
    const char* message;
public:
    InputException(const char * msg);
    const char * what() const noexcept override;
};

#endif //SZACHY_INPUTEXCEPTION_H
