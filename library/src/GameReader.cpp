#include "GameReader.h"
#include "GameData.h"
#include "Board.h"
#include "Players/HumanPlayer.h"
#include "Players/ComputerPlayer.h"
#include <fstream>
#include <sstream>

GameDataPtr GameReader::loadGame(std::string filePath) noexcept(false) {
    BoardPtr board = std::make_shared<Board>();
    PlayerPtr player1;
    PlayerPtr player2;
    PlayerPtr playerTurn;

    std::fstream file;
    file.open(filePath, std::ios::in);
    if (!file.is_open()) throw FileException(filePath);

    //creating squares
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board->addSquare(i, j);

    std::string line, table[8][8];
    for(int i = 0; i < 8; i++) {
        getline(file, line);
        std::istringstream isstream(line);
        for (int j = 0; j < 8; ++j) {
            isstream >> table[i][j];
        }
        getline(file, line);
    }
    //player that saves game
    getline(file, line);
    std::string temp, playerThatSaves;
    std::istringstream isstreamZ(line);
    isstreamZ >> temp >> playerThatSaves;

    //player1
    getline(file, line);
    std::istringstream isstream1(line);
    std::string firstPlayer, color1, squareOfCheckingPiece1;
    isstream1 >> firstPlayer >> color1 >> squareOfCheckingPiece1;
    Color colorOfPlayer1;
    if(color1 == "WHITE") colorOfPlayer1 = WHITE;
    else colorOfPlayer1 = BLACK;
    player1 = std::make_shared<HumanPlayer>(firstPlayer, colorOfPlayer1);

    //player2
    getline(file, line);
    std::istringstream isstream2(line);
    std::string secondPlayer, color2, squareOfCheckingPiece2;
    Color colorOfPlayer2;
    isstream2 >> secondPlayer >> color2 >> squareOfCheckingPiece2;
    if(color2 == "WHITE") colorOfPlayer2 = WHITE;
    else colorOfPlayer2 = BLACK;
    if(secondPlayer == "ComputerPlayer") player2 = std::make_shared<ComputerPlayer>(secondPlayer, colorOfPlayer2);
    else player2 = std::make_shared<HumanPlayer>(secondPlayer, colorOfPlayer2);

    //moves of player1
    getline(file, line);
    std::istringstream moves1(line);
    while(moves1.peek() != decltype(moves1)::traits_type::eof()){
        std::string buf;
        moves1 >> buf;
        player1->addMove(buf);
    }
    //moves of player2
    getline(file, line);
    std::istringstream moves2(line);
    while(moves2.peek() != decltype(moves2)::traits_type::eof()){
        std::string buf;
        moves2 >> buf;
        player2->addMove(buf);
    }
    //pieces captured by player1
    getline(file, line);
    std::istringstream capturedPieces1(line);
    while(capturedPieces1.peek() != decltype(capturedPieces1)::traits_type::eof()){
        std::string buf;
        capturedPieces1 >> buf;
        player1->addCapturedPiece(buf);
    }
    //pieces captured by player2
    getline(file, line);
    std::istringstream capturedPieces2(line);
    while(capturedPieces2.peek() != decltype(capturedPieces2)::traits_type::eof()){
        std::string buf;
        capturedPieces2 >> buf;
        player2->addCapturedPiece(buf);
    }
    file.close();

    //adding pieces
    PlayerPtr owner;
    PlayerPtr white;
    PlayerPtr black;
    if(player1->getColor() == WHITE) {
        white = player1;
        black = player2;
    }
    else {
        white = player2;
        black = player1;
    }
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(table[i][j][0] != '[') {
                if(table[i][j][0] == 'B') owner = black;
                if(table[i][j][0] == 'W') owner = white;
                switch(table[i][j][1]) {
                    case 'P':
                        board->addPiece(PieceType::Pawn, owner, i, j);
                        break;
                    case 'R':
                        board->addPiece(PieceType::Rook, owner, i, j);
                        break;
                    case 'N':
                        board->addPiece(PieceType::Knight, owner, i, j);
                        break;
                    case 'B':
                        board->addPiece(PieceType::Bishop, owner, i, j);
                        break;
                    case 'Q':
                        board->addPiece(PieceType::Queen, owner, i, j);
                        break;
                    case 'K':
                        board->addPiece(PieceType::King, owner, i, j);
                        owner->setKing(board->getSquare(i, j)->getPiece());
                        break;
                    default:
                        break;
                }
                if(table[i][j][2] == '0')
                    board->getSquare(i, j)->getPiece()->setFirstMove(false);
            }
        }
    }

    //set player that will move first (one that saved)
    if(playerThatSaves == player1->getName()) playerTurn = player1;
    else playerTurn = player2;

    //set check
    if(squareOfCheckingPiece1.length() > 0) {
        int row = 8 - (squareOfCheckingPiece1[1] - '0');
        char column = squareOfCheckingPiece1[0] - 'A';
        player1->setCheck(board->getSquare(row, column)->getPiece());
    }
    else if(squareOfCheckingPiece2.length() > 0) {
        int row = 8 - (squareOfCheckingPiece2[1] - '0');
        char column = squareOfCheckingPiece2[0] - 'A';
        player2->setCheck(board->getSquare(row, column)->getPiece());
    }
    return std::make_shared<GameData>(board, player1, player2, playerTurn);
}
