# CSE Tic-Tac-Toe with Minimax AI

This is a two-player strategy game implemented in Java, where a human player competes against an AI using the Minimax algorithm. The game is played on a 3x3 grid with three letters: C, S, and E.

**Game Rules:**

* Players take turns placing one of the letters (C, S, or E) in an empty cell.
* The game starts with an S already placed in the middle row (either left or right position).
* A player wins if they form one of the winning sequences:
  * "CSE" or "ESC"
  * The sequence can be formed horizontally, vertically, or diagonally.
 
* The game ends when:
  * A winning sequence is created (one player wins).
  * The grid is full with no winning sequence (draw).

**AI Implementation:**

The AI (MAX player) always plays optimally using the Minimax algorithm.
The Minimax function is implemented recursively, evaluating all possible moves to determine the best strategy.
The AI chooses the move that maximizes its chances of winning while minimizing the opponent’s chances.

This project demonstrates artificial intelligence decision-making using Minimax and recursion.
