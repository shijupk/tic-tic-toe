#include <cmath>
#include <limits>
#include <cstdlib>
#include <ctime>

#include "Board.h"
#include "common.h"
#include "MonteCarloStrategy.h"
using namespace TICTACTOE;


bool Node::IsFullyExpanded() const
{
	return children_.size() == board_.GetAvailableMoves().size();
}

Node* Node::BestChild() const
{
	Node* best = nullptr;
	double bestValue = -std::numeric_limits<double>::infinity();
	for (Node* child : children_)
	{
		const double uctValue = static_cast<double>(child->wins_) / (child->visits_ + 1)
			+ sqrt(2 * log(visits_ + 1) / (child->visits_ + 1));
		if (uctValue > bestValue)
		{
			bestValue = uctValue;
			best = child;
		}
	}
	return best;
}


Symbol MonteCarloStrategy::GetOtherSymbol(const Symbol symbol)
{
	return symbol == Symbol::Cross ? Symbol::Oh : Symbol::Cross;
}

Node* MonteCarloStrategy::Select(Node* node)
{
	while (node->board_.CheckWinner() == Symbol::Empty && !node->board_.IsFull())
	{
		if (!node->IsFullyExpanded())
		{
			return Expand(node);
		}
		else
		{
			node = node->BestChild();
		}
	}
	return node;
}

Node* MonteCarloStrategy::Expand(Node* node)
{
	for (const auto availableMoves = node->board_.GetAvailableMoves(); const auto& move : availableMoves)
	{
		bool found = false;
		for (const auto& child : node->children_)
		{
			if (child->move_ == move)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			Board newBoard = node->board_.Clone();
			newBoard.PlaceSymbol(move, current_player_);
			const auto childNode = new Node(newBoard, node, move);
			node->children_.push_back(childNode);
			return childNode;
		}
	}
	return nullptr; // This should never happen
}

int MonteCarloStrategy::Simulate(Board board) const
{
	auto currentPlayer = current_player_;
	while (board.CheckWinner() == Symbol::Empty && !board.IsFull())
	{
		auto availableMoves = board.GetAvailableMoves();
		std::pair<int, int> randomMove = availableMoves[std::rand() % availableMoves.size()];
		board.PlaceSymbol(randomMove, currentPlayer);
 		currentPlayer = GetOtherSymbol(currentPlayer);
	}

	if (board.CheckWinner(current_player_)) return 1;
	if (board.CheckWinner(GetOtherSymbol(current_player_))) return -1;
	return 0;
}

void MonteCarloStrategy::BackPropagate(Node* node, const int result)
{
	while (node != nullptr)
	{
		node->visits_++;
		node->wins_ += result;
		node = node->parent_;
	}
}

IntPair MonteCarloStrategy::GetBestMove(Board& board)
{
	const auto root = new Node(board);
	srand(static_cast<unsigned>(time(nullptr)));

	for (int i = 0; i < Simulation_count; ++i)
	{
		Node* node = Select(root);
		const int result = Simulate(node->board_);
		BackPropagate(node, result);
	}

	const Node* bestChild = root->BestChild();
	const auto bestMove =  bestChild ? bestChild->move_ : std::make_pair(-1, -1);

	// Cleanup
	delete root;

	return bestMove;
}
