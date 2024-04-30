#ifndef CHESS_GAMEDATA_H
#define CHESS_GAMEDATA_H

#include "typedefs.h"
#include "Board.h"
#include "Player.h"

class GameData {
    BoardPtr board;
    PlayerPtr player1;
    PlayerPtr player2;
    PlayerPtr playerTurn;
public:
    GameData(BoardPtr& board, PlayerPtr& player1, PlayerPtr& player2, PlayerPtr& playerTurn);

    const BoardPtr &getBoard() const;
    const PlayerPtr &getPlayer1() const;
    const PlayerPtr &getPlayer2() const;
    const PlayerPtr &getPlayerTurn() const;
    void nextTurn();
};

#endif //CHESS_GAMEDATA_H
