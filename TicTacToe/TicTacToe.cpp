// TicTacToe.cpp : Defines the entry point for the application.
//

#include "TicTacToe.h"

using namespace std;
using namespace TICTACTOE;

int main()
{
	auto player_1 = std::make_unique<AiPlayer>(std::make_unique<MiniMaxStrategy>(Symbol::Oh), Symbol::Oh);
	auto player_2 = std::make_unique<HumanPlayer>(Symbol::Cross);
	Game game(std::move(player_1), std::move(player_2));
	game.Play();

	return 0;
}
