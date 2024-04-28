#include "Square.h"

Square::Square(int x, int y) : row(x), column(y) {}

void Square::setPiece(const PiecePtr& _piece) {
    if(_piece == nullptr) piece.reset();
    piece = _piece;
}

PiecePtr Square::getPiece() {
    return piece.lock();
}

int Square::getRow() const {
    return row;
}

int Square::getColumn() const {
    return column;
}

std::string Square::toString() const {
    return char('A' + this->column) + std::to_string(8 - this->row);
}
