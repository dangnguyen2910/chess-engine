#include <gtest/gtest.h>
#include "board.h"

TEST(Board, to_string) {
    Board board;
    std::string board_str = board.to_string();  
    std::string expected = "8| r n b q k b n r \n" 
                           "7| p p p p p p p p \n"
                           "6| . . . . . . . . \n"
                           "5| . . . . . . . . \n"
                           "4| . . . . . . . . \n"
                           "3| . . . . . . . . \n"
                           "2| p p p p p p p p \n"
                           "1| r n b q k b n r \n"
                           " -----------------\n"
                           "   a b c d e f g h";
    EXPECT_EQ(board_str, expected);
}

TEST(Board, get_white_position) {
    Board board; 
    std::uint64_t position = board.get_white_pieces_pos(); 
    std::uint64_t expected = 0b1111'1111'1111'1111; 
    EXPECT_EQ(position, expected); 
}

TEST(Board, get_black_position) {
    Board board; 
    std::uint64_t position = board.get_black_pieces_pos(); 
    std::uint64_t expected = 0xFFFF000000000000; 
    EXPECT_EQ(position, expected); 
}