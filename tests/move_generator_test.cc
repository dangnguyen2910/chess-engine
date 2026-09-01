#include <gtest/gtest.h>
#include "board.h"
#include "move_generator.h"
#include "square.h"

TEST(MoveGenerator, generate_white_knights_moves_initial_position) {
    Board board;
    board.initial_position();
    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_knights_moves();
    std::uint64_t expected = 0xA50000;
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_knights_moves_pos_1) {
    Board board;
    board.set_piece(Piece::KNIGHT, Color::WHITE, Square::B2);
    board.set_piece(Piece::KNIGHT, Color::WHITE, Square::E7);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_knights_moves();
    std::uint64_t expected = to_bitboard(Square::A4) | to_bitboard(Square::C4)
                            | to_bitboard(Square::D1) | to_bitboard(Square::D3)
                            | to_bitboard(Square::C6) | to_bitboard(Square::C8)
                            | to_bitboard(Square::D5) | to_bitboard(Square::F5)
                            | to_bitboard(Square::G6) | to_bitboard(Square::G8);

    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_knights_moves_pos_2) {
    Board board;
    board.set_piece(Piece::KNIGHT, Color::WHITE, Square::E4);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_knights_moves();
    std::uint64_t expected = to_bitboard(Square::C3) | to_bitboard(Square::C5)
                             | to_bitboard(Square::D2) | to_bitboard(Square::D6)
                             | to_bitboard(Square::F2) | to_bitboard(Square::F6)
                             | to_bitboard(Square::G3) | to_bitboard(Square::G5);

    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_knights_moves_pos_3) {
    Board board;
    board.set_piece(Piece::KNIGHT, Color::WHITE, Square::B2);
    board.set_piece(Piece::KNIGHT, Color::WHITE, Square::D3);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_knights_moves();
    std::uint64_t expected = to_bitboard(Square::A4) | to_bitboard(Square::C4)
                             | to_bitboard(Square::D1) | to_bitboard(Square::B4)
                             | to_bitboard(Square::C1) | to_bitboard(Square::C5)
                             | to_bitboard(Square::E1) | to_bitboard(Square::E5)
                             | to_bitboard(Square::F2) | to_bitboard(Square::F4);

    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_black_knights_moves_pos_1) {
    Board board;
    board.set_piece(Piece::KNIGHT, Color::BLACK, Square::B2);
    board.set_piece(Piece::KNIGHT, Color::BLACK, Square::D3);
    board.set_moveside(Color::BLACK);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_knights_moves();
    std::uint64_t expected = to_bitboard(Square::A4) | to_bitboard(Square::C4)
                             | to_bitboard(Square::D1) | to_bitboard(Square::B4)
                             | to_bitboard(Square::C1) | to_bitboard(Square::C5)
                             | to_bitboard(Square::E1) | to_bitboard(Square::E5)
                             | to_bitboard(Square::F2) | to_bitboard(Square::F4);

    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_king_moves_pos1) {
    using enum Square;
    Board board;
    board.set_piece(Piece::KING, Color::WHITE, Square::A3);
    board.set_piece(Piece::ROOK, Color::WHITE, Square::A2);
    board.set_moveside(Color::WHITE);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_king_moves();
    std::uint64_t expected = 0ULL;

    expected |= to_bitboard(A4) | to_bitboard(B2) | to_bitboard(B3) | to_bitboard(B4);
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_king_moves_pos2) {
    using enum Square;
    Board board;
    board.set_piece(Piece::KING, Color::WHITE, Square::D1);
    board.set_piece(Piece::KING, Color::WHITE, Square::D8);
    board.set_piece(Piece::KING, Color::WHITE, Square::H4);
    board.set_moveside(Color::WHITE);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_king_moves();
    std::uint64_t expected = 0ULL;

    expected |= to_bitboard(C1) | to_bitboard(E1) | to_bitboard(C2) | to_bitboard(D2) | to_bitboard(E2);
    expected |= to_bitboard(H3) | to_bitboard(H5) | to_bitboard(G3) | to_bitboard(G4) | to_bitboard(G5);
    expected |= to_bitboard(C8) | to_bitboard(E8) | to_bitboard(C7) | to_bitboard(D7) | to_bitboard(E7);
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_king_moves_pos3) {
    using enum Square;
    Board board;
    board.set_piece(Piece::KING, Color::WHITE, Square::E4);
    board.set_moveside(Color::WHITE);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_king_moves();
    std::uint64_t expected = 0ULL;

    expected |= to_bitboard(D5) | to_bitboard(E5) | to_bitboard(F5) | to_bitboard(F4)
             | to_bitboard(F3) | to_bitboard(E3) | to_bitboard(D3) | to_bitboard(D4);
    ASSERT_EQ(moves, expected);
}
