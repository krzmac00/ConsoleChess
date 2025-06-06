#ifndef SZACHY_PREZENTACJATEST_H
#define SZACHY_PREZENTACJATEST_H

#include <vector>
#include <list>
#include <memory>
#include <string>
#include "typedefs.h"
#include "IView.h"


class TestView final : public IView {
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
    void displayBoard(GameDataPtr gameData) const override;
    void displayCapturedPieces(GameDataPtr gameData) const override;
    void displayEndGameMenu() const override;

public:
    TestView();
    bool readIfNewGame() const override;
    bool readIfPlayWithComputer() const override;
    Color readChoiceOfColor() const override;
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
    void displayDefView(GameDataPtr gameData) override;
    void displayWinner(PlayerPtr winner) const override;
    void displayDraw() const override;
    void displayCheckInfo(PlayerPtr &player) const override;
    std::string readUserChoiceOfMenuOption() const override;
    std::string readFilePath() const override;
    void displayMenu() const override;
    void displayPlayerMoves(const PlayerPtr& player, GameDataPtr gameData) override;
    void displayError(std::string message) const override;
    bool restartOrQuit() const override;
};


#endif //SZACHY_PREZENTACJATEST_H
