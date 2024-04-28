#include "Exceptions/InputException.h"

InputException::InputException(const char *msg) : message(msg){}

const char *InputException::what() const noexcept {
    return message;
}

