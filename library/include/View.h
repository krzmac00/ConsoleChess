#ifndef CHESS_VIEW_H
#define CHESS_VIEW_H

#include "typedefs.h"

class View {
protected:
    bool error;
private:
    virtual void displayColumnNames() const = 0;
    virtual void displayHorizontalEdge() const = 0;
    virtual void displayRow(BoardPtr &board, int row, std::string info) const = 0;
    virtual void displayBoard(GameDataPtr gameData) const = 0;
    virtual void displayCapturedPieces(PlayerPtr &player1, PlayerPtr &player2) const = 0;
    virtual void displayEndGameMenu() const = 0;
public:
    View();
    virtual ~View();
    virtual void displayDefView(GameDataPtr gameData) = 0;
    virtual bool readIfNewGame() const = 0;
    virtual bool readIfPlayWithComputer() const = 0;
    virtual void displayWinner(PlayerPtr winner) const = 0;
    virtual void displayDraw() const = 0;
    virtual Color readChoiceOfColor() const = 0;
    virtual std::string readMove(Color color) = 0;
    virtual PieceType readPromotionChoice() = 0;
    virtual void displayCheckInfo(PlayerPtr &player) const = 0;
    virtual std::string readUserChoiceOfMenuOption() const = 0;
    virtual void setError(bool _error);
    virtual std::string readFilePath() const = 0;
    virtual void displayMenu() const = 0;
    virtual void displayPlayerMoves(const PlayerPtr& player) = 0;
    virtual void displayError(std::string message) const = 0;
    virtual bool restartOrQuit() const = 0;
};

#endif //CHESS_VIEW_H
