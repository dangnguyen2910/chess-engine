#pragma once

#include "board.h"

constexpr uint64_t FILE_A = 0x0101010101010101ULL;
constexpr uint64_t FILE_B = 0x0202020202020202ULL;
constexpr uint64_t FILE_G = 0x4040404040404040ULL;
constexpr uint64_t FILE_H = 0x8080808080808080ULL;

class MoveGenerator {
    public:
        MoveGenerator(); 
        MoveGenerator(Board board);
        void generate_moves(); 

        std::uint64_t generate_pawns_moves(); 
        std::uint64_t generate_knights_moves(); 
        std::uint64_t generate_bishops_moves(); 
        std::uint64_t generate_rooks_moves(); 
        std::uint64_t generate_king_moves(); 
        std::uint64_t generate_queen_moves(); 

    private: 
        Board _board; 

};