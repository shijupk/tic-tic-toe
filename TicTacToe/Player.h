#pragma once

#include "Board.h"

namespace TICTACTOE
{
	class Player
	{
	public:
		virtual ~Player() = default;
		virtual IntPair MakeMove(Board& board) = 0;
		virtual Symbol GetSymbol() = 0;
	};
}
