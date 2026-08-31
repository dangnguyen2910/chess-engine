#include <gtest/gtest.h>
#include "move_generator.h"

TEST(MoveGenerator, generate_white_knights_moves_beginning_possition) {
    Board board;
    board.initial_position();
    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_knights_moves();
    std::uint64_t expected = 0xA50000;
    ASSERT_EQ(moves, expected);
}
