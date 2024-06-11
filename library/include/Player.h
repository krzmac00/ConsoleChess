#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <string>
#include <vector>
#include "typedefs.h"

class Player : public std::enable_shared_from_this<Player> {
    std::string name;
protected:
    Color color;
    PiecePtr king;
    PieceWeakPtr checkingPiece;
public:
    Player(std::string name, Color color);
    virtual ~Player() = 0;
    virtual std::string getName() const;

    //check-related methods
    virtual void setCheckingPiece(const PiecePtr& piece);
    virtual void cancelCheck();
    virtual bool isInCheck();
    virtual PiecePtr getCheckingPiece() const;

    virtual Color getColor() const;
    virtual void setKing(PiecePtr _king);
    virtual PiecePtr getKing() const;

    virtual MovePtr getMove(BoardPtr board, ViewPtr view) = 0;
    virtual PieceType promotion(ViewPtr view) = 0;
};

#endif //CHESS_PLAYER_H
