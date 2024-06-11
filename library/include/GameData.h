#ifndef CHESS_GAMEDATA_H
#define CHESS_GAMEDATA_H

#include "typedefs.h"
#include "Board.h"
#include "Player.h"
#include <vector>

class GameData {
    const BoardPtr board;
    const PlayerPtr player1;
    const PlayerPtr player2;
    PlayerPtr playerTurn;
    std::vector<MovePtr> movesHistory;
public:
    GameData(const BoardPtr& board, const PlayerPtr& player1, const PlayerPtr& player2, PlayerPtr& playerTurn);

    const BoardPtr &getBoard() const;
    const PlayerPtr &getPlayer1() const;
    const PlayerPtr &getPlayer2() const;
    const PlayerPtr &getPlayerTurn() const;

    void nextTurn();
    void addMove(MovePtr move);
    void removeMove(MovePtr move);
    MovePtr getLastMove() const;
    MovePtr getLastMove(PlayerPtr player) const;
    std::vector<MovePtr> getMovesOfPlayer(PlayerPtr player) const;
    const std::vector<MovePtr> &getMovesHistory() const;
};

#endif //CHESS_GAMEDATA_H
