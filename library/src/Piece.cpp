#include "Piece.h"

#include <utility>
#include "Player.h"

Piece::Piece(PieceType type, PlayerPtr player, SquarePtr square) :
        type(type), player(std::move(player)), captured(false), firstMove(true), square(std::move(square)) {}

PlayerPtr Piece::getPlayer() const {
    return player;
}

SquarePtr Piece::getSquare() const {
    return square;
}

PieceType Piece::getType() const {
    return type;
}

std::string Piece::getAbbr() const {
    std::string abbr, name;
    if(player->getColor() == WHITE) abbr = "W";
    else abbr = "B";
    switch(type) {
        case PieceType::Pawn:
            name = "P";
            break;
        case PieceType::Rook:
            name = "R";
            break;
        case PieceType::Bishop:
            name = "B";
            break;
        case PieceType::Knight:
            name = "N";
            break;
        case PieceType::Queen:
            name = "Q";
            break;
        case PieceType::King:
            name = "K";
        default:
            break;
    }
    abbr += name;
    return abbr;
}

void Piece::setSquare(SquarePtr _square) {
    firstMove = false;
    square = std::move(_square);
}

bool Piece::isCaptured() const {
    return captured;
}

void Piece::setCaptured() {
    captured = true;
    square = nullptr;
}

void Piece::restore(SquarePtr _square) {
    captured = false;
    square = std::move(_square);
}

bool Piece::isFirstMove() const {
    return firstMove;
}

void Piece::setFirstMove() {
    firstMove = true;
}

Piece::~Piece() = default;