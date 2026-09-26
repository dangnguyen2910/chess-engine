#pragma once

#include "board.h"
#include <cstdint>

constexpr uint64_t FILE_A = 0x0101010101010101ULL;
constexpr uint64_t FILE_B = 0x0202020202020202ULL;
constexpr uint64_t FILE_G = 0x4040404040404040ULL;
constexpr uint64_t FILE_H = 0x8080808080808080ULL;

constexpr uint64_t RANK_1 = 0xFFULL;
constexpr uint64_t RANK_2 = RANK_1 << 8;
constexpr uint64_t RANK_7 = RANK_1 << 48;

constexpr int KING_SIDE = 0;
constexpr int QUEEN_SIDE = 1;


class MoveGenerator {
    public:
        MoveGenerator();
        MoveGenerator(Board board);
        void generate_moves();

        std::uint64_t generate_pawns_moves(bool white_to_move);
        std::uint64_t generate_knights_moves(bool white_to_move);
        std::uint64_t generate_bishops_moves(bool white_to_move);
        std::uint64_t generate_rooks_moves(bool white_to_move);
        std::uint64_t generate_king_moves(bool white_to_move);
        std::uint64_t generate_queen_moves(bool white_to_move);

    protected:
        std::uint64_t _generate_white_pawns_moves();
        std::uint64_t _generate_black_pawns_moves();
        std::uint64_t _generate_white_moves();
        std::uint64_t _generate_black_moves();

    private:
        Board _board;

};
