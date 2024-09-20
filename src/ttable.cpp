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
	size_t size = (1024 * 1024 * mb) / sizeof(bucket_t);

	if (size > table.size())
		table.resize(size);
	else
		table = std::vector<bucket_t>(size);
}

size_t ttable_t::index(uint64_t hash) const
{
	return hash % table.size();
}

void ttable_t::clear()
{
	for (auto& b : table)
		b = {};
}

slot_t ttable_t::get(uint64_t hash) const
{
    const bucket_t& b = table[index(hash)];

    for (const auto& s : b) {
        if (s.hash == hash)
            return s;
    }
    return {};
}

void ttable_t::store(uint64_t hash, int score, move_t move, int depth, int bound)
{
    bucket_t& b = table[index(hash)];

    for (auto& s : b) {
        if (s.hash == hash || s.seen == 3 || s.depth < depth) {
            s = { hash, score, move, uint8_t(depth), uint8_t(bound), 0};
            break;
        }

        s.seen = (s.seen + 1) & 63;
    }
}
