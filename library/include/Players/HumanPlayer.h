#ifndef CHESS_HUMANPLAYER_H
#define CHESS_HUMANPLAYER_H

#include "Player.h"
#include "Move.h"

class HumanPlayer final : public Player {
public:
    HumanPlayer(std::string name, Color color);
    ~HumanPlayer() override;
    /**
     * Method calls View::readMove(), which reads users input.
     * @param board Board object within Move can be executed
     * @param view object that allows to access View methods
     */
    MovePtr getMove(BoardPtr board, ViewPtr view) override;

    /**
     * Method calls View::readPromotionChoice(), which reads users input.
     * @param view object that allows to access View methods
     */
    PieceType promotion(ViewPtr view) override;
};

#endif //CHESS_HUMANPLAYER_H
