#include "Game.h"
#include "Players/HumanPlayer.h"
#include "Players/ComputerPlayer.h"
#include "View.h"
#include "Move.h"
#include "Check.h"
#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

Game::Game(ViewPtr _view) : board(nullptr), player1(nullptr), player2(nullptr), playerTurn(nullptr), view(std::move(_view)) {}

void Game::startGame() {
    bool playWithComputer;
    Color player1Color;
    Color player2Color;
    board = std::make_shared<Board>();
    playWithComputer = view->readUserChoice();
    player1Color = view->readUserChoiceOfColor();
    player1Color == WHITE ? player2Color = BLACK : player2Color = WHITE;
    player1 = std::make_shared<HumanPlayer>("Player_1", player1Color);
    if(playWithComputer) player2 = std::make_shared<ComputerPlayer>("ComputerPlayer", player2Color);
    else player2 = std::make_shared<HumanPlayer>("Player_2", player2Color);
    initializeGame();
    if(player1->getColor() == WHITE){
        playerTurn = player1;
    }
    else {
        playerTurn = player2;
    }
}

void Game::initializeGame() {
    if (player1 == nullptr || player2 == nullptr) return;
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
    //creating squares
    for(int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            board->addSquare(i, j);
    //adding pawns
    for (int i = 0; i < 8; i++) {
        board->addPiece(PieceType::Pawn, white, 6, i);
        board->addPiece(PieceType::Pawn, black, 1, i);
    }
    //adding rooks
    board->addPiece(PieceType::Rook, white, 7, 0);
    board->addPiece(PieceType::Rook, white, 7, 7);
    board->addPiece(PieceType::Rook, black, 0, 0);
    board->addPiece(PieceType::Rook, black, 0, 7);
    //adding knights
    board->addPiece(PieceType::Knight, white, 7, 1);
    board->addPiece(PieceType::Knight, white, 7, 6);
    board->addPiece(PieceType::Knight, black, 0, 1);
    board->addPiece(PieceType::Knight, black, 0, 6);
    //adding bishops
    board->addPiece(PieceType::Bishop, white, 7, 2);
    board->addPiece(PieceType::Bishop, white, 7, 5);
    board->addPiece(PieceType::Bishop, black, 0, 2);
    board->addPiece(PieceType::Bishop, black, 0, 5);
    //adding queens
    board->addPiece(PieceType::Queen, white, 7, 3);
    board->addPiece(PieceType::Queen, black, 0, 3);
    //adding kings
    board->addPiece(PieceType::King, white, 7, 4);
    board->addPiece(PieceType::King, black, 0, 4);
    //assigning kings to players
    white->setKing(board->getSquare(7, 4)->getPiece());
    black->setKing(board->getSquare(0, 4)->getPiece());
}

bool Game::play() {
    bool continuePlaying = true;
    if(view->readIfNewGame()) this->startGame();
    else this->loadGame();

    while(continuePlaying) {
        PlayerPtr drugiGracz;
        if(playerTurn == player1){
            drugiGracz = player2;
        }
        else drugiGracz = player1;

        view->displayDefView(board, player1, player2);
        Event event = this->handleMove(playerTurn);
        view->setError(false);
        if(event == Event::quit) return false;
        if(event == Event::closeMenu) continue;
        //if event == Event::Move

        //handle checkingPiece
        playerTurn->cancelCheck();
        PiecePtr checkingPiece = this->getCheckingPiece(drugiGracz);
        if(checkingPiece != nullptr) drugiGracz->setCheck(checkingPiece);

        if(this->isCheckmate(drugiGracz)) {
            view->displayDefView(board, player1, player2);
            view->displayWinner(playerTurn);
            std::string option = view->readUserChoiceOfMenuOption();
            if(option == "N") return true;
            else return false;
        }
        else if(this->isStalemate(drugiGracz)) {
            view->displayDefView(board, player1, player2);
            view->displayDraw();
            std::string option = view->readUserChoiceOfMenuOption();
            if(option == "N") return true;
            else return false;
        }

        if(playerTurn == player1) {
            playerTurn = player2;
        }
        else {
            playerTurn = player1;
        }
    }
    return true;
}

Event Game::handleMove(PlayerPtr &player) {
    MovePtr move;
    bool isCorrect;
    do {
        bool menu = false;
        move = player->executeMove(board, view);
        if(move->getAbbr() == "M") {
            view->displayMenu();
            std::string option = view->readUserChoiceOfMenuOption();
            if     (option == "D") view->displayPlayerMoves(player);
            else if(option == "S") this->saveGame();
            else if(option == "Q") return Event::quit;
            else                  return Event::closeMenu;
            menu = true;
        }
        if(!menu) {
            if(move->getAbbr() == "O-O" || move->getAbbr() == "O-O-O")
                isCorrect = isCastlingCorrect(player, move->getAbbr());
            else isCorrect = isMoveCorrect(player, move);

            if(isCorrect) move->execute(player, board);
            else view->setError(true);
        }
    } while(!isCorrect);

    //promotion
    if(player->getColor() == WHITE) {
        if(move->getTo()->getRow() == 0) {
            int column = move->getTo()->getColumn();
            if(board->getSquare(0, column)->getPiece()->getType() == PieceType::Pawn)
                this->promotion(board->getSquare(0, column), player);
        }
    }
    else {
        if(move->getTo()->getRow() == 7) {
            int column = move->getTo()->getColumn();
            if(board->getSquare(7, column)->getPiece()->getType() == PieceType::Pawn)
                this->promotion(board->getSquare(7, column), player);
        }
    }
    return Event::move;
}

void Game::promotion(SquarePtr pawnSquare, PlayerPtr &player) {
    PieceType piece = player->promotion(view);
    board->deletePiece(pawnSquare->getPiece());
    board->addPiece(piece, player, pawnSquare->getRow(), pawnSquare->getColumn());
}

bool Game::isMoveCorrect(PlayerPtr &player, MovePtr &move) {
    if(move->getFrom() == move->getTo()) return false;
    PiecePtr piece = move->getFrom()->getPiece();
    if(piece != nullptr && piece->getPlayer() == player) { //check if on fromSquare is located a piece that belongs to player that moves
        PiecePtr pieceToBeCaptured = move->getTo()->getPiece();
        //check if piece that shall be captured is not owned by player that moves and if it's not a king
        if(pieceToBeCaptured != nullptr && (pieceToBeCaptured->getPlayer() == player ||
                                            pieceToBeCaptured->getType() == PieceType::King)) return false;
        if(!piece->canBeMovedToSquare(move->getTo(), board)) return false;
        if(this->isPlayerInCheckAfterMove(player, move)) return false;
    }
    else return false;
    return true;
}

bool Game::isCastlingCorrect(PlayerPtr &player, std::string castling) {
    if(!player->getKing()->isFirstMove()) return false;
    if(castling == "O-O") {
        if(player->getColor() == WHITE) {
            if(board->getSquare(7, 7)->getPiece() != nullptr) {
                if(board->getSquare(7, 7)->getPiece()->isFirstMove() == false) return false;
                if(board->getSquare(7, 6)->getPiece() != nullptr || board->getSquare(7, 5)->getPiece() != nullptr) return false;
                if(this->isSquareAttacked(player, board->getSquare(7, 5))) return false;
            }
            else return false;
        }
        else {
            if(board->getSquare(0, 7)->getPiece() != nullptr) {
                if(board->getSquare(0, 7)->getPiece()->isFirstMove() == false) return false;
                if(board->getSquare(0, 6)->getPiece() != nullptr || board->getSquare(0, 5)->getPiece() != nullptr) return false;
                if(this->isSquareAttacked(player, board->getSquare(0, 5))) return false;
            }
            else return false;
        }
    }
    else { //castling == "O-O-O"
        if(player->getColor() == WHITE) {
            if(board->getSquare(7, 0)->getPiece() != nullptr) {
                if(board->getSquare(7, 0)->getPiece()->isFirstMove() == false) return false;
                if(board->getSquare(7, 1)->getPiece() != nullptr || board->getSquare(7, 2)->getPiece() != nullptr ||
                   board->getSquare(7, 3)->getPiece() != nullptr) return false;
                if(this->isSquareAttacked(player, board->getSquare(7, 3))) return false;
            }
            else return false;
        }
        else {
            if(board->getSquare(0, 0)->getPiece() != nullptr) {
                if(board->getSquare(0, 0)->getPiece()->isFirstMove() == false) return false;
                if(board->getSquare(0, 1)->getPiece() != nullptr || board->getSquare(0, 2)->getPiece() != nullptr ||
                   board->getSquare(0, 3)->getPiece() != nullptr) return false;
                if(this->isSquareAttacked(player, board->getSquare(0, 3))) return false;
            }
            else return false;
        }
    }
    return true;
}

bool Game::isPlayerInCheckAfterMove(PlayerPtr &player, MovePtr &move) {
    move->execute(player, board);

    if(this->getCheckingPiece(player) != nullptr) {
        move->undo(player, board);
        return true;
    }
    else {
        move->undo(player, board);
        return false;
    }
}

bool Game::isSquareAttacked(PlayerPtr &player, SquarePtr square) {
    std::vector<PiecePtr> piecesOfAttackingPlayer;
    if(player == player1) piecesOfAttackingPlayer = board->getPiecesOfPlayer(player2);
    else piecesOfAttackingPlayer = board->getPiecesOfPlayer(player1);
    for(auto &piece : piecesOfAttackingPlayer) {
        if(piece != nullptr && !piece->isCaptured()) {
            if(piece->canBeMovedToSquare(square, board)) return true;
        }
    }
    return false;
}

PiecePtr Game::getCheckingPiece(PlayerPtr &playerInCheck) {
    std::vector<PiecePtr> piecesOfAttackingPlayer;
    PlayerPtr attackingPlayer;
    if(playerInCheck == player1) attackingPlayer = player2;
    else attackingPlayer = player1;
    for(auto &piece : board->getPiecesOfPlayer(attackingPlayer)) {
        if(piece != nullptr && !piece->isCaptured()) {
            if(piece->canBeMovedToSquare(playerInCheck->getKing()->getSquare(), board)) {
                return piece;
            }
        }
    }
    return nullptr;
}

bool Game::canCheckingPieceBeCaptured(PlayerPtr &playerInCheck) {
    SquarePtr squareOfCheckingPiece = playerInCheck->getCheckingPiece()->getCheckingPiece()->getSquare();
    for(auto &piece : board->getPiecesOfPlayer(playerInCheck)) {
        if(piece != nullptr && !piece->isCaptured()) {
            if(piece->canBeMovedToSquare(squareOfCheckingPiece, board)) {
                MovePtr move = std::make_shared<Move>(piece->getSquare(), squareOfCheckingPiece);
                if(!this->isPlayerInCheckAfterMove(playerInCheck, move)) return true;
            }
        }
    }
    return false;
}

bool Game::canCheckBeBlocked(PlayerPtr &player) {
    int kingRow = player->getKing()->getSquare()->getRow();
    int kingColumn = player->getKing()->getSquare()->getColumn();
    PiecePtr checkingPiece = player->getCheckingPiece()->getCheckingPiece();
    int checkingPieceRow = checkingPiece->getSquare()->getRow();
    int checkingPieceColumn = checkingPiece->getSquare()->getColumn();
    std::vector<PiecePtr> playerPieces = board->getPiecesOfPlayer(player);

    if(checkingPiece->getType() == PieceType::Rook) {
        if(kingRow == checkingPieceRow) {
            int column;
            if(checkingPieceColumn > kingColumn) column = kingColumn;
            else column = checkingPieceColumn;
            for(int i = 0; i < std::abs(kingColumn - checkingPieceColumn) - 1; i++) {
                column++;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(checkingPieceRow, column), this->board)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(checkingPieceRow, column));
                        if(!this->isPlayerInCheckAfterMove(player, move)) return true;
                    }
                }
            }
        }
        else { //if(kingColumn == checkingPieceColumn)
            int row;
            if(checkingPieceRow > kingRow) row = kingRow;
            else row = checkingPieceRow;
            for(int i = 0; i < std::abs(kingRow - checkingPieceRow) - 1; i++) {
                row++;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, checkingPieceColumn), this->board)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(row, checkingPieceColumn));
                        if(!this->isPlayerInCheckAfterMove(player, move)) return true;
                    }
                }
            }
        }
    }
    else if(checkingPiece->getType() == PieceType::Bishop) {
        int row = checkingPieceRow;
        int column = checkingPieceColumn;
        if(kingRow < checkingPieceRow && kingColumn > checkingPieceColumn) {
            for(int i = 0; i < std::abs(checkingPieceRow - kingRow) - 1; i++){
                row--;
                column++;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), this->board)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(), board->getSquare(row, column));
                        if(!this->isPlayerInCheckAfterMove(player, move)) return true;
                    }
                }
            }
        }
        else if(kingRow > checkingPieceRow && kingColumn < checkingPieceColumn) {
            for(int i = 0; i < std::abs(checkingPieceRow - kingRow) - 1; i++){
                row++;
                column--;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), this->board)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(), board->getSquare(row, column));
                        if(!this->isPlayerInCheckAfterMove(player, move)) return true;
                    }
                }
            }
        }
        else if(kingRow > checkingPieceRow && kingColumn > checkingPieceColumn) {
            for(int i = 0; i < std::abs(checkingPieceRow - kingRow) - 1; i++){
                row++;
                column++;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), this->board)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(), board->getSquare(row, column));
                        if(!this->isPlayerInCheckAfterMove(player, move)) return true;
                    }
                }
            }
        }
        else { //if(to->getRow() < square->getRow() && to->getColumn() < square->getColumn())
            for(int i = 0; i < std::abs(checkingPieceRow - kingRow) - 1; i++){
                row--;
                column--;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), this->board)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(), board->getSquare(row, column));
                        if(!this->isPlayerInCheckAfterMove(player, move)) return true;
                    }
                }
            }
        }
    }
    else if(checkingPiece->getType() == PieceType::Queen) {
        if(kingRow == checkingPieceRow) {
            int column;
            if(checkingPieceColumn > kingColumn) column = kingColumn;
            else column = checkingPieceColumn;
            for(int i = 0; i < std::abs(kingColumn - checkingPieceColumn) - 1; i++) {
                column++;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(checkingPieceRow, column), this->board)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(checkingPieceRow, column));
                        if(!this->isPlayerInCheckAfterMove(player, move)) return true;
                    }
                }
            }
        }
        else if(kingColumn == checkingPieceColumn) {
            int row;
            if(checkingPieceRow > kingRow) row = kingRow;
            else row = checkingPieceRow;
            for(int i = 0; i < std::abs(kingRow - checkingPieceRow) - 1; i++) {
                row++;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, checkingPieceColumn), this->board)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(row, checkingPieceColumn));
                        if(!this->isPlayerInCheckAfterMove(player, move)) return true;
                    }
                }
            }
        }
        else if(kingRow < checkingPieceRow && kingColumn > checkingPieceColumn) {
            int row = checkingPieceRow;
            int column = checkingPieceColumn;
            for(int i = 0; i < std::abs(checkingPieceRow - kingRow) - 1; i++){
                row--;
                column++;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), this->board)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(), board->getSquare(row, column));
                        if(!this->isPlayerInCheckAfterMove(player, move)) return true;
                    }
                }
            }
        }
        else if(kingRow > checkingPieceRow && kingColumn < checkingPieceColumn) {
            int row = checkingPieceRow;
            int column = checkingPieceColumn;
            for(int i = 0; i < std::abs(checkingPieceRow - kingRow) - 1; i++){
                row++;
                column--;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), this->board)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(), board->getSquare(row, column));
                        if(!this->isPlayerInCheckAfterMove(player, move)) return true;
                    }
                }
            }
        }
        else if(kingRow > checkingPieceRow && kingColumn > checkingPieceColumn) {
            int row = checkingPieceRow;
            int column = checkingPieceColumn;
            for(int i = 0; i < std::abs(checkingPieceRow - kingRow) - 1; i++){
                row++;
                column++;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), this->board)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(), board->getSquare(row, column));
                        if(!this->isPlayerInCheckAfterMove(player, move)) return true;
                    }
                }
            }
        }
        else { //if(to->getRow() < square->getRow() && to->getColumn() < square->getColumn())
            for(int i = 0; i < std::abs(checkingPieceRow - kingRow) - 1; i++){
                int row = checkingPieceRow;
                int column = checkingPieceColumn;
                row--;
                column--;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), this->board)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(), board->getSquare(row, column));
                        if(!this->isPlayerInCheckAfterMove(player, move)) return true;
                    }
                }
            }
        }
    }
    return false;
}

bool Game::canKingBeMoved(PlayerPtr &player) {
    int kingRow = player->getKing()->getSquare()->getRow();
    int kingColumn = player->getKing()->getSquare()->getColumn();
    int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dy[] = {1, -1, 0, 0, 1, 1, -1, -1};

    for(int i = 0; i < 8; i++) {
        int newRow = kingRow + dx[i];
        int newColumn = kingColumn + dy[i];

        if(newRow >= 0 && newRow < 8 && newColumn >= 0 && newColumn < 8) {
            MovePtr move = std::make_shared<Move>(board->getSquare(kingRow, kingColumn),
                                                  board->getSquare(newRow, newColumn));
            if(isMoveCorrect(player, move)) return true;
        }
    }
    return false;
}

bool Game::isCheckmate(PlayerPtr &player) {
    if(!player->isCheck()) return false;
    if(this->canCheckingPieceBeCaptured(player)) return false;
    if(this->canKingBeMoved(player)) return false;
    if(this->canCheckBeBlocked(player)) return false;
    return true;
}

bool Game::isStalemate(PlayerPtr &player) {
    for(auto &piece : board->getPiecesOfPlayer(player)) {
        SquarePtr pieceSquare = piece->getSquare();
        if(piece != nullptr && !piece->isCaptured()){
            for(int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    MovePtr move = std::make_shared<Move>(pieceSquare, board->getSquare(x, y));
                    if (isMoveCorrect(player, move)) return false;
                }
            }
        }
    }
    if(isCastlingCorrect(player, "O-O")) return false;
    if(isCastlingCorrect(player, "O-O-O")) return false;
    return true;
}

bool Game::saveGame() {
    std::string path = view->readFilePath();
    std::fstream file;
    file.open(path, std::ios::out | std::ios::trunc);
    if(!file.is_open()) return false;

    //Save pieces positions
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {
            std::string abbr;
            board->getSquare(x, y)->getPiece() == nullptr ? abbr = "()" : abbr = board->getSquare(x,
                                                                                                  y)->getPiece()->getAbbr();
            file << abbr << " ";
        }
        file << std::endl;
    }

    //Save player that saves the game
    file << "Save: " << (playerTurn == player1 ? player1->getName() : player2->getName()) << std::endl;

    //Save players
    file << player1->getName() << " " << player1->getColor() << " " <<
         (player1->isCheck() ? player1->getCheckingPiece()->getCheckingPiece()->getSquare()->toString() : "" ) << std::endl;
    file << player2->getName() << " " << player2->getColor() << " " <<
         (player2->isCheck() ? player2->getCheckingPiece()->getCheckingPiece()->getSquare()->toString() : "" ) << std::endl;

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
    return true;
}

bool Game::loadGame() {
    board = std::make_shared<Board>();
    std::string path = view->readFilePath();
    std::fstream file;
    file.open(path, std::ios::in);
    if (!file.is_open()) return false;
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
            if(table[i][j][1] != ')') {
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
    return true;
}
