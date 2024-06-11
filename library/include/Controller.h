#ifndef CHESS_CONTROLLER_H
#define CHESS_CONTROLLER_H

#include "IView.h"
#include "GameData.h"

class Controller {
protected:
    ViewPtr view;
    GameDataPtr gameData;
protected:
    Event handleMove();
public:
    Controller(ViewPtr view);
    virtual bool play();
};

#endif //CHESS_CONTROLLER_H
