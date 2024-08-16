#pragma once

#include "Common.h"

namespace TICTACTOE
{
	class AiStrategy
	{
	public:
		virtual ~AiStrategy() = default;
		virtual IntPair GetBestMove(Board& board) = 0;
	};
}
