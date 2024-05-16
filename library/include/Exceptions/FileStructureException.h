#ifndef CHESS_FILESTRUCTUREEXCEPTION_H
#define CHESS_FILESTRUCTUREEXCEPTION_H

#include "FileException.h"

class FileStructureException : FileException {
    std::string message;
public:
    FileStructureException(std::string fileName, std::string corruptedStructure);
    const char* what() const noexcept override;
};

#endif //CHESS_FILESTRUCTUREEXCEPTION_H
