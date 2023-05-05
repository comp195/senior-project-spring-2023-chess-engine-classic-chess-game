#include <iostream>
#include "header.h"
using namespace std;


void setBlank(int board[][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 2; j < 6; j++) {
            board[j][i] = blank;
        }
    }
}

void setPawns(int board[][8]) {
    for (int i = 0; i < 8; i++) {
        board[6][i] = WPawn;
        board[1][i] = BPawn;
    }
}

void setNonPawns(int board[][8]) {
    board[7][1] = WKnight;  board[0][1] = BKnight;
    board[7][6] = WKnight;  board[0][6] = BKnight;

    board[7][2] = WBishop;  board[0][2] = BBishop;
    board[7][5] = WBishop;  board[0][5] = BBishop;

    board[7][0] = WRook;  board[0][0] = BRook;
    board[7][7] = WRook;  board[0][7] = BRook;

    board[7][3] = WQueen;  board[0][3] = BQueen;

    board[7][4] = WKing;  board[0][4] = BKing;

}

void printBoard(int board[][8]) {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            switch (board[i][j]) {
            case blank:
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
                cout << "$ ";
                break;
            case BKing:
                cout << "% ";
                break;
            }
        }
        cout << endl;
    }
    cout << endl;
}

int chooseMove(int board[][8], int tempBoard[][8], int whiteDanger[][8], int blackDanger[][8], int turn) {
    int x, y, a, b, BKingX, BKingY, WKingX, WKingY;
    bool result = false;
    bool gameOver = false;
    bool check;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tempBoard[i][j] = board[i][j];
        }
    }

    cin >> x;
    cin >> y;
    cin >> a;
    cin >> b;

    tempBoard[a][b] = tempBoard[x][y];
    tempBoard[x][y] = blank;

    checkTiles(tempBoard, whiteDanger, blackDanger);

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (tempBoard[i][j] == WKing) {
                WKingX = i;
                WKingY = j;
            }
            if (tempBoard[i][j] == BKing) {
                BKingX = i;
                BKingY = j;
            }
        }
    }

    if (turn % 2 == 1) {        //White Move
        if (blackDanger[WKingX][WKingY] == 1) {
            cout << "White King In check" << endl;
        }
        else {
            switch (board[x][y]) {
            case blank:
                cout << "No Piece At Location" << endl;
                break;

            case WPawn:
                result = movePawn(x, y, a, b, board);
                if (result == true) {
                    board[a][b] = board[x][y];
                    board[x][y] = blank;
                    turn++;
                }
                break;

            case WKnight:
                result = moveKnight(x, y, a, b, board);
                if (result == true) {
                    board[a][b] = board[x][y];
                    board[x][y] = blank;
                    turn++;
                }
                break;

            case WBishop:
                result = moveBishop(x, y, a, b, board);
                if (result == true) {
                    board[a][b] = board[x][y];
                    board[x][y] = blank;
                    turn++;
                }
                break;

            case WRook:
                result = moveRook(x, y, a, b, board);
                if (result == true) {
                    board[a][b] = board[x][y];
                    board[x][y] = blank;
                    turn++;
                }
                break;

            case WQueen:
                result = moveBishop(x, y, a, b, board);
                if (result == false) {
                    result = moveRook(x, y, a, b, board);
                }
                if (result == true) {
                    board[a][b] = board[x][y];
                    board[x][y] = blank;
                    turn++;
                }
                break;

            case WKing:
                result = moveKing(x, y, a, b, board);
                if (result == true) {
                    board[a][b] = board[x][y];
                    board[x][y] = blank;
                    turn++;
                }
                break;

            }
        }

        gameOver = checkMate(board, whiteDanger, blackDanger, 1);

        if (gameOver == true) {
            cout << "CHECKMATE CHECKMATE CHECKMATE" << endl;
        }

        legal(board, whiteDanger, blackDanger);
        turn++;

    }

        gameOver = checkMate(board, whiteDanger, blackDanger, 2);

        if (gameOver == true) {
            cout << "CHECKMATE CHECKMATE CHECKMATE" << endl;
        }

    return turn;

}

int main() {
    int board[8][8];
    int tempBoard[8][8];
    int whiteDanger[8][8];
    int blackDanger[8][8];
    int turn = 1;

    setPawns(board);
    setNonPawns(board);
    setBlank(board);

    while (true) {
        printBoard(board);
        turn = chooseMove(board, tempBoard, whiteDanger, blackDanger, turn);
    }
}
