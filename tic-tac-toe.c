#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

void printBoard(char board[3][3]) {
    printf("  | 1 | 2 | 3 |\n");
    printf("%c |", 'A');
    for (int j = 0; j < 3; j++) {
        printf(" %c |", board[0][j]);
    }
    printf("\n");
    for (int i = 1; i < 3; i++) {
        printf("%c |", 'A' + i);
        for (int j = 0; j < 3; j++) {
            printf(" %c |", board[i][j]);
        }
        printf("\n");
    }
}

//Check for win or draw
bool checkWin(char board[3][3], char player) {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == 'C' && board[i][1] == 'S' && board[i][2] == 'E') ||
            (board[i][0] == 'E' && board[i][1] == 'S' && board[i][2] == 'C') ||
            (board[0][i] == 'C' && board[1][i] == 'S' && board[2][i] == 'E') ||
            (board[0][i] == 'E' && board[1][i] == 'S' && board[2][i] == 'C')) {
            return true;
        }
    }

    if ((board[0][0] == 'C' && board[1][1] == 'S' && board[2][2] == 'E') ||
        (board[0][0] == 'E' && board[1][1] == 'S' && board[2][2] == 'C') ||
        (board[0][2] == 'C' && board[1][1] == 'S' && board[2][0] == 'E') ||
        (board[0][2] == 'E' && board[1][1] == 'S' && board[2][0] == 'C')) {
        return true;
    }
    return false;
}
bool checkDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// Minimax
int minimax(char board[3][3], int depth, bool isMax) {
    // Check if the game has ended
    if (checkWin(board, '1')) return 1; // Player 1 wins (MAX)
    if (checkWin(board, '2')) return -1; // Player 2 wins (Human)
    if (checkDraw(board)) return 0; // Draw

		char currentPlayer;
	if (isMax) {
		currentPlayer = '1';
	} else {
		currentPlayer = '2';
	}

		int bestVal;
	if (isMax) {
		bestVal = -1000;
	} else {
		bestVal = 1000;
	}

    // Iterate through all empty cells
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                // Make the move for the current player
                board[i][j] = currentPlayer;
                // Recursively call minimax with the opposite player's turn
                int val = minimax(board, depth + 1, !isMax);
                // Undo the move
                board[i][j] = ' ';
                // Update bestVal based on the current player
                if ((isMax && val > bestVal) || (!isMax && val < bestVal)) {
                    bestVal = val;
                }
            }
        }
    }
    return bestVal;
}



int main() {
    char board[3][3];
    char currentPlayerLetter;
    char currentPlayer;
    int row, col;

    // Initialize the board with empty spaces
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }

    // 'S' on B1 or B3
    srand(time(NULL));
		int sCol;
	if (rand() % 2 == 0) {
		sCol = 0;
	} else {
		sCol = 2;
	}

    board[1][sCol] = 'S';

    printf("\nInitial board:\n");
    printBoard(board);

    // Main game loop
	
    for (int turn = 1; turn <= 9; turn++) {
		if (turn % 2 == 1) {
			currentPlayer = '1';
		} else {
			currentPlayer = '2';
		}

        if (currentPlayer == '1') {
            printf("\nMAX's turn\n");
        } else {
            printf("\nHuman's turn\n");
        }

        if (currentPlayer == '1') {
            // Minimax for MAX's move
            int bestMove = -1;
            int bestVal = -1000;
            // Search empty cells to find the best move
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    if (board[i][j] == ' ') {
                        for (char letter = 'C'; letter <= 'E'; letter++) {
                            // Make the move
                            board[i][j] = letter;
                            // Calculate minimax value for this move
                            int moveVal = minimax(board, 0, false);
                            // Undo the move
                            board[i][j] = ' ';
                            // Update bestVal if this move is better
                            if (moveVal > bestVal) {
                                bestVal = moveVal;
                                bestMove = i * 3 + j;
                                currentPlayerLetter = letter;
                            }
                        }
                    }
                }
            }
            // Convert bestMove to row and col
            row = bestMove / 3;
            col = bestMove % 3;

        } else {
            printf("Choose your letter (C, S, or E): ");
            scanf(" %c", &currentPlayerLetter);

            currentPlayerLetter = toupper(currentPlayerLetter);

            while (currentPlayerLetter != 'C' && currentPlayerLetter != 'S' && currentPlayerLetter != 'E') {
                printf("Invalid input! Please choose 'C', 'S', or 'E': ");
                scanf(" %c", &currentPlayerLetter);
                currentPlayerLetter = toupper(currentPlayerLetter);
            }

            printf("Enter row (A, B, C) and column (1, 2, 3) to place your letter: ");
            char move[2];
            scanf("%s", move);
            row = toupper(move[0]) - 'A';
            col = move[1] - '1';

            if (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ') {
                printf("Invalid move! Please choose an empty position.\n");
                turn--;
				
                continue;
            }
        }

        // Place player's letter on the board
        board[row][col] = currentPlayerLetter;

			printf("\nCurrent board after ");
	if (currentPlayer == '1' || currentPlayer == '0') {
		printf("MAX's");
	} else {
		printf("Human's");
	}
	printf(" move:\n");

        printBoard(board);

        if (checkWin(board, currentPlayer)) {
            if (currentPlayer == '1') {
                printf("\nMAX wins!\n");
				
            } else {
				
                printf("\nHuman wins!\n");
            }
            break;
			
        } else if (checkDraw(board)) {
            printf("\nThe game is a draw!\n");
            break;
        }
    }
    return 0;
}
