#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "typedefs.h"
#include <string>

class Move {
    SquarePtr from;
    SquarePtr to;
    std::string abbr;
    bool executed = false;
    bool pieceFirstMove = false;
    bool enPassant = false;
    PiecePtr capturedPiece;
    std::string toString();
public:
    Move(SquarePtr from, SquarePtr to);
    Move(std::string move, BoardPtr& board);
    Move(std::string move);
    void execute(const PlayerPtr &player, BoardPtr &board);
    void undo(const PlayerPtr &player, BoardPtr &board);
    std::string getAbbr();
    const SquarePtr &getFrom() const;
    const SquarePtr &getTo() const;
};

#endif //CHESS_MOVE_H
