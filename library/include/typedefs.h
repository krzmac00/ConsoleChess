#ifndef CHESS_TYPEDEFS_H
#define CHESS_TYPEDEFS_H

#include <memory>
#include <functional>
#include <string>

class Board;
class Player;
class Square;
class Piece;
class View;
class Move;
class Check;

//Enumeration
enum Color {
    WHITE = 0,
    BLACK = 1
};

inline std::ostream &operator<<(std::ostream &os, Color color) {
    std::string white = "WHITE";
    std::string black = "BLACK";
    if (color == WHITE) return os << white;
    else return os << black;
}

inline Color operator++(Color color, int) {
    if (color == WHITE) return BLACK;
    else return WHITE;
}

enum class PieceType {
    Bishop,
    Queen,
    King,
    Pawn,
    Knight,
    Rook
};

enum Event {
    move,
    closeMenu,
    quit
};

inline std::ostream &operator<<(std::ostream &os, PieceType piece) {
    std::string name;
    switch (piece) {
        case PieceType::Bishop:
            name = "Bishop";
            break;
        case PieceType::Queen:
            name = "Queen";
            break;
        case PieceType::King:
            name = "King";
            break;
        case PieceType::Pawn:
            name = "Pawn";
            break;
        case PieceType::Knight:
            name = "Knight";
            break;
        case PieceType::Rook:
            name = "Rook";
            break;
    }
    return os << name;
}

//Pointers
typedef std::shared_ptr<Board> BoardPtr;
typedef std::shared_ptr<Player> PlayerPtr;
typedef std::shared_ptr<Square> SquarePtr;
typedef std::shared_ptr<Piece> PiecePtr;
typedef std::weak_ptr<Piece> PieceWeakPtr;
typedef std::shared_ptr<View> ViewPtr;
typedef std::shared_ptr<Move> MovePtr;
typedef std::shared_ptr<Check> CheckPtr;


namespace utils {
    inline unsigned long mix(unsigned long a, unsigned long b, unsigned long c)
    {
        a=a-b;  a=a-c;  a=a^(c >> 13);
        b=b-c;  b=b-a;  b=b^(a << 8);
        c=c-a;  c=c-b;  c=c^(b >> 13);
        a=a-b;  a=a-c;  a=a^(c >> 12);
        b=b-c;  b=b-a;  b=b^(a << 16);
        c=c-a;  c=c-b;  c=c^(b >> 5);
        a=a-b;  a=a-c;  a=a^(c >> 3);
        b=b-c;  b=b-a;  b=b^(a << 10);
        c=c-a;  c=c-b;  c=c^(b >> 15);
        return c;
    }
}

#endif //CHESS_TYPEDEFS_H
