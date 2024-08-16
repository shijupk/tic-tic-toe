#include "iostream"
#include "Board.h"

using namespace TICTACTOE;


Board::Board() : grid_(Board_size, std::vector<Symbol>(Board_size, Empty))
{
}

inline bool Board::IsValidMove(const IntPair& position) const
{
	return (grid_[position.first][position.second] == Empty);
}

std::vector<IntPair> Board::GetAvailableMoves() const
{
	std::vector<IntPair> moves;
	moves.reserve(Board_size * Board_size);

	for (Uint row = 0; row < Board_size; ++row)
	{
		for (Uint column = 0; column < Board_size; ++column)
		{
			if (grid_[row][column] == Symbol::Empty)
			{
				moves.emplace_back(row, column);
			}
		}
	}
	return moves;
}

void Board::UndoMove(const IntPair& position)
{
	grid_[position.first][position.second] = Symbol::Empty;
}

Board Board::Clone() const
{
	return *this;
}

bool Board::IsFull() const
{
	for (auto rows : grid_)
	{
		if (std::ranges::find(rows, Empty) != rows.end())
			return false;
	}

	return true;
}

bool Board::PlaceSymbol(const IntPair& position, const Symbol& symbol)
{
	if (!IsValidMove(position))
		return false;

	grid_[position.first][position.second] = symbol;
	return true;
}

Symbol Board::CheckWinner() const
{
	// Check rows, columns, and diagonals
	for (int i = 0; i < Board_size; ++i)
	{
		if (grid_[i][0] == grid_[i][1] && grid_[i][1] == grid_[i][2] && grid_[i][0] != Symbol::Empty)
		{
			return grid_[i][0];
		}
		if (grid_[0][i] == grid_[1][i] && grid_[1][i] == grid_[2][i] && grid_[0][i] != Symbol::Empty)
		{
			return grid_[0][i];
		}
	}
	if (grid_[0][0] == grid_[1][1] && grid_[1][1] == grid_[2][2] && grid_[0][0] != Symbol::Empty)
	{
		return grid_[0][0];
	}
	if (grid_[0][2] == grid_[1][1] && grid_[1][1] == grid_[2][0] && grid_[0][2] != Symbol::Empty)
	{
		return grid_[0][2];
	}
	return Symbol::Empty;
}


bool Board::CheckWinner(const Symbol& symbol) const
{
	bool mainDiagonalWin = true;
	bool antiDiagonalWin = true;

	for (Uint row = 0; row < Board_size; ++row)
	{
		bool rowWin = true;
		bool colWin = true;

		for (Uint col = 0; col < Board_size; ++col)
		{
			if (grid_[row][col] != symbol)
			{
				rowWin = false;
			}
			if (grid_[col][row] != symbol)
			{
				colWin = false;
			}
		}

		// If any row or column wins, return true immediately
		if (rowWin || colWin) return true;

		// Check main diagonal and anti-diagonal
		if (row < Board_size)
		{
			if (grid_[row][row] != symbol)
			{
				mainDiagonalWin = false;
			}
			if (grid_[row][Board_size - row - 1] != symbol)
			{
				antiDiagonalWin = false;
			}
		}
	}

	// Check if either diagonal wins
	return (mainDiagonalWin || antiDiagonalWin);
}


void Board::Display() const
{
	std::cout << "\n\n";
	for (Uint row = 0; row < Board_size; row++)
	{
		for (Uint col = 0; col < Board_size; col++)
		{
			std::cout << " " << SymbolLut[grid_[row][col]] << " ";
			if (col < Board_size - 1)
				std::cout << "|";
		}

		std::cout << "\n";
		if (row < Board_size - 1)
			std::cout << "-----------" << "\n";
	}
}
