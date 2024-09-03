#pragma once

#include <sstream>
#include "board.h"
#include "search.h"

class engine_t {
	board_t board;
	searcher_t searcher;

	void uci();
	void isready();
	void ucinewgame();
	void position(std::stringstream& ss);
	void perft(std::stringstream& ss);
	void go(std::stringstream& ss);
	void setoption(std::stringstream& ss);

public:
	engine_t();
	void start();
};
