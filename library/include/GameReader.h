#ifndef CHESS_GAMEREADER_H
#define CHESS_GAMEREADER_H

#include "typedefs.h"
#include "Exceptions/FileException.h"
#include "Exceptions/FileStructureException.h"

class GameReader {
public:
    static GameDataPtr loadGame(std::string filePath) noexcept(false);
};

#endif //CHESS_GAMEREADER_H
