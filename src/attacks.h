#pragma once

#include "bitboard.h"

template<int color>
constexpr uint64_t pawn_attacks(uint64_t b)
{
    if (color == white)
        return shift<north_east, north_west>(b);
    else
        return shift<south_east, south_west>(b);
}

template<int piece>
constexpr uint64_t multiple_attacks(uint64_t b, [[maybe_unused]] uint64_t o = 0)
{
    if (piece == rook)
        return fill<north, south, east, west>(b, o);
    else if (piece == bishop)
        return fill<north_east, north_west, south_east, south_west>(b, o);
    else if (piece == queen)
        return multiple_attacks<bishop>(b, o) | multiple_attacks<rook>(b, o);
    else {
        const uint64_t side = shift<east, west>(b);

        if (piece == king)
            return shift<north, south>(b | side) | side;
        else
            return shift<north, south>(b ^ shift<east, west>(side))
                |  shift<north * 2, south * 2>(side);
    }
}

template<typename T>
using array64 = std::array<T, 64>;

template<typename Func>
consteval auto make_table(Func&& func)
{
    array64<uint64_t> ret{};
    for (size_t i = 0; i < 64; ++i)
        ret[i] = func(1ull << i);
    return ret;
}

template<int piece>
inline constexpr auto empty_attacks = make_table(
        [] (uint64_t b) {
            return multiple_attacks<piece>(b);
        });

template<int piece>
inline constexpr auto magic_masks = make_table(
        [] (uint64_t b) {
            uint64_t edges = 0;
            if (!(b & rank_1)) edges |= rank_1;
            if (!(b & rank_8)) edges |= rank_8;
            if (!(b & file_a)) edges |= file_a;
            if (!(b & file_h)) edges |= file_h;
            return multiple_attacks<piece>(b) & ~edges;
        });

template<int piece>
inline constexpr array64<uint64_t> magic_magics;

// magics numbers from Ethereal
template<>
inline constexpr array64<uint64_t> magic_magics<rook> = {
    0xa180022080400230ull, 0x0040100040022000ull, 0x0080088020001002ull, 0x0080080280841000ull,
    0x4200042010460008ull, 0x04800a0003040080ull, 0x0400110082041008ull, 0x008000a041000880ull,
    0x10138001a080c010ull, 0x0000804008200480ull, 0x00010011012000c0ull, 0x0022004128102200ull,
    0x000200081201200cull, 0x202a001048460004ull, 0x0081000100420004ull, 0x4000800380004500ull,
    0x0000208002904001ull, 0x0090004040026008ull, 0x0208808010002001ull, 0x2002020020704940ull,
    0x8048010008110005ull, 0x6820808004002200ull, 0x0a80040008023011ull, 0x00b1460000811044ull,
    0x4204400080008ea0ull, 0xb002400180200184ull, 0x2020200080100380ull, 0x0010080080100080ull,
    0x2204080080800400ull, 0x0000a40080360080ull, 0x02040604002810b1ull, 0x008c218600004104ull,
    0x8180004000402000ull, 0x488c402000401001ull, 0x4018a00080801004ull, 0x1230002105001008ull,
    0x8904800800800400ull, 0x0042000c42003810ull, 0x008408110400b012ull, 0x0018086182000401ull,
    0x2240088020c28000ull, 0x001001201040c004ull, 0x0a02008010420020ull, 0x0010003009010060ull,
    0x0004008008008014ull, 0x0080020004008080ull, 0x0282020001008080ull, 0x50000181204a0004ull,
    0x48fffe99fecfaa00ull, 0x48fffe99fecfaa00ull, 0x497fffadff9c2e00ull, 0x613fffddffce9200ull,
    0xffffffe9ffe7ce00ull, 0xfffffff5fff3e600ull, 0x0010301802830400ull, 0x510ffff5f63c96a0ull,
    0xebffffb9ff9fc526ull, 0x61fffeddfeedaeaeull, 0x53bfffedffdeb1a2ull, 0x127fffb9ffdfb5f6ull,
    0x411fffddffdbf4d6ull, 0x0801000804000603ull, 0x0003ffef27eebe74ull, 0x7645fffecbfea79eull,
};

template<>
inline constexpr array64<uint64_t> magic_magics<bishop> = {
    0xffedf9fd7cfcffffull, 0xfc0962854a77f576ull, 0x5822022042000000ull, 0x2ca804a100200020ull,
    0x0204042200000900ull, 0x2002121024000002ull, 0xfc0a66c64a7ef576ull, 0x7ffdfdfcbd79ffffull,
    0xfc0846a64a34fff6ull, 0xfc087a874a3cf7f6ull, 0x1001080204002100ull, 0x1810080489021800ull,
    0x0062040420010a00ull, 0x5028043004300020ull, 0xfc0864ae59b4ff76ull, 0x3c0860af4b35ff76ull,
    0x73c01af56cf4cffbull, 0x41a01cfad64aaffcull, 0x040c0422080a0598ull, 0x4228020082004050ull,
    0x0200800400e00100ull, 0x020b001230021040ull, 0x7c0c028f5b34ff76ull, 0xfc0a028e5ab4df76ull,
    0x0020208050a42180ull, 0x001004804b280200ull, 0x2048020024040010ull, 0x0102c04004010200ull,
    0x020408204c002010ull, 0x02411100020080c1ull, 0x102a008084042100ull, 0x0941030000a09846ull,
    0x0244100800400200ull, 0x4000901010080696ull, 0x0000280404180020ull, 0x0800042008240100ull,
    0x0220008400088020ull, 0x04020182000904c9ull, 0x0023010400020600ull, 0x0041040020110302ull,
    0xdcefd9b54bfcc09full, 0xf95ffa765afd602bull, 0x1401210240484800ull, 0x0022244208010080ull,
    0x1105040104000210ull, 0x2040088800c40081ull, 0x43ff9a5cf4ca0c01ull, 0x4bffcd8e7c587601ull,
    0xfc0ff2865334f576ull, 0xfc0bf6ce5924f576ull, 0x80000b0401040402ull, 0x0020004821880a00ull,
    0x8200002022440100ull, 0x0009431801010068ull, 0xc3ffb7dc36ca8c89ull, 0xc3ff8a54f4ca2c89ull,
    0xfffffcfcfd79edffull, 0xfc0863fccb147576ull, 0x040c000022013020ull, 0x2000104000420600ull,
    0x0400000260142410ull, 0x0800633408100500ull, 0xfc087e8e4bb2f736ull, 0x43ff9e4ef4ca2c89ull,
};

template<int piece>
class magic_bitboard_t {
    static constexpr auto bits  = piece == rook ? 12 : 9;
    static constexpr auto shift = 64 - bits;
    static constexpr auto size  = 1 << bits;

    array64<std::array<uint64_t, size>> attacks_table;

    uint64_t index(int s, uint64_t o) const
    {
        auto mask = magic_masks<piece>[s];
        auto magic = magic_magics<piece>[s];
        return ((o & mask) * magic) >> shift;
    }

public:
    magic_bitboard_t()
    {
        for (int s = 0; s < 64; s++) {
            uint64_t o = 0;
            do {
                attacks_table[s][index(s, o)] = multiple_attacks<piece>(1ull << s, o);
                o = (o - magic_masks<piece>[s]) & magic_masks<piece>[s];
            } while (o);
        }
    }

    uint64_t attacks(int s, uint64_t o) const
    {
        return attacks_table[s][index(s, o)];
    }
};

template<int piece>
inline magic_bitboard_t<piece> magic_bb{};

template<int piece>
constexpr uint64_t single_attacks(int s)
{
    return empty_attacks<piece>[s];
}

template<int piece>
constexpr uint64_t single_attacks(int s, [[maybe_unused]] uint64_t o)
{
    if constexpr (piece == rook || piece == bishop)
        return magic_bb<piece>.attacks(s, o);
    else if constexpr (piece == queen)
        return single_attacks<bishop>(s, o) | single_attacks<rook>(s, o);
    else
        return single_attacks<piece>(s);
}
