#ifndef CHESS_IVIEW_H
#define CHESS_IVIEW_H

#include "typedefs.h"

class IView {
protected:
    bool error;
private:
    virtual void displayColumnNames() const = 0;
    virtual void displayHorizontalEdge() const = 0;
    virtual void displayRow(BoardPtr &board, int row, std::string info) const = 0;
    virtual void displayBoard(GameDataPtr gameData) const = 0;
    virtual void displayCapturedPieces(GameDataPtr gameData) const = 0;
    virtual void displayEndGameMenu() const = 0;
public:
    IView();
    virtual ~IView();
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
    virtual void displayPlayerMoves(const PlayerPtr& player, GameDataPtr gameData) = 0;
    virtual void displayError(std::string message) const = 0;
    virtual bool restartOrQuit() const = 0;
};

#endif //CHESS_IVIEW_H
