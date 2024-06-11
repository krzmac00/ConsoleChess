#include "Pieces/Bishop.h"
#include "GameData.h"
#include "Board.h"

Bishop::Bishop(PlayerPtr player, SquarePtr square) : Piece(PieceType::Bishop, player, square) {}

bool Bishop::canBeMovedToSquare(SquarePtr toSquare, GameDataPtr gameData) {
    if(toSquare == square) return false;
    BoardPtr board = gameData->getBoard();
    if(std::abs(square->getRow() - toSquare->getRow()) == std::abs(square->getColumn() - toSquare->getColumn())){
        if(toSquare->getRow() < square->getRow() && toSquare->getColumn() > square->getColumn()) {
            int row = square->getRow();
            int column = square->getColumn();
            for(int i = 0; i < std::abs(square->getRow() - toSquare->getRow()) - 1; i++){
                row--;
                column++;
                if(board->getSquare(row, column)->getPiece() != nullptr) return false;
            }
        }
        else if(toSquare->getRow() > square->getRow() && toSquare->getColumn() < square->getColumn()) {
            int row = square->getRow();
            int column = square->getColumn();
            for(int i = 0; i < std::abs(square->getRow() - toSquare->getRow()) - 1; i++){
                row++;
                column--;
                if(board->getSquare(row, column)->getPiece() != nullptr) return false;
            }
        }
        else if(toSquare->getRow() > square->getRow() && toSquare->getColumn() > square->getColumn()) {
            int row = square->getRow();
            int column = square->getColumn();
            for(int i = 0; i < std::abs(square->getRow() - toSquare->getRow()) - 1; i++){
                row++;
                column++;
                if(board->getSquare(row, column)->getPiece() != nullptr) return false;
            }
        }
        else { //if(toSquare->getRow() < square->getRow() && toSquare->getColumn() < square->getColumn())
            int row = square->getRow();
            int column = square->getColumn();
            for(int i = 0; i < std::abs(square->getRow() - toSquare->getRow()) - 1; i++){
                row--;
                column--;
                if(board->getSquare(row, column)->getPiece() != nullptr) return false;
            }
        }
    }
    else return false;
    return true;
}

Bishop::~Bishop() = default;
