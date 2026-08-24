#include <iostream> 
#include <vector>
#include "board.h"

int main() {
    Board board; 
    std::string board_repr = board.to_string(); 
    std::cout << board_repr << std::endl; 

    return 0; 
}