#include <gtest/gtest.h>
#include "board.h"
#include "move_generator.h"
#include "square.h"
#include <bitset>

TEST(MoveGenerator, generate_white_knights_moves_initial_position) {
    Board board;
    board.initial_position();
    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_knights_moves(true);
    std::uint64_t expected = 0xA50000;
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_knights_moves_pos_1) {
    Board board;
    board.set_piece(Piece::KNIGHT, Color::WHITE, Square::B2);
    board.set_piece(Piece::KNIGHT, Color::WHITE, Square::E7);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_knights_moves(true);
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
    std::uint64_t moves = generator.generate_knights_moves(true);
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
    std::uint64_t moves = generator.generate_knights_moves(true);
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
    std::uint64_t moves = generator.generate_knights_moves(false);
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
    std::uint64_t moves = generator.generate_king_moves(true);
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
    std::uint64_t moves = generator.generate_king_moves(true);
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
    std::uint64_t moves = generator.generate_king_moves(true);
    std::uint64_t expected = 0ULL;

    expected |= to_bitboard(D5) | to_bitboard(E5) | to_bitboard(F5) | to_bitboard(F4)
             | to_bitboard(F3) | to_bitboard(E3) | to_bitboard(D3) | to_bitboard(D4);
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_rooks_moves_pos1) {
    using enum Square;
    Board board;
    board.set_piece(Piece::ROOK, Color::WHITE, Square::E4);
    board.set_piece(Piece::ROOK, Color::WHITE, Square::A1);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_rooks_moves(true);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = {A2, A3, A4, A5, A6, A7, A8, B1, C1, D1, E1, F1, G1, H1,
                                   E2, E3, E5, E6, E7, E8, B4, C4, D4, F4, G4, H4};
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}


TEST(MoveGenerator, generate_white_rooks_moves_pos2) {
    using enum Square;
    Board board;
    board.set_piece(Piece::ROOK, Color::WHITE, Square::E4);
    board.set_piece(Piece::PAWN, Color::WHITE, E7);
    board.set_piece(Piece::PAWN, Color::WHITE, H4);
    board.set_piece(Piece::PAWN, Color::BLACK, B4);
    board.set_piece(Piece::PAWN, Color::BLACK, E2);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_rooks_moves(true);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = {E2, E3, E5, E6, B4, C4, D4, F4, G4};
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_bishops_moves_pos1) {
    using enum Square;
    Board board;
    board.set_piece(Piece::BISHOP, Color::WHITE, Square::B5);
    board.set_piece(Piece::BISHOP, Color::WHITE, Square::E5);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_bishops_moves(true);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = {C6, D7, E8, C4, D3, E2, F1, A4, A6,
                                   F6, G7, H8, F4, G3, H2, D4, C3, B2, A1, D6, C7, B8};
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_bishops_moves_pos2) {
    using enum Square;
    Board board;
    board.set_piece(Piece::BISHOP, Color::WHITE, Square::B5);
    board.set_piece(Piece::BISHOP, Color::WHITE, Square::E5);
    board.set_piece(Piece::KNIGHT, Color::WHITE, Square::D3);
    board.set_piece(Piece::ROOK, Color::BLACK, Square::D7);
    board.set_piece(Piece::BISHOP, Color::BLACK, Square::G7);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_bishops_moves(true);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = {C6, D7, C4, A4, A6,
                                   F6, G7, F4, G3, H2, D4, C3, B2, A1, D6, C7, B8};
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_bishops_moves_pos3) {
    using enum Square;
    Board board;
    board.set_piece(Piece::BISHOP, Color::WHITE, Square::A1);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_bishops_moves(true);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = { B2, C3, D4, E5, F6, G7, H8 };
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_queen_moves_pos1) {
    using enum Square;
    Board board;
    board.set_piece(Piece::QUEEN, Color::WHITE, Square::E4);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_queen_moves(true);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = { E1, E2, E3, E5, E6, E7, E8,
                                    A4, B4, C4, D4, F4, G4, H4,
                                    B1, C2, D3, F5, G6, H7,
                                    A8, B7, C6, D5, F3, G2, H1};
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_queen_moves_pos2) {
    using enum Square;
    Board board;
    board.set_piece(Piece::QUEEN, Color::WHITE, Square::E4);
    board.set_piece(Piece::PAWN, Color::WHITE, Square::E6);
    board.set_piece(Piece::BISHOP, Color::WHITE, Square::G2);
    board.set_piece(Piece::KNIGHT, Color::WHITE, Square::E1);
    board.set_piece(Piece::QUEEN, Color::BLACK, Square::B4);
    board.set_piece(Piece::ROOK, Color::BLACK, Square::B7);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::C2);
    board.set_piece(Piece::ROOK, Color::BLACK, Square::G6);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_queen_moves(true);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = { E2, E3, E5,
                                    B4, C4, D4, F4, G4, H4,
                                    C2, D3, F5, G6,
                                    B7, C6, D5, F3 };
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_pawns_moves_pos1) {
    using enum Square;
    Board board;
    board.set_piece(Piece::PAWN, Color::WHITE, Square::A2);
    board.set_piece(Piece::PAWN, Color::WHITE, Square::B2);
    board.set_piece(Piece::PAWN, Color::WHITE, Square::C2);
    board.set_piece(Piece::PAWN, Color::WHITE, Square::D2);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_pawns_moves(true);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = { A3, B3, C3, D3,
                                    A4, B4, C4, D4 };
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_pawns_moves_pos2) {
    using enum Square;
    Board board;
    board.set_piece(Piece::PAWN, Color::WHITE, Square::A2);
    board.set_piece(Piece::PAWN, Color::WHITE, Square::B2);
    board.set_piece(Piece::PAWN, Color::WHITE, Square::C3);
    board.set_piece(Piece::PAWN, Color::WHITE, Square::D2);
    board.set_piece(Piece::PAWN, Color::WHITE, Square::E3);

    board.set_piece(Piece::BISHOP, Color::WHITE, A3);
    board.set_piece(Piece::KNIGHT, Color::BLACK, B4);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_pawns_moves(true);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = { B3, D3, C4, D4, E4 , B4 };
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_white_pawns_moves_pos3) {
    using enum Square;
    Board board;
    board.set_piece(Piece::PAWN, Color::WHITE, Square::A4);
    board.set_piece(Piece::PAWN, Color::WHITE, Square::C4);
    board.set_piece(Piece::PAWN, Color::WHITE, Square::D2);
    board.set_piece(Piece::PAWN, Color::WHITE, Square::E3);

    board.set_piece(Piece::PAWN, Color::BLACK, B5);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_pawns_moves(true);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = {A5, B5, C5, D3, D4, E4};
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_black_pawns_moves_pos1) {
    using enum Square;
    Board board;
    board.set_moveside(Color::BLACK);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::A7);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::B7);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::C7);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::D7);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_pawns_moves(false);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = { A6, B6, C6, D6,
                                    A5, B5, C5, D5 };
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_black_pawns_moves_pos2) {
    using enum Square;
    Board board;
    board.set_moveside(Color::BLACK);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::A7);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::B7);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::C6);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::D7);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::E6);

    board.set_piece(Piece::BISHOP, Color::WHITE, A6);
    board.set_piece(Piece::KNIGHT, Color::BLACK, B5);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_pawns_moves(false);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = { A6, B6, C5, D6, D5, E5 };
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}

TEST(MoveGenerator, generate_black_pawns_moves_pos3) {
    using enum Square;
    Board board;
    board.set_moveside(Color::BLACK);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::A7);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::B7);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::C6);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::D7);
    board.set_piece(Piece::PAWN, Color::BLACK, Square::E6);

    board.set_piece(Piece::BISHOP, Color::WHITE, A6);
    board.set_piece(Piece::KNIGHT, Color::WHITE, F5);
    board.set_piece(Piece::KNIGHT, Color::BLACK, B5);

    MoveGenerator generator = MoveGenerator(board);
    std::uint64_t moves = generator.generate_pawns_moves(false);

    std::uint64_t expected = 0ULL;
    std::vector<Square> squares = { A6, B6, C5, D6, D5, E5, F5 };
    std::vector<std::uint64_t> bbs = to_bitboard(squares);

    for (const auto& bb : bbs) {
        expected |= bb;
    }
    ASSERT_EQ(moves, expected);
}
