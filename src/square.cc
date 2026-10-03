#include "square.h"
#include <iostream>

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

std::string to_string(Square square) {
    int id = static_cast<int>(square);
    int rank = id / 8 + 1;
    int file = id % 8;

    std::string res = "";

    switch (rank) {
        case 1: res += "a"; break;
        case 2: res += "b"; break;
        case 3: res += "c"; break;
        case 4: res += "d"; break;
        case 5: res += "e"; break;
        case 6: res += "f"; break;
        case 7: res += "g"; break;
        case 8: res += "h"; break;
    }

    res += std::to_string(file + 1);

    return res;
}
