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
                    whiteRook1_X, whiteRook1_Y, whiteKnight1_X, whiteKnight1_Y, whiteBishop1_Y, whiteBishop1_X,
                    whiteKing_X, whiteKing_Y, whiteQueen_X, whiteQueen_Y,
                    whiteRook2_X, whiteRook2_Y, whiteKnight2_X, whiteKnight2_Y, whiteBishop2_Y, whiteBishop2_X,
                    whitePawn1_X, whitePawn1_Y, whitePawn2_X, whitePawn2_Y, whitePawn3_X, whitePawn3_Y, whitePawn4_X, whitePawn4_Y,
                    whitePawn5_X, whitePawn5_Y, whitePawn6_X, whitePawn6_Y, whitePawn7_X, whitePawn7_Y, whitePawn8_X, whitePawn8_Y;

BOOL                blackRook1_Exist, blackKnight1_Exist, blackBishop1_Exist, 
                    blackKing_Exist, blackQueen_Exist,
                    blackRook2_Exist, blackKnight2_Exist, blackBishop2_Exist, blackPawn1_Exist, blackPawn2_Exist, blackPawn3_Exist,
                    blackPawn4_Exist, blackPawn5_Exist, blackPawn6_Exist, blackPawn7_Exist, blackPawn8_Exist,
                    whiteRook1_Exist, whiteKnight1_Exist, whiteBishop1_Exist,
                    whiteKing_Exist, whiteQueen_Exist,
                    whiteRook2_Exist, whiteKnight2_Exist, whiteBishop2_Exist, whitePawn1_Exist, whitePawn2_Exist, whitePawn3_Exist,
                    whitePawn4_Exist, whitePawn5_Exist, whitePawn6_Exist, whitePawn7_Exist, whitePawn8_Exist;
void AddControls(HWND);
void loadImages();
void setBoard(int[][8]);
bool chooseMove(int, int, int, int, int[][8]);
INT board[8][8];

HWND hButton, hLayout, hKing, blackRook1, blackKnight1, blackBishop1, blackRook2, blackKnight2, blackBishop2, blackKing, blackQueen,
     blackPawn1, blackPawn2, blackPawn3, blackPawn4, blackPawn5, blackPawn6, blackPawn7, blackPawn8, whiteRook1, whiteKnight1, whiteBishop1, whiteRook2, whiteKnight2, whiteBishop2, whiteKing, whiteQueen,
    whitePawn1, whitePawn2, whitePawn3, whitePawn4, whitePawn5, whitePawn6, whitePawn7, whitePawn8;

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
            blackRook1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B ROOK1",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackRook1_X, blackRook1_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackRook2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B ROOK2",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackRook2_X, blackRook2_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackKnight2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B KNIGHT2",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackKnight2_X, blackKnight2_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackKnight1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B KNIGHT1",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackKnight1_X, blackKnight1_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            blackKnight1_Exist = true;
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
            blackBishop2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B BISHOP2",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackBishop2_X, blackBishop2_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackBishop1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B BISHOP1",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackBishop1_X, blackBishop1_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackKing = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B KING",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackKing_X, blackKing_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackQueen = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B QUEEN",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackQueen_X, blackQueen_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackPawn1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B PAWN1",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackPawn1_X, blackPawn1_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackPawn2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B PAWN2",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackPawn2_X, blackPawn2_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackPawn3 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B PAWN3",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackPawn3_X, blackPawn3_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackPawn4 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B PAWN4",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackPawn4_X, blackPawn4_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackPawn5 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B PAWN5",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackPawn5_X, blackPawn5_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackPawn6 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B PAWN6",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackPawn6_X, blackPawn6_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackPawn7 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B PAWN7",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackPawn7_X, blackPawn7_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
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
            blackPawn8 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"B PAWN8",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                blackPawn8_X, blackPawn8_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            blackPawn8_Exist = true;
            break;
        }
        if (!whiteRook1_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whiteRook1_X - 5) / 80);
            int yOri = ((whiteRook1_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whiteRook1_X = iPosX;
                whiteRook1_Y = iPosY;
            }
            whiteRook1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W ROOK1",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whiteRook1_X, whiteRook1_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whiteRook1_Exist = true;
            break;
        }
        if (!whiteRook2_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whiteRook2_X - 5) / 80);
            int yOri = ((whiteRook2_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whiteRook2_X = iPosX;
                whiteRook2_Y = iPosY;
            }
            whiteRook2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W ROOK2",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whiteRook2_X, whiteRook2_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whiteRook2_Exist = true;
            break;
        }
        if (!whiteKnight2_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whiteKnight2_X - 5) / 80);
            int yOri = ((whiteKnight2_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whiteKnight2_X = iPosX;
                whiteKnight2_Y = iPosY;
            }
            whiteKnight2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W KNIGHT2",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whiteKnight2_X, whiteKnight2_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whiteKnight2_Exist = true;
            break;
        }
        if (!whiteKnight1_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whiteKnight1_X - 5) / 80);
            int yOri = ((whiteKnight1_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whiteKnight1_X = iPosX;
                whiteKnight1_Y = iPosY;
            }
            whiteKnight1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W KNIGHT1",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whiteKnight1_X, whiteKnight1_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whiteKnight1_Exist = true;
            break;
        }
        if (!whiteBishop2_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whiteBishop2_X - 5) / 80);
            int yOri = ((whiteBishop2_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whiteBishop2_X = iPosX;
                whiteBishop2_Y = iPosY;
            }
            whiteBishop2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W BISHOP2",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whiteBishop2_X, whiteBishop2_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whiteBishop2_Exist = true;
            break;
        }
        if (!whiteBishop1_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whiteBishop1_X - 5) / 80);
            int yOri = ((whiteBishop1_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whiteBishop1_X = iPosX;
                whiteBishop1_Y = iPosY;
            }
            whiteBishop1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W BISHOP1",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whiteBishop1_X, whiteBishop1_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whiteBishop1_Exist = true;
            break;
        }
        if (!whiteKing_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whiteKing_X - 5) / 80);
            int yOri = ((whiteKing_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whiteKing_X = iPosX;
                whiteKing_Y = iPosY;
            }
            whiteKing = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W KING",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whiteKing_X, whiteKing_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whiteKing_Exist = true;
            break;
        }
        if (!whiteQueen_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whiteQueen_X - 5) / 80);
            int yOri = ((whiteQueen_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whiteQueen_X = iPosX;
                whiteQueen_Y = iPosY;
            }
            whiteQueen = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W QUEEN",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whiteQueen_X, whiteQueen_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whiteQueen_Exist = true;
            break;
        }
        if (!whitePawn1_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whitePawn1_X - 5) / 80);
            int yOri = ((whitePawn1_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whitePawn1_X = iPosX;
                whitePawn1_Y = iPosY;
            }
            whitePawn1 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN1",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whitePawn1_X, whitePawn1_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whitePawn1_Exist = true;
            break;
        }
        if (!whitePawn2_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whitePawn2_X - 5) / 80);
            int yOri = ((whitePawn2_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whitePawn2_X = iPosX;
                whitePawn2_Y = iPosY;
            }
            whitePawn2 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN2",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whitePawn2_X, whitePawn2_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whitePawn2_Exist = true;
            break;
        }
        if (!whitePawn3_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whitePawn3_X - 5) / 80);
            int yOri = ((whitePawn3_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whitePawn3_X = iPosX;
                whitePawn3_Y = iPosY;
            }
            whitePawn3 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN3",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whitePawn3_X, whitePawn3_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whitePawn3_Exist = true;
            break;
        }
        if (!whitePawn4_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whitePawn4_X - 5) / 80);
            int yOri = ((whitePawn4_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whitePawn4_X = iPosX;
                whitePawn4_Y = iPosY;
            }
            whitePawn4 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN4",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whitePawn4_X, whitePawn4_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whitePawn4_Exist = true;
            break;
        }
        if (!whitePawn5_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whitePawn5_X - 5) / 80);
            int yOri = ((whitePawn5_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whitePawn5_X = iPosX;
                whitePawn5_Y = iPosY;
            }
            whitePawn5 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN5",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whitePawn5_X, whitePawn5_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whitePawn5_Exist = true;
            break;
        }
        if (!whitePawn6_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whitePawn6_X - 5) / 80);
            int yOri = ((whitePawn6_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whitePawn6_X = iPosX;
                whitePawn6_Y = iPosY;
            }
            whitePawn6 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN6",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whitePawn6_X, whitePawn6_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whitePawn6_Exist = true;
            break;
        }
        if (!whitePawn7_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whitePawn7_X - 5) / 80);
            int yOri = ((whitePawn7_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whitePawn7_X = iPosX;
                whitePawn7_Y = iPosY;
            }
            whitePawn7 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN7",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whitePawn7_X, whitePawn7_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whitePawn7_Exist = true;
            break;
        }
        if (!whitePawn8_Exist && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
            int xPos = int(round(iPosX / SpaceSize));
            int yPos = int(round(iPosY / SpaceSize));
            int xOri = ((whitePawn8_X - 5) / 80);
            int yOri = ((whitePawn8_Y - 5) / 80);
            if (chooseMove(xOri, yOri, xPos, yPos, board)) {
                board[xPos][yPos] = board[xOri][yOri];
                board[xOri][yOri] = blank;
                iPosX = int(round(iPosX / SpaceSize) * SpaceSize) + 5;
                iPosY = int(round(iPosY / SpaceSize) * SpaceSize) + 5;
                whitePawn8_X = iPosX;
                whitePawn8_Y = iPosY;
            }
            whitePawn8 = CreateWindowEx(WS_EX_CLIENTEDGE, L"STATIC", L"W PAWN8",
                WS_VISIBLE | WS_CHILD | ES_LEFT,
                whitePawn8_X, whitePawn8_Y, 70, 70,
                hWnd,
                (HMENU)IDC_BUTTON, hInst, NULL);
            whitePawn8_Exist = true;
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
        if (iPosX > whiteRook2_X && iPosX < (whiteRook2_X + 75) && iPosY > whiteRook2_Y && iPosY < (whiteRook2_Y + 75)) {
            DestroyWindow(whiteRook2);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whiteRook2_Exist = false;
            break;
        }
        if (iPosX > whiteRook1_X && iPosX < (whiteRook1_X + 75) && iPosY > whiteRook1_Y && iPosY < (whiteRook1_Y + 75)) {
            DestroyWindow(whiteRook1);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whiteRook1_Exist = false;
            break;
        }
        if (iPosX > whiteKnight2_X && iPosX < (whiteKnight2_X + 75) && iPosY > whiteKnight2_Y && iPosY < (whiteKnight2_Y + 75)) {
            DestroyWindow(whiteKnight2);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whiteKnight2_Exist = false;
            break;
        }
        if (iPosX > whiteKnight1_X && iPosX < (whiteKnight1_X + 75) && iPosY > whiteKnight1_Y && iPosY < (whiteKnight1_Y + 75)) {
            DestroyWindow(whiteKnight1);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whiteKnight1_Exist = false;
            break;
        }
        if (iPosX > whiteBishop2_X && iPosX < (whiteBishop2_X + 75) && iPosY > whiteBishop2_Y && iPosY < (whiteBishop2_Y + 75)) {
            DestroyWindow(whiteBishop2);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whiteBishop2_Exist = false;
            break;
        }
        if (iPosX > whiteBishop1_X && iPosX < (whiteBishop1_X + 75) && iPosY > whiteBishop1_Y && iPosY < (whiteBishop1_Y + 75)) {
            DestroyWindow(whiteBishop1);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whiteBishop1_Exist = false;
            break;
        }
        if (iPosX > whiteKing_X && iPosX < (whiteKing_X + 75) && iPosY > whiteKing_Y && iPosY < (whiteKing_Y + 75)) {
            DestroyWindow(whiteKing);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whiteKing_Exist = false;
            break;
        }
        if (iPosX > whiteQueen_X && iPosX < (whiteQueen_X + 75) && iPosY > whiteQueen_Y && iPosY < (whiteQueen_Y + 75)) {
            DestroyWindow(whiteQueen);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whiteQueen_Exist = false;
            break;
        }
        if (iPosX > whitePawn1_X && iPosX < (whitePawn1_X + 75) && iPosY > whitePawn1_Y && iPosY < (whitePawn1_Y + 75)) {
            DestroyWindow(whitePawn1);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whitePawn1_Exist = false;
            break;
        }
        if (iPosX > whitePawn2_X && iPosX < (whitePawn2_X + 75) && iPosY > whitePawn2_Y && iPosY < (whitePawn2_Y + 75)) {
            DestroyWindow(whitePawn2);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whitePawn2_Exist = false;
            break;
        }
        if (iPosX > whitePawn3_X && iPosX < (whitePawn3_X + 75) && iPosY > whitePawn3_Y && iPosY < (whitePawn3_Y + 75)) {
            DestroyWindow(whitePawn3);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whitePawn3_Exist = false;
            break;
        }
        if (iPosX > whitePawn4_X && iPosX < (whitePawn4_X + 75) && iPosY > whitePawn4_Y && iPosY < (whitePawn4_Y + 75)) {
            DestroyWindow(whitePawn4);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whitePawn4_Exist = false;
            break;
        }
        if (iPosX > whitePawn5_X && iPosX < (whitePawn5_X + 75) && iPosY > whitePawn5_Y && iPosY < (whitePawn5_Y + 75)) {
            DestroyWindow(whitePawn5);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whitePawn5_Exist = false;
            break;
        }
        if (iPosX > whitePawn6_X && iPosX < (whitePawn6_X + 75) && iPosY > whitePawn6_Y && iPosY < (whitePawn6_Y + 75)) {
            DestroyWindow(whitePawn6);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whitePawn6_Exist = false;
            break;
        }
        if (iPosX > whitePawn7_X && iPosX < (whitePawn7_X + 75) && iPosY > whitePawn7_Y && iPosY < (whitePawn7_Y + 75)) {
            DestroyWindow(whitePawn7);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whitePawn7_Exist = false;
            break;
        }
        if (iPosX > whitePawn8_X && iPosX < (whitePawn8_X + 75) && iPosY > whitePawn8_Y && iPosY < (whitePawn8_Y + 75)) {
            DestroyWindow(whitePawn8);
            if (board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))] != 6) whitePawn8_Exist = false;
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
        
        loadImages();
        AddControls(hWnd);
       













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
        
        whiteRook1_X = 5;
        whiteRook1_Y = 565;
        whiteRook1_Exist = true;
        OrangeRookImage = (HBITMAP)LoadImageW(NULL, L"images/rookorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whiteRook1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whiteRook1_X, whiteRook1_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whiteRook1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeRookImage);

        whiteKnight1_X = 85;
        whiteKnight1_Y = 565;
        whiteKnight1_Exist = true;
        OrangeKnightImage = (HBITMAP)LoadImageW(NULL, L"images/knightorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whiteKnight1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whiteKnight1_X, whiteKnight1_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whiteKnight1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeKnightImage);

        whiteBishop1_X = 165;
        whiteBishop1_Y = 565;
        whiteBishop1_Exist = true;
        OrangeBishopImage = (HBITMAP)LoadImageW(NULL, L"images/bishoporange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whiteBishop1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whiteBishop1_X, whiteBishop1_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whiteBishop1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeBishopImage);

        whiteKing_X = 325;
        whiteKing_Y = 565;
        whiteKing_Exist = true;
        OrangeKingImage = (HBITMAP)LoadImageW(NULL, L"images/kingorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whiteKing = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whiteKing_X, whiteKing_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whiteKing, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeKingImage);

        whiteQueen_X = 245;
        whiteQueen_Y = 565;
        whiteQueen_Exist = true;
        OrangeQueenImage = (HBITMAP)LoadImageW(NULL, L"images/queenorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whiteQueen = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whiteQueen_X, whiteQueen_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whiteQueen, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeQueenImage);

        whiteBishop2_X = 405;
        whiteBishop2_Y = 565;
        whiteBishop2_Exist = true;
        OrangeBishopImage = (HBITMAP)LoadImageW(NULL, L"images/bishoporange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whiteBishop2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whiteBishop2_X, whiteBishop2_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whiteBishop2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeBishopImage);

        whiteKnight2_X = 485;
        whiteKnight2_Y = 565;
        whiteKnight2_Exist = true;
        OrangeKnightImage = (HBITMAP)LoadImageW(NULL, L"images/knightorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whiteKnight2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whiteKnight2_X, whiteKnight2_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whiteKnight2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeKnightImage);

        whiteRook2_X = 565;
        whiteRook2_Y = 565;
        whiteRook2_Exist = true;
        OrangeRookImage = (HBITMAP)LoadImageW(NULL, L"images/rookorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whiteRook2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whiteRook2_X, whiteRook2_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whiteRook2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeRookImage);

        whitePawn1_X = 5;
        whitePawn1_Y = 485;
        whitePawn1_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whitePawn1 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whitePawn1_X, whitePawn1_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whitePawn1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        whitePawn2_X = 85;
        whitePawn2_Y = 485;
        whitePawn2_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whitePawn2 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whitePawn2_X, whitePawn2_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whitePawn2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        whitePawn3_X = 165;
        whitePawn3_Y = 485;
        whitePawn3_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whitePawn3 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whitePawn3_X, whitePawn3_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whitePawn3, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        whitePawn4_X = 245;
        whitePawn4_Y = 485;
        whitePawn4_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whitePawn4 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whitePawn4_X, whitePawn4_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whitePawn4, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        whitePawn5_X = 325;
        whitePawn5_Y = 485;
        whitePawn5_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whitePawn5 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whitePawn5_X, whitePawn5_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whitePawn5, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        whitePawn6_X = 405;
        whitePawn6_Y = 485;
        whitePawn6_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whitePawn6 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whitePawn6_X, whitePawn6_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whitePawn6, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        whitePawn7_X = 485;
        whitePawn7_Y = 485;
        whitePawn7_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whitePawn7 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whitePawn7_X, whitePawn7_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whitePawn7, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);

        whitePawn8_X = 565;
        whitePawn8_Y = 485;
        whitePawn8_Exist = true;
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        whitePawn8 = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, whitePawn8_X, whitePawn8_Y, 70, 70, hWnd, NULL, NULL, NULL);
        SendMessageW(whitePawn8, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);




   
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


void AddControls(HWND hWnd) {
    hLayout = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 100, 100, hWnd, NULL, NULL, NULL);
    SendMessageW(hLayout, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hBoardImage);

    hKing = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 400, 2, 100, 100, hWnd, NULL, NULL, NULL);
    SendMessageW(hKing, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hKingImage);
}


void loadImages() {
    hBoardImage = (HBITMAP)LoadImageW(NULL, L"ChessLayout.bmp", IMAGE_BITMAP, 645, 645, LR_LOADFROMFILE);
    hKingImage = (HBITMAP)LoadImageW(NULL, L"queen2.bmp", IMAGE_BITMAP, 75, 75, LR_LOADFROMFILE);
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
