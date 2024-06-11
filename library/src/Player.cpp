#include "Player.h"
#include <utility>
#include "Piece.h"

Player::Player(std::string name, Color color) : name(std::move(name)), color(color), king(nullptr) {}

std::string Player::getName() const {
    return name;
}

Color Player::getColor() const {
    return color;
}

void Player::setKing(PiecePtr _king) {
    king = std::move(_king);
}

PiecePtr Player::getKing() const {
    return king;
}

bool Player::isInCheck() {
    if(checkingPiece.lock() == nullptr) return false;
    else return true;
}

void Player::setCheckingPiece(const PiecePtr& piece) {
    checkingPiece = piece;
}

void Player::cancelCheck() {
    checkingPiece.reset();
}

PiecePtr Player::getCheckingPiece() const {
    return checkingPiece.lock();
}

Player::~Player() = default;
