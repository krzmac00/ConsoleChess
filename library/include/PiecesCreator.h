#ifndef CHESS_PIECESCREATOR_H
#define CHESS_PIECESCREATOR_H

#include "typedefs.h"

class PiecesCreator {
public:
    static PiecePtr create(PieceType rodzaj, PlayerPtr gracz, SquarePtr pole);
};

#endif //CHESS_PIECESCREATOR_H
