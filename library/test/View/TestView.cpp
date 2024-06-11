#include "TestView.h"
#include <iostream>
#include <sstream>

TestView::TestView() : IView(),
                       newGame(true),
                       gameWithComputer(false),
                       player1Color(WHITE),
                       menuOption(std::string("Q")) {}

bool TestView::readIfNewGame() const {
    return newGame;
}

bool TestView::readIfPlayWithComputer() const {
    return gameWithComputer;
}

Color TestView::readChoiceOfColor() const {
    return player1Color;
}

std::string TestView::readMove([[maybe_unused]] Color color) {
    if(moves.empty()) {
        menuOption = std::string("Q");
        return std::string{"M"};
    }
    std::string move = moves.front();
    moves.pop_front();
    return move;
}

PieceType TestView::readPromotionChoice() {
    return promotion;
}

std::string TestView::readUserChoiceOfMenuOption() const {
    return menuOption;
}

std::string TestView::readFilePath() const {
    return filePath;
}


//setters
void TestView::setNewGame(bool _newGame) {
    TestView::newGame = _newGame;
}

void TestView::setGameWithComputer(bool _gameWithComputer) {
    TestView::gameWithComputer = _gameWithComputer;
}

void TestView::setPlayer1Color(Color _player1Color) {
    TestView::player1Color = _player1Color;
}

void TestView::setMoves(const std::string &_moves) {
    std::istringstream iss(_moves);
    std::string move;
    while (std::getline(iss, move, ' ')) {
        if (!move.empty()) {
            moves.push_back(move);
        }
    }
}

void TestView::setPromotion(PieceType type) {
    TestView::promotion = type;
}

void TestView::setMenuOption(const std::string &option) {
    menuOption = option;
}

void TestView::setFilePath(const std::string &path) {
    TestView::filePath = path;
}


//unused
void TestView::displayColumnNames() const {}
void TestView::displayHorizontalEdge() const {}
void TestView::displayRow([[maybe_unused]] BoardPtr &board, [[maybe_unused]] int row, [[maybe_unused]] std::string info) const {}
void TestView::displayBoard([[maybe_unused]] GameDataPtr gameData) const {}
void TestView::displayCapturedPieces([[maybe_unused]] GameDataPtr gameData) const {}
void TestView::displayEndGameMenu() const {}
void TestView::displayDefView([[maybe_unused]] GameDataPtr gameData) {}
void TestView::displayWinner([[maybe_unused]] PlayerPtr winner) const {}
void TestView::displayDraw() const {}
void TestView::displayCheckInfo([[maybe_unused]] PlayerPtr &player) const {}
void TestView::displayMenu() const {}
void TestView::displayPlayerMoves([[maybe_unused]] const PlayerPtr& player, [[maybe_unused]] GameDataPtr gameData) {}
void TestView::displayError([[maybe_unused]] std::string message) const {}
bool TestView::restartOrQuit() const {return true;}
