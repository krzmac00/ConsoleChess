#ifndef CHESS_COMPUTERPLAYER_H
#define CHESS_COMPUTERPLAYER_H

#include "Player.h"
#include "Move.h"

class ComputerPlayer final : public Player {
public:
    ComputerPlayer(std::string name, Color color);
    ~ComputerPlayer() override;
    MovePtr getMove(BoardPtr, ViewPtr) override;
    PieceType promotion(ViewPtr) override;
};

#endif //CHESS_COMPUTERPLAYER_H
