#ifndef _CHECKERS_H_
#define _CHECKERS_H_
#include <vector>

	class Checkers {
	
		public:
			Checkers();
			~Checkers();
			void Move(int); //Allows user to move to a specified index
			bool isValidMove(int pieceToMove[], int whereToMove[], char);
			bool isPromoted(int); // checks if the checker can move backwards
			void printBoard(); // print the total board
			void play();
			bool isWithinBounds(int row, int col);
			bool canDoubleJump(int pieceRow, int pieceCol, char redOrBlack);
			bool hasWon();
<<<<<<< HEAD
			bool hasAvailableMoves(int x, int y);
=======
>>>>>>> c66e627355e9e5bbd5942826703143e2eb42a333
		private:
				std::vector< std::vector < char > > Board;
	
	};




#endif
