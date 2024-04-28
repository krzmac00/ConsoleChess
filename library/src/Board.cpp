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
    chessboard[row][column] = std::make_shared<Square>(row, column);
}

SquarePtr Board::getSquare(int row, int column) {
    return chessboard[row][column];
}

void Board::addPiece(PieceType piece, PlayerPtr player, int row, int column) {
    PiecePtr fig = PiecesCreator::create(piece, player, chessboard[row][column]);
    chessboard[row][column]->setPiece(fig);
    pieces.emplace_back(fig);
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

std::string Board::toString() const {
    std::string result;
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {
            std::string abbr;
            chessboard[x][y]->getPiece() == nullptr ? abbr = "()" : abbr = chessboard[x][y]->getPiece()->getAbbr();
            result += abbr + " ";
            //if(y != 7) result += " ";
        }
        result += "\n";
    }
    return result;
}
