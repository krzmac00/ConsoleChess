#ifndef CHESS_GAMELOGIC_H
#define CHESS_GAMELOGIC_H

#include "typedefs.h"

class GameLogic {
public:
    static GameDataPtr initializeGame(Color player1Color, bool playWithComputer);

    static bool isMoveCorrect(PlayerPtr &player, MovePtr &move, GameDataPtr gameData);
    static bool isCastlingCorrect(PlayerPtr &player, std::string castling, GameDataPtr gameData);
    static bool isSquareAttacked(PlayerPtr &player, SquarePtr square, GameDataPtr gameData);
    static bool isPlayerInCheckAfterMove(PlayerPtr &player, MovePtr &move, GameDataPtr gameData);
    static PiecePtr getCheckingPiece(PlayerPtr &playerInCheck, GameDataPtr gameData);

    static SquarePtr checkIfPromotion(MovePtr move, GameDataPtr gameData);
    static void promotePawn(PieceType piece, SquarePtr pawnSquare, GameDataPtr gameData);

    static bool isCheckmate(PlayerPtr &player, GameDataPtr gameData);
    static bool canCheckingPieceBeCaptured(PlayerPtr &playerInCheck, GameDataPtr gameData);
    static bool canKingBeMoved(PlayerPtr &player, GameDataPtr gameData);
    static bool canCheckBeBlocked(PlayerPtr &playerInCheck, GameDataPtr gameData);

    static bool isStalemate(PlayerPtr &player, GameDataPtr gameData);
};

#endif //CHESS_GAMELOGIC_H
