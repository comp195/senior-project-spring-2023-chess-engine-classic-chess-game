#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "header.h"
using namespace std;

struct legalMoves {
    pair<int, int> start_pos;
    pair<int, int> end_pos;

    legalMoves(int x, int y, int a, int b) {
        start_pos = make_pair(x, y);
        end_pos = make_pair(a, b);
    }
};


void legal(int board[][8], int whiteDanger[][8], int blackDanger[][8]) {
    vector<legalMoves> moves;
    srand(time(0));

    int tempBoard[8][8];
    bool result = false;
    bool inCheck = true;
    int KingX, KingY;
    int pointDiff, topX, topY, topA, topB;
    int bestPoints = -999;

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
                                moves.emplace_back(x, y, a, b);
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
                                moves.emplace_back(x, y, a, b);
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
                                moves.emplace_back(x, y, a, b);
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
                                moves.emplace_back(x, y, a, b);
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
                                moves.emplace_back(x, y, a, b);
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
                                moves.emplace_back(x, y, a, b);
                            }
                        }

                        break;

                    }
                }
            }
        }
    }

    for (const legalMoves& move : moves) {
        pointDiff = legalJump(board, whiteDanger, blackDanger, move.start_pos.first, move.start_pos.second, move.end_pos.first, move.end_pos.second);

        //cout << pointDiff << " Start pos: (" << move.start_pos.first << ", " << move.start_pos.second << "). End pos: (" << move.end_pos.first << ", " << move.end_pos.second << ")" << endl;
        if (pointDiff > bestPoints) {
            bestPoints = pointDiff;
            topX = move.start_pos.first;
            topY = move.start_pos.second;
            topA = move.end_pos.first;
            topB = move.end_pos.second;
        }
        else if (pointDiff == bestPoints) {
            int randomNum = rand() % 10 + 1;
            cout << randomNum << endl;
            if (randomNum < 4) {
                bestPoints = pointDiff;
                topX = move.start_pos.first;
                topY = move.start_pos.second;
                topA = move.end_pos.first;
                topB = move.end_pos.second;
            }
        }
    }

    board[topA][topB] = board[topX][topY];
    board[topX][topY] = blank;

}

int legalJump(int board[][8], int whiteDanger[][8], int blackDanger[][8], int newX, int newY, int newA, int newB) {
    vector<legalMoves> secondMoves;

    int blackPoints = 0;
    int whitePoints = 0;
    int worstPoints = 100000;
    int totalPoints;
    int tempBoard[8][8];
    bool result = false;
    bool inCheck = true;
    int KingX, KingY;

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            for (int a = 0; a < 8; a++) {
                for (int b = 0; b < 8; b++) {

                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {
                            tempBoard[i][j] = board[i][j];
                        }
                    }

                    tempBoard[newA][newB] = tempBoard[newX][newY];
                    tempBoard[newX][newY] = blank;

                    switch (tempBoard[x][y]) {

                    case WPawn:
                        result = movePawn(x, y, a, b, tempBoard);

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
                                secondMoves.emplace_back(x, y, a, b);
                            }
                        }

                        break;

                    case WKnight:
                        result = moveKnight(x, y, a, b, tempBoard);

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
                                secondMoves.emplace_back(x, y, a, b);
                            }
                        }

                        break;

                    case WBishop:
                        result = moveBishop(x, y, a, b, tempBoard);

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
                                secondMoves.emplace_back(x, y, a, b);
                            }
                        }

                        break;

                    case WRook:
                        result = moveRook(x, y, a, b, tempBoard);

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
                                secondMoves.emplace_back(x, y, a, b);
                            }
                        }

                        break;

                    case WQueen:
                        result = moveBishop(x, y, a, b, tempBoard);
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
                                secondMoves.emplace_back(x, y, a, b);
                            }
                        }

                        break;

                    case WKing:
                        result = moveKing(x, y, a, b, tempBoard);

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
                                secondMoves.emplace_back(x, y, a, b);
                            }
                        }

                        break;

                    }
                }
            }
        }
    }

    for (const legalMoves& move : secondMoves) {

        for (int p = 0; p < 8; p++) {
            for (int q = 0; q < 8; q++) {
                tempBoard[p][q] = board[p][q];
            }
        }

        tempBoard[newA][newB] = tempBoard[newX][newY];
        tempBoard[newX][newY] = blank;
        tempBoard[move.end_pos.first][move.end_pos.second] = tempBoard[move.start_pos.first][move.start_pos.second];
        tempBoard[move.start_pos.first][move.start_pos.second] = blank;

        whitePoints = 0;
        blackPoints = 0;

        for (int p = 0; p < 8; p++) {
            for (int q = 0; q < 8; q++) {
                switch (tempBoard[p][q]) {

                case WPawn:
                    whitePoints++;
                    break;

                case WKnight:
                    whitePoints = whitePoints + 3;
                    break;

                case WBishop:
                    whitePoints = whitePoints + 3;
                    break;

                case WRook:
                    whitePoints = whitePoints + 5;
                    break;

                case WQueen:
                    whitePoints = whitePoints + 9;
                    break;

                case WKing:
                    whitePoints = whitePoints + 1000;
                    break;

                case BPawn:
                    blackPoints++;
                    break;

                case BKnight:
                    blackPoints = blackPoints + 3;
                    break;

                case BBishop:
                    blackPoints = blackPoints + 3;
                    break;

                case BRook:
                    blackPoints = blackPoints + 5;
                    break;

                case BQueen:
                    blackPoints = blackPoints + 9;
                    break;

                case BKing:
                    blackPoints = blackPoints + 1000;
                    break;
                }


            }
        }

        totalPoints = blackPoints - whitePoints;
        if (totalPoints < worstPoints) {
            worstPoints = totalPoints;
        }

    }


    return worstPoints;

}
