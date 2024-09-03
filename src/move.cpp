#include "move.h"
#include "util.h"

std::ostream& operator<<(std::ostream& os, move_t move)
{
	os << square_to_string(move.from());
	os << square_to_string(move.to());

	if (const int promo = move.promo())
		os << piece_to_ascii(promo);

	return os;
}

std::istream& operator>>(std::istream& is, move_t& move)
{
	int from, to, promo;
	std::string token;

	if (is >> token) {
		from = string_to_square(token.substr(0, 2));
		to = string_to_square(token.substr(2, 2));

		if (token.size() > 4)
			promo = ascii_to_piece(token[4]);
		else
			promo = 0;

		move = { from, to, promo };
	}

	return is;
}
