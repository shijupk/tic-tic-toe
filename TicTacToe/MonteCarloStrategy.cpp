#include <cmath>
#include <limits>
#include <cstdlib>

#include "Board.h"
#include "common.h"
#include "MonteCarloStrategy.h"
using namespace TICTACTOE;


bool TreeNode::IsFullyExpanded() const
{
	return children_.size() == board_.GetAvailableMoves().size();
}

std::shared_ptr<TreeNode> TreeNode::GetChildForMove(const IntPair move) const
{
	for (const auto& child : children_)
	{
		if (child->move_ == move)
		{
			return child;
		}
	}
	return nullptr;
}

std::shared_ptr<TreeNode> TreeNode::AddChild(IntPair move)
{
	Board newBoard = board_;
	newBoard.PlaceSymbol(move, current_player_);
	auto child = make_shared<TreeNode>(newBoard, shared_from_this(), move, GetOtherSymbol(Cross));
	children_.push_back(child);
	return child;
}

Symbol TreeNode::GetOtherSymbol(const Symbol symbol)
{
	return symbol == Cross ? Oh : Cross;
}


double MonteCarloStrategy::UctValue(const int totalVisits, const int nodeVisits, const double nodeWins)
{
	if (nodeVisits == 0)
		return std::numeric_limits<double>::infinity();

	return (nodeWins / nodeVisits) + sqrt(2 * log(totalVisits) / nodeVisits);
}

Symbol MonteCarloStrategy::GetOtherSymbol(const Symbol symbol)
{
	return symbol == Cross ? Oh : Cross;
}

std::shared_ptr<TreeNode> MonteCarloStrategy::Select(std::shared_ptr<TreeNode> node)
{
	while (!node->board_.IsFull() && node->board_.CheckWinner() == Empty)
	{
		if (node->IsFullyExpanded())
		{
			std::shared_ptr<TreeNode> bestChild = nullptr;
			double bestValue = std::numeric_limits<double>::min();
			for (const auto& child : node->children_)
			{
				if (const double value = UctValue(node->visits_, child->visits_, child->wins_); value > bestValue)
				{
					bestValue = value;
					bestChild = child;
				}
			}
			node = bestChild;
		}
		else
		{
			return Expand(node);
		}
	}
	return node;
}

std::shared_ptr<TreeNode> MonteCarloStrategy::Expand(std::shared_ptr<TreeNode> node)
{
	const auto availableMoves = node->board_.GetAvailableMoves();
	for (const auto& move : availableMoves)
	{
		if (node->GetChildForMove(move) == nullptr)
		{
			return node->AddChild(move);
		}
	}
	return nullptr;
}


double MonteCarloStrategy::Simulate(Board board) const
{
	std::random_device rd; // a seed source for the random number engine
	std::mt19937 gen(rd());

	auto currentPlayer = current_player_;
	while (!board.IsFull() && board.CheckWinner() == Empty)
	{
		auto availableMoves = board.GetAvailableMoves();
		std::uniform_int_distribution<> dist(0, static_cast<int>(availableMoves.size() - 1));

		auto randomMove = availableMoves[dist(gen)];
		board.PlaceSymbol(randomMove, currentPlayer);
		currentPlayer = GetOtherSymbol(currentPlayer);
	}
	const auto winner = board.CheckWinner();
	if (winner == Cross) return 1.0;
	if (winner == Oh) return 0.0;
	return 0.5; // Draw
}

void MonteCarloStrategy::BackPropagate(std::shared_ptr<TreeNode> node, double result)
{
	while (node)
	{
		node->visits_++;
		node->wins_ += result;
		node = node->parent_.lock(); // Convert weak_ptr to shared_ptr
	}
}


IntPair MonteCarloStrategy::GetBestMove(Board& board)
{
	root_ = std::make_shared<TreeNode>(board);

	for (int i = 0; i < Simulation_count; ++i)
	{
		const auto selectedNode = Select(root_);
		const double result = Simulate(selectedNode->board_);
		BackPropagate(selectedNode, result);
	}

	std::shared_ptr<TreeNode> bestChild = nullptr;
	double bestWinRatio = std::numeric_limits<double>::min();
	for (const auto& child : root_->children_)
	{
		if (const double winRatio = child->wins_ / child->visits_; winRatio > bestWinRatio)
		{
			bestWinRatio = winRatio;
			bestChild = child;
		}
	}
	return bestChild ? bestChild->move_ : std::make_pair(-1, -1);
}
