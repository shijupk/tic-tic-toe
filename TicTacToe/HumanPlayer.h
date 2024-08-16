#pragma once

#include "Player.h"

namespace TICTACTOE
{
	class HumanPlayer : public Player
	{
	private:
		Symbol symbol_;

	public:
		explicit HumanPlayer(const Symbol symbol);
		~HumanPlayer() override = default;

		IntPair MakeMove(Board& board) override;
		Symbol GetSymbol() override { return symbol_; }
	};

	inline HumanPlayer::HumanPlayer(const Symbol symbol) : symbol_(symbol)
	{
	}

	inline IntPair HumanPlayer::MakeMove(Board& board)
	{
		Uint row, col;
		std::cin >> row >> col;
		return {row, col};
	}
}
