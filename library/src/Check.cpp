#include "Check.h"

Check::Check() : check(false), checkingPiece(nullptr) {}

void Check::setCheck(bool isCheck) {
    Check::check = isCheck;
}

void Check::setCheckingPiece(const PiecePtr& _checkingPiece) {
    Check::checkingPiece = _checkingPiece;
}

bool Check::isCheck() const {
    return check;
}

const PiecePtr &Check::getCheckingPiece() const {
    return checkingPiece;
}
