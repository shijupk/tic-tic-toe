#include "MiniMaxStrategy.h"
using namespace TICTACTOE;

IntPair MiniMaxStrategy::GetBestMove(Board& board)
{
	int bestVal = std::numeric_limits<int>::min();
	IntPair bestMove = {-1, -1};

	for (const auto& move : board.GetAvailableMoves())
	{
		board.PlaceSymbol(move, current_player_);
		const int moveVal = MiniMax(board, 0, false, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
		board.UndoMove(move);

		if (moveVal > bestVal)
		{
			bestMove = move;
			bestVal = moveVal;
		}
	}

	return bestMove;
}

Symbol MiniMaxStrategy::GetOtherSymbol(const Symbol symbol)
{
	return symbol == Symbol::Cross ? Symbol::Oh : Symbol::Cross;
}

int MiniMaxStrategy::MiniMax(Board& board, const int depth, const bool isMaximizingPlayer, int alpha, int beta)
{
	if (board.CheckWinner(current_player_)) return 10 - depth;
	if (board.CheckWinner(GetOtherSymbol(current_player_))) return depth - 10;
	if (board.IsFull()) return 0;

	if (isMaximizingPlayer)
	{
		int maxEval = std::numeric_limits<int>::min();
		for (const auto& move : board.GetAvailableMoves())
		{
			board.PlaceSymbol(move, current_player_);
			int eval = MiniMax(board, depth + 1, false, alpha, beta);
			board.UndoMove(move);
			maxEval = std::max(maxEval, eval);
			alpha = std::max(alpha, eval);
			if (beta <= alpha)
			{
				break;
			}
		}
		return maxEval;
	}
	else
	{
		int minEval = std::numeric_limits<int>::max();
		for (const auto& move : board.GetAvailableMoves())
		{
			auto otherSymbol = GetOtherSymbol(current_player_);
			board.PlaceSymbol(move, otherSymbol);
			int eval = MiniMax(board, depth + 1, true, alpha, beta);
			board.UndoMove(move);
			minEval = std::min(minEval, eval);
			beta = std::min(beta, eval);
			if (beta <= alpha)
			{
				break;
			}
		}
		return minEval;
	}
}
