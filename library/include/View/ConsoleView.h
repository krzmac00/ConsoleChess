#ifndef CHESS_CONSOLEVIEW_H
#define CHESS_CONSOLEVIEW_H

#include <memory>
#include <string>
#include "IView.h"

class Board;
class Player;

class ConsoleView final : public IView {

private:
    void displayColumnNames() const override;
    void displayHorizontalEdge() const override;
    void displayRow(BoardPtr &board, int row, std::string info) const override;
    void displayBoard(GameDataPtr gameData) const override;
    void displayCapturedPieces(GameDataPtr gameData) const override;
    void displayEndGameMenu() const override;
public:
    ConsoleView();
    void displayDefView(GameDataPtr gameData) override;
    bool readIfNewGame() const override;
    bool readIfPlayWithComputer() const override;
    void displayWinner(PlayerPtr winner) const override;
    void displayDraw() const override;
    Color readChoiceOfColor() const override;
    std::string readMove(Color color) override;
    PieceType readPromotionChoice() override;
    void displayCheckInfo(PlayerPtr &player) const override;
    std::string readUserChoiceOfMenuOption() const override;
    std::string readFilePath() const override;
    void displayMenu() const override;
    void displayPlayerMoves(const PlayerPtr &player, GameDataPtr gameData) override;
    void displayError(std::string message) const override;
    bool restartOrQuit() const override;
};

#endif //CHESS_CONSOLEVIEW_H
