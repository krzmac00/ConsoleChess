#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <string>
#include <vector>
#include "typedefs.h"

class Player {
    std::string name;
protected:
    Color color;
    PiecePtr king;
    std::vector<std::string> moves;
    std::vector<std::string> capturedPieces;
    CheckPtr check;
public:
    Player(std::string name, Color color);
    virtual ~Player() = 0;
    virtual std::string getName() const;

    //check-related methods
    virtual void setCheck(const PiecePtr& checkingPiece);
    virtual void cancelCheck();
    virtual bool isInCheck();
    virtual CheckPtr getCheck() const;

    virtual Color getColor() const;
    virtual void setKing(PiecePtr _king);
    virtual PiecePtr getKing() const;

    virtual MovePtr getMove(BoardPtr board, ViewPtr view) = 0;
    virtual PieceType promotion(ViewPtr view) = 0;
    virtual void addMove(const std::string& move);
    virtual void addCapturedPiece(const std::string& piece);
    virtual void removeLastCapturedPiece();
    virtual void removeLastMove();
    virtual std::string getLastMove() const;
    virtual std::vector<std::string> getCapturedPieces() const;
    virtual std::vector<std::string> getMoves() const;
};

#endif //CHESS_PLAYER_H
