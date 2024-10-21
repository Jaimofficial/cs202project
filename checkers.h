#ifndef _CHECKERS_H_

#define _CHECKERS_H_

	class Board {
	
		public:
			void Move(int); //Allows user to move to a specified index
			bool isPromoted(int); // checks if the checker can move backwards
		private:
		vector< vector < char > > Board;
	
	};




#endif
