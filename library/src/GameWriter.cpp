#include "GameWriter.h"
#include "GameData.h"
#include "Board.h"
#include "Player.h"
#include "Check.h"
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
         (player1->isInCheck() ? player1->getCheck()->getCheckingPiece()->getSquare()->toString() : "" ) << std::endl;
    file << player2->getName() << " " << player2->getColor() << " " <<
         (player2->isInCheck() ? player2->getCheck()->getCheckingPiece()->getSquare()->toString() : "" ) << std::endl;

    //Save players moves
    std::vector<std::string> movesOfPlayer1 = player1->getMoves();
    std::vector<std::string> movesOfPlayer2 = player2->getMoves();
    bool first = true;
    for(auto &move : movesOfPlayer1) {
        if(first) {
            file << move;
            first = false;
        }
        else file << " " << move;
    }
    file << std::endl;
    first = true;
    for(auto &move : movesOfPlayer2) {
        if(first) {
            file << move;
            first = false;
        }
        else file << " " << move;
    }
    file << std::endl;

    //Save captured pieces
    std::vector<std::string> piecesCapturedByPlayer1 = player1->getCapturedPieces();
    std::vector<std::string> piecesCapturedByPlayer2 = player2->getCapturedPieces();
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
