#include "Pieces/King.h"
#include "Board.h"
#include <cmath>

King::King(PlayerPtr player, SquarePtr square) : Piece(PieceType::King, player, square) {}

bool King::canBeMovedToSquare(SquarePtr toSquare, [[maybe_unused]]GameDataPtr gameData) {
    if(toSquare == square) return false;
    if(std::abs(square->getRow() - toSquare->getRow()) <= 1 && std::abs(square->getColumn() - toSquare->getColumn()) <= 1) {
        return true;
    }
    else return false;
}

King::~King() = default;
