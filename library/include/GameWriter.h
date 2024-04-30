#ifndef CHESS_GAMEWRITER_H
#define CHESS_GAMEWRITER_H

#include "typedefs.h"
#include "Exceptions/FileException.h"

class GameWriter {
public:
    static void saveGame(GameDataPtr gameData, std::string filePath) noexcept(false);
};


#endif //CHESS_GAMEWRITER_H
