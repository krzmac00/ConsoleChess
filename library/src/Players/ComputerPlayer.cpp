#include "Players/ComputerPlayer.h"
#include "Move.h"
#include "Board.h"
#include <cstdlib>
#include <csignal>

ComputerPlayer::ComputerPlayer(std::string name, Color color) : Player(name, color) {}

ComputerPlayer::~ComputerPlayer() = default;

MovePtr ComputerPlayer::executeMove(BoardPtr board, [[maybe_unused]] ViewPtr view) {
    unsigned long seed = utils::mix(clock(), time(nullptr), getpid());
    srand(seed);
    int toRow;
    int toColumn;
    std::vector<PiecePtr> pieces = board->getPiecesOfPlayer(shared_from_this());
    std::vector<PiecePtr> activePieces;
    for (auto &piece : pieces) {
        if (piece != nullptr && piece->isCaptured() == false) activePieces.push_back(piece);
    }
    int drawPiece = static_cast<int>(rand() % activePieces.size());
    PiecePtr piece = activePieces[drawPiece];
    do {
        if (moves.size() < 4) {
            toRow = rand() % 1 + 2;
            if (color == WHITE) toRow += 2;
        }
        else toRow = rand() % 8;
        toColumn = rand() % 8;
    } while (piece->getSquare() == board->getSquare(toRow, toColumn));
    return std::make_shared<Move>(piece->getSquare(), board->getSquare(toRow, toColumn));
}

PieceType ComputerPlayer::promotion([[maybe_unused]] ViewPtr view) {
    PieceType type;
    unsigned long seed = utils::mix(clock(), time(nullptr), getpid());
    srand(seed);
    int num = static_cast<int>(rand() % 4);
    switch(num) {
        case 0:
            type = PieceType::Knight;
            break;
        case 1:
            type = PieceType::Rook;
            break;
        case 2:
            type = PieceType::Bishop;
            break;
        default:
            type = PieceType::Queen;
            break;
    }
    return type;
}
