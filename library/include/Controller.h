#ifndef CHESS_CONTROLLER_H
#define CHESS_CONTROLLER_H

#include "IView.h"
#include "GameData.h"

class Controller {
protected:
    ViewPtr view;
    GameDataPtr gameData;
protected:
    /**
     * Handles getting move, its execution and special events that can be triggered when move is obtained from a user.
     * @return Event::move if user entered move, Event::quit if user chose to quit
     */
    Event handleMove();
public:
    Controller(ViewPtr view);

    /**
     * Chess game main loop.
     * @return true if user wishes to continue\n
     *         false if user wants to quit
     */
    virtual bool play();
};

#endif //CHESS_CONTROLLER_H
