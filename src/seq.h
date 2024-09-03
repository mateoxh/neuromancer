#pragma once

#include "board.h"
#include "gen.h"
#include "history.h"

class sequencer_t {
	movelist_t moves;
	movelist_t::iterator it;

public:
	sequencer_t(const board_t& board, move_t pv_move, const history_t& history);
	sequencer_t(const board_t& board);

	bool operator>>(move_t& move);
};
