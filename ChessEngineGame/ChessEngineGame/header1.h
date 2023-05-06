#pragma once
#include <iostream>
using namespace std;

enum piece {
    WPawn, WKnight, WBishop, WRook, WQueen, WKing, //0-5
    blank,                                         //6
    BPawn, BKnight, BBishop, BRook, BQueen, BKing  //7-12
};


bool movePawn(int x, int y, int a, int b, int board[][8]);
bool moveKnight(int x, int y, int a, int b, int board[][8]);
bool moveBishop(int x, int y, int a, int b, int board[][8]);
bool moveRook(int x, int y, int a, int b, int board[][8]);
bool moveKing(int x, int y, int a, int b, int board[][8]);

void checkTiles(int board[][8], int whiteDanger[][8], int blackDanger[][8]);
bool checkMate(int board[][8], int whiteDanger[][8], int blackDanger[][8], int color);

void legal(int board[][8], int whiteDanger[][8], int blackDanger[][8]);
int legalJump(int board[][8], int whiteDanger[][8], int blackDanger[][8], int x, int y, int a, int b);