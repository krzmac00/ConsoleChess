#include "View/ConsoleView.h"
#include "typedefs.h"
#include "Game.h"
#include "Controllers/ConsoleController.h"


using namespace std;

int main() {
    ViewPtr consoleView = std::make_shared<ConsoleView>();
//    Game game(consoleView);
//    bool play = true;
//    while(play){
//        play = game.play();
//    }
    ConsoleController controller(consoleView);
    bool play = true;
    while(play){
        play = controller.play();
    }
    return 0;
}
