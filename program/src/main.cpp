#include "View/ConsoleView.h"
#include "typedefs.h"
#include "Game.h"


using namespace std;

int main() {
    ViewPtr consoleView = std::make_shared<ConsoleView>();
    Game game(consoleView);
    bool play = true;
    while(play){
        play = game.play();
    }
    return 0;
}
