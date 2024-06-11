#include "GameLogic.h"
#include "GameData.h"
#include "Players/HumanPlayer.h"
#include "Players/ComputerPlayer.h"

GameDataPtr GameLogic::initializeGame(Color player1Color, bool playWithComputer) {
    BoardPtr board = std::make_shared<Board>();
    PlayerPtr player1 = std::make_shared<HumanPlayer>("Player_1", player1Color);
    PlayerPtr player2;
    PlayerPtr playerTurn;

    //creating player2
    Color player2Color = player1Color == WHITE ? BLACK : WHITE;
    if(playWithComputer) player2 = std::make_shared<ComputerPlayer>("ComputerPlayer", player2Color);
    else player2 = std::make_shared<HumanPlayer>("Player_2", player2Color);

    if(player1->getColor() == WHITE) playerTurn = player1;
    else playerTurn = player2;

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

    return std::make_shared<GameData>(board, player1, player2, playerTurn);
}


bool GameLogic::isMoveCorrect(MovePtr &move, GameDataPtr gameData) {
    if(move->getFrom() == move->getTo()) return false;
    PlayerPtr player = move->getPlayer();
    PiecePtr piece = move->getFrom()->getPiece();
    if(piece != nullptr && piece->getPlayer() == player) { //check if on fromSquare is located a piece that belongs to player that moves
        PiecePtr pieceToBeCaptured = move->getTo()->getPiece();
        //check if piece that shall be captured is not owned by player that moves and if it's not a king
        if(pieceToBeCaptured != nullptr && (pieceToBeCaptured->getPlayer() == player ||
                                            pieceToBeCaptured->getType() == PieceType::King)) return false;
        if(!piece->canBeMovedToSquare(move->getTo(), gameData)) return false;
        if(GameLogic::isPlayerInCheckAfterMove(player, move, gameData)) return false;
    }
    else return false;
    return true;
}


bool GameLogic::isPlayerInCheckAfterMove(const PlayerPtr &player, MovePtr &move, GameDataPtr gameData) {
    move->execute(gameData);
    if(GameLogic::getCheckingPiece(player, gameData) != nullptr) {
        move->undo(gameData);
        return true;
    }
    else {
        move->undo(gameData);
        return false;
    }
}


PiecePtr GameLogic::getCheckingPiece(const PlayerPtr &playerInCheck, GameDataPtr gameData) {
    BoardPtr board = gameData->getBoard();
    PlayerPtr player1 = gameData->getPlayer1();
    PlayerPtr player2 = gameData->getPlayer2();
    std::vector<PiecePtr> piecesOfAttackingPlayer;
    PlayerPtr attackingPlayer;
    if(playerInCheck == player1) attackingPlayer = player2;
    else attackingPlayer = player1;
    for(auto &piece : board->getPiecesOfPlayer(attackingPlayer)) {
        if(piece != nullptr && !piece->isCaptured()) {
            if(piece->canBeMovedToSquare(playerInCheck->getKing()->getSquare(), gameData)) {
                return piece;
            }
        }
    }
    return nullptr;
}


bool GameLogic::isCastlingCorrect(const PlayerPtr &player, std::string castling, GameDataPtr gameData) {
    BoardPtr board = gameData->getBoard();
    if(player->isInCheck()) return false;
    if(!player->getKing()->isFirstMove()) return false;
    if(castling == "O-O") {
        if(player->getColor() == WHITE) {
            if(board->getSquare(7, 7)->getPiece() != nullptr) {
                if(board->getSquare(7, 7)->getPiece()->isFirstMove() == false) return false;
                if(board->getSquare(7, 6)->getPiece() != nullptr || board->getSquare(7, 5)->getPiece() != nullptr) return false;
                if(GameLogic::isSquareAttacked(player, board->getSquare(7, 5), gameData)) return false;
                if(GameLogic::isSquareAttacked(player, board->getSquare(7, 6), gameData)) return false;
            }
            else return false;
        }
        else { //player->getColor() == BLACK
            if(board->getSquare(0, 7)->getPiece() != nullptr) {
                if(board->getSquare(0, 7)->getPiece()->isFirstMove() == false) return false;
                if(board->getSquare(0, 6)->getPiece() != nullptr || board->getSquare(0, 5)->getPiece() != nullptr) return false;
                if(GameLogic::isSquareAttacked(player, board->getSquare(0, 5), gameData)) return false;
                if(GameLogic::isSquareAttacked(player, board->getSquare(0, 6), gameData)) return false;
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
                if(GameLogic::isSquareAttacked(player, board->getSquare(7, 2), gameData)) return false;
                if(GameLogic::isSquareAttacked(player, board->getSquare(7, 3), gameData)) return false;
            }
            else return false;
        }
        else { //player->getColor() == BLACK
            if(board->getSquare(0, 0)->getPiece() != nullptr) {
                if(board->getSquare(0, 0)->getPiece()->isFirstMove() == false) return false;
                if(board->getSquare(0, 1)->getPiece() != nullptr || board->getSquare(0, 2)->getPiece() != nullptr ||
                   board->getSquare(0, 3)->getPiece() != nullptr) return false;
                if(GameLogic::isSquareAttacked(player, board->getSquare(0, 2), gameData)) return false;
                if(GameLogic::isSquareAttacked(player, board->getSquare(0, 3), gameData)) return false;
            }
            else return false;
        }
    }
    return true;
}


bool GameLogic::isSquareAttacked(const PlayerPtr &player, SquarePtr square, GameDataPtr gameData) {
    BoardPtr board = gameData->getBoard();
    PlayerPtr player1 = gameData->getPlayer1();
    PlayerPtr player2 = gameData->getPlayer2();
    std::vector<PiecePtr> piecesOfAttackingPlayer;
    if(player == player1) piecesOfAttackingPlayer = board->getPiecesOfPlayer(player2);
    else piecesOfAttackingPlayer = board->getPiecesOfPlayer(player1);
    for(auto &piece : piecesOfAttackingPlayer) {
        if(piece != nullptr && !piece->isCaptured()) {
            if(piece->canBeMovedToSquare(square, gameData)) return true;
        }
    }
    return false;
}


//==================================================== PROMOTION =======================================================

SquarePtr GameLogic::checkIfPromotion(MovePtr move, GameDataPtr gameData) {
    BoardPtr board = gameData->getBoard();
    PlayerPtr player = move->getPlayer();
    if(player->getColor() == WHITE) {
        if(move->getTo()->getRow() == 0) {
            int column = move->getTo()->getColumn();
            if(board->getSquare(0, column)->getPiece()->getType() == PieceType::Pawn)
                return board->getSquare(0, column);
        }
    }
    else {
        if(move->getTo()->getRow() == 7) {
            int column = move->getTo()->getColumn();
            if(board->getSquare(7, column)->getPiece()->getType() == PieceType::Pawn)
                return board->getSquare(7, column);
        }
    }
    return nullptr;
}

void GameLogic::promotePawn(PieceType piece, SquarePtr pawnSquare, GameDataPtr gameData) {
    BoardPtr board = gameData->getBoard();
    PlayerPtr player = gameData->getPlayerTurn();
    board->deletePiece(pawnSquare->getPiece());
    board->addPiece(piece, player, pawnSquare->getRow(), pawnSquare->getColumn());
}


//==================================================== CHECKMATE =======================================================

bool GameLogic::isCheckmate(const PlayerPtr &player, GameDataPtr gameData) {
    if(!player->isInCheck()) return false;
    if(GameLogic::canCheckingPieceBeCaptured(player, gameData)) return false;
    if(GameLogic::canKingBeMoved(player, gameData)) return false;
    if(GameLogic::canCheckBeBlocked(player, gameData)) return false;
    return true;
}

bool GameLogic::canCheckingPieceBeCaptured(const PlayerPtr &playerInCheck, GameDataPtr gameData) {
    BoardPtr board = gameData->getBoard();
    SquarePtr squareOfCheckingPiece = playerInCheck->getCheckingPiece()->getSquare();
    for(auto &piece : board->getPiecesOfPlayer(playerInCheck)) {
        if(piece != nullptr && !piece->isCaptured()) {
            if(piece->canBeMovedToSquare(squareOfCheckingPiece, gameData)) {
                MovePtr move = std::make_shared<Move>(piece->getSquare(), squareOfCheckingPiece, playerInCheck);
                if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
            }
        }
    }
    return false;
}

bool GameLogic::canKingBeMoved(const PlayerPtr &player, GameDataPtr gameData) {
    BoardPtr board = gameData->getBoard();
    int kingRow = player->getKing()->getSquare()->getRow();
    int kingColumn = player->getKing()->getSquare()->getColumn();
    int dx[] = {0, 0, 1, -1, 1, -1, 1, -1};
    int dy[] = {1, -1, 0, 0, 1, 1, -1, -1};

    for(int i = 0; i < 8; i++) {
        int newRow = kingRow + dx[i];
        int newColumn = kingColumn + dy[i];

        if(newRow >= 0 && newRow < 8 && newColumn >= 0 && newColumn < 8) {
            MovePtr move = std::make_shared<Move>(board->getSquare(kingRow, kingColumn),
                                                  board->getSquare(newRow, newColumn),
                                                  player);
            if(GameLogic::isMoveCorrect(move, gameData)) return true;
        }
    }
    return false;
}

bool GameLogic::canCheckBeBlocked(const PlayerPtr &playerInCheck, GameDataPtr gameData) {
    BoardPtr board = gameData->getBoard();

    int kingRow = playerInCheck->getKing()->getSquare()->getRow();
    int kingColumn = playerInCheck->getKing()->getSquare()->getColumn();
    PiecePtr checkingPiece = playerInCheck->getCheckingPiece();
    int checkingPieceRow = checkingPiece->getSquare()->getRow();
    int checkingPieceColumn = checkingPiece->getSquare()->getColumn();
    std::vector<PiecePtr> playerPieces = board->getPiecesOfPlayer(playerInCheck);

    if(checkingPiece->getType() == PieceType::Rook) {
        if(kingRow == checkingPieceRow) {
            int column;
            if(checkingPieceColumn > kingColumn) column = kingColumn;
            else column = checkingPieceColumn;
            for(int i = 0; i < std::abs(kingColumn - checkingPieceColumn) - 1; i++) {
                column++;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(checkingPieceRow, column), gameData)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(checkingPieceRow, column),
                                                              playerInCheck);
                        if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
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
                    if(piece->canBeMovedToSquare(board->getSquare(row, checkingPieceColumn), gameData)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(row, checkingPieceColumn),
                                                              playerInCheck);
                        if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
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
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), gameData)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(row, column),
                                                              playerInCheck);
                        if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
                    }
                }
            }
        }
        else if(kingRow > checkingPieceRow && kingColumn < checkingPieceColumn) {
            for(int i = 0; i < std::abs(checkingPieceRow - kingRow) - 1; i++){
                row++;
                column--;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), gameData)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(row, column),
                                                              playerInCheck);
                        if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
                    }
                }
            }
        }
        else if(kingRow > checkingPieceRow && kingColumn > checkingPieceColumn) {
            for(int i = 0; i < std::abs(checkingPieceRow - kingRow) - 1; i++){
                row++;
                column++;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), gameData)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(row, column),
                                                              playerInCheck);
                        if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
                    }
                }
            }
        }
        else { //if(to->getRow() < square->getRow() && to->getColumn() < square->getColumn())
            for(int i = 0; i < std::abs(checkingPieceRow - kingRow) - 1; i++){
                row--;
                column--;
                for(auto &piece : playerPieces) {
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), gameData)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(row, column),
                                                              playerInCheck);
                        if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
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
                    if(piece->canBeMovedToSquare(board->getSquare(checkingPieceRow, column), gameData)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(checkingPieceRow, column),
                                                              playerInCheck);
                        if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
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
                    if(piece->canBeMovedToSquare(board->getSquare(row, checkingPieceColumn), gameData)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(row, checkingPieceColumn),
                                                              playerInCheck);
                        if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
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
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), gameData)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(row, column),
                                                              playerInCheck);
                        if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
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
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), gameData)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(row, column),
                                                              playerInCheck);
                        if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
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
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), gameData)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(row, column),
                                                              playerInCheck);
                        if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
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
                    if(piece->canBeMovedToSquare(board->getSquare(row, column), gameData)) {
                        MovePtr move = std::make_shared<Move>(piece->getSquare(),
                                                              board->getSquare(row, column),
                                                              playerInCheck);
                        if(!GameLogic::isPlayerInCheckAfterMove(playerInCheck, move, gameData)) return true;
                    }
                }
            }
        }
    }
    return false;
}


//==================================================== STALEMATE =======================================================

bool GameLogic::isStalemate(const PlayerPtr &player, GameDataPtr gameData) {
    BoardPtr board = gameData->getBoard();
    for(auto &piece : board->getPiecesOfPlayer(player)) {
        SquarePtr pieceSquare = piece->getSquare();
        if(piece != nullptr && !piece->isCaptured()){
            for(int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    MovePtr move = std::make_shared<Move>(pieceSquare,
                                                          board->getSquare(x, y),
                                                          player);
                    if(GameLogic::isMoveCorrect(move, gameData)) return false;
                }
            }
        }
    }
    if(GameLogic::isCastlingCorrect(player, "O-O", gameData)) return false;
    if(GameLogic::isCastlingCorrect(player, "O-O-O", gameData)) return false;
    return true;
}
