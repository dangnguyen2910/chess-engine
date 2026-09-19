#include "move_generator.h"
#include "board.h"
#include <bit>
#include <bitset>
#include <iostream>

MoveGenerator::MoveGenerator() {
    _board = Board();
}

MoveGenerator::MoveGenerator(Board board) {
    _board = board;
}

std::uint64_t MoveGenerator::generate_knights_moves() {
    std::uint64_t knights_pos;
    std::uint64_t friend_pos;
    std::uint64_t moves = 0ULL;

    if (_board.is_white_move()) {
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
std::uint64_t MoveGenerator::generate_king_moves() {
    std::uint64_t king_pos;
    std::uint64_t friend_pos;
    std::uint64_t moves = 0ULL;

    if (_board.is_white_move()) {
        king_pos = _board.get_white_king_pos();
        friend_pos = _board.get_white_pieces_pos();
    } else {
        king_pos = _board.get_black_king_pos();
        friend_pos = _board.get_black_pieces_pos();
    }

    moves |= ((king_pos & (~FILE_H)) << 1) & (~friend_pos);
    moves |= ((king_pos & (~FILE_A)) << 7) & (~friend_pos);
    moves |= king_pos << 8 & (~friend_pos);
    moves |= ((king_pos & (~FILE_H)) << 9) & (~friend_pos);

    moves |= ((king_pos & (~FILE_A)) >> 1) & (~friend_pos);
    moves |= ((king_pos & (~FILE_H)) >> 7) & (~friend_pos);
    moves |= king_pos >> 8 & (~friend_pos);
    moves |= ((king_pos & (~FILE_A)) >> 9) & (~friend_pos);

    return moves;
}

std::uint64_t MoveGenerator::generate_rooks_moves() {
    std::uint64_t rooks_pos;
    std::uint64_t friend_pos;
    std::uint64_t enemy_pos;
    std::uint64_t moves = 0ULL;

    if (_board.is_white_move()) {
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

std::uint64_t MoveGenerator::generate_bishops_moves() {
    std::uint64_t moves = 0ULL;
    std::uint64_t bishops_pos;
    std::uint64_t friend_pos;
    std::uint64_t enemy_pos;

    if (_board.is_white_move()) {
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

std::uint64_t MoveGenerator::generate_queen_moves() {
    std::uint64_t queen_pos = 0ULL;
    std::uint64_t friend_pos = 0ULL;
    std::uint64_t enemy_pos = 0ULL;
    std::uint64_t moves = 0ULL;


    if (_board.is_white_move()) {
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

    Board board;
    board.set_piece(Piece::QUEEN, Color::WHITE, moves);
    std::cout << board.to_string() << std::endl;

    return moves;
}
