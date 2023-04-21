#include <iostream>
#include "header.h"
using namespace std;

bool movePawn(int x, int y, int a, int b, int board[][8]) {
    if (board[x][y] == WPawn) {    //WHITE
        if (x == 6 && a == 4 && y == b && board[x - 2][y] == blank && board[x - 1][y] == blank) {  //checking for double first pawn move
            return true;
        }
        else if (y == b && x - 1 == a) {      // checking for normal first pawn move
            return true;
        }
        else if ((b == y + 1 || b == y - 1) && board[a][b] > 6 && a == x - 1) {  //pawn capture
            return true;
        }
    }
    else {    //BLACK
        if (x == 1 && a == 3 && y == b && board[x + 2][y] == blank && board[x + 1][y] == blank) {  //checking for double first pawn move
            return true;
        }
        else if (y == b && x + 1 == a) {      // checking for normal first pawn move
            return true;
        }
        else if ((b == y + 1 || b == y - 1) && board[a][b] < 6 && a == x + 1) {  //pawn capture
            return true;
        }
    }
}

bool moveKnight(int x, int y, int a, int b, int board[][8]) {
    if (board[x][y] == WKnight && board[a][b] >= 6) {
        if ((a == x - 2 || a == x + 2) && (b == y - 1 || b == y + 1)) {
            return true;
        }
        else if ((b == y - 2 || b == y + 2) && (a == x - 1 || a == x + 1)) {
            return true;
        }
    }

    else if (board[x][y] == BKnight && board[a][b] <= 6) {
        if ((a == x - 2 || a == x + 2) && (b == y - 1 || b == y + 1)) {
            return true;
        }
        else if ((b == y - 2 || b == y + 2) && (a == x - 1 || a == x + 1)) {
            return true;
        }
    }
}


bool moveBishop(int x, int y, int a, int b, int board[][8]) {
    bool posCheck = true;
    if (abs(x - a) == abs(y - b)) {
        if ((board[x][y] == WBishop || board[x][y] == WQueen) && board[a][b] >= 6) {
            if (a > x && b > y) {    //collision for bishop moves down, right
                for (int i = 1; i < abs(x - a); i++) {
                    if (board[x + i][y + i] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
            else if (a > x && b < y) {  //collision for bishop moves down, left
                for (int i = 1; i < abs(x - a); i++) {
                    if (board[x + i][y - i] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
            else if (a < x && b < y) {  //collision for bishop moves up, left
                for (int i = 1; i < abs(x - a); i++) {
                    if (board[x - i][y - i] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
            else if (a < x && b > y) {  //collision for bishop moves up, right
                for (int i = 1; i < abs(x - a); i++) {
                    if (board[x - i][y + i] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
        }
        else if ((board[x][y] == BBishop || board[x][y] == BQueen) && board[a][b] <= 6) {
            if (a > x && b > y) {    //collision for bishop moves down, right
                for (int i = 1; i < abs(x - a); i++) {
                    if (board[x + i][y + i] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
            else if (a > x && b < y) {  //collision for bishop moves down, left
                for (int i = 1; i < abs(x - a); i++) {
                    if (board[x + i][y - i] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
            else if (a < x && b < y) {  //collision for bishop moves up, left
                for (int i = 1; i < abs(x - a); i++) {
                    if (board[x - i][y - i] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
            else if (a < x && b > y) {  //collision for bishop moves up, right
                for (int i = 1; i < abs(x - a); i++) {
                    if (board[x - i][y + i] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
        }
    }
}

bool moveRook(int x, int y, int a, int b, int board[][8]) {
    bool posCheck = true;
    if (x == a || y == b) {
        if ((board[x][y] == WRook || board[x][y] == WQueen) && board[a][b] >= 6) {
            if (a == x && b > y) {    //collision for right
                for (int i = 1; i < abs(y - b); i++) {
                    if (board[a][y + i] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
            else if (a == x && b < y) {    //collision for left
                for (int i = 1; i < abs(y - b); i++) {
                    if (board[a][y - i] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
            else if (a > x && b == y) {    //collision for down
                for (int i = 1; i < abs(x - a); i++) {
                    if (board[x + i][b] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
            else if (a < x && b == y) {    //collision for up
                for (int i = 1; i < abs(x - a); i++) {
                    if (board[x - i][b] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
        }
        else if ((board[x][y] == BRook || board[x][y] == BQueen) && board[a][b] <= 6) {
            if (a == x && b > y) {    //collision for right
                for (int i = 1; i < abs(y - b); i++) {
                    if (board[a][y + i] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
            else if (a == x && b < y) {    //collision for left
                for (int i = 1; i < abs(y - b); i++) {
                    if (board[a][y - i] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
            else if (a > x && b == y) {    //collision for down
                for (int i = 1; i < abs(x - a); i++) {
                    if (board[x + i][b] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
            else if (a < x && b == y) {    //collision for up
                for (int i = 1; i < abs(x - a); i++) {
                    if (board[x - i][b] != blank) {
                        posCheck = false;
                    }
                }
                if (posCheck != false) {
                    return true;
                }
            }
        }
    }
}

bool moveKing(int x, int y, int a, int b, int board[][8], int illigal[][8]) {
    if (board[x][y] == WKing && board[a][b] >= 6) {
        if (abs(x - a) <= 1 && abs(y - b) <= 1) {
            return true;
        }
    }
    if (board[x][y] == BKing && board[a][b] <= 6) {
        if (abs(x - a) <= 1 && abs(y - b) <= 1) {
            return true;
        }
    }
}
