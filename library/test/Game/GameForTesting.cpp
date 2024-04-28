#include "GameForTesting.h"

GameForTesting::GameForTesting(ViewPtr view) : Game(view) {}

const BoardPtr &GameForTesting::getBoard() const {
    return board;
}

void GameForTesting::setBoard(const BoardPtr &board) {
    Game::board = board;
}

PlayerPtr GameForTesting::getPlayer1() const {
    return Game::player1;
}

PlayerPtr GameForTesting::getPlayer2() const {
    return Game::player2;
}

PlayerPtr GameForTesting::getPlayerTurn() const {
    return Game::playerTurn;
}

void GameForTesting::setPlayer1(const PlayerPtr &player) {
    Game::player1 = player;
}

void GameForTesting::setPlayer2(const PlayerPtr &player) {
    Game::player2 = player;
}

void GameForTesting::setPlayerTurn(const PlayerPtr &player) {
    Game::playerTurn = player;
}

//public methods calling private methods from base class Game (only for testing purposes)
bool GameForTesting::loadGamePublic() {
    return Game::loadGame();
}

bool GameForTesting::saveGamePublic() {
    return Game::saveGame();
}

void GameForTesting::startGamePublic() {
    Game::startGame();
}

void GameForTesting::initializeGamePublic() {
    Game::initializeGame();
}

Event GameForTesting::handleMovePublic(PlayerPtr &player) {
    return Game::handleMove(player);
}

bool GameForTesting::isMoveCorrectPublic(PlayerPtr &player, MovePtr &move) {
    return Game::isMoveCorrect(player, move);
}

bool GameForTesting::isCastlingCorrectPublic(PlayerPtr &player, std::string castling) {
    return Game::isCastlingCorrect(player, castling);
}

void GameForTesting::promotionPublic(SquarePtr pawnSquare, PlayerPtr &player) {
    Game::promotion(pawnSquare, player);
}

bool GameForTesting::isPlayerInCheckAfterMovePublic(PlayerPtr &player, MovePtr &move) {
    return Game::isPlayerInCheckAfterMove(player, move);
}

PiecePtr GameForTesting::getCheckingPiecePublic(PlayerPtr &playerInCheck) {
    return Game::getCheckingPiece(playerInCheck);
}

bool GameForTesting::isCheckmatePublic(std::shared_ptr<Player> player) {
    return Game::isCheckmate(player);
}

bool GameForTesting::isSquareAttackedPublic(PlayerPtr &player, SquarePtr square) {
    return Game::isSquareAttacked(player, square);
}

bool GameForTesting::canCheckingPieceBeCapturedPublic(PlayerPtr &playerInCheck) {
    return Game::canCheckingPieceBeCaptured(playerInCheck);
}

bool GameForTesting::canKingBeMovedPublic(PlayerPtr &player) {
    return Game::canKingBeMoved(player);
}

bool GameForTesting::canCheckBeBlockedPublic(PlayerPtr &player) {
    return Game::canCheckBeBlocked(player);
}

bool GameForTesting::isStalematePublic(std::shared_ptr<Player> player) {
    return Game::isStalemate(player);
}
