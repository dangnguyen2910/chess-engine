#pragma once

#include <vector>
#include <cstdint> 
#include <string>

class Board {
    public: 
        Board(); 
        ~Board(); 

        std::string print(); 


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
        
        bool white_move; 
        bool white_can_castle; 
        bool black_can_castle; 

}; 