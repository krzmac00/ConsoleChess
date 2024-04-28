#ifndef CHESS_QUEEN_H
#define CHESS_QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
    Queen(PlayerPtr player, SquarePtr square);
    ~Queen() override;
    bool canBeMovedToSquare(SquarePtr toSquare, BoardPtr board) override;
};

#endif //CHESS_QUEEN_H
