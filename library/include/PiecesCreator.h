#ifndef CHESS_PIECESCREATOR_H
#define CHESS_PIECESCREATOR_H

#include "typedefs.h"

class PiecesCreator {
public:
    static PiecePtr create(PieceType type, PlayerPtr player, SquarePtr square);
};

#endif //CHESS_PIECESCREATOR_H
