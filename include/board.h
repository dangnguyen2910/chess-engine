#pragma once

#include <vector>
#include <cstdint> 
#include <string>

class Board {
    public: 
        Board(); 
        ~Board(); 

        std::string to_string(); 


    private: 
        std::uint64_t white_pawns_pos; 
        std::uint64_t white_rooks_pos; 
        std::uint64_t white_knights_pos; 
        std::uint64_t white_bishops_pos; 
        std::uint64_t white_king_pos; 
        std::uint64_t white_queen_pos; 

        std::uint64_t black_pawns_pos; 
        std::uint64_t black_rooks_pos; 
        std::uint64_t black_knights_pos; 
        std::uint64_t black_bishops_pos; 
        std::uint64_t black_king_pos; 
        std::uint64_t black_queen_pos;

        std::uint64_t en_passant_pos; 
        
        bool white_move; 
        std::vector<bool> white_castling_right; 
        std::vector<bool> black_castling_right; 

        int halfmove_clock; 

}; 