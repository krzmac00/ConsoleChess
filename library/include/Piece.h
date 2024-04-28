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
    virtual void restore(SquarePtr);
    virtual bool isFirstMove() const;
    virtual void setFirstMove(bool isFirst);
    virtual bool canBeMovedToSquare(SquarePtr, BoardPtr) = 0;
};

#endif //CHESS_PIECE_H
