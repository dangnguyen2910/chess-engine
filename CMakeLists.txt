cmake_minimum_required(VERSION 3.20)

project(ChessEngine LANGUAGES CXX)

add_executable(chess-engine src/main.cc)

target_compile_features(chess-engine PRIVATE cxx_std_20)
