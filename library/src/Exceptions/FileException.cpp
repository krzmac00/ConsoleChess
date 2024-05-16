#include "Exceptions/FileException.h"
#include <cstring>

FileException::FileException(std::string fileName) : fileName("Failed to open file: " + fileName) {}


const char *FileException::what() const noexcept {
    return fileName.c_str();
}
