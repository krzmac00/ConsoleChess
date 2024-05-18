#include "GameData.h"

GameData::GameData(const BoardPtr& board, const PlayerPtr& player1, const PlayerPtr& player2, PlayerPtr& playerTurn) :
    board(board),
    player1(player1),
    player2(player2),
    playerTurn(playerTurn == player1 ? const_cast<PlayerPtr&>(this->player1) : const_cast<PlayerPtr&>(this->player2)) {}

const BoardPtr &GameData::getBoard() const {
    return board;
}

const PlayerPtr &GameData::getPlayer1() const {
    return player1;
}

const PlayerPtr &GameData::getPlayer2() const {
    return player2;
}

const PlayerPtr &GameData::getPlayerTurn() const {
    return playerTurn;
}

void GameData::nextTurn() {
    if(playerTurn == player1) {
        playerTurn = player2;
    }
    else {
        playerTurn = player1;
    }
}
