#include "Players/HumanPlayer.h"
#include "IView.h"

HumanPlayer::HumanPlayer(std::string name, Color color) : Player(name, color) {}

HumanPlayer::~HumanPlayer() = default;

MovePtr HumanPlayer::getMove(BoardPtr board, ViewPtr view) {
    std::string move = view->readMove(this->getColor());
    if(move.size() == 1) return nullptr;
    return std::make_shared<Move>(move, board, shared_from_this());
}

PieceType HumanPlayer::promotion(ViewPtr view) {
    return view->readPromotionChoice();
}
