#include <vector>
#include <iostream>
#include "checkers.h"

using namespace std;

Checkers::Checkers() {
	Board.resize(8);
	for (int rows = 0; rows < 8; rows++) {
		Board[rows].resize(8, ' ');
	}
	for (int i = 0; i < 3; i++) { 
		for (int j = 0; j < 8; j++) {
			Board[i][(j + i) % 8] = 'b';
			Board[7 - i][(j++ + i + 1) % 8] = 'r';
		}
	}
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
int main() {

	Checkers check;
	check.printBoard();

}
