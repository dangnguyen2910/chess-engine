#pragma once

#include <string>

enum class Piece : int {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
};

std::string to_string(Piece piece);
