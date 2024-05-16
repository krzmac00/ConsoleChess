#ifndef CHESS_IOEXCEPTION_H
#define CHESS_IOEXCEPTION_H

#include <exception>
#include <string>

class FileException : public std::exception {
    std::string fileName;
public:
    FileException(std::string fileName);
    const char* what() const noexcept override;
};

#endif //CHESS_IOEXCEPTION_H
