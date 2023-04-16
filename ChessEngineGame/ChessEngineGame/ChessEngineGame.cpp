// ChessEngineGame.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "ChessEngineGame.h"
#include "header1.h"
#include <cmath>

#define MAX_LOADSTRING 100
#define IDC_BUTTON 1001



//each square is 80 pixels
const int SpaceSize = 80;



// Global Variables: 
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT                 blackRook1_X, blackRook1_Y, blackKnight1_X, blackKnight1_Y, blackBishop1_Y, blackBishop1_X,
                    blackKing_X, blackKing_Y, blackQueen_X, blackQueen_Y,
                    blackRook2_X, blackRook2_Y, blackKnight2_X, blackKnight2_Y, blackBishop2_Y, blackBishop2_X,
                    blackPawn1_X, blackPawn1_Y, blackPawn2_X, blackPawn2_Y, blackPawn3_X, blackPawn3_Y, blackPawn4_X, blackPawn4_Y,
                    blackPawn5_X, blackPawn5_Y, blackPawn6_X, blackPawn6_Y, blackPawn7_X, blackPawn7_Y, blackPawn8_X, blackPawn8_Y,
                    orangeRook1_X, orangeRook1_Y, orangeKnight1_X, orangeKnight1_Y, orangeBishop1_Y, orangeBishop1_X,
                    orangeKing_X, orangeKing_Y, orangeQueen_X, orangeQueen_Y,
                    orangeRook2_X, orangeRook2_Y, orangeKnight2_X, orangeKnight2_Y, orangeBishop2_Y, orangeBishop2_X,
                    orangePawn1_X, orangePawn1_Y, orangePawn2_X, orangePawn2_Y, orangePawn3_X, orangePawn3_Y, orangePawn4_X, orangePawn4_Y,
                    orangePawn5_X, orangePawn5_Y, orangePawn6_X, orangePawn6_Y, orangePawn7_X, orangePawn7_Y, orangePawn8_X, orangePawn8_Y;

BOOL                blackRook1_Exist, blackKnight1_Exist, blackBishop1_Exist, 
                    blackKing_Exist, blackQueen_Exist,
                    blackRook2_Exist, blackKnight2_Exist, blackBishop2_Exist, blackPawn1_Exist, blackPawn2_Exist, blackPawn3_Exist,
                    blackPawn4_Exist, blackPawn5_Exist, blackPawn6_Exist, blackPawn7_Exist, blackPawn8_Exist,
                    orangeRook1_Exist, orangeKnight1_Exist, orangeBishop1_Exist,
                    orangeKing_Exist, orangeQueen_Exist,
                    orangeRook2_Exist, orangeKnight2_Exist, orangeBishop2_Exist, orangePawn1_Exist, orangePawn2_Exist, orangePawn3_Exist,
                    orangePawn4_Exist, orangePawn5_Exist, orangePawn6_Exist, orangePawn7_Exist, orangePawn8_Exist;
void AddControls(HWND);
void loadImages();
void setBoard(int[][8]);
bool chooseMove(int, int, int, int, int[][8]);
INT board[8][8];

HWND hButton, hLayout, hKing, blackRook1, blackKnight1, blackBishop1, blackRook2, blackKnight2, blackBishop2, blackKing, blackQueen,
     blackPawn1, blackPawn2, blackPawn3, blackPawn4, blackPawn5, blackPawn6, blackPawn7, blackPawn8, orangeRook1, orangeKnight1, orangeBishop1, orangeRook2, orangeKnight2, orangeBishop2, orangeKing, orangeQueen,
    orangePawn1, orangePawn2, orangePawn3, orangePawn4, orangePawn5, orangePawn6, orangePawn7, orangePawn8;

HBITMAP hBoardImage, hKingImage, BlackKingImage, BlackQueenImage, BlackRookImage, BlackKnightImage, BlackBishopImage, BlackPawnImage,
        OrangeKingImage, OrangeQueenImage, OrangeRookImage, OrangeKnightImage, OrangeBishopImage, OrangePawnImage;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);


    // TODO: Place code here.

    setBoard(board);


    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_CHESSENGINEGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    
    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CHESSENGINEGAME));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHESSENGINEGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CHESSENGINEGAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
    
    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


void DrawBoard(HDC hdc)
{
    HPEN hPenOld;
    HPEN hLinePen;
    COLORREF qLineColor;
    qLineColor = RGB(8, 25, 10);
    hLinePen = CreatePen(PS_SOLID, 1, qLineColor);
    hPenOld = (HPEN)SelectObject(hdc, hLinePen);

    MoveToEx(hdc, 8 * SpaceSize, 0, NULL);
    LineTo(hdc, 8 * SpaceSize, 8 * SpaceSize);
    MoveToEx(hdc, 0, 8 * SpaceSize, NULL);
    LineTo(hdc, 8 * SpaceSize, 8 * SpaceSize);

    for (int iX = SpaceSize; iX < 8 * SpaceSize; iX += SpaceSize) {
        MoveToEx(hdc, iX, 0, NULL);
        LineTo(hdc, iX, 8 * SpaceSize);
   }

    for (int iY = SpaceSize; iY < 8 * SpaceSize; iY += SpaceSize) {
        MoveToEx(hdc, 0, iY, NULL);
        LineTo(hdc, 8 * SpaceSize, iY);
    }

    SelectObject(hdc, hPenOld);
    DeleteObject(hLinePen);

}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{        


    switch (message)
    {
    
    case WM_LBUTTONDOWN:
    {
        // extract coordinates of mouse when mouse is left clicked
        int iPosX = LOWORD(lParam);
        int iPosY = HIWORD(lParam);

        //If the piece does not exist, place it at location if inside of the board
        if (!blackRook1_Exist && iPosX < SpaceSize*8 && iPosY < SpaceSize*8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackRook1_X - 5) / 80);
            int yOri = ((blackRook1_Y - 5) / 80);
            if(chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackRook1_X = iPosX;
                blackRook1_Y = iPosY;
            }

            BlackRookImage = (HBITMAP)LoadImageW(NULL, L"images/rookpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackRook1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackRook1_X, blackRook1_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackRook1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackRookImage);
            blackRook1_Exist = true;
            break;
        }
        if (!blackRook2_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackRook2_X - 5) / 80);
            int yOri = ((blackRook2_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackRook2_X = iPosX;
                blackRook2_Y = iPosY;
            }

            BlackRookImage = (HBITMAP)LoadImageW(NULL, L"images/rookpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackRook2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackRook2_X, blackRook2_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackRook2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackRookImage);
            blackRook2_Exist = true;
            break;
        }
        if (!blackKnight2_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackKnight2_X - 5) / 80);
            int yOri = ((blackKnight2_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackKnight2_X = iPosX;
                blackKnight2_Y = iPosY;
            }
            BlackKnightImage = (HBITMAP)LoadImageW(NULL, L"images/knightpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackKnight2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackKnight2_X, blackKnight2_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackKnight2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackKnightImage);
            blackKnight2_Exist = true;
            break;
        }
        if (!blackKnight1_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackKnight1_X - 5) / 80);
            int yOri = ((blackKnight1_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackKnight1_X = iPosX;
                blackKnight1_Y = iPosY;
            }
            BlackKnightImage = (HBITMAP)LoadImageW(NULL, L"images/knightpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackKnight1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackKnight1_X, blackKnight1_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackKnight1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackKnightImage);
            break;
        }
        if (!blackBishop2_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackBishop2_X - 5) / 80);
            int yOri = ((blackBishop2_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackBishop2_X = iPosX;
                blackBishop2_Y = iPosY;
            }
            BlackBishopImage = (HBITMAP)LoadImageW(NULL, L"images/bishoppiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackBishop2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackBishop2_X, blackBishop2_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackBishop2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackBishopImage);
            blackBishop2_Exist = true;
            break;
        }
        if (!blackBishop1_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackBishop1_X - 5) / 80);
            int yOri = ((blackBishop1_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackBishop1_X = iPosX;
                blackBishop1_Y = iPosY;
            }
            BlackBishopImage = (HBITMAP)LoadImageW(NULL, L"images/bishoppiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackBishop1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackBishop1_X, blackBishop1_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackBishop1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackBishopImage);
            blackBishop1_Exist = true;
            break;
        }
        if (!blackKing_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackKing_X - 5) / 80);
            int yOri = ((blackKing_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackKing_X = iPosX;
                blackKing_Y = iPosY;
            }
            BlackKingImage = (HBITMAP)LoadImageW(NULL, L"images/kingpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackKing = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackKing_X, blackKing_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackKing, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackKingImage);
            blackKing_Exist = true;
            break;
        }
        if (!blackQueen_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackQueen_X - 5) / 80);
            int yOri = ((blackQueen_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackQueen_X = iPosX;
                blackQueen_Y = iPosY;
            }
            BlackQueenImage = (HBITMAP)LoadImageW(NULL, L"images/queenpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackQueen = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackQueen_X, blackQueen_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackQueen, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackQueenImage);
            blackQueen_Exist = true;
            break;
        }
        if (!blackPawn1_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackPawn1_X - 5) / 80);
            int yOri = ((blackPawn1_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackPawn1_X = iPosX;
                blackPawn1_Y = iPosY;
            }
            BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackPawn1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn1_X, blackPawn1_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackPawn1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);
            blackPawn1_Exist = true;
            break;
        }
        if (!blackPawn2_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackPawn2_X - 5) / 80);
            int yOri = ((blackPawn2_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackPawn2_X = iPosX;
                blackPawn2_Y = iPosY;
            }
            BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackPawn2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn2_X, blackPawn2_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackPawn2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);
            blackPawn2_Exist = true;
            break;
        }
        if (!blackPawn3_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackPawn3_X - 5) / 80);
            int yOri = ((blackPawn3_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackPawn3_X = iPosX;
                blackPawn3_Y = iPosY;
            }
            BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackPawn3 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn3_X, blackPawn3_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackPawn3, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);
            blackPawn3_Exist = true;
            break;
        }
        if (!blackPawn4_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackPawn4_X - 5) / 80);
            int yOri = ((blackPawn4_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackPawn4_X = iPosX;
                blackPawn4_Y = iPosY;
            }
            BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackPawn4 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn4_X, blackPawn4_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackPawn4, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);
            blackPawn4_Exist = true;
            break;
        }
        if (!blackPawn5_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackPawn5_X - 5) / 80);
            int yOri = ((blackPawn5_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackPawn5_X = iPosX;
                blackPawn5_Y = iPosY;
            }
            BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackPawn5 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn5_X, blackPawn5_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackPawn5, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);
            blackPawn5_Exist = true;
            break;
        }
        if (!blackPawn6_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackPawn6_X - 5) / 80);
            int yOri = ((blackPawn6_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackPawn6_X = iPosX;
                blackPawn6_Y = iPosY;
            }
            BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackPawn6 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn6_X, blackPawn6_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackPawn6, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);
            blackPawn6_Exist = true;
            break;
        }
        if (!blackPawn7_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackPawn7_X - 5) / 80);
            int yOri = ((blackPawn7_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackPawn7_X = iPosX;
                blackPawn7_Y = iPosY;
            }
            BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackPawn7 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn7_X, blackPawn7_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackPawn7, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);
            blackPawn7_Exist = true;
            break;
        }
        if (!blackPawn8_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((blackPawn8_X - 5) / 80);
            int yOri = ((blackPawn8_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                blackPawn8_X = iPosX;
                blackPawn8_Y = iPosY;
            }
            BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            blackPawn8 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn8_X, blackPawn8_Y, 70, 70, hWnd, NULL, NULL, NULL);
            SendMessageW(blackPawn8, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);
            blackPawn8_Exist = true;
            break;
        }
        if (!orangeRook1_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangeRook1_X - 5) / 80);
            int yOri = ((orangeRook1_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangeRook1_X = iPosX;
                orangeRook1_Y = iPosY;
            }
            orangeRook1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W ROOK1",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangeRook1_X, orangeRook1_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangeRook1_Exist = true;
            break;
        }
        if (!orangeRook2_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangeRook2_X - 5) / 80);
            int yOri = ((orangeRook2_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangeRook2_X = iPosX;
                orangeRook2_Y = iPosY;
            }
            orangeRook2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W ROOK2",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangeRook2_X, orangeRook2_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangeRook2_Exist = true;
            break;
        }
        if (!orangeKnight2_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangeKnight2_X - 5) / 80);
            int yOri = ((orangeKnight2_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangeKnight2_X = iPosX;
                orangeKnight2_Y = iPosY;
            }
            orangeKnight2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W KNIGHT2",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangeKnight2_X, orangeKnight2_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangeKnight2_Exist = true;
            break;
        }
        if (!orangeKnight1_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangeKnight1_X - 5) / 80);
            int yOri = ((orangeKnight1_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangeKnight1_X = iPosX;
                orangeKnight1_Y = iPosY;
            }
            orangeKnight1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W KNIGHT1",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangeKnight1_X, orangeKnight1_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangeKnight1_Exist = true;
            break;
        }
        if (!orangeBishop2_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangeBishop2_X - 5) / 80);
            int yOri = ((orangeBishop2_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangeBishop2_X = iPosX;
                orangeBishop2_Y = iPosY;
            }
            orangeBishop2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W BISHOP2",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangeBishop2_X, orangeBishop2_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangeBishop2_Exist = true;
            break;
        }
        if (!orangeBishop1_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangeBishop1_X - 5) / 80);
            int yOri = ((orangeBishop1_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangeBishop1_X = iPosX;
                orangeBishop1_Y = iPosY;
            }
            orangeBishop1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W BISHOP1",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangeBishop1_X, orangeBishop1_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangeBishop1_Exist = true;
            break;
        }
        if (!orangeKing_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangeKing_X - 5) / 80);
            int yOri = ((orangeKing_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangeKing_X = iPosX;
                orangeKing_Y = iPosY;
            }
            orangeKing = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W KING",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangeKing_X, orangeKing_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangeKing_Exist = true;
            break;
        }
        if (!orangeQueen_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangeQueen_X - 5) / 80);
            int yOri = ((orangeQueen_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangeQueen_X = iPosX;
                orangeQueen_Y = iPosY;
            }
            orangeQueen = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W QUEEN",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangeQueen_X, orangeQueen_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangeQueen_Exist = true;
            break;
        }
        if (!orangePawn1_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangePawn1_X - 5) / 80);
            int yOri = ((orangePawn1_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangePawn1_X = iPosX;
                orangePawn1_Y = iPosY;
            }
            orangePawn1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN1",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangePawn1_X, orangePawn1_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangePawn1_Exist = true;
            break;
        }
        if (!orangePawn2_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangePawn2_X - 5) / 80);
            int yOri = ((orangePawn2_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangePawn2_X = iPosX;
                orangePawn2_Y = iPosY;
            }
            orangePawn2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN2",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangePawn2_X, orangePawn2_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangePawn2_Exist = true;
            break;
        }
        if (!orangePawn3_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangePawn3_X - 5) / 80);
            int yOri = ((orangePawn3_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangePawn3_X = iPosX;
                orangePawn3_Y = iPosY;
            }
            orangePawn3 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN3",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangePawn3_X, orangePawn3_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangePawn3_Exist = true;
            break;
        }
        if (!orangePawn4_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangePawn4_X - 5) / 80);
            int yOri = ((orangePawn4_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangePawn4_X = iPosX;
                orangePawn4_Y = iPosY;
            }
            orangePawn4 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN4",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangePawn4_X, orangePawn4_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangePawn4_Exist = true;
            break;
        }
        if (!orangePawn5_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangePawn5_X - 5) / 80);
            int yOri = ((orangePawn5_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangePawn5_X = iPosX;
                orangePawn5_Y = iPosY;
            }
            orangePawn5 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN5",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangePawn5_X, orangePawn5_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangePawn5_Exist = true;
            break;
        }
        if (!orangePawn6_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangePawn6_X - 5) / 80);
            int yOri = ((orangePawn6_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangePawn6_X = iPosX;
                orangePawn6_Y = iPosY;
            }
            orangePawn6 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN6",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangePawn6_X, orangePawn6_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangePawn6_Exist = true;
            break;
        }
        if (!orangePawn7_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangePawn7_X - 5) / 80);
            int yOri = ((orangePawn7_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangePawn7_X = iPosX;
                orangePawn7_Y = iPosY;
            }
            orangePawn7 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN7",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangePawn7_X, orangePawn7_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangePawn7_Exist = true;
            break;
        }
        if (!orangePawn8_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((orangePawn8_X - 5) / 80);
            int yOri = ((orangePawn8_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                orangePawn8_X = iPosX;
                orangePawn8_Y = iPosY;
            }
            orangePawn8 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN8",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                orangePawn8_X, orangePawn8_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            orangePawn8_Exist = true;
            break;
        }


        // Check whether in image(piece) is selected by mouse click
        // TODO replace with ButtonPress/Image
        // Placeholder Destruction if ghost blank piece is in place, but does not fix issue due to overlapping)
        if (iPosX > blackRook2_X && iPosX < (blackRook2_X + 75) && iPosY > blackRook2_Y && iPosY < (blackRook2_Y + 75)) {
            DestroyWindow(blackRook2);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackRook2_Exist = false;
            break;
        }
        if (iPosX > blackRook1_X && iPosX < (blackRook1_X + 75) && iPosY > blackRook1_Y && iPosY < (blackRook1_Y + 75)) {
            DestroyWindow(blackRook1);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackRook1_Exist = false;
            break;
        }
        if (iPosX > blackKnight2_X && iPosX < (blackKnight2_X + 75) && iPosY > blackKnight2_Y && iPosY < (blackKnight2_Y + 75)) {
            DestroyWindow(blackKnight2);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackKnight2_Exist = false;
            break;
        }
        if (iPosX > blackKnight1_X && iPosX < (blackKnight1_X + 75) && iPosY > blackKnight1_Y && iPosY < (blackKnight1_Y + 75)) {
            DestroyWindow(blackKnight1);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackKnight1_Exist = false;
            break;
        }
        if (iPosX > blackBishop2_X && iPosX < (blackBishop2_X + 75) && iPosY > blackBishop2_Y && iPosY < (blackBishop2_Y + 75)) {
            DestroyWindow(blackBishop2);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackBishop2_Exist = false;
            break;
        }
        if (iPosX > blackBishop1_X && iPosX < (blackBishop1_X + 75) && iPosY > blackBishop1_Y && iPosY < (blackBishop1_Y + 75)) {
            DestroyWindow(blackBishop1);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackBishop1_Exist = false;
            break;
        }
        if (iPosX > blackKing_X && iPosX < (blackKing_X + 75) && iPosY > blackKing_Y && iPosY < (blackKing_Y + 75)) {
            DestroyWindow(blackKing);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackKing_Exist = false;
            break;
        }
        if (iPosX > blackQueen_X && iPosX < (blackQueen_X + 75) && iPosY > blackQueen_Y && iPosY < (blackQueen_Y + 75)) {
            DestroyWindow(blackQueen);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackQueen_Exist = false;
            break;
        }
        if (iPosX > blackPawn1_X && iPosX < (blackPawn1_X + 75) && iPosY > blackPawn1_Y && iPosY < (blackPawn1_Y + 75)) {
            DestroyWindow(blackPawn1);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackPawn1_Exist = false;
            break;
        }
        if (iPosX > blackPawn2_X && iPosX < (blackPawn2_X + 75) && iPosY > blackPawn2_Y && iPosY < (blackPawn2_Y + 75)) {
            DestroyWindow(blackPawn2);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackPawn2_Exist = false;
            break;
        }
        if (iPosX > blackPawn3_X && iPosX < (blackPawn3_X + 75) && iPosY > blackPawn3_Y && iPosY < (blackPawn3_Y + 75)) {
            DestroyWindow(blackPawn3);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackPawn3_Exist = false;
            break;
        }
        if (iPosX > blackPawn4_X && iPosX < (blackPawn4_X + 75) && iPosY > blackPawn4_Y && iPosY < (blackPawn4_Y + 75)) {
            DestroyWindow(blackPawn4);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackPawn4_Exist = false;
            break;
        }
        if (iPosX > blackPawn5_X && iPosX < (blackPawn5_X + 75) && iPosY > blackPawn5_Y && iPosY < (blackPawn5_Y + 75)) {
            DestroyWindow(blackPawn5);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackPawn5_Exist = false;
            break;
        }
        if (iPosX > blackPawn6_X && iPosX < (blackPawn6_X + 75) && iPosY > blackPawn6_Y && iPosY < (blackPawn6_Y + 75)) {
            DestroyWindow(blackPawn6);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackPawn6_Exist = false;
            break;
        }
        if (iPosX > blackPawn7_X && iPosX < (blackPawn7_X + 75) && iPosY > blackPawn7_Y && iPosY < (blackPawn7_Y + 75)) {
            DestroyWindow(blackPawn7);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackPawn7_Exist = false;
            break;
        }
        if (iPosX > blackPawn8_X && iPosX < (blackPawn8_X + 75) && iPosY > blackPawn8_Y && iPosY < (blackPawn8_Y + 75)) {
            DestroyWindow(blackPawn8);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) blackPawn8_Exist = false;
            break;
        }
        if (iPosX > orangeRook2_X && iPosX < (orangeRook2_X + 75) && iPosY > orangeRook2_Y && iPosY < (orangeRook2_Y + 75)) {
            DestroyWindow(orangeRook2);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangeRook2_Exist = false;
            break;
        }
        if (iPosX > orangeRook1_X && iPosX < (orangeRook1_X + 75) && iPosY > orangeRook1_Y && iPosY < (orangeRook1_Y + 75)) {
            DestroyWindow(orangeRook1);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangeRook1_Exist = false;
            break;
        }
        if (iPosX > orangeKnight2_X && iPosX < (orangeKnight2_X + 75) && iPosY > orangeKnight2_Y && iPosY < (orangeKnight2_Y + 75)) {
            DestroyWindow(orangeKnight2);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangeKnight2_Exist = false;
            break;
        }
        if (iPosX > orangeKnight1_X && iPosX < (orangeKnight1_X + 75) && iPosY > orangeKnight1_Y && iPosY < (orangeKnight1_Y + 75)) {
            DestroyWindow(orangeKnight1);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangeKnight1_Exist = false;
            break;
        }
        if (iPosX > orangeBishop2_X && iPosX < (orangeBishop2_X + 75) && iPosY > orangeBishop2_Y && iPosY < (orangeBishop2_Y + 75)) {
            DestroyWindow(orangeBishop2);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangeBishop2_Exist = false;
            break;
        }
        if (iPosX > orangeBishop1_X && iPosX < (orangeBishop1_X + 75) && iPosY > orangeBishop1_Y && iPosY < (orangeBishop1_Y + 75)) {
            DestroyWindow(orangeBishop1);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangeBishop1_Exist = false;
            break;
        }
        if (iPosX > orangeKing_X && iPosX < (orangeKing_X + 75) && iPosY > orangeKing_Y && iPosY < (orangeKing_Y + 75)) {
            DestroyWindow(orangeKing);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangeKing_Exist = false;
            break;
        }
        if (iPosX > orangeQueen_X && iPosX < (orangeQueen_X + 75) && iPosY > orangeQueen_Y && iPosY < (orangeQueen_Y + 75)) {
            DestroyWindow(orangeQueen);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangeQueen_Exist = false;
            break;
        }
        if (iPosX > orangePawn1_X && iPosX < (orangePawn1_X + 75) && iPosY > orangePawn1_Y && iPosY < (orangePawn1_Y + 75)) {
            DestroyWindow(orangePawn1);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangePawn1_Exist = false;
            break;
        }
        if (iPosX > orangePawn2_X && iPosX < (orangePawn2_X + 75) && iPosY > orangePawn2_Y && iPosY < (orangePawn2_Y + 75)) {
            DestroyWindow(orangePawn2);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangePawn2_Exist = false;
            break;
        }
        if (iPosX > orangePawn3_X && iPosX < (orangePawn3_X + 75) && iPosY > orangePawn3_Y && iPosY < (orangePawn3_Y + 75)) {
            DestroyWindow(orangePawn3);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangePawn3_Exist = false;
            break;
        }
        if (iPosX > orangePawn4_X && iPosX < (orangePawn4_X + 75) && iPosY > orangePawn4_Y && iPosY < (orangePawn4_Y + 75)) {
            DestroyWindow(orangePawn4);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangePawn4_Exist = false;
            break;
        }
        if (iPosX > orangePawn5_X && iPosX < (orangePawn5_X + 75) && iPosY > orangePawn5_Y && iPosY < (orangePawn5_Y + 75)) {
            DestroyWindow(orangePawn5);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangePawn5_Exist = false;
            break;
        }
        if (iPosX > orangePawn6_X && iPosX < (orangePawn6_X + 75) && iPosY > orangePawn6_Y && iPosY < (orangePawn6_Y + 75)) {
            DestroyWindow(orangePawn6);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangePawn6_Exist = false;
            break;
        }
        if (iPosX > orangePawn7_X && iPosX < (orangePawn7_X + 75) && iPosY > orangePawn7_Y && iPosY < (orangePawn7_Y + 75)) {
            DestroyWindow(orangePawn7);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangePawn7_Exist = false;
            break;
        }
        if (iPosX > orangePawn8_X && iPosX < (orangePawn8_X + 75) && iPosY > orangePawn8_Y && iPosY < (orangePawn8_Y + 75)) {
            DestroyWindow(orangePawn8);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) orangePawn8_Exist = false;
            break;
        }

            // declaring an array of wide chars to hold the coordinates as string
            wchar_t waCoord[20];

            //print function that uses wide char string
            wsprintf(waCoord, _T("(%i, %i, %d)"), int(round(iPosX / SpaceSize)) , int(round(iPosY / SpaceSize)), board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))]);
            //after the function call, the array Coord is filled with the coordinates

            //corrdinate string is passed to the message box function to display
            //will want to eventually eliminate this functionality 
            ::MessageBox(hWnd, waCoord, _T("LMB Click"), MB_OK);
        
        break;
    }

 
    case WM_CREATE:

        hBoardImage = (HBITMAP)LoadImageW(NULL, L"ChessLayout.bmp", IMAGE_BITMAP, 645, 645, LR_LOADFROMFILE);
        hLayout = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 100, 100, hWnd, NULL, NULL, NULL);
        SendMessageW(hLayout, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBoardImage);
               
        //TODO Replace with image, cause I can't git images to work rn
        blackRook1_X = 5;
        blackRook1_Y = 5;
        blackRook1_Exist = true;
        BlackRookImage = (HBITMAP)LoadImageW(NULL, L"images/rookpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackRook1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackRook1_X, blackRook1_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackRook1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackRookImage);
        
        blackKnight1_X = 85;
        blackKnight1_Y = 5;
        blackKnight1_Exist = true;
        BlackKnightImage = (HBITMAP)LoadImageW(NULL, L"images/knightpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackKnight1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackKnight1_X, blackKnight1_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackKnight1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackKnightImage);

        blackBishop1_X = 165;
        blackBishop1_Y = 5;
        blackBishop1_Exist = true;
        BlackBishopImage = (HBITMAP)LoadImageW(NULL, L"images/bishoppiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackBishop1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackBishop1_X, blackBishop1_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackBishop1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackBishopImage);

        blackKing_X = 325;
        blackKing_Y = 5;
        blackKing_Exist = true;
        BlackKingImage = (HBITMAP)LoadImageW(NULL, L"images/kingpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackKing = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackKing_X, blackKing_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackKing, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackKingImage);

        blackQueen_X = 245;
        blackQueen_Y = 5;
        blackQueen_Exist = true;
        BlackQueenImage = (HBITMAP)LoadImageW(NULL, L"images/queenpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackQueen = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackQueen_X, blackQueen_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackQueen, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackQueenImage);

        blackBishop2_X = 405;
        blackBishop2_Y = 5;
        blackBishop2_Exist = true;
        BlackBishopImage = (HBITMAP)LoadImageW(NULL, L"images/bishoppiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackBishop2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackBishop2_X, blackBishop2_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackBishop2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackBishopImage);

        blackKnight2_X = 485;
        blackKnight2_Y = 5;
        blackKnight2_Exist = true;
        BlackKnightImage = (HBITMAP)LoadImageW(NULL, L"images/knightpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackKnight2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackKnight2_X, blackKnight2_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackKnight2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackKnightImage);

        blackRook2_X = 565;
        blackRook2_Y = 5;
        blackRook2_Exist = true;
        BlackRookImage = (HBITMAP)LoadImageW(NULL, L"images/rookpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackRook2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackRook2_X, blackRook2_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackRook2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackRookImage);

        blackPawn1_X = 5;
        blackPawn1_Y = 85;
        blackPawn1_Exist = true;
        BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackPawn1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn1_X, blackPawn1_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackPawn1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);

        blackPawn2_X = 85;
        blackPawn2_Y = 85;
        blackPawn2_Exist = true;
        BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackPawn2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn2_X, blackPawn2_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackPawn2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);

        blackPawn3_X = 165;
        blackPawn3_Y = 85;
        blackPawn3_Exist = true;
        BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackPawn3 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn3_X, blackPawn3_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackPawn3, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);

        blackPawn4_X = 245;
        blackPawn4_Y = 85;
        blackPawn4_Exist = true;
        BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackPawn4 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn4_X, blackPawn4_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackPawn4, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);

        blackPawn5_X = 325;
        blackPawn5_Y = 85;
        blackPawn5_Exist = true;
        BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackPawn5 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn5_X, blackPawn5_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackPawn5, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);

        blackPawn6_X = 405;
        blackPawn6_Y = 85;
        blackPawn6_Exist = true;
        BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackPawn6 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn6_X, blackPawn6_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackPawn6, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);

        blackPawn7_X = 485;
        blackPawn7_Y = 85;
        blackPawn7_Exist = true;
        BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackPawn7 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn7_X, blackPawn7_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackPawn7, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);

        blackPawn8_X = 565;
        blackPawn8_Y = 85;
        blackPawn8_Exist = true;
        BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        blackPawn8 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, blackPawn8_X, blackPawn8_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(blackPawn8, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);
        
        orangeRook1_X = 5;
        orangeRook1_Y = 565;
        orangeRook1_Exist = true;
        OrangeRookImage = (HBITMAP)LoadImageW(NULL, L"images/rookorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangeRook1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangeRook1_X, orangeRook1_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangeRook1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeRookImage);

        orangeKnight1_X = 85;
        orangeKnight1_Y = 565;
        orangeKnight1_Exist = true;
        OrangeKnightImage = (HBITMAP)LoadImageW(NULL, L"images/knightorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangeKnight1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangeKnight1_X, orangeKnight1_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangeKnight1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeKnightImage);

        orangeBishop1_X = 165;
        orangeBishop1_Y = 565;
        orangeBishop1_Exist = true;
        OrangeBishopImage = (HBITMAP)LoadImageW(NULL, L"images/bishoporange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangeBishop1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangeBishop1_X, orangeBishop1_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangeBishop1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeBishopImage);

        orangeKing_X = 325;
        orangeKing_Y = 565;
        orangeKing_Exist = true;
        OrangeKingImage = (HBITMAP)LoadImageW(NULL, L"images/kingorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangeKing = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangeKing_X, orangeKing_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangeKing, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeKingImage);

        orangeQueen_X = 245;
        orangeQueen_Y = 565;
        orangeQueen_Exist = true;
        OrangeQueenImage = (HBITMAP)LoadImageW(NULL, L"images/queenorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangeQueen = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangeQueen_X, orangeQueen_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangeQueen, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeQueenImage);

        orangeBishop2_X = 405;
        orangeBishop2_Y = 565;
        orangeBishop2_Exist = true;
        OrangeBishopImage = (HBITMAP)LoadImageW(NULL, L"images/bishoporange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangeBishop2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangeBishop2_X, orangeBishop2_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangeBishop2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeBishopImage);

        orangeKnight2_X = 485;
        orangeKnight2_Y = 565;
        orangeKnight2_Exist = true;
        OrangeKnightImage = (HBITMAP)LoadImageW(NULL, L"images/knightorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangeKnight2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangeKnight2_X, orangeKnight2_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangeKnight2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeKnightImage);

        orangeRook2_X = 565;
        orangeRook2_Y = 565;
        orangeRook2_Exist = true;
        OrangeRookImage = (HBITMAP)LoadImageW(NULL, L"images/rookorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangeRook2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangeRook2_X, orangeRook2_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangeRook2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeRookImage);

        orangePawn1_X = 5;
        orangePawn1_Y = 485;
        orangePawn1_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangePawn1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangePawn1_X, orangePawn1_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangePawn1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        orangePawn2_X = 85;
        orangePawn2_Y = 485;
        orangePawn2_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangePawn2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangePawn2_X, orangePawn2_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangePawn2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        orangePawn3_X = 165;
        orangePawn3_Y = 485;
        orangePawn3_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangePawn3 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangePawn3_X, orangePawn3_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangePawn3, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        orangePawn4_X = 245;
        orangePawn4_Y = 485;
        orangePawn4_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangePawn4 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangePawn4_X, orangePawn4_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangePawn4, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        orangePawn5_X = 325;
        orangePawn5_Y = 485;
        orangePawn5_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangePawn5 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangePawn5_X, orangePawn5_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangePawn5, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        orangePawn6_X = 405;
        orangePawn6_Y = 485;
        orangePawn6_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangePawn6 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangePawn6_X, orangePawn6_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangePawn6, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        orangePawn7_X = 485;
        orangePawn7_Y = 485;
        orangePawn7_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangePawn7 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangePawn7_X, orangePawn7_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangePawn7, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        orangePawn8_X = 565;
        orangePawn8_Y = 485;
        orangePawn8_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        orangePawn8 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, orangePawn8_X, orangePawn8_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(orangePawn8, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);






   
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            
            DrawBoard(hdc);
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}






void setBoard(int board[][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = blank;
        }
    }
    board[1][7] = WKnight;  board[1][0] = BKnight;
    board[6][7] = WKnight;  board[6][0] = BKnight;

    board[2][7] = WBishop;  board[2][0] = BBishop;
    board[5][7] = WBishop;  board[5][0] = BBishop;

    board[0][7] = WRook;  board[0][0] = BRook;
    board[7][7] = WRook;  board[7][0] = BRook;

    board[3][7] = WQueen;  board[3][0] = BQueen;

    board[4][7] = WKing;  board[4][0] = BKing;
    
    for (int i = 0; i < 8; i++) {
        board[i][1] = BPawn;
        board[i][6] = WPawn;
    }
    
}

bool chooseMove(int x, int y, int a, int b, int board1[][8]) {
    bool result = false;
    
    switch (board1[x][y]) {
    case blank:
        break;
    case BPawn:
        result = movePawn(x, y, a, b, board1);
        break;
    case WPawn:
        result = movePawn(x, y, a, b, board1);
        break;
    
    case WKnight:
        result = moveKnight(x, y, a, b, board1);
        break;
    case BKnight:
        result = moveKnight(x, y, a, b, board1);
        break;
    case WBishop:
        result = moveBishop(x, y, a, b, board1);
        break;
    case BBishop:
        result = moveBishop(x, y, a, b, board1);
  
        break;
    case WRook:
        result = moveRook(x, y, a, b, board1);

        break;
    case BRook:
        result = moveRook(x, y, a, b, board1);
       
        break;
    case WQueen:
        result = moveBishop(x, y, a, b, board1);
        if (result == false) {
            result = moveRook(x, y, a, b, board1);
        }

        break;
    case BQueen:
        result = moveBishop(x, y, a, b, board1);
        if (result == false) {
            result = moveRook(x, y, a, b, board1);
        }

        break;
    case WKing:
        result = moveKing(x, y, a, b, board1);

        break;
    case BKing:
        result = moveKing(x, y, a, b, board1);

        break;
    }
    return result;

}
