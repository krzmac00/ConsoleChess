#ifndef CHESS_GAMEDATA_H
#define CHESS_GAMEDATA_H

#include "typedefs.h"
#include "Board.h"
#include "Player.h"

class GameData {
    const BoardPtr board;
    const PlayerPtr player1;
    const PlayerPtr player2;
    PlayerPtr& playerTurn;
public:
    GameData(const BoardPtr& board, const PlayerPtr& player1, const PlayerPtr& player2, PlayerPtr& playerTurn);

    const BoardPtr &getBoard() const;
    const PlayerPtr &getPlayer1() const;
    const PlayerPtr &getPlayer2() const;
    const PlayerPtr &getPlayerTurn() const;
    void nextTurn();
};

#endif //CHESS_GAMEDATA_H
