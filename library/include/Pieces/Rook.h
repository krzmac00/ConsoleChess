#ifndef CHESS_ROOK_H
#define CHESS_ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
    Rook(PlayerPtr player, SquarePtr square);
    ~Rook() override;
    bool canBeMovedToSquare(SquarePtr toSquare, BoardPtr board) override;
};

#endif //CHESS_ROOK_H
