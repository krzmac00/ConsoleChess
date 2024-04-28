#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include <string>
#include "typedefs.h"
#include "Board.h"
#include "Player.h"

class Game {
protected:
    BoardPtr board;
    PlayerPtr player1;
    PlayerPtr player2;
    PlayerPtr playerTurn;
    ViewPtr view;

    bool loadGame();
    bool saveGame();
    void startGame();
    void initializeGame();

    Event handleMove(PlayerPtr &player);
    bool isMoveCorrect(PlayerPtr &player, MovePtr &move);
    bool isCastlingCorrect(PlayerPtr &player, std::string castling);
    bool isSquareAttacked(PlayerPtr &player, SquarePtr square);
    void promotion(SquarePtr pawnSquare, PlayerPtr &player);

    bool isPlayerInCheckAfterMove(PlayerPtr &player, MovePtr &move);
    PiecePtr getCheckingPiece(PlayerPtr &playerInCheck);

    bool isCheckmate(PlayerPtr &player);
    bool canCheckingPieceBeCaptured(PlayerPtr &playerInCheck);
    bool canKingBeMoved(PlayerPtr &player);
    bool canCheckBeBlocked(PlayerPtr &player);

    bool isStalemate(PlayerPtr &player);

public:
    Game(ViewPtr _view);
    bool play();
};

#endif //CHESS_GAME_H
