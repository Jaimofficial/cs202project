#ifndef _CHECKERS_H_
#define _CHECKERS_H_
#include <vector>

	class Checkers {
	
		public:
			Checkers();
			~Checkers();
			void Move(int); //Allows user to move to a specified index
			bool isValidMove(std::vector< std::vector < char > >, int pieceToMove[], int whereToMove[], char);
			bool isPromoted(int); // checks if the checker can move backwards
			void printBoard(); // print the total board
			void play();
		private:
				std::vector< std::vector < char > > Board;
	
	};




#endif
