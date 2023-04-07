#include <iostream>
#include "header.h"
using namespace std;


class Piece {
public:

};


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

void chooseMove(int board[][8]) {
    int x, y, a, b;
    cin >> x;
    cin >> y;
    cin >> a;
    cin >> b;

    switch (board[x][y]) {
    case blank:
        cout << "Invalid Piece" << endl;
        break;
    case WPawn:
        movePawn(x, y, a, b, board);
        break;
    case BPawn:
        movePawn(x, y, a, b, board);
        break;
    case WKnight:
        moveKnight(x, y, a, b, board);
        break;
    case BKnight:
        moveKnight(x, y, a, b, board);
        break;
    case WBishop:
        moveBishop(x, y, a, b, board);
        break;
    case BBishop:
        moveBishop(x, y, a, b, board);
        break;
    case WRook:
        moveRook(x, y, a, b, board);
        break;
    case BRook:
        moveRook(x, y, a, b, board);
        break;
    case WQueen:
        moveBishop(x, y, a, b, board);
        moveRook(x, y, a, b, board);
        break;
    case BQueen:
        moveBishop(x, y, a, b, board);
        moveRook(x, y, a, b, board);
        break;
    case WKing:
        moveKing(x, y, a, b, board);
        break;
    case BKing:
        moveKing(x, y, a, b, board);
        break;
    }

    //checkTiles(board);

}

int main() {
    int board[8][8];
    setPawns(board);
    setNonPawns(board);
    setBlank(board);

    while (true) {
        printBoard(board);
        chooseMove(board);
    }
}
