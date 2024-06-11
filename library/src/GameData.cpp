#include "GameData.h"
#include "Move.h"
#include <algorithm>

GameData::GameData(const BoardPtr& board, const PlayerPtr& player1, const PlayerPtr& player2, PlayerPtr& playerTurn) :
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

void GameData::addMove(MovePtr move) {
    movesHistory.emplace_back(move);
}

void GameData::removeMove(MovePtr move) {
    movesHistory.erase(std::remove(movesHistory.begin(), movesHistory.end(), move), movesHistory.end());
}

MovePtr GameData::getLastMove() const {
    if(movesHistory.empty()) return nullptr;
    else return movesHistory.back();
}

std::vector<MovePtr> GameData::getMovesOfPlayer(PlayerPtr player) const {
    std::vector<MovePtr> moves;
    for(auto &m : movesHistory) {
        if(m->getPlayer() == player) moves.emplace_back(m);
    }
    return moves;
}

MovePtr GameData::getLastMove(PlayerPtr player) const {
    MovePtr move = GameData::getLastMove();
    if(move == nullptr || move->getPlayer() == player) return move;
    else if (movesHistory.size() < 2 ) return nullptr;
    return movesHistory[movesHistory.size() - 2];
}

const std::vector<MovePtr> &GameData::getMovesHistory() const {
    return movesHistory;
}
