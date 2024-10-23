#include <vector>
#include <iostream>
#include <stdlib.h>
#include "checkers.h"

using namespace std;

Checkers::Checkers() {
	Board.resize(8);
	for (int rows = 0; rows < 8; rows++) {
		Board[rows].resize(8, ' '); // used to create an 8x8 board
	}
	for (int i = 0; i < 3; i++) { 
		for (int j = 0; j < 8; j++) {
			Board[i][(j + i) % 8] = 'b';
			Board[7 - i][(j++ + i + 1) % 8] = 'r';
		}
	} // places red and black on the board and staggers them accordingly.
}
Checkers::~Checkers() {
}
void Checkers::printBoard() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			cout << "|" << Board[i][j];
		}
		cout << "|" << endl;
	}
}
// just a within bound checks for the row and col 
bool Checkers::isWithinBounds(int row, int col) {
	if (row >= 0 && row < 8 && col >= 0 && col < 8) {
		return true;
	}
	return false;
}



//**need to add logic for kings eventually**
//pieceToMove[0] is the row position of the piece the player wants to move. pieceToMove[1] is the corresponding col position. 
//whereToMove[0] is the row position of where the player wants to move their piece. whereToMove[1] is the corresponding col position
bool Checkers::isValidMove(int pieceToMove[], int whereToMove[], char redOrBlack) {
	//checks to see if pieceToMove and whereToMove are within the board dimensions
	if(!(pieceToMove[0] < 8) || !(pieceToMove[1] < 8) || !(whereToMove[0] < 8) || !(whereToMove[1] < 8)) return false;

	//check to see if there is the piece at pieceToMove location
	if(Board[pieceToMove[0]][pieceToMove[1]] != redOrBlack) return false;

	//checks to see that the black is moving down the board and red is moving up the board
	if(redOrBlack == 'b') {
		if(pieceToMove[0] > whereToMove[0]) return false;
	}
	else if (redOrBlack == 'r') {
		if(pieceToMove[0] < whereToMove[0]) return false;
	}

	//checks to see if there is a piece where the player wants to move
	if(Board[whereToMove[0]][whereToMove[1]] != ' ') return false;

	//the move is valid if the the piece is moved one space diagonally ***change?***
	if(redOrBlack == 'b') {
		//explanation fo Hein. the line below says the following: for black moving one space diagonally, the target row should be one more than the piece row and the target column should be either one more or one less than the piece row. look at a board to see the logic here
		if(whereToMove[0] == (pieceToMove[0] + 1) && ((whereToMove[1] - 1) == pieceToMove[1] || (whereToMove[1] + 1) == pieceToMove[1])) return true;
	}
	else if (redOrBlack == 'r') {
		if(whereToMove[0] == (pieceToMove[0] - 1) && ((whereToMove[1] - 1) == pieceToMove[1] || (whereToMove[1] + 1) == pieceToMove[1])) return true;
	}

	//if the player wants to take a piece aka jump over a piece
	if(redOrBlack == 'b') {
		//explanation for Hein. for black moving two diagonally to take a piece: the target row should be 2 more than the piece row and target column should be two more than the piece column and there should be a red piece one diagonally
		if(whereToMove[0] == (pieceToMove[0] + 2) && whereToMove[1] == (pieceToMove[1] + 2) && Board[pieceToMove[0] + 1][pieceToMove[1] + 1] == 'r') return true;
		//explanation for Hein. the other case is when the target column is two less than the piece column. This is also valid
		if(whereToMove[0] == (pieceToMove[0] + 2) && whereToMove[1] == (pieceToMove[1] - 2) && Board[pieceToMove[0] + 1][pieceToMove[1] - 1] == 'r') return true;
	}
	else if (redOrBlack == 'r') {
		if(whereToMove[0] == (pieceToMove[0] - 2) && whereToMove[1] == (pieceToMove[1] + 2) && Board[pieceToMove[0] - 1][pieceToMove[1] + 1] == 'b') return true;
		if(whereToMove[0] == (pieceToMove[0] - 2) && whereToMove[1] == (pieceToMove[1] - 2) && Board[pieceToMove[0] - 1][pieceToMove[1] - 1] == 'b') return true;
	}

	return false;

}

// the double take function 
bool Checkers::canDoubleJump(int pieceRow, int pieceCol, char redOrBlack) {

	//movement direction for normal (not king pieces add later)
	int direction;
	if(redOrBlack == 'r') {
		direction = -1; // red pieces move up the board
	}
	else {
		direction = 1; //black moves down the board
	}

	// the possible capture moves for normal pieces (up left and right no king pieces)
	int possibleMoves[2][2] = {
		{pieceRow + 2 * direction, pieceCol + 2}, // diagonal right
		{pieceRow + 2 * direction, pieceCol - 2} // diagonal left
	};

	for (int i = 0; i < 2; i++) {
		int targetRow = possibleMoves[i][0];
		int targetCol = possibleMoves[i][1];

		//bound checks
		if (!isWithinBounds(targetRow, targetCol)) {
			continue;
		}
		//create arrays to pass to isValidMove
		int pieceToMove[2] = {pieceRow, pieceCol};
		int whereToMove[2] = {targetRow, targetCol};
		// check if the move is valid and is a capture move
		if (isValidMove(pieceToMove, whereToMove, redOrBlack)) {

			return true;
		}
	}
	// no more additional capture move
	return false;
}

void Checkers::play() {

	int turn = 0;

	while (true) {
		char player;
		int rowPieceToMove, colPieceToMove, rowWhereToMove, colWhereToMove; 
		printBoard();
		
		// determine the current plater based on the turn number
		if (turn % 2 == 0) { 
			cout << "\nBlack's "; 
			player = 'b';
		}
		else {
			cout << "\nRed's ";
			player = 'r';
		}
		cout << "turn. " << endl;

		cout << "Enter the checker you want to move in the format \"X Y\": ";
		cin >> rowPieceToMove >> colPieceToMove;

		//checks to see if in bounds and if there is a piece at the position the player has entered
		while (rowPieceToMove < 0 || colPieceToMove < 0 || rowPieceToMove > 7 || colPieceToMove > 7 || Board[rowPieceToMove][colPieceToMove] != player) {
			cout << "Invalid. Please try again." << endl;
			cout << "Enter the checker you want to move in the format \"X Y\": ";
			cin >> rowPieceToMove >> colPieceToMove;
		} 

		// change this part a lil bit - Hien
		bool additionalCaptureAvailable = false; // bool flag to handle multiple captures

		do {
			// prompt asking the player to enter the coordinates to move
			cout << "Enter where you want to move your piece in the format \"X Y\": ";
			cin >> rowWhereToMove >> colWhereToMove;
			int piecePosition[2] = {rowPieceToMove, colPieceToMove};
			int movePosition[2] = {rowWhereToMove, colWhereToMove};
			
			// validate the move using isValidMove
			while (!isValidMove(piecePosition, movePosition, player)) {
				cout << "Invalid move. Please try again." << endl; //should we change this error message to something less broad?
				cout << "Enter where you want to move your piece in the format \"X Y\": ";
				cin >> movePosition[0] >> movePosition[1];
			}

			//implementing the changes to the board after the move is confirmed to be valid
			if (player == 'b') {
				Board[rowPieceToMove][colPieceToMove] = ' '; // move the black piece to the desired spot and delete the original
				Board[movePosition[0]][movePosition[1]] = 'b';

				//if they want to take a piece we also need to remove that piece
				if(rowPieceToMove + 2 == movePosition[0]) {
					if(colPieceToMove + 2 == movePosition[1]) {
						Board[rowPieceToMove + 1][colPieceToMove + 1] = ' '; // diagonal right capture
					}
					else if(colPieceToMove - 2 == movePosition[1]) { 
						Board[rowPieceToMove + 1][colPieceToMove - 1] = ' '; // diagonal left capture
					}
				}
			}
			else if (player == 'r') {
				Board[rowPieceToMove][colPieceToMove] = ' ';
				Board[movePosition[0]][movePosition[1]] = 'r';

				//if they want to take a piece we also need to remove that piece
				if(rowPieceToMove - 2 == movePosition[0]) {
					if(colPieceToMove + 2 == movePosition[1]) { 
						Board[rowPieceToMove - 1][colPieceToMove + 1] = ' '; // diagonal right 
					}
					else if(colPieceToMove - 2 == movePosition[1]) { 
						Board[rowPieceToMove - 1][colPieceToMove - 1] = ' '; // diagonal left
					}
				}
			}

			//updating the piece position to the new position
			rowPieceToMove = movePosition[0];
			colPieceToMove = movePosition[1];
			
			//checks if a capture was made 
			if (abs(movePosition[0] - piecePosition[0]) == 2) {
				// a capture was made now check for additional captures
				if (canDoubleJump(rowPieceToMove, colPieceToMove, player)) {
					printBoard();
					cout << "You can make another capture! Continue your turn." << endl;
					additionalCaptureAvailable = true; // continue capturing
				}
			}
			else {
				additionalCaptureAvailable = false; // no further captures
			}
		}
		while (additionalCaptureAvailable); // continue move if there is additional captures available
		turn++; // switch player
	}
}
int main() {

	Checkers check;
	check.play();
	
}
