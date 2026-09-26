#include "move_generator.h"
#include "board.h"
#include "square.h"
#include <bit>
#include <bitset>
#include <iostream>

MoveGenerator::MoveGenerator() {
    _board = Board();
}

MoveGenerator::MoveGenerator(Board board) {
    _board = board;
}

std::uint64_t MoveGenerator::generate_knights_moves(bool white_to_move) {
    std::uint64_t knights_pos;
    std::uint64_t friend_pos;
    std::uint64_t moves = 0ULL;

    if (white_to_move) {
        knights_pos = _board.get_white_knights_pos();
        friend_pos = _board.get_white_pieces_pos();
    } else {
        knights_pos = _board.get_black_knights_pos();
        friend_pos = _board.get_black_pieces_pos();
    }

    moves |= ((knights_pos & ~(FILE_A | FILE_B)) << 6) & ~friend_pos;
    moves |= ((knights_pos & ~(FILE_G | FILE_H)) << 10) & ~friend_pos;
    moves |= ((knights_pos & ~FILE_A) << 15) & ~friend_pos;
    moves |= ((knights_pos & ~FILE_H) << 17) & ~friend_pos;

    moves |= ((knights_pos & ~(FILE_G | FILE_H)) >> 6) & ~friend_pos;
    moves |= ((knights_pos & ~(FILE_A | FILE_B)) >> 10) & ~friend_pos;
    moves |= ((knights_pos & ~FILE_H) >> 15) & ~friend_pos;
    moves |= ((knights_pos & ~FILE_A) >> 17) & ~friend_pos;

    return moves;
}

// TODO: Current function generate pseudo-legal moves only, Implement
// generating legal moves after done with other pieces.
std::uint64_t MoveGenerator::generate_king_moves(bool white_to_move) {
    std::uint64_t king_pos = 0ULL;
    std::uint64_t friend_pos = 0ULL;
    std::uint64_t enemy_pos = 0ULL;
    std::vector<bool> castling_right = {};
    bool king_at_initial_pos = false;
    std::uint64_t moves = 0ULL;
    std::vector<bool> rooks_at_initial_pos = { false, false };

    if (white_to_move) {
        king_pos = _board.get_white_king_pos();
        friend_pos = _board.get_white_pieces_pos();
        enemy_pos = _board.get_black_pieces_pos();

        castling_right = _board.get_white_castling_right();
        king_at_initial_pos = king_pos & to_bitboard(Square::E1);
        std::uint64_t rooks_pos = _board.get_white_rooks_pos();
        rooks_at_initial_pos[KING_SIDE] = rooks_pos & to_bitboard(Square::H1);
        rooks_at_initial_pos[QUEEN_SIDE] = rooks_pos & to_bitboard(Square::A1);
    } else {
        king_pos = _board.get_black_king_pos();
        friend_pos = _board.get_black_pieces_pos();
        enemy_pos = _board.get_white_pieces_pos();

        castling_right = _board.get_black_castling_right();
        king_at_initial_pos = king_pos & to_bitboard(Square::E8);
        std::uint64_t rooks_pos = _board.get_black_rooks_pos();
        rooks_at_initial_pos[KING_SIDE] = rooks_pos & to_bitboard(Square::H8);
        rooks_at_initial_pos[QUEEN_SIDE] = rooks_pos & to_bitboard(Square::A8);
    }

    std::uint64_t pieces = friend_pos | enemy_pos;

    moves |= ((king_pos & (~FILE_H)) << 1) & (~friend_pos);
    moves |= ((king_pos & (~FILE_A)) << 7) & (~friend_pos);
    moves |= king_pos << 8 & (~friend_pos);
    moves |= ((king_pos & (~FILE_H)) << 9) & (~friend_pos);

    moves |= ((king_pos & (~FILE_A)) >> 1) & (~friend_pos);
    moves |= ((king_pos & (~FILE_H)) >> 7) & (~friend_pos);
    moves |= king_pos >> 8 & (~friend_pos);
    moves |= ((king_pos & (~FILE_A)) >> 9) & (~friend_pos);

    // Castling right = true && King at initial position &&
    // Rook at initial position
    // No friend pieces and enemy pices on path &&
    // No enemy piece is attacking at path.
    std::uint64_t attacked_squares = 0ULL;

    if (castling_right[KING_SIDE] && king_at_initial_pos
        && rooks_at_initial_pos[KING_SIDE]
    ) {
        attacked_squares = white_to_move ? _generate_black_moves() : _generate_white_moves();

        if (((~attacked_squares >> 1) & king_pos)
            && ((~attacked_squares >> 2) & king_pos)
            && ((~pieces >> 1) & king_pos)
            && ((~pieces >> 2) & king_pos)
        ) {
            moves |= king_pos << 2;
        }
    } else {
        castling_right[KING_SIDE] = false;
    }

    if (castling_right[QUEEN_SIDE] && king_at_initial_pos
        && rooks_at_initial_pos[QUEEN_SIDE]
    ) {
        attacked_squares = white_to_move ? _generate_black_moves() : _generate_white_moves();

        if (((~attacked_squares << 1) & king_pos)
            && ((~attacked_squares << 2) & king_pos)
            && ((~pieces << 1) & king_pos)
            && ((~pieces << 2) & king_pos)
        ) {
            moves |= king_pos >> 2;
        }
    } else {
        castling_right[QUEEN_SIDE] = false;
    }

    return moves;
}

std::uint64_t MoveGenerator::generate_rooks_moves(bool white_to_move) {
    std::uint64_t rooks_pos;
    std::uint64_t friend_pos;
    std::uint64_t enemy_pos;
    std::uint64_t moves = 0ULL;

    if (white_to_move) {
        rooks_pos = _board.get_white_rooks_pos();
        friend_pos = _board.get_white_pieces_pos();
        enemy_pos = _board.get_black_pieces_pos();
    } else {
        rooks_pos = _board.get_black_rooks_pos();
        friend_pos = _board.get_black_pieces_pos();
        enemy_pos = _board.get_white_pieces_pos();
    }

    while (rooks_pos != 0) {
        std::uint64_t rook = rooks_pos & (-rooks_pos);
        int pos = std::countr_zero(rook);
        int rank = pos / 8;
        int file = pos % 8;

        // North
        for (int i = rank; i < 8; i++) {
            std::uint64_t attack_square = (1ULL << (8 * i + file)) & (~friend_pos);
            if (i != rank && attack_square == 0) break;
            moves |= attack_square;
            if (1ULL << (8 * i + file) & enemy_pos) break;
        }

        // South
        for (int i = rank; i >= 0; i--) {
            std::uint64_t attack_square = (1ULL << (8 * i + file)) & (~friend_pos);
            if (i != rank && attack_square == 0) break;
            moves |= attack_square;
            if (1ULL << (8 * i + file) & enemy_pos) break;
        }

        // East
        for (int j = file; j < 8; j++) {
            std::uint64_t attack_square = (1ULL << (8 * rank + j)) & (~friend_pos);
            if (j != file && attack_square == 0) break;
            moves |= attack_square;
            if (1ULL << (8 * rank + j) & enemy_pos) break;
        }

        // West
        for (int j = file; j >= 0; j--) {
            std::uint64_t attack_square = (1ULL << (8 * rank + j)) & (~friend_pos);
            if (j != file && attack_square == 0) break;
            moves |= attack_square;
            if (1ULL << (8 * rank + j) & enemy_pos) break;
        }
        rooks_pos -= rook;
    }

    return moves;
}

std::uint64_t MoveGenerator::generate_bishops_moves(bool white_to_move) {
    std::uint64_t moves = 0ULL;
    std::uint64_t bishops_pos;
    std::uint64_t friend_pos;
    std::uint64_t enemy_pos;

    if (white_to_move) {
        bishops_pos = _board.get_white_bishops_pos();
        friend_pos = _board.get_white_pieces_pos();
        enemy_pos = _board.get_black_pieces_pos();
    } else {
        bishops_pos = _board.get_black_bishops_pos();
        friend_pos = _board.get_black_pieces_pos();
        enemy_pos = _board.get_white_pieces_pos();
    }

    while (bishops_pos != 0) {
        std::uint64_t bishop = bishops_pos & (-bishops_pos);

        int pos = std::countr_zero(bishop);
        int rank = pos / 8;
        int file = pos % 8;

        // North-East
        std::uint64_t attack_square = bishop;
        for (int i = file + 1; i < 8; i++) {
            attack_square = attack_square << 9;
            if ((attack_square & (~friend_pos)) == 0) break;
            moves |= attack_square;
            if ((attack_square & (~enemy_pos)) == 0) break;
        }

        // South-East
        attack_square = bishop;
        for (int i = file + 1; i < 8; i++) {
            attack_square = attack_square >> 7;
            if ((attack_square & (~friend_pos)) == 0) break;
            moves |= attack_square;
            if ((attack_square & (~enemy_pos)) == 0) break;
        }

        // South-West
        attack_square = bishop;
        for (int i = file - 1; i >= 0; i--) {
            attack_square = attack_square >> 9;
            if ((attack_square & (~friend_pos)) == 0) break;
            moves |= attack_square;
            if ((attack_square & (~enemy_pos)) == 0) break;
        }

        // North-West
        attack_square = bishop;
        for (int i = file - 1; i >= 0; i--) {
            attack_square = attack_square << 7;
            if ((attack_square & (~friend_pos)) == 0) break;
            moves |= attack_square;
            if ((attack_square & (~enemy_pos)) == 0) break;
        }

        bishops_pos -= bishop;
    }

    return moves;
}

std::uint64_t MoveGenerator::generate_queen_moves(bool white_to_move) {
    std::uint64_t queen_pos = 0ULL;
    std::uint64_t friend_pos = 0ULL;
    std::uint64_t enemy_pos = 0ULL;
    std::uint64_t moves = 0ULL;


    if (white_to_move) {
        queen_pos = _board.get_white_queen_pos();
        friend_pos = _board.get_white_pieces_pos();
        enemy_pos = _board.get_black_pieces_pos();
    } else {
        queen_pos = _board.get_black_queen_pos();
        friend_pos = _board.get_black_pieces_pos();
        enemy_pos = _board.get_white_pieces_pos();
    }

    while (queen_pos != 0) {
        std::uint64_t queen = queen_pos & (-queen_pos);
        int pos = std::countr_zero(queen);
        int rank = pos / 8;
        int file = pos % 8;

        // North
        for (int i = rank; i < 8; i++) {
            std::uint64_t attack_square = (1ULL << (8 * i + file)) & (~friend_pos);
            if (i != rank && attack_square == 0) break;
            moves |= attack_square;
            if (1ULL << (8 * i + file) & enemy_pos) break;
        }

        // South
        for (int i = rank; i >= 0; i--) {
            std::uint64_t attack_square = (1ULL << (8 * i + file)) & (~friend_pos);
            if (i != rank && attack_square == 0) break;
            moves |= attack_square;
            if (1ULL << (8 * i + file) & enemy_pos) break;
        }

        // East
        for (int j = file; j < 8; j++) {
            std::uint64_t attack_square = (1ULL << (8 * rank + j)) & (~friend_pos);
            if (j != file && attack_square == 0) break;
            moves |= attack_square;
            if (1ULL << (8 * rank + j) & enemy_pos) break;
        }

        // West
        for (int j = file; j >= 0; j--) {
            std::uint64_t attack_square = (1ULL << (8 * rank + j)) & (~friend_pos);
            if (j != file && attack_square == 0) break;
            moves |= attack_square;
            if (1ULL << (8 * rank + j) & enemy_pos) break;
        }

        // North-East
        std::uint64_t attack_square = queen;
        for (int i = file + 1; i < 8; i++) {
            attack_square = attack_square << 9;
            if ((attack_square & (~friend_pos)) == 0) break;
            moves |= attack_square;
            if ((attack_square & (~enemy_pos)) == 0) break;
        }

        // South-East
        attack_square = queen;
        for (int i = file + 1; i < 8; i++) {
            attack_square = attack_square >> 7;
            if ((attack_square & (~friend_pos)) == 0) break;
            moves |= attack_square;
            if ((attack_square & (~enemy_pos)) == 0) break;
        }

        // South-West
        attack_square = queen;
        for (int i = file - 1; i >= 0; i--) {
            attack_square = attack_square >> 9;
            if ((attack_square & (~friend_pos)) == 0) break;
            moves |= attack_square;
            if ((attack_square & (~enemy_pos)) == 0) break;
        }

        // North-West
        attack_square = queen;
        for (int i = file - 1; i >= 0; i--) {
            attack_square = attack_square << 7;
            if ((attack_square & (~friend_pos)) == 0) break;
            moves |= attack_square;
            if ((attack_square & (~enemy_pos)) == 0) break;
        }

        queen_pos -= queen;
    }

    return moves;
}

std::uint64_t MoveGenerator::generate_pawns_moves(bool white_to_move) {
    std::uint64_t moves = 0ULL;

    if (white_to_move) {
        moves = _generate_white_pawns_moves();

    } else {
        moves = _generate_black_pawns_moves();
    }

    return moves;
}

std::uint64_t MoveGenerator::_generate_white_pawns_moves() {
    std::uint64_t moves = 0ULL;
    std::uint64_t pawns_pos = _board.get_white_pawns_pos();
    std::uint64_t friend_pos = _board.get_white_pieces_pos();
    std::uint64_t enemy_pos = _board.get_black_pieces_pos();
    std::uint64_t pieces_no_pawns = (friend_pos | enemy_pos) - pawns_pos;

    moves |= (pawns_pos << 8) & ~pieces_no_pawns;
    moves |= (pawns_pos & RANK_2 & ~(pieces_no_pawns >> 8) & ~(pieces_no_pawns >> 16)) << 16;
    moves |= ((pawns_pos & ~FILE_A) << 7) & enemy_pos;
    moves |= ((pawns_pos & ~FILE_H) << 9) & enemy_pos;

    return moves;
}

std::uint64_t MoveGenerator::_generate_black_pawns_moves() {
    std::uint64_t moves = 0ULL;
    std::uint64_t pawns_pos = _board.get_black_pawns_pos();
    std::uint64_t friend_pos = _board.get_black_pieces_pos();
    std::uint64_t enemy_pos = _board.get_white_pieces_pos();
    std::uint64_t pieces_no_pawns = (friend_pos | enemy_pos) - pawns_pos;

    moves |= (pawns_pos >> 8) & ~pieces_no_pawns;
    moves |= (pawns_pos & RANK_7 & ~(pieces_no_pawns << 8) & ~(pieces_no_pawns << 16)) >> 16;
    moves |= ((pawns_pos & ~FILE_A) >> 7) & enemy_pos;
    moves |= ((pawns_pos & ~FILE_H) >> 9) & enemy_pos;

    return moves;
}

std::uint64_t MoveGenerator::_generate_white_moves() {
    std::uint64_t moves = 0ULL;
    moves |= generate_pawns_moves(true);
    moves |= generate_king_moves(true);
    moves |= generate_queen_moves(true);
    moves |= generate_bishops_moves(true);
    moves |= generate_knights_moves(true);
    moves |= generate_rooks_moves(true);
    return moves;
}

std::uint64_t MoveGenerator::_generate_black_moves() {
    std::uint64_t moves = 0ULL;
    moves |= generate_pawns_moves(false);
    moves |= generate_king_moves(false);
    moves |= generate_queen_moves(false);
    moves |= generate_bishops_moves(false);
    moves |= generate_knights_moves(false);
    moves |= generate_rooks_moves(false);
    return moves;
}
