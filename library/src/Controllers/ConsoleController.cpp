#include "Controllers/ConsoleController.h"
#include "Exceptions/FileException.h"
#include "GameLogic.h"
#include "GameReader.h"
#include "GameWriter.h"
#include "Move.h"

ConsoleController::ConsoleController(ViewPtr view) : IController(view) {}

bool ConsoleController::play() {

    if(view->readIfNewGame()) {
        bool playWithComputer = view->readIfPlayWithComputer();
        Color player1Color = view->readChoiceOfColor();
        this->gameData = GameLogic::initializeGame(player1Color, playWithComputer);
    }
    else {
        std::string path = view->readFilePath();
        try{
            this->gameData = GameReader::loadGame(path);
        }
        catch (FileException &e) {
            view->displayError(e.what());
            if(view->restartOrQuit()) return true;
            else return false;
        }
    }

    while(true) {
        BoardPtr board = gameData->getBoard();
        PlayerPtr player1 = gameData->getPlayer1();
        PlayerPtr player2 = gameData->getPlayer2();
        PlayerPtr playerTurn = gameData->getPlayerTurn();

        PlayerPtr otherPlayer;
        if(playerTurn == player1){
            otherPlayer = player2;
        }
        else otherPlayer = player1;

        view->displayDefView(gameData);
        Event event = this->handleMove();
        view->setError(false);
        if(event == Event::quit) return false;
        //if(event == Event::Move)

        playerTurn->cancelCheck();
        //check if other player is in check
        PiecePtr checkingPiece = GameLogic::getCheckingPiece(otherPlayer, gameData);
        if(checkingPiece != nullptr) otherPlayer->setCheck(checkingPiece);

        if(GameLogic::isCheckmate(otherPlayer, gameData)) {
            view->displayDefView(gameData);
            view->displayWinner(playerTurn);
            std::string option = view->readUserChoiceOfMenuOption();
            if(option == "N") return true;
            else return false;
        }
        else if(GameLogic::isStalemate(otherPlayer, gameData)) {
            view->displayDefView(gameData);
            view->displayDraw();
            std::string option = view->readUserChoiceOfMenuOption();
            if(option == "N") return true;
            else return false;
        }

        gameData->nextTurn();
    }
}

Event ConsoleController::handleMove() {
    BoardPtr board = gameData->getBoard();
    const PlayerPtr& player = gameData->getPlayerTurn();
    MovePtr move;
    bool isCorrect = false;
    do {
        move = player->getMove(board, view);
        if(move == nullptr) {
            while(true) {
                view->displayMenu();
                std::string option = view->readUserChoiceOfMenuOption();
                if (option == "D") view->displayPlayerMoves(player);
                else if(option == "S") {
                    try {
                        GameWriter::saveGame(gameData, view->readFilePath());
                    }
                    catch (FileException &e) {
                        view->displayError(e.what());
                    }
                }
                else if(option == "Q") return Event::quit;
                else break;
            }
        }
        else {
            if(move->getAbbr() == "O-O" || move->getAbbr() == "O-O-O")
                isCorrect = GameLogic::isCastlingCorrect(player, move->getAbbr(), gameData);
            else isCorrect = GameLogic::isMoveCorrect(player, move, gameData);

            if(isCorrect) move->execute(player, board);
            else view->setError(true);
        }
    } while(!isCorrect);
    //promotion
    if(GameLogic::checkIfPromotion(move, gameData)) {
        PieceType piece = player->promotion(view);
        GameLogic::promotePawn(piece, GameLogic::checkIfPromotion(move, gameData), gameData);
    }
    return Event::move;
}
