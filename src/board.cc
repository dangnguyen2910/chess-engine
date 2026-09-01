#include "board.h"
#include "square.h"
#include <string>

Board::Board() {
    _white_pawns_pos = 0;
    _white_rooks_pos = 0;
    _white_knights_pos = 0;
    _white_bishops_pos = 0;
    _white_king_pos = 0;
    _white_queen_pos = 0;

    _black_pawns_pos = 0;
    _black_rooks_pos = 0;
    _black_knights_pos = 0;
    _black_bishops_pos = 0;
    _black_queen_pos = 0;
    _black_king_pos = 0;

    _en_passant_pos = 0;

    _is_white_move = true;
    _white_castling_right = {true, true};
    _black_castling_right = {true, true};

    _halfmove_clock = 0;
}

void Board::initial_position() {
    _white_pawns_pos = 65280ULL;
    _white_rooks_pos = 129ULL;
    _white_knights_pos = 66ULL;
    _white_bishops_pos = 36ULL;
    _white_king_pos = 16ULL;
    _white_queen_pos = 8ULL;

    _black_pawns_pos = 71776119061217280ULL;
    _black_rooks_pos = 9295429630892703744ULL;
    _black_knights_pos = 4755801206503243776ULL;
    _black_bishops_pos = 2594073385365405696ULL;
    _black_queen_pos = 576460752303423488ULL;
    _black_king_pos = 1152921504606846976ULL;

    _en_passant_pos = 1099494850560ULL;

    _is_white_move = true;
    _white_castling_right = {true, true};
    _black_castling_right = {true, true};

    _halfmove_clock = 0;
}

Board::~Board() {

}

void Board::set_piece(Piece piece, Color color, Square square) {
    switch (piece) {
        case Piece::KNIGHT:
            if (color == Color::WHITE) _white_knights_pos |= to_bitboard(square);
            if (color == Color::BLACK) _black_knights_pos |= to_bitboard(square);
        case Piece::PAWN:
            if (color == Color::WHITE) _white_pawns_pos |= to_bitboard(square);
            if (color == Color::BLACK) _black_pawns_pos |= to_bitboard(square);
        case Piece::BISHOP:
            if (color == Color::WHITE) _white_bishops_pos |= to_bitboard(square);
            if (color == Color::BLACK) _black_bishops_pos |= to_bitboard(square);
        case Piece::KING:
            if (color == Color::WHITE) _white_king_pos |= to_bitboard(square);
            if (color == Color::BLACK) _black_king_pos |= to_bitboard(square);
        case Piece::QUEEN:
            if (color == Color::WHITE) _white_queen_pos |= to_bitboard(square);
            if (color == Color::BLACK) _black_queen_pos |= to_bitboard(square);
        case Piece::ROOK:
            if (color == Color::WHITE) _white_rooks_pos |= to_bitboard(square);
            if (color == Color::BLACK) _black_rooks_pos |= to_bitboard(square);
    }
}

void Board::set_moveside(Color color) {
    switch (color) {
        case Color::WHITE: _is_white_move = true; break;
        case Color::BLACK: _is_white_move = false; break;
    }
}

std::uint64_t Board::get_white_pieces_pos() {
    return _white_pawns_pos | _white_rooks_pos | _white_knights_pos |
           _white_bishops_pos | _white_king_pos | _white_queen_pos;
}

std::uint64_t Board::get_black_pieces_pos() {
    return _black_pawns_pos | _black_rooks_pos | _black_knights_pos |
           _black_bishops_pos | _black_king_pos | _black_queen_pos;
}

std::string Board::to_string() {
    std::string board_visualization = "";

    for (int rank = 7; rank >= 0; rank--) {
        board_visualization += std::to_string(rank + 1) + "| ";
        for (int file = 0; file < 8; file++) {
            int square = rank * 8 + file;
            if (_white_pawns_pos & (1ULL << square) || _black_pawns_pos & (1ULL << square)) {
                board_visualization += "p ";
            } else if (_white_rooks_pos & (1ULL << square) || _black_rooks_pos & (1ULL << square)) {
                board_visualization += "r ";
            } else if (_white_knights_pos & (1ULL << square) || _black_knights_pos & (1ULL << square)) {
                board_visualization += "n ";
            } else if (_white_bishops_pos & (1ULL << square) || _black_bishops_pos & (1ULL << square)) {
                board_visualization += "b ";
            } else if (_white_king_pos & (1ULL << square) || _black_king_pos & (1ULL << square)) {
                board_visualization += "k ";
            } else if (_white_queen_pos & (1ULL << square) || _black_queen_pos & (1ULL << square)) {
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
