#include <vector>
#include <iostream>
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

//**need to add logic for kings eventually**
bool Checkers::isValidMove(vector< vector < char > > Board, int pieceToMove[], int whereToMove[], char redOrBlack) {
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

	//the player should only be able to move one square forward diagonally ***change?***
	if(redOrBlack == 'b') {
		if(whereToMove[0] == (pieceToMove[0] + 1) && ((whereToMove[1] - 1) == pieceToMove[1] || (whereToMove[1] + 1) == pieceToMove[1])) return true;
	}
	else if (redOrBlack == 'r') {
		if(whereToMove[0] == (pieceToMove[0] - 1) && ((whereToMove[1] - 1) == pieceToMove[1] || (whereToMove[1] + 1) == pieceToMove[1])) return true;
	}

	//if the player wants to take a piece aka jump over a piece
	if(redOrBlack == 'b') {
		if(whereToMove[0] == (pieceToMove[0] + 2) && whereToMove[1] == (pieceToMove[1] + 2) && Board[pieceToMove[0] + 1][pieceToMove[1] + 1] == 'r') return true;
		if(whereToMove[0] == (pieceToMove[0] + 2) && whereToMove[1] == (pieceToMove[1] - 2) && Board[pieceToMove[0] + 1][pieceToMove[1] - 1] == 'r') return true;
	}
	else if (redOrBlack == 'r') {
		if(whereToMove[0] == (pieceToMove[0] - 2) && whereToMove[1] == (pieceToMove[1] + 2) && Board[pieceToMove[0] - 1][pieceToMove[1] + 1] == 'b') return true;
		if(whereToMove[0] == (pieceToMove[0] - 2) && whereToMove[1] == (pieceToMove[1] - 2) && Board[pieceToMove[0] - 1][pieceToMove[1] - 1] == 'b') return true;
	}

	return false;

}

void Checkers::play() {
	int turn = 0;

	while (true) {
		char player;
		int XPieceToMove, YPieceToMove; 
		printBoard();
		
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
		cin >> XPieceToMove >> YPieceToMove;

		while (XPieceToMove < 0 || YPieceToMove < 0 || XPieceToMove > 7 || YPieceToMove > 7) {
			cout << "Out of bounds of board. Please try again." << endl;
			cout << "Enter the checker you want to move in the format \"X Y\": ";
			cin >> XPieceToMove >> YPieceToMove;
		} 


		turn++;
	}

}
int main() {

	Checkers check;
	check.play();
	
}
