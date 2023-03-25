#pragma once

#include <vector>
#include "move.h"
#include "board.h"

class scored_move_t : public move_t {
public:
	using move_t::move_t;

	void set_score(int new_score)
	{
		score = new_score;
	}

	bool operator<(const scored_move_t& other) const
	{
		return score < other.score;
	}

private:
	int score;
};

using movelist_t = std::vector<scored_move_t>;

movelist_t generate_all(const board_t& board);
movelist_t generate_noisy(const board_t& board);
