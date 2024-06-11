#ifndef CHESS_TESTCONTROLLER_H
#define CHESS_TESTCONTROLLER_H

#include "Controller.h"


class TestController final : public Controller {

public:
    TestController(ViewPtr view);
    Event handleMovePublic();
    bool play() override;
    const GameDataPtr &getGameData() const;
};

#endif //CHESS_TESTCONTROLLER_H
