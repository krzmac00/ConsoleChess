#include "GameReader.h"
#include "GameData.h"
#include "Board.h"
#include "Move.h"
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

    //board
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
    Color colorOfPlayer1;
    isstream1 >> firstPlayer >> color1 >> squareOfCheckingPiece1;
    if(firstPlayer.empty()) {
        file.close();
        throw FileStructureException(filePath, "Player1 name");
    }
    if(color1 == "WHITE") colorOfPlayer1 = WHITE;
    else if(color1 == "BLACK")colorOfPlayer1 = BLACK;
    else {
        file.close();
        throw FileStructureException(filePath, "Player1 color");
    }
    player1 = std::make_shared<HumanPlayer>(firstPlayer, colorOfPlayer1);

    //player2
    getline(file, line);
    std::istringstream isstream2(line);
    std::string secondPlayer, color2, squareOfCheckingPiece2;
    Color colorOfPlayer2;
    isstream2 >> secondPlayer >> color2 >> squareOfCheckingPiece2;
    if(secondPlayer.empty()) {
        file.close();
        throw FileStructureException(filePath, "Player2 name");
    }
    if(color2 == "WHITE") colorOfPlayer2 = WHITE;
    else if(color2 == "BLACK") colorOfPlayer2 = BLACK;
    else {
        file.close();
        throw FileStructureException(filePath, "Player2 color");
    }
    if(secondPlayer == "ComputerPlayer") player2 = std::make_shared<ComputerPlayer>(secondPlayer, colorOfPlayer2);
    else player2 = std::make_shared<HumanPlayer>(secondPlayer, colorOfPlayer2);

    //read history of moves
    getline(file, line);
    std::istringstream moves(line);

    //pieces captured by player1
    getline(file, line);
    std::istringstream capturedPieces1(line);
    while(capturedPieces1.peek() != decltype(capturedPieces1)::traits_type::eof()){
        std::string buf;
        capturedPieces1 >> buf;
        PieceType pieceType;
        switch(buf[1]){
            case 'P':
                pieceType = PieceType::Pawn;
                break;
            case 'R':
                pieceType = PieceType::Rook;
                break;
            case 'N':
                pieceType = PieceType::Knight;
                break;
            case 'B':
                pieceType = PieceType::Bishop;
                break;
            case 'Q':
                pieceType = PieceType::Queen;
                break;
            case 'K':
                pieceType = PieceType::King;
                break;
            default:
                file.close();
                throw FileStructureException(filePath, "invalid piece name: " + std::to_string(buf[1]));
        }
        board->addCapturedPiece(pieceType, player2);
    }
    //pieces captured by player2
    getline(file, line);
    std::istringstream capturedPieces2(line);
    while(capturedPieces2.peek() != decltype(capturedPieces2)::traits_type::eof()){
        std::string buf;
        capturedPieces2 >> buf;
        PieceType pieceType;
        switch(buf[1]){
            case 'P':
                pieceType = PieceType::Pawn;
                break;
            case 'R':
                pieceType = PieceType::Rook;
                break;
            case 'N':
                pieceType = PieceType::Knight;
                break;
            case 'B':
                pieceType = PieceType::Bishop;
                break;
            case 'Q':
                pieceType = PieceType::Queen;
                break;
            case 'K':
                pieceType = PieceType::King;
                break;
            default:
                file.close();
                throw FileStructureException(filePath, "invalid piece name: " + std::to_string(buf[1]));
        }
        board->addCapturedPiece(pieceType, player1);
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
            if(table[i][j].length() != 3) {
                throw FileStructureException(filePath,
                                             "square("+ std::to_string(i)+","+std::to_string(j)+")");
            }
            if(table[i][j][0] != '[') {
                if(table[i][j][0] == 'B') owner = black;
                else if(table[i][j][0] == 'W') owner = white;
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
                        throw FileStructureException(filePath, "invalid piece name: " + std::to_string(table[i][j][1]));
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
        try {
            player1->setCheckingPiece(board->getSquare(row, column)->getPiece());
        }
        catch(...) {
            throw FileStructureException(filePath, "invalid checking piece square format for player1");
        }
    }
    else if(squareOfCheckingPiece2.length() > 0) {
        int row = 8 - (squareOfCheckingPiece2[1] - '0');
        char column = squareOfCheckingPiece2[0] - 'A';
        try {
            player2->setCheckingPiece(board->getSquare(row, column)->getPiece());
        }
        catch(...) {
            throw FileStructureException(filePath, "invalid checking piece square format for player2");
        }
    }

    GameDataPtr gameData = std::make_shared<GameData>(board, player1, player2, playerTurn);

    //recreate moves objects
    PlayerPtr playerThatMoves = player1->getColor() == WHITE ? player1 : player2;
    while(moves.peek() != decltype(moves)::traits_type::eof()){
        std::string buf;
        moves >> buf;
        MovePtr move;
        if(buf == "O-O" || buf == "O-O-O") move = std::make_shared<Move>(buf, playerThatMoves);
        else {
            if(buf.length() != 5) {
                throw FileStructureException(filePath, "invalid move format: " + buf);
            }
            if(buf[0] < 'A' || buf[0] > 'H' || buf[1] < '1' || buf[1] > '8' || buf[3] < 'A' || buf[3] > 'H' || buf[4] < '1' || buf[4] > '8')
                throw FileStructureException(filePath, "invalid move format: " + buf);
            move = std::make_shared<Move>(buf, board, playerThatMoves);
        }
        gameData->addMove(move);
        if(playerThatMoves == player1) playerThatMoves = player2;
        else playerThatMoves = player1;
    }

    return gameData;
}
