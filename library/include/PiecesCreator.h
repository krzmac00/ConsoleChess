#ifndef CHESS_PIECESCREATOR_H
#define CHESS_PIECESCREATOR_H

#include "typedefs.h"

class PiecesCreator {
public:
    /**
     * Factory method.
     * @param type {Bishop, King, Knight, Pawn, Queen, Rook}
     * @param player piece owner
     * @param square Square that piece is originally placed in
     * @return newly created Piece
     */
    static PiecePtr create(PieceType type, PlayerPtr player, SquarePtr square);
};

#endif //CHESS_PIECESCREATOR_H
