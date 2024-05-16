#include "Exceptions/FileAccessException.h"

FileAccessException::FileAccessException(std::string fileName) :
    FileException(fileName),
    message("Cannot access file: " + fileName) {}

const char *FileAccessException::what() const noexcept {
    return message.c_str();
}
