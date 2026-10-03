#include <gtest/gtest.h>
#include "square.h"

TEST(Square, to_bitboard_a1) {
    std::uint64_t expected = 1ULL;
    std::uint64_t output = to_bitboard(Square::A1);
    EXPECT_EQ(output, expected);
}

TEST(Square, to_bitboard_e5) {
    std::uint64_t expected = 1ULL << 36;
    std::uint64_t output = to_bitboard(Square::E5);
    EXPECT_EQ(output, expected);
}

TEST(Square, to_bitboard_g7) {
    std::uint64_t expected = 1ULL << 54;
    std::uint64_t output = to_bitboard(Square::G7);
    EXPECT_EQ(output, expected);
}

TEST(Square, to_string) {
    using enum Square;
    EXPECT_EQ("a1", to_string(A1));
    EXPECT_EQ("h8", to_string(H8));
    EXPECT_EQ("e5", to_string(E5));
}
