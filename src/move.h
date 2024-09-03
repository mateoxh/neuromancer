#pragma once

#include <iostream>
#include <cstdint>

class move_t {
    uint16_t move;

public:
    move_t()
        : move()
    {
    }

    move_t(int from, int to)
        : move(from | to << 6)
    {
    }

    move_t(int from, int to, int promo)
        : move(from | to << 6 | promo << 12)
    {
    }

    int from() const
    {
        return move & 63;
    }

    int to() const
    {
        return (move >> 6) & 63;
    }

    int promo() const
    {
        return move >> 12;
    }

    bool operator==(const move_t&) const = default;
};

std::ostream& operator<<(std::ostream& os, move_t move);
std::istream& operator>>(std::istream& is, move_t& move);
