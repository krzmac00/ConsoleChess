#ifndef CHESS_PIECE_H
#define CHESS_PIECE_H

#include <string>
#include "typedefs.h"
#include "Square.h"

class Piece {
    PieceType type;
protected:
    PlayerPtr player;
    bool captured;
    bool firstMove;
    SquarePtr square;
public:
    Piece(PieceType, PlayerPtr, SquarePtr);
    virtual ~Piece() = 0;
    virtual PlayerPtr getPlayer() const;
    virtual SquarePtr getSquare() const;
    virtual PieceType getType() const;
    virtual std::string getAbbr() const;
    virtual void setSquare(SquarePtr _square);
    virtual bool isCaptured() const;
    virtual void setCaptured();
    /// sets Piece.square = inSquare and Piece.captured = false
    virtual void restore(SquarePtr inSquare);
    virtual bool isFirstMove() const;
    virtual void setFirstMove(bool isFirst);
    /**
     * Checks if moving Piece to Square complies with piece move pattern and if there are pieces (on the way) blocking the move. \n
     * Checking does not involve other game state components.
     * @param toSquare destination Square
     * @param gameData object containing the Board where Piece belongs
     */
    virtual bool canBeMovedToSquare(SquarePtr toSquare, GameDataPtr gameData) = 0;
};

#endif //CHESS_PIECE_H
