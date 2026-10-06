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
    int file = id % 8 + 1;

    std::string res = "";

    switch (file) {
        case 1: res += "a"; break;
        case 2: res += "b"; break;
        case 3: res += "c"; break;
        case 4: res += "d"; break;
        case 5: res += "e"; break;
        case 6: res += "f"; break;
        case 7: res += "g"; break;
        case 8: res += "h"; break;
    }

    res += std::to_string(rank);

    return res;
}

Square to_square(std::string sqr) {
    char file = sqr[0]; 
    char rank = sqr[1] - 1; 
    int rank_no = rank - '0'; 

    int file_no = 0; 
    switch (file) {
        case 'a': file_no = 0; break; 
        case 'b': file_no = 1; break; 
        case 'c': file_no = 2; break; 
        case 'd': file_no = 3; break; 
        case 'e': file_no = 4; break; 
        case 'f': file_no = 5; break; 
        case 'g': file_no = 6; break; 
        case 'h': file_no = 7; break; 
    }

    return static_cast<Square>(rank_no * 8 + file_no); 
}