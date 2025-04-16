#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <vector>
#include "typedefs.h"
#include "Piece.h"
/**
 * @brief Stores and manages squares and pieces
 */
class Board {
    /**
     * Stores Squares(SquarePtr) as 2-dimensional array,
     * so that each square can be accessed by two numbers: row and column.\n
     * Array is arranged in a way that chessboard[0][0] refers to chessboard left top corner (A8 square)
     * and chessboard[7][7] refers to chessboard bottom right corner (H1 square).
     */
    SquarePtr chessboard[8][8];
    std::vector<PiecePtr> pieces;
public:
    /**
     * @brief Basic Board ctor.
     * Initializes pieces vector with capacity of 32
     */
    Board();

    /**
     * @brief Initializes SquarePtr with object of Square(row, column)
     * @param row [0, 7]
     * @param column [0, 7]
     */
    void addSquare(int row, int column);

    /**
     * @brief Adds Piece object to pieces vector.
     * Object creation is delegated to PiecesCreator::create() method.
     * @param pieceType {Bishop, Queen, King, Pawn, Knight, Rook}
     * @param player piece owner
     * @param row row of Square that piece is placed in
     * @param column column of Square that piece is placed in
     */
    void addPiece(PieceType pieceType, PlayerPtr player, int row, int column);

    /**
     * @brief Adds Piece that is captured (Piece.square = nullptr, Piece.captured = true)
     * Method designed for restoring information from game save.
     * @param pieceType {Bishop, Queen, King, Pawn, Knight, Rook}
     * @param player piece owner
     */
    void addCapturedPiece(PieceType pieceType, PlayerPtr player);

    /**
     * @brief Removes piece from pieces vector.
     * Used for deleting pawn when promotion occurs.
     * @param piece
     */
    void deletePiece(PiecePtr piece);

    SquarePtr getSquare(int row, int column);
    std::vector<PiecePtr> getPieces() const;
    std::vector<PiecePtr> getPiecesOfPlayer(PlayerPtr player) const;
    std::vector<PiecePtr> getPiecesCapturedByPlayer(PlayerPtr player) const;

    /**
     * @brief Exports information about Board to std::string in human readable format.
     * Each square is defined by 3 characters and its position in 2d array.
     * Empty Square is denoted as "[.]".
     * If Square is occupied by Piece:\n
     *  - first character defines color of player that owns the piece - "B" for black or "W" for white\n
     *  - second character defines piece type, value is from {B, K, N, Q, R}\n
     *  - third character stores information if piece has already moved - value can be 1 if piece hasn't moved and 0 if has moved\n
     */
    std::string toString() const;
};

#endif //CHESS_BOARD_H
