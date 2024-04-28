#include "Player.h"

#include <utility>
#include "Piece.h"
#include "Check.h"

Player::Player(std::string name, Color color) : name(std::move(name)), color(color), king(nullptr) {
    check = std::make_shared<Check>();
    moves.reserve(15);
    capturedPieces.reserve(15);
}

std::string Player::getName() const {
    return name;
}

Color Player::getColor() const {
    return color;
}

void Player::addMove(const std::string& move) {
    moves.emplace_back(move);
}

std::vector<std::string> Player::getMoves() const {
    return moves;
}

void Player::addCapturedPiece(const std::string& piece) {
    capturedPieces.emplace_back(piece);
}

std::vector<std::string> Player::getCapturedPieces() const {
    return capturedPieces;
}

void Player::setKing(PiecePtr _king) {
    king = std::move(_king);
}

std::string Player::getLastMove() const {
    if (moves.empty()) return "";
    else return moves.back();
}

PiecePtr Player::getKing() const {
    return king;
}

bool Player::isInCheck() {
    return check->isCheck();
}

void Player::setCheck(const PiecePtr& checkingPiece) {
    check->setCheck(true);
    check->setCheckingPiece(checkingPiece);
}

void Player::cancelCheck() {
    check->setCheck(false);
    check->setCheckingPiece(nullptr);
}

CheckPtr Player::getCheck() const {
    return this->check;
}

void Player::removeLastCapturedPiece() {
    if(!capturedPieces.empty()) capturedPieces.pop_back();
}

void Player::removeLastMove() {
    if(!moves.empty()) moves.pop_back();
}

Player::~Player() = default;
