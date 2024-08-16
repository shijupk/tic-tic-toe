# CMakeList.txt : CMake project for TicTacToe, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (TicTacToe "TicTacToe.cpp" "TicTacToe.h" "Board.cpp" "Player.h" "common.h" "HumanPlayer.h" "Game.h" "AiPlayer.h" "AiStrategy.h" "MiniMaxStrategy.h" "MiniMaxStrategy.cpp" "MonteCarloStrategy.h"   "MonteCarloStrategy.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET TicTacToe PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
