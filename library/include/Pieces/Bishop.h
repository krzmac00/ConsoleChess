#ifndef CHESS_BISHOP_H
#define CHESS_BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(PlayerPtr player, SquarePtr square);
    ~Bishop() override;
    bool canBeMovedToSquare(SquarePtr toSquare, BoardPtr board) override;
};

#endif //CHESS_BISHOP_H
