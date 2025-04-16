#ifndef CHESS_COMPUTERPLAYER_H
#define CHESS_COMPUTERPLAYER_H

#include "Player.h"
#include "Move.h"

class ComputerPlayer final : public Player {
public:
    ComputerPlayer(std::string name, Color color);
    ~ComputerPlayer() override;
    /**
     * Returns random move. Method does not check for move correctness.
     * @param board Board object within Move can be executed
     * @param view unused
     */
    MovePtr getMove(BoardPtr board, ViewPtr view) override;

    /**
     * Returns random PieceType
     * @param view unused
     * @return value from {Knight, Rook, Bishop, Queen}
     */
    PieceType promotion(ViewPtr view) override;
};

#endif //CHESS_COMPUTERPLAYER_H
