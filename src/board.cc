#include "board.h"
#include <string>

Board::Board() {
    white_pawns_pos = 65280ULL; 
    white_rooks_pos = 129ULL;
    white_knights_pos = 66ULL; 
    white_bishops_pos = 36ULL; 
    white_king_pos = 16ULL; 
    white_queen_pos = 8ULL; 

    black_pawns_pos = 71776119061217280ULL; 
    black_rooks_pos = 9295429630892703744ULL; 
    black_knights_pos = 4755801206503243776ULL; 
    black_bishops_pos = 2594073385365405696ULL; 
    black_queen_pos = 576460752303423488ULL; 
    black_king_pos = 1152921504606846976ULL; 

    white_move = true; 
    white_can_castle = true; 
    black_can_castle = true; 
}

Board::~Board() {

}

std::string Board::print() {
    std::string board_visualization = ""; 

    for (int rank = 7; rank >= 0; rank--) {
        board_visualization += std::to_string(rank + 1) + "| "; 
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file; 
            if (white_pawns_pos & (1ULL << square) || black_pawns_pos & (1ULL << square)) {
                board_visualization += "p "; 
            } else if (white_rooks_pos & (1ULL << square) || black_rooks_pos & (1ULL << square)) {
                board_visualization += "r "; 
            } else if (white_knights_pos & (1ULL << square) || black_knights_pos & (1ULL << square)) {
                board_visualization += "n "; 
            } else if (white_bishops_pos & (1ULL << square) || black_bishops_pos & (1ULL << square)) {
                board_visualization += "b "; 
            } else if (white_king_pos & (1ULL << square) || black_king_pos & (1ULL << square)) {
                board_visualization += "k "; 
            } else if (white_queen_pos & (1ULL << square) || black_queen_pos & (1ULL << square)) {
                board_visualization += "q "; 
            } else {
                board_visualization += ". "; 
            }
        }
        board_visualization += "\n"; 
    }

    board_visualization += " -----------------\n   a b c d e f g h";

    return board_visualization; 
}