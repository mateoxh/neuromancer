#pragma once

#include <vector>
#include <chrono>
#include <limits>
#include <atomic>
#include "board.h"
#include "ttable.h"
#include "history.h"

constexpr int max_ply = 256;
constexpr int mate = std::numeric_limits<int>::max();
constexpr int min_mate = mate - max_ply;

using pv_t = std::vector<move_t>;
using tc_t = std::chrono::high_resolution_clock;

struct info_t {
	tc_t::time_point start;
	move_t prev_best;
	int64_t nodes;

	void reset();
	void report(const pv_t& pv, int depth, int score);
};

class searcher_t {
	std::atomic<bool> stop;
	tc_t::time_point max_time;
	int max_depth;
	bool infinite;

	ttable_t tt;
	history_t history;

	std::vector<uint64_t> game_history;

public:
	void reset();
	void prepare(long msec, int depth);
	void request_stop();
	bool should_stop(int64_t nodes);
	void set_hash(size_t mb);

	int negamax(board_t& board, info_t& info, pv_t& pv, int alpha, int beta, int depth, int ply, bool do_null);
	int quiesce(board_t& board, info_t& info, int alpha, int beta);
	void think(board_t& board);

	void update_game_history(const board_t& board);
	bool is_repetition(uint64_t hash) const;
};
