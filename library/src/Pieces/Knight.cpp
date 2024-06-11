#include "Pieces/Knight.h"
#include <cmath>

Knight::Knight(PlayerPtr player, SquarePtr square) : Piece(PieceType::Knight, player, square) {}

bool Knight::canBeMovedToSquare(SquarePtr toSquare, [[maybe_unused]]GameDataPtr gameData) {
    if(toSquare == square) return false;
    if(std::abs(square->getRow() - toSquare->getRow()) == 2 && std::abs(square->getColumn() - toSquare->getColumn()) == 1) {}
    else if(std::abs(square->getColumn() - toSquare->getColumn()) == 2 && std::abs(square->getRow() -
                                                                                   toSquare->getRow()) == 1) {}
    else return false;
    return true;
}

Knight::~Knight() = default;
