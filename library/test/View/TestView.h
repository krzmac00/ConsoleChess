#ifndef SZACHY_PREZENTACJATEST_H
#define SZACHY_PREZENTACJATEST_H

#include <vector>
#include <list>
#include <memory>
#include <string>
#include "typedefs.h"
#include "View.h"


class TestView final : public View {
private:
    bool newGame;
    bool gameWithComputer;
    Color player1Color;
    std::list<std::string> moves;
    PieceType promotion;
    std::string menuOption;
    std::string filePath;

    void displayColumnNames() const override;
    void displayHorizontalEdge() const override;
    void displayRow(BoardPtr &board, int row, std::string info) const override;
    void displayBoard(BoardPtr &board, PlayerPtr &player1, PlayerPtr &player2) const override;
    void displayCapturedPieces(PlayerPtr &player1, PlayerPtr &player2) const override;
    void displayEndGameMenu() const override;

public:
    TestView();
    bool readIfNewGame() const override;
    bool readUserChoice() const override;
    Color readUserChoiceOfColor() const override;
    std::string readMove(Color color) override;
    PieceType readPromotionChoice() override;

    //setters
    void setNewGame(bool _newGame);
    void setGameWithComputer(bool _gameWithComputer);
    void setPlayer1Color(Color _player1Color);
    void setMoves(const std::string &_moves);
    void setPromotion(PieceType type);
    void setMenuOption(const std::string &option);
    void setFilePath(const std::string &path);

    //unused
    void displayDefView(BoardPtr &board, PlayerPtr &player1, PlayerPtr &player2) override;
    void displayWinner(PlayerPtr winner) const override;
    void displayDraw() const override;
    void displayCheckInfo(PlayerPtr &player) const override;
    std::string readUserChoiceOfMenuOption() const override;
    std::string readFilePath() const override;
    void displayMenu() const override;
    void displayPlayerMoves(PlayerPtr&) override;
    void displayError(std::string message) const override;
    bool restartOrQuit() const override;
};


#endif //SZACHY_PREZENTACJATEST_H
