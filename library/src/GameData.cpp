#include "GameData.h"
#include "Players/HumanPlayer.h"
#include "Players/ComputerPlayer.h"

GameData::GameData(BoardPtr& board, PlayerPtr& player1, PlayerPtr& player2, PlayerPtr& playerTurn) :
    board(board),
    player1(player1),
    player2(player2),
    playerTurn(playerTurn) {}

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
