#include "move.h"
#include "square.h"
#include <optional>
#include <string>
 
Move::Move(Square from, Square to, Piece piece, std::optional<Piece> promotion)
    : from(from), to(to), piece(piece), promotion(promotion) {
}

std::string Move::to_string() {
    return ::to_string(from) + ::to_string(to) + ::to_string(piece);
}
