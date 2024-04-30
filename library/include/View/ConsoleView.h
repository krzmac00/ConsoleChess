#ifndef CHESS_CONSOLEVIEW_H
#define CHESS_CONSOLEVIEW_H

#include <memory>
#include <string>
#include "View.h"

class Board;
class Player;

class ConsoleView final : public View {

private:
    void displayColumnNames() const override;
    void displayHorizontalEdge() const override;
    void displayRow(BoardPtr &board, int row, std::string info) const override;
    void displayBoard(BoardPtr &board, PlayerPtr &player1, PlayerPtr &player2) const override;
    void displayCapturedPieces(PlayerPtr &player1, PlayerPtr &player2) const override;
    void displayEndGameMenu() const override;
public:
    ConsoleView();
    void displayDefView(BoardPtr &board, PlayerPtr &player1, PlayerPtr &player2) override;
    bool readIfNewGame() const override;
    bool readUserChoice() const override;
    void displayWinner(PlayerPtr winner) const override;
    void displayDraw() const override;
    Color readUserChoiceOfColor() const override;
    std::string readMove(Color color) override;
    PieceType readPromotionChoice() override;
    void displayCheckInfo(PlayerPtr &player) const override;
    std::string readUserChoiceOfMenuOption() const override;
    std::string readFilePath() const override;
    void displayMenu() const override;
    void displayPlayerMoves(PlayerPtr &player) override;
    void displayError(std::string message) const override;
    bool restartOrQuit() const override;
};

#endif //CHESS_CONSOLEVIEW_H
