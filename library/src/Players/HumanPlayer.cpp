#include "Players/HumanPlayer.h"
#include "View.h"

HumanPlayer::HumanPlayer(std::string name, Color color) : Player(name, color) {}

HumanPlayer::~HumanPlayer() = default;

MovePtr HumanPlayer::executeMove(BoardPtr board, ViewPtr view) {
    std::string move = view->readMove(this->getColor());
    if(move.size() == 1) return std::make_shared<Move>(move);
    return std::make_shared<Move>(move, board);
}

PieceType HumanPlayer::promotion(ViewPtr view) {
    return view->readPromotionChoice();
}
