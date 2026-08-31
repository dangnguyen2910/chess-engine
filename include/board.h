#pragma once

#include <vector>
#include <cstdint>
#include <string>
#include "square.h"

enum class Piece : int {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
};

enum class Color {
    WHITE,
    BLACK
};

class Board {
    public:
        Board();
        ~Board();

        void initial_position();

        void set_piece(Piece piece, Color color, Square square);

        std::uint64_t get_white_pieces_pos();
        std::uint64_t get_white_knights_pos() { return _white_knights_pos; }

        std::uint64_t get_black_pieces_pos();
        std::uint64_t get_black_knights_pos() { return _black_knights_pos; };

        bool is_white_move() { return _is_white_move; }

        std::string to_string();


    private:
        std::uint64_t _white_pawns_pos;
        std::uint64_t _white_rooks_pos;
        std::uint64_t _white_knights_pos;
        std::uint64_t _white_bishops_pos;
        std::uint64_t _white_king_pos;
        std::uint64_t _white_queen_pos;

        std::uint64_t _black_pawns_pos;
        std::uint64_t _black_rooks_pos;
        std::uint64_t _black_knights_pos;
        std::uint64_t _black_bishops_pos;
        std::uint64_t _black_king_pos;
        std::uint64_t _black_queen_pos;

        std::uint64_t _en_passant_pos;

        bool _is_white_move;
        std::vector<bool> _white_castling_right;
        std::vector<bool> _black_castling_right;

        int _halfmove_clock;

};
