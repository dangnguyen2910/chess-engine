cmake_minimum_required(VERSION 3.20...4.3)

project(ChessEngine LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_library(chess-engine
    src/board.cc include/board.h    
    src/move_generator.cc include/move_generator.h
    src/square.cc include/square.h
)
target_include_directories(chess-engine PUBLIC include)

add_executable(chess-engine-app 
    src/main.cc 
)
target_link_libraries(chess-engine-app PRIVATE chess-engine)

# Tests
enable_testing()
add_executable(chess-tests
    tests/board_test.cc
    tests/move_generator_test.cc
    tests/square_test.cc
)
target_link_libraries(
    chess-tests
    GTest::gtest_main
    chess-engine
)

include(GoogleTest)
gtest_discover_tests(chess-tests)