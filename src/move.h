#pragma once

#include <iostream>
#include <cstdint>

class move_t {
public:
	move_t() = default;
	move_t(int from, int to);
	move_t(int from, int to, int promo);

	int from() const;
	int to() const;
	int promo() const;

	bool operator==(const move_t& other)
	{
		return move == other.move;
	}

	bool operator!=(const move_t& other)
	{
		return move != other.move;
	}

private:
	uint16_t move;
};

std::ostream& operator<<(std::ostream& os, move_t move);
std::istream& operator>>(std::istream& is, move_t& move);
