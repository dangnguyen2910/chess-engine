#pragma once

#include "square.h"
#include "piece.h"
#include <optional>
#include <string>

enum class MOVE_FLAG : int {
    QUIET, 
    CAPTURE, 
    DOUBLE_PUSH, 
    EN_PASANT, 
    CASTLE_KING, 
    CASTLE_QUEEN, 
};

struct Move {
    Square from;
    Square to;
    Piece piece;
    std::optional<Piece> promotion;

    Move(Square from, Square to, Piece piece, std::optional<Piece> promotion = std::nullopt); 
    std::string to_string();
};
