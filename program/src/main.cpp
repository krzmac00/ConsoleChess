#include "View/ConsoleView.h"
#include "typedefs.h"
#include "Controller.h"


using namespace std;

int main() {
    ViewPtr consoleView = std::make_shared<ConsoleView>();
    Controller controller(consoleView);
    bool play = true;
    while(play) {
        play = controller.play();
    }
    return 0;
}
