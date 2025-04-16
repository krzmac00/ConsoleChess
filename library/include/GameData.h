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

    // getters
    const BoardPtr &getBoard() const;
    const PlayerPtr &getPlayer1() const;
    const PlayerPtr &getPlayer2() const;
    const PlayerPtr &getPlayerTurn() const;
    const std::vector<MovePtr> &getMovesHistory() const;

    /// switch playerTurn to point other player
    void nextTurn();
    /// adds Move to moveHistory vector
    void addMove(MovePtr move);
    /// removes Move from moveHistory vector
    void removeMove(MovePtr move);
    /// @return last Move from moveHistory vector
    MovePtr getLastMove() const;
    /// @return last Move of player from moveHistory vector
    MovePtr getLastMove(PlayerPtr player) const;
    /// @return all Moves of player from moveHistory vector
    std::vector<MovePtr> getMovesOfPlayer(PlayerPtr player) const;
};

#endif //CHESS_GAMEDATA_H
