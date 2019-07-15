//Author: Jonathan Louis
//Unbeatable AI for TicTacToe


#include <iostream>
#include <time.h>
#include <vector>

using namespace std;

//global variables
char board[3][3];
int computerX, computerY;


//structure to save simulated moves
struct Move {
	Move() {};
	Move(int Score) : score(Score) {};
	int x;
	int y;
	int score;
};


char winCheck();
void createBoard();
void playerMove();
void computerMove(int turn);
void printBoard();
Move minimaxAlgorithm(int currentTurn);

int main()
{

	bool playAgain = true;
	char again = 'Y';

	//loop to continue until player chooses to quit
	while (playAgain) {
		char winner = ' ';
		int turn = 1;
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

		cout << "Would you like to play again(Q to quit or Y to play again)?\n";

		cin >> again;

		if ((again == 'Q') | (again == 'q')) {
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

Move minimaxAlgorithm(int currentTurn) {
	Move move;
	
	//vector to store the list of moves to find the best move
	vector<Move> bestMoves;

	//changing between computer and player symbols for each simulated turn for the board
	currentTurn = -currentTurn;

	char currentMark;
	char winner;

	//base case for score, if player wins returns negative, computer wins is positive, and cat is 0
	winner = winCheck();

	if (winner == 'X') {
		return Move(-10);
	}
	else if (winner == 'O') {
		return Move(10);
	}
	else if ((winner == 'C')) {
		return Move(0);
	}



	//  1 = player
	//  -1 = computer
	if (currentTurn == 1) {
		currentMark = 'X';
	}
	else {
		currentMark = 'O';
	}

	//uptating the board and simulating the next move if a space is still available
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			if (board[i][j] == ' ') {
				board[i][j] = currentMark;

				move = minimaxAlgorithm(currentTurn);

				move.x = i;
				move.y = j;
				
				bestMoves.push_back(move);

				//resetting changes to the board
				board[i][j] = ' ';
			}
		}
	}


	//variable to save best move in the iterations
	int bestMove = 0;
	
	//on computer turn looking for the heighest score
	if (currentTurn == -1) {

		int bestScore = -20;
		for (int i = 0; i < bestMoves.size(); i++) {

			if (bestMoves.at(i).score > bestScore) {
				bestScore = bestMoves.at(i).score;
				bestMove = i;
			}

		}
	}
	//on players turn looking for the lowest score
	else {
		int bestScore = 20;

		for (int i = 0; i < bestMoves.size(); i++) {

			if (bestMoves.at(i).score < bestScore) {
				bestScore = bestMoves.at(i).score;
				bestMove = i;
			}

		}
	}
	
	return bestMoves.at(bestMove);

}

//computer move class
void computerMove(int turn) {

	srand(time(0));

	//random selection for corners, if player selects middle allows computer to not always take same corner
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
		Move move;
		move = minimaxAlgorithm(1);

		computerX = move.x;
		computerY = move.y;

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
	//checks if all spaces have been occupied, if not play continues
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