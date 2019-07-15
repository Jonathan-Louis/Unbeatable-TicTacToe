// TicTacToe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>

using namespace std;

char board[3][3];
int computerX, computerY;


char winCheck();
void createBoard();
void playerMove();
void computerMove(int turn);
void printBoard();
int minimaxAlgorithm(int currentTurn);

int main()
{

	bool playAgain = true;
	char again = 'Y';


	while (playAgain) {
		char winner = ' ';
		int turn = 0;
		cout << "Welcome to Tic Tac Toe.\n";
		cout << "Player is 'X' and computer is 'O'\nPlayer goes first.\n\n";

		createBoard();

		//controls game until winner found or draw found
		while (1) {
			printBoard();

			//player move
			playerMove();
			winner = winCheck();

			if (winner != ' ') {
				break;
			}

			//compter move
			computerMove(turn);
			winner = winCheck();

			if (winner != ' ') {
				break;
			}

			turn++;
		}

		printBoard();

		cout << endl << endl;

		if (winner == 'X') {
			cout << "Player Wins!\n";
		}

		if (winner == 'O') {
			cout << "Computer Wins!\n";
		}

		if (winner == 'C') {
			cout << "Game is a draw.\n";
		}

		cout << "Would you like to play again(Y for yes or N for no)?\n";

		cin >> again;

		if ((again == 'N') | (again == 'n')) {
			playAgain = false;
		}
	}

	return 0;
}

//creating the initial board spaces
void createBoard() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = ' ';
		}
	}
}

//prints the board
void printBoard() {

	cout << "\n  1 2 3 \n\n";

	for (int i = 0; i < 3; i++) {

		cout << i + 1 << " ";

		for (int j = 0; j < 3; j++) {

			cout << board[i][j];

			if (j < 2) {
				cout << "|";
			}
		}
		cout << endl;

		if (i < 2) {
			cout << "  - - -\n";
		}
	}
}

//player move class, move entered as coordinates
void playerMove() {
	int playerX, playerY;

	cout << "\nEnter row number: \n";
	cin >> playerX;

	cout << "Enter column number: \n";
	cin >> playerY;

	//checks if valid move
	if (board[playerX - 1][playerY - 1] != ' ') {
		cout << "Invalid Selection.\n\n";
		playerMove();
	}
	else {
		board[playerX - 1][playerY - 1] = 'X';
	}
}

int minimaxAlgorithm(int currentTurn) {
	int move[2] = { -1, -1 };
	int score = -20;

	//changing between computer and player symbols for the board
	currentTurn = -currentTurn;

	char currentMark;
	char winner;

	//base case for score
	winner = winCheck();

	if (winner == 'X') {
		return -10;
	}
	else if (winner == 'O') {
		return 10;
	}
	else if ((winner == 'C')) {
		return 0;
	}


	//  1 = player
	//  -1 = computer
	if (currentTurn == 1) {
		currentMark = 'X';
	}
	else {
		currentMark = 'O';
	}

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			if (board[i][j] == ' ') {
				board[i][j] = currentMark;

				int moveScore = minimaxAlgorithm(currentTurn);

				//on computer turn looking for the heighest score
				if (currentTurn == 1) {
					if (moveScore > score) {
						score = moveScore;
						move[0] = i;
						move[1] = j;
					}
				}
				//on players simulated turn looking for the lowest score
				else {
					score = -score;
					if (moveScore < score) {
						score = moveScore;
						move[0] = i;
						move[1] = j;
					}
				}

				board[i][j] = ' ';
			}



		}
	}


	if ((move[0] == -1) | (move[1] == -1)) {
		return 0;
	}
	else {
		computerX = move[0];
		computerY = move[1];
		return -1;
	}
}

//computer move class
void computerMove(int turn) {

	srand(time(0));

	computerX = rand() % 3;
	computerY = rand() % 3;

	//sets computer to take middle if open after players first move
	if (board[1][1] == ' ') {
		board[1][1] = 'O';
	}

	//if player took middle space on turn 1 then computer set to take a corner
	else if ((board[1][1] == 'X') & (turn == 1)) {
		if ((computerX == 0) | (computerX == 2)) {}
		else {
			computerX = 0;
		}

		if ((computerY == 0) | (computerY == 2)) {}
		else {
			computerY = 2;
		}

		board[computerX][computerY] = 'O';
	}

	//after first turn minimax algorithm used to find computers next move location
	else {

		//calling minimaxAlgorithm with computer taking first turn
		minimaxAlgorithm(-1);

		board[computerX][computerY] = 'O';

	}

}

//class to check for winner
char winCheck() {
	char winner = ' ';

	//check rows for winner
	for (int i = 0; i < 3; i++) {
		if (board[i][0] != ' ') {
			if ((board[i][0] == board[i][1]) & (board[i][1] == board[i][2])) {
				winner = board[i][0];
			}
		}
	}

	//check columns for winner
	for (int i = 0; i < 3; i++) {
		if (board[0][i] != ' ') {
			if ((board[0][i] == board[1][i]) & (board[1][i] == board[2][i])) {
				winner = board[0][i];
			}
		}
	}

	//check diagonals
	if (((board[0][0] == board[1][1]) & (board[1][1] == board[2][2])) & (board[0][0] != ' ')) {
		winner = board[1][1];
	}
	if (((board[0][2] == board[1][1]) & (board[1][1] == board[2][0])) & (board[0][2] != ' ')) {
		winner = board[1][1];
	}

	//check for cat game 
	// checks if all spaces have been occupied, if not play continues
	int count = 0;
	if (winner == ' ') {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (board[i][j] != ' ') {
					count++;
				}
			}
		}
	}

	if (count == 9) {
		winner = 'C';
	}

	return winner;
}