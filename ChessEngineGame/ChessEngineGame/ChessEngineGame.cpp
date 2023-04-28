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
orangePawn4_Exist, orangePawn5_Exist, orangePawn6_Exist, orangePawn7_Exist, orangePawn8_Exist, BoardReset;


BOOL turnCount;
INT pieceExist[32];
HWND pieceImage[32];
INT pieceX[32];
INT pieceY[32];
BOOL pieceSelect[32];

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
    if (!InitInstance(hInstance, nCmdShow))
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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CHESSENGINEGAME));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_CHESSENGINEGAME);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

    case WM_CREATE:
    {
        turnCount = true;

        //set pieceSelect, pieceExist
        for (int i = 0; i < 32; i++) {
            pieceSelect[i] = false;
            pieceExist[i] = true;
        }
        //set pieceX, pieceY
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 8; j++) {
                if (i < 2) { pieceY[8 * i + j] = i; }
                else { pieceY[8 * i + j] = i + 4; }
                pieceX[8 * i + j] = j;
            }
        }

       CreateWindowW(L"static", L"Current Piece Held", WS_VISIBLE | WS_CHILD, 660, 80, 125, 23, hWnd, NULL, NULL, NULL);

        BlackRookImage = (HBITMAP)LoadImageW(NULL, L"images/rookpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        BlackKnightImage = (HBITMAP)LoadImageW(NULL, L"images/knightpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        BlackBishopImage = (HBITMAP)LoadImageW(NULL, L"images/bishoppiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        BlackKingImage = (HBITMAP)LoadImageW(NULL, L"images/kingpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        BlackQueenImage = (HBITMAP)LoadImageW(NULL, L"images/queenpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        OrangePawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        OrangeKingImage = (HBITMAP)LoadImageW(NULL, L"images/kingorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        OrangeQueenImage = (HBITMAP)LoadImageW(NULL, L"images/queenorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        OrangeBishopImage = (HBITMAP)LoadImageW(NULL, L"images/bishoporange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        OrangeKnightImage = (HBITMAP)LoadImageW(NULL, L"images/knightorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        OrangeRookImage = (HBITMAP)LoadImageW(NULL, L"images/rookorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
        for (int i = 0; i < 32; i++) {
            DestroyWindow(pieceImage[i]);
            if (board[pieceX[i]][pieceY[i]] != blank && pieceExist[i]) {
                pieceImage[i] = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, (pieceX[i] * 80 + 5), (pieceY[i] * 80) + 5, 70, 70, hWnd, NULL, NULL, NULL);
                switch (board[pieceX[i]][pieceY[i]]) {
                case WPawn:
                    SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);
                    break;
                case BPawn:
                    SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);
                    break;
                case WKing:
                    SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeKingImage);
                    break;
                case WQueen:
                    SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeQueenImage);
                    break;
                case WRook:
                    SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeRookImage);
                    break;
                case WBishop:
                    SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeBishopImage);
                    break;
                case WKnight:
                    SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeKnightImage);
                    break;
                case BKnight:
                    SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackKnightImage);
                    break;
                case BKing:
                    SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackKingImage);
                    break;
                case BQueen:
                    SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackQueenImage);
                    break;
                case BRook:
                    SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackRookImage);
                    break;
                case BBishop:
                    SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackBishopImage);
                    break;
                }
            }
            else {
                pieceExist[i] = false;
            }
        }
    }

    case WM_LBUTTONDOWN:
    {

        // extract coordinates of mouse when mouse is left clicked
        int iPosX = LOWORD(lParam);
        int iPosY = HIWORD(lParam);
        BoardReset = false;

        for (int i = 0; i < 32; i++) {
            //If the piece does not exist, place it at location if inside of the board
            if (pieceSelect[i] && iPosX < SpaceSize * 8 && iPosY < SpaceSize * 8) {
                pieceSelect[i] = false;
                int xPos = int(round(iPosX / SpaceSize));
                int yPos = int(round(iPosY / SpaceSize));
                if (chooseMove(pieceX[i], pieceY[i], xPos, yPos, board)) {
                    board[xPos][yPos] = board[pieceX[i]][pieceY[i]];
                    board[pieceX[i]][pieceY[i]] = blank;
                    pieceX[i] = xPos;
                    pieceY[i] = yPos;
                }
                BoardReset = true;
            }
        }
        for (int i = 0; i < 32; i++) {
            if (!BoardReset && iPosX > (pieceX[i] * 80 + 5) && iPosX < (pieceX[i] * 80 + 80) && iPosY >(pieceY[i] * 80 + 5) && iPosY < ((pieceY[i] * 80 + 80))) {
                BoardReset = true;
                pieceSelect[i] = true;
            }
        }
        // Check whether in image(piece) is selected by mouse click


        //Reset Board
        if (BoardReset) {
            BlackRookImage = (HBITMAP)LoadImageW(NULL, L"images/rookpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            BlackKnightImage = (HBITMAP)LoadImageW(NULL, L"images/knightpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            BlackBishopImage = (HBITMAP)LoadImageW(NULL, L"images/bishoppiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            BlackKingImage = (HBITMAP)LoadImageW(NULL, L"images/kingpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            BlackQueenImage = (HBITMAP)LoadImageW(NULL, L"images/queenpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            BlackPawnImage = (HBITMAP)LoadImageW(NULL, L"images/pawnpiece.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            OrangeKingImage = (HBITMAP)LoadImageW(NULL, L"images/kingorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            OrangeQueenImage = (HBITMAP)LoadImageW(NULL, L"images/queenorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            OrangeBishopImage = (HBITMAP)LoadImageW(NULL, L"images/bishoporange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            OrangeKnightImage = (HBITMAP)LoadImageW(NULL, L"images/knightorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            OrangeRookImage = (HBITMAP)LoadImageW(NULL, L"images/rookorange.bmp", IMAGE_BITMAP, 35, 45, LR_LOADFROMFILE);
            for (int i = 0; i < 32; i++) {
                DestroyWindow(pieceImage[i]);
                if (board[pieceX[i]][pieceY[i]] != blank && pieceExist[i]) {
                    if (pieceSelect[i]) {
                        pieceImage[i] = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 700, 20, 70, 70, hWnd, NULL, NULL, NULL);
                    }
                    else {
                        pieceImage[i] = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, (pieceX[i] * 80 + 5), (pieceY[i] * 80) + 5, 70, 70, hWnd, NULL, NULL, NULL);
                    }
                    switch (board[pieceX[i]][pieceY[i]]) {
                    case WPawn:
                        SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangePawnImage);
                        break;
                    case BPawn:
                        SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackPawnImage);
                        break;
                    case WKing:
                        SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeKingImage);
                        break;
                    case WQueen:
                        SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeQueenImage);
                        break;
                    case WRook:
                        SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeRookImage);
                        break;
                    case WBishop:
                        SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeBishopImage);
                        break;
                    case WKnight:
                        SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)OrangeKnightImage);
                        break;
                    case BKnight:
                        SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackKnightImage);
                        break;
                    case BKing:
                        SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackKingImage);
                        break;
                    case BQueen:
                        SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackQueenImage);
                        break;
                    case BRook:
                        SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackRookImage);
                        break;
                    case BBishop:
                        SendMessageW(pieceImage[i], STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)BlackBishopImage);
                        break;
                    }
                }
                else {
                    pieceExist[i] = false;
                }
            }
            BoardReset = false;
            break;
        }
        //pop up message box functionality
        /*
            // declaring an array of wide chars to hold the coordinates as string
            wchar_t waCoord[20];

            //print function that uses wide char string
            wsprintf(waCoord, _T("(%i, %i, %d)"), int(round(iPosX / SpaceSize)) , int(round(iPosY / SpaceSize)), board[int(round(iPosX / SpaceSize))][int(round(iPosY / SpaceSize))]);
            //after the function call, the array Coord is filled with the coordinates

            //corrdinate string is passed to the message box function to display
            //will want to eventually eliminate this functionality
            ::MessageBox(hWnd, waCoord, _T("LMB Click"), MB_OK);

        */

        break;

    }

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        // TODO: Add any drawing code that uses hdc here...

        HPEN hPenOld;
        HPEN hLinePen;
        COLORREF qLineColor;
        qLineColor = RGB(8, 25, 10);
        hLinePen = CreatePen(PS_SOLID, 1, qLineColor);
        hPenOld = (HPEN)SelectObject(hdc, hLinePen);

        MoveToEx(hdc, 685, 15, NULL);
        LineTo(hdc, 685, 70);

        MoveToEx(hdc, 750, 15, NULL);
        LineTo(hdc, 750, 70);

        MoveToEx(hdc, 685, 70, NULL);
        LineTo(hdc, 751, 70);

        MoveToEx(hdc, 685, 15, NULL);
        LineTo(hdc, 751, 15);

        DrawBoard(hdc);
        EndPaint(hWnd, &ps);

        hBoardImage = (HBITMAP)LoadImageW(NULL, L"ChessLayout.bmp", IMAGE_BITMAP, 645, 645, LR_LOADFROMFILE);
        hLayout = CreateWindowW(L"Static", NULL, WS_VISIBLE | WS_CHILD | SS_BITMAP, 0, 0, 100, 100, hWnd, NULL, NULL, NULL);
        SendMessageW(hLayout, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBoardImage);
        BringWindowToTop(hLayout);
    }
    break;


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

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
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
