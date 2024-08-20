#pragma once

#include <memory>
#include <random>

#include "Board.h"
#include "AiStrategy.h"

namespace TICTACTOE
{
	constexpr int Simulation_count = 3000;

	struct TreeNode : public std::enable_shared_from_this<TreeNode>
	{
		TreeNode(Board board, std::shared_ptr<TreeNode> parent = nullptr, IntPair move = {-1, -1},
		         Symbol current_player =
			         Cross) : board_(board), parent_(parent),
			                  move_(move), wins_(0.0), visits_(0), current_player_(current_player)
		{
		}

		bool IsFullyExpanded() const;
		std::shared_ptr<TreeNode> GetChildForMove(IntPair move) const;
		std::shared_ptr<TreeNode> AddChild(IntPair move);
		static Symbol GetOtherSymbol(Symbol symbol);
		Board board_;
		std::weak_ptr<TreeNode> parent_;
		IntPair move_;
		std::vector<std::shared_ptr<TreeNode>> children_;
		double wins_;
		int visits_;
		Symbol current_player_;
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
		std::shared_ptr<TreeNode> root_;

		Symbol current_player_;


		static double UctValue(int totalVisits, int nodeVisits, double nodeWins);

		static Symbol GetOtherSymbol(Symbol symbol);

		std::shared_ptr<TreeNode> Select(std::shared_ptr<TreeNode> node);
		std::shared_ptr<TreeNode> Expand(std::shared_ptr<TreeNode> node);
		double Simulate(Board board) const;
		static void BackPropagate(std::shared_ptr<TreeNode>, double result);
	};
}
