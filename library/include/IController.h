#ifndef CHESS_ICONTROLLER_H
#define CHESS_ICONTROLLER_H

#include "typedefs.h"
#include "View.h"
#include "GameData.h"

class IController {
protected:
    ViewPtr view;
    GameDataPtr gameData;
public:
    IController(ViewPtr _view);
    virtual bool play() = 0;
};

#endif //CHESS_ICONTROLLER_H
