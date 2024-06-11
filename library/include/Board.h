#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include "typedefs.h"
#include "Piece.h"

class Board {
    SquarePtr chessboard[8][8];
    std::vector<PiecePtr> pieces;
public:
    Board();
    void addSquare(int row, int column);
    void addPiece(PieceType pieceType, PlayerPtr player, int row, int column);
    void addCapturedPiece(PieceType pieceType, PlayerPtr player);
    void deletePiece(PiecePtr piece);

    SquarePtr getSquare(int row, int column);
    std::vector<PiecePtr> getPieces() const;
    std::vector<PiecePtr> getPiecesOfPlayer(PlayerPtr player) const;
    std::vector<PiecePtr> getPiecesCapturedByPlayer(PlayerPtr player) const;
    std::string toString() const;
};

#endif //CHESS_BOARD_H
