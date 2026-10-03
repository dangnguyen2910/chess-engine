#include <gtest/gtest.h>
#include "piece.h"

TEST(Piece, to_string) {
    EXPECT_EQ("p", to_string(Piece::PAWN));
    EXPECT_EQ("k", to_string(Piece::KING));
    EXPECT_EQ("q", to_string(Piece::QUEEN));
    EXPECT_EQ("b", to_string(Piece::BISHOP));
    EXPECT_EQ("n", to_string(Piece::KNIGHT));
    EXPECT_EQ("r", to_string(Piece::ROOK));
}
