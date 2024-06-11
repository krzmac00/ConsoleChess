#include "Pieces/Queen.h"
#include "Board.h"
#include "GameData.h"
#include <cmath>

Queen::Queen(PlayerPtr player, SquarePtr square) : Piece(PieceType::Queen, player, square) {}

bool Queen::canBeMovedToSquare(SquarePtr toSquare, GameDataPtr gameData) {
    if(toSquare == square) return false;
    BoardPtr board = gameData->getBoard();
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
    else if(std::abs(square->getRow() - toSquare->getRow()) == std::abs(square->getColumn() - toSquare->getColumn())){
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
        else { //if(to->getRow() < square->getRow() && to->getColumn() < square->getColumn())
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

Queen::~Queen() = default;
