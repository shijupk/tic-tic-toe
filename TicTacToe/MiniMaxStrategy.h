#pragma once

#include "Board.h"
#include "AiStrategy.h"

namespace TICTACTOE
{
	class MiniMaxStrategy : public AiStrategy
	{
	public:
		MiniMaxStrategy(const Symbol symbol) : current_player_(symbol)
		{
		}

		~MiniMaxStrategy() override = default;
		IntPair GetBestMove(Board& board) override;

	private:
		Symbol current_player_;
		int MiniMax(Board& board, int depth, bool isMaximizingPlayer, int alpha, int beta);
		static Symbol GetOtherSymbol(const Symbol symbol);
	};
}
