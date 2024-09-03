#pragma once

#include <vector>
#include <cstdint>
#include "move.h"

constexpr int lower_bound = 0;
constexpr int exact_bound = 1;
constexpr int upper_bound = 2;

struct slot_t {
	uint64_t hash;
	int32_t score;
	move_t move;
	uint8_t depth;
	uint8_t bound;
};

class ttable_t {
	std::vector<slot_t> table;

public:
	ttable_t();
	ttable_t(size_t mb);

	size_t index(uint64_t hash) const;

	void resize(size_t mb);
	void clear();
	void store(uint64_t hash, int score, move_t move, int depth, int bound);
	slot_t& get(uint64_t hash);
};
