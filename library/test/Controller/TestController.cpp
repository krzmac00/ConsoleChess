#include "TestController.h"

TestController::TestController(ViewPtr view) : Controller(view) {}

const GameDataPtr &TestController::getGameData() const {
    return Controller::gameData;
}

Event TestController::handleMovePublic() {
    return Controller::handleMove();
}

bool TestController::play() {
    return Controller::play();
}
