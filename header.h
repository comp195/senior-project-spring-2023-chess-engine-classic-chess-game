#pragma once
#include <iostream>
using namespace std;

enum piece {
    WPawn, WKnight, WBishop, WRook, WQueen, WKing,
    blank,
    BPawn, BKnight, BBishop, BRook, BQueen, BKing
};


bool movePawn(int x, int y, int a, int b, int board[][8]);
bool moveKnight(int x, int y, int a, int b, int board[][8]);
bool moveBishop(int x, int y, int a, int b, int board[][8]);
bool moveRook(int x, int y, int a, int b, int board[][8]);
bool moveKing(int x, int y, int a, int b, int board[][8]);

void checkTiles(int board[][8], int whiteDanger[][8], int blackDanger[][8]);
bool checkMate(int board[][8], int whiteDanger[][8], int blackDanger[][8], int color);
