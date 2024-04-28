#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include "typedefs.h"

class Square {
    int row;
    int column;
    PieceWeakPtr piece;
public:
    Square(int, int);
    PiecePtr getPiece();
    void setPiece(const PiecePtr& _piece);
    int getRow() const;
    int getColumn() const;
    std::string toString() const;
};

#endif //CHESS_SQUARE_H
