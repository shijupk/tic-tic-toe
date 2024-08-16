#pragma once
#include "Board.h"
#include "AiStrategy.h"

namespace TICTACTOE
{
	constexpr int Simulation_count = 1000;

	struct Node
	{
		Node(Board board, Node* parent = nullptr, IntPair move = {-1, -1}) : board_(board), parent_(parent),
		                                                                     move_(move), wins_(0), visits_(0)
		{
		}

		bool IsFullyExpanded() const;
		Node* BestChild() const;

		Board board_;
		Node* parent_;
		IntPair move_;
		std::vector<Node*> children_;
		int wins_;
		int visits_;
	};


	class MonteCarloStrategy : public AiStrategy
	{
	public:
		MonteCarloStrategy(const Symbol symbol) : current_player_(symbol)
		{
		}

		~MonteCarloStrategy() override = default;
		IntPair GetBestMove(Board& board) override;

	private:
		Symbol current_player_;
		static Symbol GetOtherSymbol(const Symbol symbol);

		Node* Select(Node* node);
		Node* Expand(Node* node);
		int Simulate(Board board) const;
		static void BackPropagate(Node* node, int result);
	};
}
