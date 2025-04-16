#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H

#include <string>
#include <vector>
#include "typedefs.h"

/**
 * @brief Stores information about player and player-related properties.
 */
class Player : public std::enable_shared_from_this<Player> {
    std::string name;
protected:
    Color color;
    PiecePtr king;
    PieceWeakPtr checkingPiece;
public:
    /**
     * @brief Basic Player ctor.
     * Initializes name and color. King is set to nullptr by default.
     */
    Player(std::string name, Color color);
    virtual ~Player() = 0;
    virtual std::string getName() const;

    //check-related methods
    virtual void setCheckingPiece(const PiecePtr& piece);

    /**
     * Sets checkingPiece to nullptr.
     */
    virtual void cancelCheck();

    /**
     * If checkingPiece == nullptr return false, else - true.
     */
    virtual bool isInCheck();
    virtual PiecePtr getCheckingPiece() const;

    virtual Color getColor() const;
    virtual void setKing(PiecePtr _king);
    virtual PiecePtr getKing() const;

    /**
     * Method is meant to obtain valid move from player.
     */
    virtual MovePtr getMove(BoardPtr board, ViewPtr view) = 0;

    /**
     * Method is meant to obtain type of piece that will be assigned to player when promotion occurs.
     */
    virtual PieceType promotion(ViewPtr view) = 0;
};

#endif //CHESS_PLAYER_H
