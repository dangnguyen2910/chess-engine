#include "square.h"

std::uint64_t to_bitboard(Square square) {
    return 1ULL << static_cast<int>(square);
}

std::vector<std::uint64_t> to_bitboard(std::vector<Square> squares) {
    std::vector<std::uint64_t> bbs;

    for (const auto& square : squares) {
        bbs.push_back(to_bitboard(square));
    }

    return bbs;
}
