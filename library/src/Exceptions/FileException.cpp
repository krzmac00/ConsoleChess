#include "Exceptions/FileException.h"
#include <cstring>

FileException::FileException(std::string fileName) : message("Failed to open file: " + fileName) {}


const char *FileException::what() const noexcept {
    return message.c_str();
}
