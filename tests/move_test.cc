#include <gtest/gtest.h> 
#include "move.h"
#include "piece.h"

TEST(Move, to_string) {
    using enum Square; 
    using enum Piece; 
    Move move = Move(E2, E4, PAWN); 
    ASSERT_EQ("e2e4p", move.to_string()); 

    Move move2 = Move(B1, C3, KNIGHT); 
    ASSERT_EQ("b1c3n", move2.to_string()); 
}