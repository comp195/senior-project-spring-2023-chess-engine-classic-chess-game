#include <iostream>
#include <utility>
#include "header1.h"
using namespace std;

void checkTiles(int board[][8], int whiteDanger[][8], int blackDanger[][8]) {


    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            whiteDanger[x][y] = 0;
            blackDanger[x][y] = 0;
        }
    }

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            int i = 1;
            int j = 1;
            switch (board[x][y]) {
            case blank:
                //cout << "Invalid Piece" << endl;
                break;
            case WPawn:
                if (y - 1 >= 0) {
                    whiteDanger[x - 1][y - 1] = 1;
                }
                if (y + 1 <= 7) {
                    whiteDanger[x - 1][y + 1] = 1;
                }
                break;
            case BPawn:
                if (y - 1 >= 0) {
                    blackDanger[x + 1][y - 1] = 1;
                }
                if (y + 1 <= 7) {
                    blackDanger[x + 1][y + 1] = 1;
                }
                break;
            case WKnight:
                if ((x + 1 <= 7) && (y + 2 <= 7)) {
                    whiteDanger[x + 1][y + 2] = 1;
                }
                if (x + 1 <= 7 && y - 2 >= 0) {
                    whiteDanger[x + 1][y - 2] = 1;
                }
                if (x - 1 >= 0 && y + 2 <= 7) {
                    whiteDanger[x - 1][y + 2] = 1;
                }
                if (x - 1 >= 0 && y - 2 >= 0) {
                    whiteDanger[x - 1][y - 2] = 1;
                }

                if (x + 2 <= 7 && y + 1 <= 7) {
                    whiteDanger[x + 2][y + 1] = 1;
                }
                if (x + 2 <= 7 && y - 1 >= 0) {
                    whiteDanger[x + 2][y - 1] = 1;
                }
                if (x - 2 >= 0 && y + 1 <= 7) {
                    whiteDanger[x - 2][y + 1] = 1;
                }
                if (x - 2 >= 0 && y - 1 >= 0) {
                    whiteDanger[x - 2][y - 1] = 1;
                }

                break;
            case BKnight:
                if ((x + 1 <= 7) && (y + 2 <= 7)) {
                    blackDanger[x + 1][y + 2] = 1;
                }
                if (x + 1 <= 7 && y - 2 >= 0) {
                    blackDanger[x + 1][y - 2] = 1;
                }
                if (x - 1 >= 0 && y + 2 <= 7) {
                    blackDanger[x - 1][y + 2] = 1;
                }
                if (x - 1 >= 0 && y - 2 >= 0) {
                    blackDanger[x - 1][y - 2] = 1;
                }

                if (x + 2 <= 7 && y + 1 <= 7) {
                    blackDanger[x + 2][y + 1] = 1;
                }
                if (x + 2 <= 7 && y - 1 >= 0) {
                    blackDanger[x + 2][y - 1] = 1;
                }
                if (x - 2 >= 0 && y + 1 <= 7) {
                    blackDanger[x - 2][y + 1] = 1;
                }
                if (x - 2 >= 0 && y - 1 >= 0) {
                    blackDanger[x - 2][y - 1] = 1;
                }
                break;
            case WBishop:    //white bishop
                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    whiteDanger[x + i][y + j] = 1;
                    i++;
                    j++;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    whiteDanger[x + i][y + j] = 1;
                }
                i = -1, j = 1;

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    whiteDanger[x + i][y + j] = 1;
                    i--;
                    j++;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    whiteDanger[x + i][y + j] = 1;
                }
                i = 1, j = -1;

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    whiteDanger[x + i][y + j] = 1;
                    i++;
                    j--;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    whiteDanger[x + i][y + j] = 1;
                }
                i = -1, j = -1;

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    whiteDanger[x + i][y + j] = 1;
                    i--;
                    j--;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    whiteDanger[x + i][y + j] = 1;
                }

                break;


            case BBishop:  //black bishop
                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    blackDanger[x + i][y + j] = 1;
                    i++;
                    j++;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    blackDanger[x + i][y + j] = 1;
                }
                i = -1, j = 1;

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    blackDanger[x + i][y + j] = 1;
                    i--;
                    j++;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    blackDanger[x + i][y + j] = 1;
                }
                i = 1, j = -1;

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    blackDanger[x + i][y + j] = 1;
                    i++;
                    j--;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    blackDanger[x + i][y + j] = 1;
                }
                i = -1, j = -1;

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    blackDanger[x + i][y + j] = 1;
                    i--;
                    j--;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    blackDanger[x + i][y + j] = 1;
                }

                break;
            case WRook:
                //cout << "Coordinates are (" << x << ", " << y << ")" << endl;

                while (x + i <= 7 && board[x + i][y] == blank) {
                    whiteDanger[x + i][y] = 1;
                    i++;
                }
                if (x + i <= 7) {
                    whiteDanger[x + i][y] = 1;
                }
                i = 1;

                while (y + i <= 7 && board[x][y + i] == blank) {
                    whiteDanger[x][y + i] = 1;
                    i++;
                }
                if (y + i <= 7) {
                    whiteDanger[x][y + i] = 1;
                }
                i = -1;

                while (x + i >= 0 && board[x + i][y] == blank) {
                    whiteDanger[x + i][y] = 1;
                    i--;
                }
                if (x + i >= 0) {
                    whiteDanger[x + i][y] = 1;
                }
                i = -1;

                while (y + i >= 0 && board[x][y + i] == blank) {
                    whiteDanger[x][y + i] = 1;
                    i--;
                }
                if (y + i >= 0) {
                    whiteDanger[x][y + i] = 1;
                }


                break;
            case BRook:

                while (x + i <= 7 && board[x + i][y] == blank) {
                    blackDanger[x + i][y] = 1;
                    i++;
                }
                if (x + i <= 7) {
                    blackDanger[x + i][y] = 1;
                }
                i = 1;

                while (y + i <= 7 && board[x][y + i] == blank) {
                    blackDanger[x][y + i] = 1;
                    i++;
                }
                if (y + i <= 7) {
                    blackDanger[x][y + i] = 1;
                }
                i = -1;

                while (x + i >= 0 && board[x + i][y] == blank) {
                    blackDanger[x + i][y] = 1;
                    i--;
                }
                if (x + i >= 0) {
                    blackDanger[x + i][y] = 1;
                }
                i = -1;

                while (y + i >= 0 && board[x][y + i] == blank) {
                    blackDanger[x][y + i] = 1;
                    i--;
                }
                if (y + i >= 0) {
                    blackDanger[x][y + i] = 1;
                }

                break;
            case WQueen:

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    whiteDanger[x + i][y + j] = 1;
                    i++;
                    j++;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    whiteDanger[x + i][y + j] = 1;
                }
                i = -1, j = 1;

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    whiteDanger[x + i][y + j] = 1;
                    i--;
                    j++;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    whiteDanger[x + i][y + j] = 1;
                }
                i = 1, j = -1;

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    whiteDanger[x + i][y + j] = 1;
                    i++;
                    j--;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    whiteDanger[x + i][y + j] = 1;
                }
                i = -1, j = -1;

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    whiteDanger[x + i][y + j] = 1;
                    i--;
                    j--;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    whiteDanger[x + i][y + j] = 1;
                }

                while (x + i <= 7 && board[x + i][y] == blank) {
                    whiteDanger[x + i][y] = 1;
                    i++;
                }
                if (x + i <= 7) {
                    whiteDanger[x + i][y] = 1;
                }
                i = 1;

                while (y + i <= 7 && board[x][y + i] == blank) {
                    whiteDanger[x][y + i] = 1;
                    i++;
                }
                if (y + i <= 7) {
                    whiteDanger[x][y + i] = 1;
                }
                i = -1;

                while (x + i >= 0 && board[x + i][y] == blank) {
                    whiteDanger[x + i][y] = 1;
                    i--;
                }
                if (x + i >= 0) {
                    whiteDanger[x + i][y] = 1;
                }
                i = -1;

                while (y + i >= 0 && board[x][y + i] == blank) {
                    whiteDanger[x][y + i] = 1;
                    i--;
                }
                if (y + i >= 0) {
                    whiteDanger[x][y + i] = 1;
                }

                break;
            case BQueen:

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    blackDanger[x + i][y + j] = 1;
                    i++;
                    j++;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    blackDanger[x + i][y + j] = 1;
                }
                i = -1, j = 1;

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    blackDanger[x + i][y + j] = 1;
                    i--;
                    j++;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    blackDanger[x + i][y + j] = 1;
                }
                i = 1, j = -1;

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    blackDanger[x + i][y + j] = 1;
                    i++;
                    j--;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    blackDanger[x + i][y + j] = 1;
                }
                i = -1, j = -1;

                while (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7 && board[x + i][y + j] == blank) {
                    blackDanger[x + i][y + j] = 1;
                    i--;
                    j--;
                }
                if (x + i >= 0 && x + i <= 7 && y + j >= 0 && y + j <= 7) {
                    blackDanger[x + i][y + j] = 1;
                }

                while (x + i <= 7 && board[x + i][y] == blank) {
                    blackDanger[x + i][y] = 1;
                    i++;
                }
                if (x + i <= 7) {
                    blackDanger[x + i][y] = 1;
                }
                i = 1;

                while (y + i <= 7 && board[x][y + i] == blank) {
                    blackDanger[x][y + i] = 1;
                    i++;
                }
                if (y + i <= 7) {
                    blackDanger[x][y + i] = 1;
                }
                i = -1;

                while (x + i >= 0 && board[x + i][y] == blank) {
                    blackDanger[x + i][y] = 1;
                    i--;
                }
                if (x + i >= 0) {
                    blackDanger[x + i][y] = 1;
                }
                i = -1;

                while (y + i >= 0 && board[x][y + i] == blank) {
                    blackDanger[x][y + i] = 1;
                    i--;
                }
                if (y + i >= 0) {
                    blackDanger[x][y + i] = 1;
                }

                break;
            case WKing:
                if ((x + 1 <= 7) && (y + 1 <= 7)) {
                    whiteDanger[x + 1][y + 1] = 1;
                }
                if ((x + 1 <= 7) && (y - 1 >= 0)) {
                    whiteDanger[x + 1][y - 1] = 1;
                }
                if ((x - 1 >= 0) && (y + 1 <= 7)) {
                    whiteDanger[x - 1][y + 1] = 1;
                }
                if ((x - 1 >= 0) && (y - 1 >= 0)) {
                    whiteDanger[x - 1][y - 1] = 1;
                }
                if (x - 1 >= 0) {
                    whiteDanger[x - 1][y] = 1;
                }
                if (x + 1 <= 7) {
                    whiteDanger[x + 1][y] = 1;
                }
                if (y - 1 >= 0) {
                    whiteDanger[x][y - 1] = 1;
                }
                if (y + 1 <= 7) {
                    whiteDanger[x][y + 1] = 1;
                }
                break;
            case BKing:
                if ((x + 1 <= 7) && (y + 1 <= 7)) {
                    blackDanger[x + 1][y + 1] = 1;
                }
                if ((x + 1 <= 7) && (y - 1 >= 0)) {
                    blackDanger[x + 1][y - 1] = 1;
                }
                if ((x - 1 >= 0) && (y + 1 <= 7)) {
                    blackDanger[x - 1][y + 1] = 1;
                }
                if ((x - 1 >= 0) && (y - 1 >= 0)) {
                    blackDanger[x - 1][y - 1] = 1;
                }
                if (x - 1 >= 0) {
                    blackDanger[x - 1][y] = 1;
                }
                if (x + 1 <= 7) {
                    blackDanger[x + 1][y] = 1;
                }
                if (y - 1 >= 0) {
                    blackDanger[x][y - 1] = 1;
                }
                if (y + 1 <= 7) {
                    blackDanger[x][y + 1] = 1;
                }
                break;
            }
        }
    }

}

bool checkMate(int board[][8], int whiteDanger[][8], int blackDanger[][8], int color) {
    int tempBoard[8][8];
    bool result = false;
    bool inCheck = true;
    int KingX, KingY;

    if (color == 2) {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                for (int a = 0; a < 8; a++) {
                    for (int b = 0; b < 8; b++) {

                        for (int i = 0; i < 8; i++) {
                            for (int j = 0; j < 8; j++) {
                                tempBoard[i][j] = board[i][j];
                            }
                        }

                        switch (board[x][y]) {

                        case WPawn:
                            result = movePawn(x, y, a, b, board);

                            if (result == true) {
                                tempBoard[a][b] = tempBoard[x][y];
                                tempBoard[x][y] = blank;

                                checkTiles(tempBoard, whiteDanger, blackDanger);

                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (tempBoard[i][j] == WKing) {
                                            KingX = i;
                                            KingY = j;
                                        }
                                    }
                                }

                                if (blackDanger[KingX][KingY] == 0) {
                                    //cout << "Can be saved by (" << x << "," << y << ") to (" << a << "," << b << ")" << endl;
                                    return false;
                                }
                            }

                            break;

                        case WKnight:
                            result = moveKnight(x, y, a, b, board);

                            if (result == true) {
                                tempBoard[a][b] = tempBoard[x][y];
                                tempBoard[x][y] = blank;

                                checkTiles(tempBoard, whiteDanger, blackDanger);

                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (tempBoard[i][j] == WKing) {
                                            KingX = i;
                                            KingY = j;
                                        }
                                    }
                                }

                                if (blackDanger[KingX][KingY] == 0) {
                                    //cout << "Can be saved by (" << x << "," << y << ") to (" << a << "," << b << ")" << endl;
                                    return false;
                                }
                            }

                            break;

                        case WBishop:
                            result = moveBishop(x, y, a, b, board);

                            if (result == true) {
                                tempBoard[a][b] = tempBoard[x][y];
                                tempBoard[x][y] = blank;

                                checkTiles(tempBoard, whiteDanger, blackDanger);

                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (tempBoard[i][j] == WKing) {
                                            KingX = i;
                                            KingY = j;
                                        }
                                    }
                                }

                                if (blackDanger[KingX][KingY] == 0) {
                                    //cout << "Can be saved by (" << x << "," << y << ") to (" << a << "," << b << ")" << endl;
                                    return false;
                                }
                            }

                            break;

                        case WRook:
                            result = moveRook(x, y, a, b, board);

                            if (result == true) {
                                tempBoard[a][b] = tempBoard[x][y];
                                tempBoard[x][y] = blank;

                                checkTiles(tempBoard, whiteDanger, blackDanger);

                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (tempBoard[i][j] == WKing) {
                                            KingX = i;
                                            KingY = j;
                                        }
                                    }
                                }

                                if (blackDanger[KingX][KingY] == 0) {
                                    //cout << "Can be saved by (" << x << "," << y << ") to (" << a << "," << b << ")" << endl;
                                    return false;
                                }
                            }

                            break;

                        case WQueen:
                            result = moveBishop(x, y, a, b, board);
                            if (result == false) {
                                result = moveRook(x, y, a, b, board);
                            }

                            if (result == true) {
                                tempBoard[a][b] = tempBoard[x][y];
                                tempBoard[x][y] = blank;

                                checkTiles(tempBoard, whiteDanger, blackDanger);

                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (tempBoard[i][j] == WKing) {
                                            KingX = i;
                                            KingY = j;
                                        }
                                    }
                                }

                                if (blackDanger[KingX][KingY] == 0) {
                                    //cout << "Can be saved by (" << x << "," << y << ") to (" << a << "," << b << ")" << endl;
                                    return false;
                                }
                            }

                            break;

                        case WKing:
                            result = moveKing(x, y, a, b, board);

                            if (result == true) {
                                tempBoard[a][b] = tempBoard[x][y];
                                tempBoard[x][y] = blank;

                                checkTiles(tempBoard, whiteDanger, blackDanger);

                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (tempBoard[i][j] == WKing) {
                                            KingX = i;
                                            KingY = j;
                                        }
                                    }
                                }

                                if (blackDanger[KingX][KingY] == 0) {
                                    //cout << "Can be saved by (" << x << "," << y << ") to (" << a << "," << b << ")" << endl;
                                    return false;
                                }
                            }

                            break;

                        }
                    }
                }
            }
        }
        cout << "Checkmate" << endl;
        return true;
    }
    else {
        for (int x = 0; x < 8; x++) {
            for (int y = 0; y < 8; y++) {
                for (int a = 0; a < 8; a++) {
                    for (int b = 0; b < 8; b++) {

                        for (int i = 0; i < 8; i++) {
                            for (int j = 0; j < 8; j++) {
                                tempBoard[i][j] = board[i][j];
                            }
                        }

                        switch (board[x][y]) {

                        case BPawn:
                            result = movePawn(x, y, a, b, board);

                            if (result == true) {
                                tempBoard[a][b] = tempBoard[x][y];
                                tempBoard[x][y] = blank;

                                checkTiles(tempBoard, whiteDanger, blackDanger);

                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (tempBoard[i][j] == BKing) {
                                            KingX = i;
                                            KingY = j;
                                        }
                                    }
                                }

                                if (whiteDanger[KingX][KingY] == 0) {
                                    //cout << "Can be saved by (" << x << "," << y << ") to (" << a << "," << b << ")" << endl;
                                    return false;
                                }
                            }

                            break;

                        case BKnight:
                            result = moveKnight(x, y, a, b, board);

                            if (result == true) {
                                tempBoard[a][b] = tempBoard[x][y];
                                tempBoard[x][y] = blank;

                                checkTiles(tempBoard, whiteDanger, blackDanger);

                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (tempBoard[i][j] == BKing) {
                                            KingX = i;
                                            KingY = j;
                                        }
                                    }
                                }

                                if (whiteDanger[KingX][KingY] == 0) {
                                    //cout << "Can be saved by (" << x << "," << y << ") to (" << a << "," << b << ")" << endl;
                                    return false;
                                }
                            }

                            break;

                        case BBishop:
                            result = moveBishop(x, y, a, b, board);

                            if (result == true) {
                                tempBoard[a][b] = tempBoard[x][y];
                                tempBoard[x][y] = blank;

                                checkTiles(tempBoard, whiteDanger, blackDanger);

                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (tempBoard[i][j] == BKing) {
                                            KingX = i;
                                            KingY = j;
                                        }
                                    }
                                }

                                if (whiteDanger[KingX][KingY] == 0) {
                                    //cout << "Can be saved by (" << x << "," << y << ") to (" << a << "," << b << ")" << endl;
                                    return false;
                                }
                            }

                            break;

                        case BRook:
                            result = moveRook(x, y, a, b, board);

                            if (result == true) {
                                tempBoard[a][b] = tempBoard[x][y];
                                tempBoard[x][y] = blank;

                                checkTiles(tempBoard, whiteDanger, blackDanger);

                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (tempBoard[i][j] == BKing) {
                                            KingX = i;
                                            KingY = j;
                                        }
                                    }
                                }

                                if (whiteDanger[KingX][KingY] == 0) {
                                    //cout << "Can be saved by (" << x << "," << y << ") to (" << a << "," << b << ")" << endl;
                                    return false;
                                }
                            }

                            break;

                        case BQueen:
                            result = moveBishop(x, y, a, b, board);
                            if (result == false) {
                                result = moveRook(x, y, a, b, board);
                            }

                            if (result == true) {
                                tempBoard[a][b] = tempBoard[x][y];
                                tempBoard[x][y] = blank;

                                checkTiles(tempBoard, whiteDanger, blackDanger);

                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (tempBoard[i][j] == BKing) {
                                            KingX = i;
                                            KingY = j;
                                        }
                                    }
                                }

                                if (whiteDanger[KingX][KingY] == 0) {
                                    //cout << "Can be saved by (" << x << "," << y << ") to (" << a << "," << b << ")" << endl;
                                    return false;
                                }
                            }

                            break;

                        case BKing:
                            result = moveKing(x, y, a, b, board);

                            if (result == true) {
                                tempBoard[a][b] = tempBoard[x][y];
                                tempBoard[x][y] = blank;

                                checkTiles(tempBoard, whiteDanger, blackDanger);

                                for (int i = 0; i < 8; i++) {
                                    for (int j = 0; j < 8; j++) {
                                        if (tempBoard[i][j] == BKing) {
                                            KingX = i;
                                            KingY = j;
                                        }
                                    }
                                }

                                if (whiteDanger[KingX][KingY] == 0) {
                                    //cout << "Can be saved by (" << x << "," << y << ") to (" << a << "," << b << ")" << endl;
                                    return false;
                                }
                            }

                            break;

                        }
                    }
                }
            }
            cout << "loop" << endl;
        }
        cout << "Checkmate" << endl;
        return true;
    }
}