#include "piece.h"

std::string to_string(Piece piece) {
    using enum Piece;

    switch (piece) {
        case PAWN: return "p";
        case KING: return "k";
        case QUEEN: return "q";
        case BISHOP: return "b";
        case KNIGHT: return "n";
        case ROOK: return "r";
    }
}
