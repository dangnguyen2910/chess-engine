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