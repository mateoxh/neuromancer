#include "ttable.h"

ttable_t::ttable_t(size_t mb)
{
    static_assert(sizeof(slot_t) == 16);

	resize(mb);
	clear();
}

ttable_t::ttable_t()
	: ttable_t(128)
{
}

void ttable_t::resize(size_t mb)
{
	size_t size = (1024 * 1024 * mb) / sizeof(slot_t);

	if (size > table.size())
		table.resize(size);
	else
		table = std::vector<slot_t>(size);
}

size_t ttable_t::index(uint64_t hash) const
{
	return hash % table.size();
}

void ttable_t::clear()
{
	for (auto& s : table)
		s = {};
}

slot_t& ttable_t::get(uint64_t hash)
{
	return table[index(hash)];
}

void ttable_t::store(uint64_t hash, int score, move_t move, int depth, int bound)
{
	get(hash) = { hash, score, move, uint8_t(depth), uint8_t(bound) };
}
