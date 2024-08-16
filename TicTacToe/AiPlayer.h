#pragma once
#include "Board.h"
#include "AiStrategy.h"

namespace TICTACTOE
{
	class AiPlayer : public Player
	{
	private:
		Symbol symbol_;
		std::unique_ptr<AiStrategy> move_strategy_;

	public:
		AiPlayer(std::unique_ptr<AiStrategy> strategy, const Symbol& symbol) : symbol_(symbol),
		                                                                       move_strategy_(std::move(strategy))
		{
		}

		~AiPlayer() override = default;
		IntPair MakeMove(Board& board) override;
		Symbol GetSymbol() override { return symbol_; }
	};

	inline IntPair AiPlayer::MakeMove(Board& board)
	{
		return move_strategy_->GetBestMove(board);
	}
}
