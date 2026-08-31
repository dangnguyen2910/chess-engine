#include "square.h"

std::uint64_t to_bitboard(Square square) {
    return 1ULL << static_cast<int>(square);
}
