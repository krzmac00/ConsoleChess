#include "Exceptions/InputException.h"

InputException::InputException(std::string msg) : message(msg){}

const char *InputException::what() const noexcept {
    return message.c_str();
}

