#include <iostream>
#include <string.h>

using namespace std;


class Piece {
  public:

};

enum piece {
  WPawn, WKnight, WBishop, WRook, WQueen, WKing,
  empty, 
  BPawn, BKnight, BBishop, BRook, BQueen, BKing
};


int board[8][8];


void setEmpty() {
  for (int i = 0; i < 8; i++) {
    for (int j = 2; j < 6; j++) {
      board[j][i] = empty;
    }
  }  
}

void setPawns() {
  for (int i = 0; i < 8; i++) {
    board[6][i] = WPawn;
    board[1][i] = BPawn; 
  }
}

void setNonPawns() {
  board[7][1] = WKnight;  board[0][1] = BKnight;
  board[7][6] = WKnight;  board[0][6] = BKnight;

  board[7][2] = WBishop;  board[0][2] = BBishop;
  board[7][5] = WBishop;  board[0][5] = BBishop;

  board[7][0] = WRook;  board[0][0] = BRook;
  board[7][7] = WRook;  board[0][7] = BRook;

  board[7][3] = WQueen;  board[0][3] = BQueen;

  board[7][4] = WKing;  board[0][4] = BKing;
  
}

void printBoard() {
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      switch (board[i][j]) {
        case empty:
          cout << "  ";
            break;
        case WPawn:
          cout << "P ";
            break;
        case BPawn:
          cout << "p ";
            break;
        case WKnight:
          cout << "K ";
            break;
        case BKnight:
          cout << "k ";
            break;
        case WBishop:
          cout << "B ";
            break;
        case BBishop:
          cout << "b ";
            break;
        case WRook:
          cout << "R ";
            break;
        case BRook:
          cout << "r ";
            break;
        case WQueen:
          cout << "Q ";
            break;
        case BQueen:
          cout << "q ";
            break;
        case WKing:
          cout << "* ";
            break;
        case BKing:
          cout << "* ";
            break;
      }
    }
    cout << endl;
  }
  cout << endl;
}


void movePawn(int x, int y, int a, int b) {
  if (board[x][y] == WPawn) {    //WHITE
    if (x == 6 && a == 4 && y == b && board[x-2][y] == empty && board[x-1][y] == empty) {  //checking for double first pawn move
      cout << "legal double move" << endl;
      board[a][b] = board[x][y];
      board[x][y] = empty;
    }
    else if (y == b && x-1 == a){      // checking for normal first pawn move
      board[a][b] = board[x][y];
      board[x][y] = empty;
    }
    else if ((b == y+1 || b == y-1) && board[a][b] > 6 && a == x-1) {  //pawn capture
      board[a][b] = board[x][y];
      board[x][y] = empty;
    }
  }
  else {    //BLACK
    if (x == 1 && a == 3 && y == b && board[x+2][y] == empty && board[x+1][y] == empty) {  //checking for double first pawn move
      cout << "legal double move" << endl;
      board[a][b] = board[x][y];
      board[x][y] = empty;
    }
    else if (y == b && x+1 == a){      // checking for normal first pawn move
      board[a][b] = board[x][y];
      board[x][y] = empty;
    }
    else if ((b == y+1 || b == y-1) && board[a][b] < 6 && a == x+1) {  //pawn capture
      board[a][b] = board[x][y];
      board[x][y] = empty;
    }
  }
}

void moveKnight(int x, int y, int a, int b) {

}

void chooseMove() {
  int x, y, a, b;
  cin >> x;
  cin >> y;
  cin >> a;
  cin >> b;

  switch (board[x][y]) {
    case empty:
      cout << "Invalid Piece" << endl;
        break;
    case WPawn:
      movePawn(x, y, a, b);
        break;
    case BPawn:
      movePawn(x, y, a, b);
        break;
    case WKnight:
      board[a][b] = board[x][y];
      board[x][y] = empty;
        break;
    case BKnight:
      board[a][b] = board[x][y];
      board[x][y] = empty;
        break;
    case WBishop:
      board[a][b] = board[x][y];
      board[x][y] = empty;
        break;
    case BBishop:
      board[a][b] = board[x][y];
      board[x][y] = empty;
        break;
    case WRook:
      board[a][b] = board[x][y];
      board[x][y] = empty;
        break;
    case BRook:
      board[a][b] = board[x][y];
      board[x][y] = empty;
        break;
    case WQueen:
      board[a][b] = board[x][y];
      board[x][y] = empty;
        break;
    case BQueen:
      board[a][b] = board[x][y];
      board[x][y] = empty;
        break;
    case WKing:
      board[a][b] = board[x][y];
      board[x][y] = empty;
        break;
    case BKing:
      board[a][b] = board[x][y];
      board[x][y] = empty;
        break;
  }
}

int main() {
  setPawns();
  setNonPawns();
  setEmpty();
  
  while(true) {
    printBoard();
    chooseMove();
  }
}
