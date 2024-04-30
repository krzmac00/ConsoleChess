#ifndef CHESS_CONSOLECONTROLLER_H
#define CHESS_CONSOLECONTROLLER_H

#include "IController.h"

class ConsoleController final : public IController {
    Event handleMove();
public:
    ConsoleController(ViewPtr view);
    bool play() override;
};

#endif //CHESS_CONSOLECONTROLLER_H
