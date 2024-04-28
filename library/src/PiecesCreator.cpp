#include "PiecesCreator.h"
#include "Pieces/Bishop.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"
#include "Pieces/Pawn.h"
#include "Pieces/Knight.h"
#include "Pieces/Rook.h"

PiecePtr PiecesCreator::create(PieceType rodzaj, PlayerPtr gracz, SquarePtr pole) {
    switch(rodzaj) {
        case PieceType::Bishop:
            return std::make_shared<Bishop>(gracz, pole);
        case PieceType::Queen:
            return std::make_shared<Queen>(gracz, pole);
        case PieceType::King:
            return std::make_shared<King>(gracz, pole);
        case PieceType::Pawn:
            return std::make_shared<Pawn>(gracz, pole);
        case PieceType::Knight:
            return std::make_shared<Knight>(gracz, pole);
        case PieceType::Rook:
            return std::make_shared<Rook>(gracz, pole);
        default:
            return nullptr;
    }
}
