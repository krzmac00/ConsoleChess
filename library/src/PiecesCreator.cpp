#include "PiecesCreator.h"
#include "Pieces/Bishop.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"
#include "Pieces/Pawn.h"
#include "Pieces/Knight.h"
#include "Pieces/Rook.h"

PiecePtr PiecesCreator::create(PieceType type, PlayerPtr player, SquarePtr square) {
    switch(type) {
        case PieceType::Bishop:
            return std::make_shared<Bishop>(player, square);
        case PieceType::Queen:
            return std::make_shared<Queen>(player, square);
        case PieceType::King:
            return std::make_shared<King>(player, square);
        case PieceType::Pawn:
            return std::make_shared<Pawn>(player, square);
        case PieceType::Knight:
            return std::make_shared<Knight>(player, square);
        case PieceType::Rook:
            return std::make_shared<Rook>(player, square);
        default:
            return nullptr;
    }
}
