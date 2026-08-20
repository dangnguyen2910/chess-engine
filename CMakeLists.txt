cmake_minimum_required(VERSION 3.20)

project(ChessEngine LANGUAGES CXX)

add_executable(chess-engine 
    src/main.cc 
    src/board.cc include/board.h
)

target_include_directories(chess-engine PRIVATE include)

target_compile_features(chess-engine PRIVATE cxx_std_20)
