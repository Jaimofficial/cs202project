#include "checkers.h"
#include <cctype>
#include <iostream>
#include <stdlib.h>
#include <vector>

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
Checkers::~Checkers() {}
void Checkers::printBoard() {
  cout << "The board will have coordinates represented by |XY|" << endl;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      cout << "|" << i << j;
    }
    cout << "|" << endl;
  }

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
// pieceToMove[0] is the row position of the piece the player wants to move.
// pieceToMove[1] is the corresponding col position. whereToMove[0] is the row
// position of where the player wants to move their piece. whereToMove[1] is the
// corresponding col position
bool Checkers::isValidMove(int pieceToMove[], int whereToMove[],
                           char redOrBlack) {
  // checks to see if pieceToMove and whereToMove are within the board
  // dimensions
  if(!isWithinBounds(pieceToMove[0], pieceToMove[1]) || !isWithinBounds(whereToMove[0], whereToMove[1]))
    return false;

  // check to see if there is the piece at pieceToMove location
  if ((Board[pieceToMove[0]][pieceToMove[1]]) != redOrBlack)
    return false;
  // checks to see that the black is moving down the board and red is moving up
  // the board
  if (redOrBlack == 'b') {
    if (pieceToMove[0] > whereToMove[0])
      return false;
  } else if (redOrBlack == 'r') {
    if (pieceToMove[0] < whereToMove[0])
      return false;
  }
  // checks to see if there is a piece where the player wants to move
  if (Board[whereToMove[0]][whereToMove[1]] != ' ')
    return false;

  // the move is valid if the the piece is moved one space diagonally
  if (redOrBlack == 'b') {
    if (whereToMove[0] == (pieceToMove[0] + 1) &&
        ((whereToMove[1] - 1) == pieceToMove[1] ||
         (whereToMove[1] + 1) == pieceToMove[1]))
      return true;
  } 
  else if (redOrBlack == 'r') {
    if (whereToMove[0] == (pieceToMove[0] - 1) &&
        ((whereToMove[1] - 1) == pieceToMove[1] ||
         (whereToMove[1] + 1) == pieceToMove[1]))
      return true;
  } 
  else if (redOrBlack == 'R' || redOrBlack == 'B') {
    if (whereToMove[0] == (pieceToMove[0] + 1) &&
        ((whereToMove[1] - 1) == pieceToMove[1] ||
         (whereToMove[1] + 1) == pieceToMove[1]))
      return true;
    if (whereToMove[0] == (pieceToMove[0] - 1) &&
        ((whereToMove[1] - 1) == pieceToMove[1] ||
         (whereToMove[1] + 1) == pieceToMove[1]))
      return true;
  }
  // if the player wants to take a piece aka jump over a piece
  if (redOrBlack != ' ' && redOrBlack != 'r') {
    char piece = (redOrBlack == 'R') ? 'b' : 'r';
    // explanation for Hein. for black moving two diagonally to take a piece:
    // the target row should be 2 more than the piece row and target column
    // should be two more than the piece column and there should be a red piece
    // one diagonally
    if (whereToMove[0] == (pieceToMove[0] + 2) &&
        whereToMove[1] == (pieceToMove[1] + 2) &&
        (Board[pieceToMove[0] + 1][pieceToMove[1] + 1] == piece ||
        Board[pieceToMove[0] + 1][pieceToMove[1] + 1] == piece - 32))
      return true;
    // explanation for Hein. the other case is when the target column is two
    // less than the piece column. This is also valid
    if (whereToMove[0] == (pieceToMove[0] + 2) &&
        whereToMove[1] == (pieceToMove[1] - 2) &&
        (Board[pieceToMove[0] + 1][pieceToMove[1] - 1] == piece ||
        Board[pieceToMove[0] + 1][pieceToMove[1] - 1] == piece - 32))
      return true;
  } 
  if (redOrBlack != ' ' && redOrBlack != 'b') {
    char piece = (redOrBlack == 'B') ? 'r' : 'b';
    if (whereToMove[0] == (pieceToMove[0] - 2) &&
        whereToMove[1] == (pieceToMove[1] + 2) &&
        (Board[pieceToMove[0] - 1][pieceToMove[1] + 1] == piece ||
        Board[pieceToMove[0] - 1][pieceToMove[1] + 1] == piece - 32))
      return true;
    if (whereToMove[0] == (pieceToMove[0] - 2) &&
        whereToMove[1] == (pieceToMove[1] - 2) &&
        (Board[pieceToMove[0] - 1][pieceToMove[1] - 1] == piece ||
        Board[pieceToMove[0] - 1][pieceToMove[1] - 1] == piece - 32)) 
      return true;
  }
  return false;
}

// the double take function
bool Checkers::canDoubleJump(int pieceRow, int pieceCol, char redOrBlack) {
  // movement direction for normal (not king pieces add later)
  int direction;
  int loop;
  if (redOrBlack == 'r') {
    direction = -1; // red pieces move up the board
    loop = 0;
  } else if (redOrBlack == 'b') {
    direction = 1; // black moves down the board
    loop = 0;
  } else {
    direction = -1;
    loop = 1; // set so that we can check both moving up and down the board
  }
  // Need to include else statement for Capital letters
  // the possible capture moves for normal pieces (up left and right no king
  // pieces)
  do {
  int possibleMoves[2][2] = {
      {pieceRow + 2 * direction, pieceCol + 2}, // diagonal right
      {pieceRow + 2 * direction, pieceCol - 2}  // diagonal left
  };

  for (int i = 0; i < 2; i++) {
    int targetRow = possibleMoves[i][0];
    int targetCol = possibleMoves[i][1];

    //I'm commenting this out because isValidMove (shown below) checks for bounds already - Tom
    //// bound checks
    //if (!isWithinBounds(targetRow, targetCol)) {
    //  continue;
    //}

    // create arrays to pass to isValidMove
    int pieceToMove[2] = {pieceRow, pieceCol};
    int whereToMove[2] = {targetRow, targetCol};
    // check if the move is valid and is a capture move
    if (isValidMove(pieceToMove, whereToMove, redOrBlack)) {

      return true;
    }
  }
  if (loop > 0 && direction == -1) direction = 1; // change the direction
                                                  // if promoted piece
  } while (loop-- > 0);
  // no more additional capture move
  return false;
}

bool Checkers::hasAvailableMoves(int x, int y) {
  int piecePosition[2] = {x, y};
  int moveLeft[2];
  int moveRight[2];

    if (tolower(Board[x][y]) == 'r') {
      char piece = Board[x][y]; // can get either 'R' or 'r'.
      moveLeft[0] = x - 1;
      moveLeft[1] = y - 1;
      moveRight[0] = x - 1;
      moveRight[1] = y + 1; // possible movements for r (moving up)
      if (!(isValidMove(piecePosition, moveLeft, piece) || 
            isValidMove(piecePosition, moveRight, piece))) {
              if (moveLeft[0] >= 0 && moveLeft[1] >= 0 &&
                  tolower(Board[moveLeft[0]][moveLeft[1]]) == 'b') {
                  moveLeft[0] = x - 2;
                  moveLeft[1] = y - 2;
                if (isValidMove(piecePosition, moveLeft, piece)) return true;
              }
              if (moveRight[0] >= 0 && moveRight[1] < 8 &&
                  tolower(Board[moveRight[0]][moveRight[1]]) == 'b') {
                moveRight[0] = x - 2;
                moveRight[1] = y + 2;
                if (isValidMove(piecePosition, moveRight, piece)) return true;
              }
              moveLeft[0] = x + 1;
              moveLeft[1] = y - 1;
              moveRight[0] = x + 1;
              moveRight[1] = y + 1;
              // need to check promoted movements in the opposite direction
             if (piece == 'R') { 
                if ((isValidMove(piecePosition, moveLeft, piece) || //left jump
                  isValidMove(piecePosition, moveRight, piece))) return true;
                   if (moveLeft[0] < 8 && moveLeft[1] >= 0 &&
                        tolower(Board[moveLeft[0]][moveRight[1]]) == 'b') {
                  moveLeft[0] = x + 2;
                  moveLeft[1] = y - 2;
                if (isValidMove(piecePosition, moveLeft, piece)) return true;
              }
              if (moveRight[0] < 8 && moveRight[1] < 8 && // right jump
                  tolower(Board[moveRight[0]][moveRight[1]]) == 'b') {
                  moveRight[0] = x + 2;
                  moveRight[1] = y + 2;
                if (isValidMove(piecePosition, moveRight, piece)) return true;
              }
              } 
                return false;
            }
    }
    else if (tolower(Board[x][y]) == 'b') {
      char piece = Board[x][y]; // can get either 'B' or 'b'.
      moveLeft[0] = x + 1;
      moveLeft[1] = y - 1;
      moveRight[0] = x + 1;
      moveRight[1] = y + 1; // possible movements for b (going down)
      if (!(isValidMove(piecePosition, moveLeft, piece) || 
            isValidMove(piecePosition, moveRight, piece))) {
              if (moveLeft[0] < 8 && moveLeft[1] >= 0 && 
                  tolower(Board[moveLeft[0]][moveRight[1]]) == 'r') { // checks for jumps
                  moveLeft[0] = x + 2;
                  moveLeft[1] = y - 2;
                if (isValidMove(piecePosition, moveLeft, piece)) return true;
              }
              if (moveRight[0] < 8 && moveRight[1] < 8 &&
                  tolower(Board[moveRight[0]][moveRight[1]]) == 'r') { // right jump
                  moveRight[0] = x + 2;
                  moveRight[1] = y + 2;
                if (isValidMove(piecePosition, moveRight, piece)) return true;
              }
              moveLeft[0] = x - 1;
              moveLeft[1] = y - 1;
              moveRight[0] = x - 1;
              moveRight[1] = y + 1;
               if (piece == 'B') { // need to check if the piece is promoted, so have to see
                                   // other side's possible moves
                if ((isValidMove(piecePosition, moveLeft, piece) || 
                  isValidMove(piecePosition, moveRight, piece))) return true;
                   if (moveLeft[0] >= 0 && moveLeft[1] >= 0 &&
                      tolower(Board[moveLeft[0]][moveRight[1]]) == 'r') {
                  moveLeft[0] = x - 2;
                  moveLeft[1] = y - 2;
                if (isValidMove(piecePosition, moveLeft, piece)) return true;
              }
              if (moveRight[0] >= 0 && moveRight[1] < 8 &&
                  tolower(Board[moveRight[0]][moveRight[1]]) == 'r') {
                  moveRight[0] = x - 2;
                  moveRight[1] = y + 2;
                if (isValidMove(piecePosition, moveRight, piece)) return true;
              }
              } 
                return false;
            }
    }
    else return false; // for space on board
    return true;
}

bool Checkers::hasWon() {
  int bCount = 0;
  int rCount = 0;
  for (int i = 0; i < 64; i++) {
    if (tolower(Board[i / 8][i % 8]) == 'r')  rCount++;
    else if (tolower(Board[i / 8][i % 8]) == 'b') bCount++;
  }
  if (rCount == 0 || bCount == 0) {
    if (rCount == 0 && bCount == 0) {
      cout << "Tie." << endl;
      return true;
    }
      cout << ((rCount < bCount) ? "Black " : "Red ") << "won!" << endl;
      return true;
  }
  // int piecePosition[2];
  // int moveLeft[2];
  // int moveRight[2];
  for (int i = 0; i < 64; i++) {
    // Keep for now, I could be wrong in hasAvailableMoves (tested strongly though)
    // - Jai
    /*
    piecePosition[0] = i / 8;
    piecePosition[1] = i % 8;
    if (tolower(Board[i / 8][i % 8]) == 'r') {
      char piece = Board[i / 8][i % 8]; // can get either 'R' or 'r'.
      moveLeft[0] = (i - 8) / 8;
      moveLeft[1] = (i - 1) % 8;
      moveRight[0] = (i - 8) / 8;
      moveRight[1] = (i + 1) % 8;
      if (!(isValidMove(piecePosition, moveLeft, piece) || 
            isValidMove(piecePosition, moveRight, piece))) {
              moveLeft[0] = (i + 8) / 8;
              moveLeft[1] = (i - 1) % 8;
              moveRight[0] = (i + 8) / 8;
              moveRight[1] = (i + 1) % 8;
              if (piece == 'R' && (isValidMove(piecePosition, moveLeft, piece) || 
            isValidMove(piecePosition, moveRight, piece))) continue;
                rCount--;
            }
    }
    else if (tolower(Board[i / 8][i % 8]) == 'b') {
      char piece = Board[i / 8][i % 8]; // can get either 'B' or 'b'.
      moveLeft[0] = (i + 8) / 8;
      moveLeft[1] = (i - 1) % 8;
      moveRight[0] = (i + 8) / 8;
      moveRight[1] = (i + 1) % 8;
      if (!(isValidMove(piecePosition, moveLeft, piece) || 
            isValidMove(piecePosition, moveRight, piece))) {
              moveLeft[0] = (i - 8) / 8;
              moveLeft[1] = (i - 1) % 8;
              moveRight[0] = (i - 8) / 8;
              moveRight[1] = (i + 1) % 8;
              if (piece == 'B' && (isValidMove(piecePosition, moveLeft, piece) || 
            isValidMove(piecePosition, moveRight, piece))) continue;
                bCount--;
            }
    }*/
    if (tolower(Board[i / 8][i % 8]) == 'r' && !hasAvailableMoves(i/8, i%8)) rCount--;
    else if (tolower(Board[i / 8][i % 8]) == 'b' && !hasAvailableMoves(i/8, i%8)) bCount--;
    if (rCount == 0 || bCount == 0) {
    if (rCount == 0 && bCount == 0) {
      cout << "Tie." << endl;
      return true;
    }
      cout << ((rCount < bCount) ? "Black " : "Red ") << "won!" << endl;
      return true;
  }
  }
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
    } else {
      cout << "\nRed's ";
      player = 'r';
    }
    cout << "turn. " << endl;

    cout << "Enter the checker you want to move in the format \"X Y\": ";
    cin >> rowPieceToMove >> colPieceToMove;

    // checks to see if in bounds and if there is a piece at the position the
    // player has entered
    while (rowPieceToMove < 0 || colPieceToMove < 0 || rowPieceToMove > 7 ||
           colPieceToMove > 7 ||
           tolower(Board[rowPieceToMove][colPieceToMove]) != player ||
           !hasAvailableMoves(rowPieceToMove, colPieceToMove)) {
      cout << "Invalid. Please try again." << endl;
      cout << "Enter the checker you want to move in the format \"X Y\": ";
      cin >> rowPieceToMove >> colPieceToMove;
    }
    char piece;
    // change this part a lil bit - Hien
    bool additionalCaptureAvailable =
        false; // bool flag to handle multiple captures
    do {
      piece = player;
      // prompt asking the player to enter the coordinates to move
      cout << "Enter where you want to move your piece in the format \"X Y\": ";
      cin >> rowWhereToMove >> colWhereToMove;
      int piecePosition[2] = {rowPieceToMove, colPieceToMove};
      if (Board[rowPieceToMove][colPieceToMove] == 'R' ||
          Board[rowPieceToMove][colPieceToMove] == 'B') {
        piece -= 32;
      }
      int movePosition[2] = {rowWhereToMove, colWhereToMove};
      // validate the move using isValidMove
      while (!isValidMove(piecePosition, movePosition, piece)) {
        cout << "Invalid move. Please try again."
             << endl; // should we change this error message to something less
                      // broad?
        printBoard();
        cout << "You chose the coordinates " << rowPieceToMove << " "
             << colPieceToMove << "." << endl;
        cout << "Enter where you want to move your piece in the format \"X "
                "Y\": ";
        cin >> movePosition[0] >> movePosition[1];
      }
      // implementing the changes to the board after the move is confirmed to be
      // valid
      if (piece == 'b') {
        Board[rowPieceToMove][colPieceToMove] =
            ' '; // move the black piece to the desired spot and delete the
                 // original
        Board[movePosition[0]][movePosition[1]] = piece;

        // if they want to take a piece we also need to remove that piece
        if (rowPieceToMove + 2 == movePosition[0]) {
          if (colPieceToMove + 2 == movePosition[1]) {
            Board[rowPieceToMove + 1][colPieceToMove + 1] =
                ' '; // diagonal right capture
          } else if (colPieceToMove - 2 == movePosition[1]) {
            Board[rowPieceToMove + 1][colPieceToMove - 1] =
                ' '; // diagonal left capture
          }
        }
      } else if (piece == 'r') {
        Board[rowPieceToMove][colPieceToMove] = ' ';
        Board[movePosition[0]][movePosition[1]] = piece;

        // if they want to take a piece we also need to remove that piece
        if (rowPieceToMove - 2 == movePosition[0]) {
          if (colPieceToMove + 2 == movePosition[1]) {
            Board[rowPieceToMove - 1][colPieceToMove + 1] =
                ' '; // diagonal right
          } else if (colPieceToMove - 2 == movePosition[1]) {
            Board[rowPieceToMove - 1][colPieceToMove - 1] =
                ' '; // diagonal left
          }
        }
      } else {
        Board[rowPieceToMove][colPieceToMove] = ' ';
        Board[movePosition[0]][movePosition[1]] = piece;
        // if they want to take a piece we also need to remove that piece
        if (rowPieceToMove - 2 == movePosition[0] ||
            rowPieceToMove + 2 == movePosition[0]) {
          bool up = true;
          if (rowPieceToMove + 2 == movePosition[0]) {
            up = false;
          }
          if (colPieceToMove + 2 == movePosition[1]) {
            if (up)
              Board[rowPieceToMove - 1][colPieceToMove + 1] =
                  ' '; // up diagonal right capture
            else
              Board[rowPieceToMove + 1][colPieceToMove + 1] =
                  ' '; // down diagonal right capture
          } else if (colPieceToMove - 2 == movePosition[1]) {
            if (up)
              Board[rowPieceToMove - 1][colPieceToMove - 1] =
                  ' '; // up diagonal left
            else
              Board[rowPieceToMove + 1][colPieceToMove - 1] =
                  ' '; // bottom diagonal left capture
          }
        }
      }
      // updating the piece position to the new position
      rowPieceToMove = movePosition[0];
      colPieceToMove = movePosition[1];
      if ((rowPieceToMove == 7 && piece == 'b') ||
          (rowPieceToMove == 0 && piece == 'r')) {
        Board[rowPieceToMove][colPieceToMove] -= 32;
        piece = Board[rowPieceToMove][colPieceToMove]; // updates if piece promotes.
        cout << "The Piece has been Promoted!" << endl;
      }
      // checks if a capture was made
      if (abs(movePosition[0] - piecePosition[0]) == 2) {
        // a capture was made now check for additional capturess

        if (canDoubleJump(rowPieceToMove, colPieceToMove, piece)) {
          printBoard();
          cout << "You can make another capture! Continue your turn." << endl;
          additionalCaptureAvailable = true; // continue capturing
          continue;
        }
      }
      additionalCaptureAvailable = false; // no further captures
    } while (additionalCaptureAvailable); // continue move if there is
                                          // additional captures available
    if (hasWon()) {
      string person = ((turn % 2 == 0) ? "Red " : "Black ");
      cout << person << "won! Do you want to play another game? " << endl;
      printBoard();
      return;
    }
    turn++; // switch player
  }
}
int main() {

  Checkers check;
  check.play();
}
