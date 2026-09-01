#include "move_generator.h"

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
