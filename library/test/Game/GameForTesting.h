#ifndef CHESS_GAMEFORTESTING_H
#define CHESS_GAMEFORTESTING_H

#include "../include/Game.h"

class GameForTesting final : public Game {

public:
    GameForTesting(ViewPtr view);

    //public methods calling private methods from base class Game (only for testing purposes)
    bool loadGamePublic();
    bool saveGamePublic();
    void startGamePublic();
    void initializeGamePublic();

    Event handleMovePublic(PlayerPtr &player);
    bool isMoveCorrectPublic(PlayerPtr &player, MovePtr &move);
    bool isCastlingCorrectPublic(PlayerPtr &player, std::string castling);
    bool isSquareAttackedPublic(PlayerPtr &player, SquarePtr square);
    void promotionPublic(SquarePtr pawnSquare, PlayerPtr &player);

    bool isPlayerInCheckAfterMovePublic(PlayerPtr &player, MovePtr &move);
    PiecePtr getCheckingPiecePublic(PlayerPtr &playerInCheck);

    bool isCheckmatePublic(PlayerPtr player);
    bool canCheckingPieceBeCapturedPublic(PlayerPtr &playerInCheck);
    bool canKingBeMovedPublic(PlayerPtr &player);
    bool canCheckBeBlockedPublic(PlayerPtr &player);

    bool isStalematePublic(PlayerPtr player);

    //GameForTesting own functions for reading & manipulating state
    void setBoard(const BoardPtr &board);
    const BoardPtr &getBoard() const;
    PlayerPtr getPlayer1() const;
    PlayerPtr getPlayer2() const;
    PlayerPtr getPlayerTurn() const;
    void setPlayer1(const PlayerPtr &player);
    void setPlayer2(const PlayerPtr &player);
    void setPlayerTurn(const PlayerPtr &player);
};


#endif //CHESS_GAMEFORTESTING_H
