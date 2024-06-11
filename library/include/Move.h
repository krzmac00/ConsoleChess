#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "typedefs.h"
#include <string>

class Move : public std::enable_shared_from_this<Move> {
    SquarePtr from = nullptr;
    SquarePtr to = nullptr;
    const PlayerWeakPtr player;
    std::string abbr;
    bool executed = false;
    bool pieceFirstMove = false;
    bool enPassant = false;
    PiecePtr capturedPiece;
    std::string toString();
public:
    Move(SquarePtr from, SquarePtr to, PlayerPtr player);
    Move(std::string move, BoardPtr& board, PlayerPtr player);
    Move(std::string move, PlayerPtr player);
    void execute(GameDataPtr &gameData);
    void undo(GameDataPtr &gameData);
    std::string getAbbr();
    const SquarePtr &getFrom() const;
    const SquarePtr &getTo() const;
    PlayerPtr getPlayer() const;
};

#endif //CHESS_MOVE_H
