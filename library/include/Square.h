#ifndef CHESS_SQUARE_H
#define CHESS_SQUARE_H

#include "typedefs.h"

/**
 * @brief Representation of square.
 * Holds reference to piece as std::weak_ptr<Piece>.
 */
class Square {
    int row;
    int column;
    PieceWeakPtr piece;
public:
    /**
     * @brief Initializes square object with row = x and column = y
     */
    Square(int x, int y);
    PiecePtr getPiece();
    void setPiece(const PiecePtr& _piece);
    int getRow() const;
    int getColumn() const;

    /**
     * Translates square coordinates(row & column) to format used in chess.
     * Works only for row & column values from [0, 7].
     * @return square position in format: columnLetter,rowNumber [eg. A7 when ]
     */
    std::string toString() const;
};

#endif //CHESS_SQUARE_H
