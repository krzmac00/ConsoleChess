#ifndef CHESS_GAMELOGIC_H
#define CHESS_GAMELOGIC_H

#include "typedefs.h"

class GameLogic {
public:
    static GameDataPtr initializeGame(Color player1Color, bool playWithComputer);

    static bool isMoveCorrect(const PlayerPtr &player, MovePtr &move, GameDataPtr gameData);
    static bool isCastlingCorrect(const PlayerPtr &player, std::string castling, GameDataPtr gameData);
    static bool isSquareAttacked(const PlayerPtr &player, SquarePtr square, GameDataPtr gameData);
    static bool isPlayerInCheckAfterMove(const PlayerPtr &player, MovePtr &move, GameDataPtr gameData);
    static PiecePtr getCheckingPiece(const PlayerPtr &playerInCheck, GameDataPtr gameData);

    static SquarePtr checkIfPromotion(MovePtr move, GameDataPtr gameData);
    static void promotePawn(PieceType piece, SquarePtr pawnSquare, GameDataPtr gameData);

    static bool isCheckmate(const PlayerPtr &player, GameDataPtr gameData);
    static bool canCheckingPieceBeCaptured(const PlayerPtr &playerInCheck, GameDataPtr gameData);
    static bool canKingBeMoved(const PlayerPtr &player, GameDataPtr gameData);
    static bool canCheckBeBlocked(const PlayerPtr &playerInCheck, GameDataPtr gameData);

    static bool isStalemate(const PlayerPtr &player, GameDataPtr gameData);
};

#endif //CHESS_GAMELOGIC_H
