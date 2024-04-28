#ifndef CHESS_HUMANPLAYER_H
#define CHESS_HUMANPLAYER_H

#include "Player.h"
#include "Move.h"

class HumanPlayer final : public Player {
public:
    HumanPlayer(std::string name, Color color);
    ~HumanPlayer() override;
    MovePtr executeMove(BoardPtr, ViewPtr) override;
    PieceType promotion(ViewPtr) override;
};

#endif //CHESS_HUMANPLAYER_H
