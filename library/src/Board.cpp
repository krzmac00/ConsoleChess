#include "Board.h"
#include "PiecesCreator.h"
#include "Player.h"
#include "Square.h"
#include <memory>
#include <algorithm>

Board::Board() {
    pieces.reserve(32);
}

void Board::addSquare(int row, int column) {
    if(row < 0 || row > 7 || column < 0 || column > 7) return;
    chessboard[row][column] = std::make_shared<Square>(row, column);
}

SquarePtr Board::getSquare(int row, int column) {
    return chessboard[row][column];
}

void Board::addPiece(PieceType pieceType, PlayerPtr player, int row, int column) {
    PiecePtr piece = PiecesCreator::create(pieceType, player, chessboard[row][column]);
    chessboard[row][column]->setPiece(piece);
    pieces.emplace_back(piece);
}

void Board::addCapturedPiece(PieceType pieceType, PlayerPtr player) {
    PiecePtr piece = PiecesCreator::create(pieceType, player, nullptr);
    piece->setCaptured();
    pieces.emplace_back(piece);
}

void Board::deletePiece(PiecePtr piece) {
    //piece->getSquare()->setPiece(nullptr);
    pieces.erase(std::remove(pieces.begin(), pieces.end(), piece), pieces.end());
}

std::vector<PiecePtr> Board::getPieces() const {
    return pieces;
}

std::vector<PiecePtr> Board::getPiecesOfPlayer(PlayerPtr player) const {
    std::vector<PiecePtr> playerPieces;
    for(auto &piece : pieces) {
        if(piece->getPlayer() == player && !piece->isCaptured()) playerPieces.push_back(piece);
    }
    return playerPieces;
}

std::vector<PiecePtr> Board::getPiecesCapturedByPlayer(PlayerPtr player) const {
    std::vector<PiecePtr> capturedPieces;
    for(auto &piece : pieces) {
        if(piece->getPlayer() != player && piece->isCaptured()) capturedPieces.push_back(piece);
    }
    return capturedPieces;
}

std::string Board::toString() const {
    std::string result;
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {
            std::string abbr;
            chessboard[x][y]->getPiece() == nullptr ?
            abbr = "[.]" : (abbr = chessboard[x][y]->getPiece()->getAbbr() + (chessboard[x][y]->getPiece()->isFirstMove() ? "1" : "0"));
            result += abbr + "   ";
        }
        result += "\n\n";
    }
    return result;
}
