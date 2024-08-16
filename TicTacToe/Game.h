#pragma once
#include <memory>

#include "Board.h"
#include "Player.h"

namespace TICTACTOE
{
	using PlayerRef = std::unique_ptr<Player>;

	class Game
	{
	public:
		Game(PlayerRef player_1, PlayerRef player_2) : board_(), first_player_(std::move(player_1)),
		                                               second_player_(std::move(player_2))
		{
		}

		void Play();

	private:
		Board board_;
		PlayerRef first_player_;
		PlayerRef second_player_;

		void SwitchPlayer();
	};

	inline void Game::SwitchPlayer()
	{
		std::swap(first_player_, second_player_);
	}

	inline void Game::Play()
	{
		while (true)
		{
			board_.Display();
			std::cout << "\n";

			std::cout << "Player " << SymbolLut[first_player_->GetSymbol()] << ", enter your move (Row, Column): ";
			if (auto position = first_player_->MakeMove(board_); !board_.PlaceSymbol(
				position, first_player_->GetSymbol()))
			{
				std::cout << "Invalid move. Try Again\n";
				continue;
			}

			if (board_.CheckWinner(first_player_->GetSymbol()))
			{
				board_.Display();
				std::cout << "Player " << SymbolLut[first_player_->GetSymbol()] << " wins!\n";
				break;
			}

			if (board_.IsFull())
			{
				board_.Display();
				std::cout << "It's a draw!\n";
				break;
			}

			SwitchPlayer();
			std::cout << "\n";
		}
	}
}
