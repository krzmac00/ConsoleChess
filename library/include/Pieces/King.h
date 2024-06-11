#ifndef CHESS_KING_H
#define CHESS_KING_H

#include "Piece.h"

class King : public Piece {
public:
    King(PlayerPtr player, SquarePtr square);
    ~King() override;
    bool canBeMovedToSquare(SquarePtr toSquare, GameDataPtr gameData) override;
};

#endif //CHESS_KING_H
