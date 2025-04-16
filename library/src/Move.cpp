#include "Move.h"
#include "Board.h"
#include "Player.h"
#include "GameData.h"

Move::Move(SquarePtr from, SquarePtr to, PlayerPtr player) : from(from), to(to), player(player){
    abbr = this->toString();
}

Move::Move(std::string move, BoardPtr &board, PlayerPtr player) : player(player) {
    int fromRow = 8 - (move[1] - '0');
    char fromColumn = move[0] - 'A';
    int toRow = 8 - (move[4] - '0');
    char toColumn = move[3] - 'A';
    from = board->getSquare(fromRow, fromColumn);
    to = board->getSquare(toRow, toColumn);
    abbr = this->toString();
}

Move::Move(std::string move, PlayerPtr player) : player(player) {
    abbr = move;
}

std::string Move::getAbbr() {
    return abbr;
}

const SquarePtr &Move::getFrom() const {
    return from;
}

const SquarePtr &Move::getTo() const {
    return to;
}

std::string Move::toString() {
    if(to == nullptr || from == nullptr) return "";
    std::string move = from->toString() + "-" + to->toString();
    return move;
}

void Move::execute(GameDataPtr &gameData) {
    if(executed) return;
    if(player.lock() == nullptr) return;
    BoardPtr board = gameData->getBoard();
    if(abbr == "O-O") {
        int row;
        if(player.lock()->getColor() == WHITE) row = 7;
        else row = 0;

        PiecePtr king = board->getSquare(row, 4)->getPiece();
        board->getSquare(row, 6)->setPiece(king);
        king->setSquare(board->getSquare(row, 6));
        board->getSquare(row, 4)->setPiece(nullptr);

        PiecePtr rook = board->getSquare(row, 7)->getPiece();
        board->getSquare(row, 5)->setPiece(rook);
        rook->setSquare(board->getSquare(row, 5));
        board->getSquare(row, 7)->setPiece(nullptr);
    }
    else if(abbr == "O-O-O") {
        int row;
        if(player.lock()->getColor() == WHITE) row = 7;
        else row = 0;

        PiecePtr king = board->getSquare(row, 4)->getPiece();
        board->getSquare(row, 2)->setPiece(king);
        king->setSquare(board->getSquare(row, 2));
        board->getSquare(row, 4)->setPiece(nullptr);

        PiecePtr rook = board->getSquare(row, 0)->getPiece();
        board->getSquare(row, 3)->setPiece(rook);
        rook->setSquare(board->getSquare(row, 3));
        board->getSquare(row, 0)->setPiece(nullptr);
    }
    else {
        pieceFirstMove = from->getPiece()->isFirstMove();
        if(to->getPiece() != nullptr) {
            capturedPiece = to->getPiece();
            to->getPiece()->setCaptured();
        }
        //en passant
        else if(from->getPiece()->getType() == PieceType::Pawn &&
                abs(from->getRow() - to->getRow()) == 1 &&
                abs(from->getColumn() - to->getColumn()) == 1) {
            enPassant = true;
            SquarePtr squareOfCapturedPawn = board->getSquare(from->getRow(), to->getColumn());
            capturedPiece = squareOfCapturedPawn->getPiece();
            squareOfCapturedPawn->getPiece()->setCaptured();
            squareOfCapturedPawn->setPiece(nullptr);
            pieceFirstMove = false;
        }
        PiecePtr piece = from->getPiece();
        to->setPiece(piece);
        piece->setSquare(to);
        from->setPiece(nullptr);
    }
    gameData->addMove(shared_from_this());
    executed = true;
}

void Move::undo(GameDataPtr &gameData) {
    if(!executed) return;
    if(player.lock() == nullptr) return;
    BoardPtr board = gameData->getBoard();
    if(abbr == "O-O") {
        int row;
        if(player.lock()->getColor() == WHITE) row = 7;
        else row = 0;

        PiecePtr king = board->getSquare(row, 6)->getPiece();
        board->getSquare(row, 4)->setPiece(king);
        king->setSquare(board->getSquare(row, 4));
        board->getSquare(row, 6)->setPiece(nullptr);
        king->setFirstMove(true);

        PiecePtr rook = board->getSquare(row, 5)->getPiece();
        board->getSquare(row, 7)->setPiece(rook);
        rook->setSquare(board->getSquare(row, 7));
        board->getSquare(row, 5)->setPiece(nullptr);
        rook->setFirstMove(true);
    }
    else if(abbr == "O-O-O") {
        int row;
        if(player.lock()->getColor() == WHITE) row = 7;
        else row = 0;

        PiecePtr king = board->getSquare(row, 2)->getPiece();
        board->getSquare(row, 4)->setPiece(king);
        king->setSquare(board->getSquare(row, 4));
        board->getSquare(row, 2)->setPiece(nullptr);
        king->setFirstMove(true);

        PiecePtr rook = board->getSquare(row, 3)->getPiece();
        board->getSquare(row, 0)->setPiece(rook);
        rook->setSquare(board->getSquare(row, 0));
        board->getSquare(row, 3)->setPiece(nullptr);
        rook->setFirstMove(true);
    }
    else {
        PiecePtr piece = to->getPiece();
        from->setPiece(piece);
        piece->setSquare(from);
        if(pieceFirstMove) piece->setFirstMove(true);
        if(capturedPiece != nullptr) {
            if(enPassant) {
                SquarePtr squareOfCapturedPawn = board->getSquare(from->getRow(), to->getColumn());
                capturedPiece->restore(squareOfCapturedPawn);
                squareOfCapturedPawn->setPiece(capturedPiece);
                to->setPiece(nullptr);
            }
            else {
                capturedPiece->restore(to);
                to->setPiece(capturedPiece);
            }
        }
        else to->setPiece(nullptr);
    }
    gameData->removeMove(shared_from_this());
    executed = false;
}

PlayerPtr Move::getPlayer() const {
    return player.lock();
}
