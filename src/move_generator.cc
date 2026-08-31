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
    }
    else {
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
