#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "typedefs.h"
#include <string>

/**
 * Stores move properties and allows to execute or undo a move in given gameData.
 */
class Move : public std::enable_shared_from_this<Move> {
    SquarePtr from = nullptr;
    SquarePtr to = nullptr;
    const PlayerWeakPtr player;
    std::string abbr;
    bool executed = false;
    bool pieceFirstMove = false;
    bool enPassant = false;
    PiecePtr capturedPiece;
    /// @return string with move description in chess format (ex. A2-A3)
    std::string toString();
public:
    /**
     * @param from square containing a piece which shall be moved
     * @param to square that piece shall be moved to
     * @param player move owner
     */
    Move(SquarePtr from, SquarePtr to, PlayerPtr player);

    /**
     * @param move string with move description in chess format (ex. A2-A3)
     * @param board board that consequent squares will initialize from and to members
     * @param player move owner
     */
    Move(std::string move, BoardPtr& board, PlayerPtr player);

    /**
     * Constructor meant to handle special moves (such as O-O or O-O-O) and control string.
     * @param move should be "O-O" for short castling or "O-O-O" for long castling or can be control string \n
     * is used to directly initialize abbr member
     * @param player
     */
    Move(std::string move, PlayerPtr player);

    /**
     * @brief Executes move and handles its logic.
     *
     * Saves all data allowing to restore game state from before move execution.
     * Once execute() is called, further calling has no effect unless undo() method is called.\n
     * Changes state and handles coherence of all Pieces and Squares involved in Move.\n
     * Adds Move to gameData.
     * @param gameData has to be compatible with Squares or Board that Move was initialized with
     */
    void execute(GameDataPtr &gameData);

    /**
     * @brief Restores game data from before move execution.
     *
     * If execute() hasn't been called undo() has no effect.\n
     * Once undo() is called, further calling has no effect unless execute() method is called again.\n
     * @param gameData has to be compatible with gameData that execute() was called with
     */
    void undo(GameDataPtr &gameData);

    /// Move.abbr getter
    std::string getAbbr();
    const SquarePtr &getFrom() const;
    const SquarePtr &getTo() const;
    PlayerPtr getPlayer() const;
};

#endif //CHESS_MOVE_H
