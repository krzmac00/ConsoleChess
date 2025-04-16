#ifndef CHESS_GAMELOGIC_H
#define CHESS_GAMELOGIC_H

#include "typedefs.h"

class GameLogic {
public:
    /// Creates all GameData members and initializes them with values that allows to start playing game.
    static GameDataPtr initializeGame(Color player1Color, bool playWithComputer);

    /// Completely checks if move is correct and can be executed.
    static bool isMoveCorrect(MovePtr &move, GameDataPtr gameData);

    /// Checks if castling can be executed.
    static bool isCastlingCorrect(const PlayerPtr &player, std::string castling, GameDataPtr gameData);

    /// Checks if enemy players pieces could possibly make a valid move to square.
    static bool isSquareAttacked(const PlayerPtr &player, SquarePtr square, GameDataPtr gameData);

    /// Executes move and checks if check occurs, then game state is restored to state before move execution.
    static bool isPlayerInCheckAfterMove(const PlayerPtr &player, MovePtr &move, GameDataPtr gameData);

    /// @return PiecePtr of Piece that causes a check, if player is not in check returns nullptr.
    static PiecePtr getCheckingPiece(const PlayerPtr &playerInCheck, GameDataPtr gameData);

    /**
     * Checks if after move is executed pawn promotion occurs.
     * @param move
     * @param gameData
     * @return SquarePtr of pawn that is promoted, nullptr if there's no promotion
     */
    static SquarePtr checkIfPromotion(MovePtr move, GameDataPtr gameData);

    /// Handles adding new Piece to Board and deleting pawn.
    static void promotePawn(PieceType piece, SquarePtr pawnSquare, GameDataPtr gameData);

    /// Uses canCheckingPieceBeCaptured(), canKingBeMoved(), canCheckBeBlocked() to check for checkmate.
    static bool isCheckmate(const PlayerPtr &player, GameDataPtr gameData);
    static bool canCheckingPieceBeCaptured(const PlayerPtr &playerInCheck, GameDataPtr gameData);
    static bool canKingBeMoved(const PlayerPtr &player, GameDataPtr gameData);
    static bool canCheckBeBlocked(const PlayerPtr &playerInCheck, GameDataPtr gameData);

    /// Checks for stalemate.
    static bool isStalemate(const PlayerPtr &player, GameDataPtr gameData);
};

#endif //CHESS_GAMELOGIC_H
