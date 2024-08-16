#pragma once

#include <vector>
#include "common.h"


namespace TICTACTOE
{
	class Board
	{
	private:
		std::vector<std::vector<Symbol>> grid_;

	public:
		Board();
		~Board() = default;

		bool IsValidMove(const IntPair& position) const;
		bool IsFull() const;
		bool PlaceSymbol(const IntPair& position, const Symbol& symbol);
		bool CheckWinner(const Symbol& symbol) const;
		Symbol CheckWinner() const;
		void Display() const;
		std::vector<IntPair> GetAvailableMoves() const;
		void UndoMove(const IntPair& position);
		Board Clone() const;
	};
}
