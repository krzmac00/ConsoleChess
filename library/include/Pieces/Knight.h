#ifndef CHESS_KNIGHT_H
#define CHESS_KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
public:
    Knight(PlayerPtr player, SquarePtr square);
    ~Knight() override;
    bool canBeMovedToSquare(SquarePtr toSquare, BoardPtr board) override;
};

#endif //CHESS_KNIGHT_H
