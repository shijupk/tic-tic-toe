#pragma once

namespace TICTACTOE
{
	constexpr unsigned int Board_size = 3;
	using Uint = unsigned int;
	using IntPair = std::pair<int, int>;

	enum Symbol
	{
		Empty = 0,
		Oh,
		Cross
	};

	static constexpr char SymbolLut[3] = {'_', 'O', 'X'};
}
