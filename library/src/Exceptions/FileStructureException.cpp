#include "Exceptions/FileStructureException.h"

FileStructureException::FileStructureException(std::string fileName, std::string corruptedStructure) :
    FileException(fileName),
    message("Error in file: " + fileName + " : Invalid file format: missing or corrupted structure: " + corruptedStructure) {}

const char *FileStructureException::what() const noexcept {
    return message.c_str();
}
