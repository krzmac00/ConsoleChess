#ifndef CHESS_PAWN_H
#define CHESS_PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(PlayerPtr player, SquarePtr square);
    ~Pawn() override;
    bool canBeMovedToSquare(SquarePtr toSquare, GameDataPtr gameData) override;
};

#endif //CHESS_PAWN_H
