#ifndef CHESS_CHECK_H
#define CHESS_CHECK_H

#include "typedefs.h"

class Check {
    bool check;
    PiecePtr checkingPiece;
public:
    Check();
    void setCheck(bool isCheck);
    void setCheckingPiece(const PiecePtr& _checkingPiece);
    bool isCheck() const;
    const PiecePtr& getCheckingPiece() const;
};

#endif //CHESS_CHECK_H
