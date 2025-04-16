#include "GameWriter.h"
#include "GameData.h"
#include "Board.h"
#include "Player.h"
#include "Move.h"
#include <fstream>
#include <sstream>

void GameWriter::saveGame(GameDataPtr gameData, std::string filePath) noexcept(false) {
    BoardPtr board = gameData->getBoard();
    PlayerPtr player1 = gameData->getPlayer1();
    PlayerPtr player2 = gameData->getPlayer2();
    PlayerPtr playerTurn = gameData->getPlayerTurn();

    std::fstream file;
    file.open(filePath, std::ios::out | std::ios::trunc);
    if(!file.is_open()) throw FileException(filePath);

    //Save pieces positions
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {
            std::string abbr;
            board->getSquare(x, y)->getPiece() == nullptr ?
                    abbr = "[.]" : (abbr = board->getSquare(x,y)->getPiece()->getAbbr() + (board->getSquare(x,y)->getPiece()->isFirstMove() ? "1" : "0"));
            file << abbr << "   ";
        }
        file << std::endl << std::endl;
    }

    //Save player that saves the game
    file << "Save: " << (playerTurn == player1 ? player1->getName() : player2->getName()) << std::endl;

    //Save players
    file << player1->getName() << " " << player1->getColor() << " " <<
         (player1->isInCheck() ? player1->getCheckingPiece()->getSquare()->toString() : "" ) << std::endl;
    file << player2->getName() << " " << player2->getColor() << " " <<
         (player2->isInCheck() ? player2->getCheckingPiece()->getSquare()->toString() : "" ) << std::endl;

    //Save history of moves
    auto movesHistory = gameData->getMovesHistory();
    for(auto it = movesHistory.begin(); it != movesHistory.end() - 1; it++) file << (*it)->getAbbr() << " ";
    file << (*(movesHistory.end() - 1))->getAbbr()<< std::endl;

    //Save players moves
//    std::vector<std::string> abbrMovesOfPlayer1;
//    std::vector<std::string> abbrMovesOfPlayer2;
//    std::vector<MovePtr> movesOfPlayer1 = gameData->getMovesOfPlayer(player1);
//    std::vector<MovePtr> movesOfPlayer2 = gameData->getMovesOfPlayer(player2);
//    for(auto &m : movesOfPlayer1) {
//        abbrMovesOfPlayer1.emplace_back(m->getAbbr());
//    }
//    for(auto &m : movesOfPlayer2) {
//        abbrMovesOfPlayer2.emplace_back(m->getAbbr());
//    }
//
//    bool first = true;
//    for(auto &move : abbrMovesOfPlayer1) {
//        if(first) {
//            file << move;
//            first = false;
//        }
//        else file << " " << move;
//    }
//    file << std::endl;
//    first = true;
//    for(auto &move : abbrMovesOfPlayer2) {
//        if(first) {
//            file << move;
//            first = false;
//        }
//        else file << " " << move;
//    }
//    file << std::endl;

    bool first = true;

    //Save captured pieces
    auto pieces = board->getPieces();
    std::vector<std::string> piecesCapturedByPlayer1;
    std::vector<std::string> piecesCapturedByPlayer2;

    for(auto &piece : pieces) {
        if(piece->isCaptured()) {
            if(piece->getPlayer() == player1) piecesCapturedByPlayer2.emplace_back(piece->getAbbr());
            else piecesCapturedByPlayer1.emplace_back(piece->getAbbr());
        }
    }

    first = true;
    for(auto &piece : piecesCapturedByPlayer1) {
        if(first) {
            file << piece;
            first = false;
        }
        else file << " " << piece;
    }
    file << std::endl;
    first = true;
    for(auto &piece : piecesCapturedByPlayer2) {
        if(first) {
            file << piece;
            first = false;
        }
        else file << " " << piece;
    }
    file << std::endl;
    file.close();
}
