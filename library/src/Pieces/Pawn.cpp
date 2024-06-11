#include "Pieces/Pawn.h"
#include "Player.h"
#include "GameData.h"
#include "Board.h"
#include "Move.h"
#include <cmath>

Pawn::Pawn(PlayerPtr player, SquarePtr square) : Piece(PieceType::Pawn, player, square) {}

bool Pawn::canBeMovedToSquare(SquarePtr toSquare, GameDataPtr gameData) {
    if(toSquare == square) return false;
    BoardPtr board = gameData->getBoard();
    if(player->getColor() == WHITE) {
        if(toSquare->getPiece() == nullptr) {
            if(square->getColumn() == toSquare->getColumn()) {
                //move 1 square forward
                if((square->getRow() - toSquare->getRow()) == 1) {}
                //move 2 square forward
                else if((square->getRow() - toSquare->getRow()) == 2) {
                    if(!firstMove) return false;
                    if(board->getSquare(square->getRow() - 1, square->getColumn())->getPiece() != nullptr) return false;
                }
                else return false;
            }
            //en passant
            else if(std::abs(square->getColumn() - toSquare->getColumn()) == 1) {
                PiecePtr piece = board->getSquare(square->getRow(), toSquare->getColumn())->getPiece();
                if(piece != nullptr && piece->getType() == PieceType::Pawn &&
                   piece->getPlayer()->getColor() != player->getColor()) {
                    MovePtr lastMove = gameData->getLastMove();
                    if(lastMove->getFrom() == nullptr || lastMove->getTo() == nullptr) return false;
                    int toColumn = toSquare->getColumn();
                    if(lastMove->getFrom()->getColumn() == toColumn && lastMove->getFrom()->getRow() == 1 &&
                        lastMove->getTo()->getColumn() == toColumn && lastMove->getTo()->getRow() == 3) {}
                    else return false;
                }
                else return false;
            }
            else return false;
        }
        //to->getPiece() != nullptr
        else {
            //default capture
            if(std::abs(square->getColumn() - toSquare->getColumn()) == 1 && square->getRow() -
                                                                             toSquare->getRow() == 1) {}
            else return false;
        }
    }
    //player->getColor() == BLACK
    else {
        if(toSquare->getPiece() == nullptr) {
            if(square->getColumn() == toSquare->getColumn()) {
                //move 1 square forward
                if((toSquare->getRow()) - square->getRow() == 1) {}
                //move 2 square forward
                else if((toSquare->getRow()) - square->getRow() == 2) {
                    if(!firstMove) return false;
                    if(board->getSquare(square->getRow() + 1, square->getColumn())->getPiece() != nullptr) return false;
                }
                else return false;
            }
            //en passant
            else if(std::abs(square->getColumn() - toSquare->getColumn()) == 1) {
                PiecePtr piece = board->getSquare(square->getRow(), toSquare->getColumn())->getPiece();
                if(piece != nullptr && piece->getType() == PieceType::Pawn &&
                   piece->getPlayer()->getColor() != player->getColor()) {
                    MovePtr lastMove = gameData->getLastMove();
                    if(lastMove->getFrom() == nullptr || lastMove->getTo() == nullptr) return false;
                    int toColumn = toSquare->getColumn();
                    if(lastMove->getFrom()->getColumn() == toColumn && lastMove->getFrom()->getRow() == 6 &&
                        lastMove->getTo()->getColumn() == toColumn && lastMove->getTo()->getRow() == 4) {}
                    else return false;
                }
                else return false;
            }
            else return false;
        }
        //toSquare->getPiece() != nullptr
        else {
            //default capture
            if(std::abs(square->getColumn() - toSquare->getColumn()) == 1 && toSquare->getRow() -
                                                                             square->getRow() == 1) {}
            else return false;
        }
    }
    return true;
}

Pawn::~Pawn() = default;
