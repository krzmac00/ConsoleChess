#ifndef CHESS_FILEACCESSEXCEPTION_H
#define CHESS_FILEACCESSEXCEPTION_H

#include "FileException.h"

class FileAccessException : public FileException {
    std::string message;
public:
    FileAccessException(std::string fileName);
    const char* what() const noexcept override;
};

#endif //CHESS_FILEACCESSEXCEPTION_H
