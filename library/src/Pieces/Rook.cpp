#include "Pieces/Rook.h"
#include "Board.h"
#include <cmath>

Rook::Rook(PlayerPtr player, SquarePtr square) : Piece(PieceType::Rook, player, square) {}

bool Rook::canBeMovedToSquare(SquarePtr toSquare, BoardPtr board) {
    if(toSquare == square) return false;
    if(square->getRow() == toSquare->getRow()) {
        int row = square->getRow();
        int column;
        if(square->getColumn() > toSquare->getColumn()) column = toSquare->getColumn();
        else column = square->getColumn();
        for(int i = 0; i < std::abs(square->getColumn() - toSquare->getColumn()) - 1; i++) {
            column++;
            if(board->getSquare(row, column)->getPiece() != nullptr) return false;
        }
    }
    else if(square->getColumn() == toSquare->getColumn()) {
        int row;
        int column = square->getColumn();
        if(square->getRow() > toSquare->getRow()) row = toSquare->getRow();
        else row = square->getRow();
        for(int i = 0; i < std::abs(square->getRow() - toSquare->getRow()) - 1; i++) {
            row++;
            if(board->getSquare(row, column)->getPiece() != nullptr) return false;
        }
    }
    else return false;
    return true;
}

Rook::~Rook() = default;
