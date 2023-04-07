#pragma once
#include <iostream>
using namespace std;

enum piece {
    WPawn, WKnight, WBishop, WRook, WQueen, WKing,
    blank,
    BPawn, BKnight, BBishop, BRook, BQueen, BKing
};


void movePawn(int x, int y, int a, int b, int board[][8]);
void moveKnight(int x, int y, int a, int b, int board[][8]);
void moveBishop(int x, int y, int a, int b, int board[][8]);
void moveRook(int x, int y, int a, int b, int board[][8]);
void moveKing(int x, int y, int a, int b, int board[][8]);

void checkTiles(int board[][8]);
