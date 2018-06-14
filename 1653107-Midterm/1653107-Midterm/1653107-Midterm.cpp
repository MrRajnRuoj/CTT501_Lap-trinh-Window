// 1653107-Midterm.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "DataStructure.h"

#define MAX_LOADSTRING	100
#define COUNTDOWN		12345 
#define INPUT_FILE		"pacman-params.txt"

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HMENU hMenu;
int timer;		// seconds
GameData* gData;
Game* game;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_MY1653107MIDTERM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1653107MIDTERM));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1653107MIDTERM));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1653107MIDTERM);
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

void importData() {
	fstream fInput;
	fInput.open(INPUT_FILE, ios::in);
	int nMapline;
	fInput >> nMapline;
	for (int i = 0; i < nMapline; ++i) {
		MapLine mLine;
		fInput >> mLine.start.x >> mLine.start.y;
		fInput >> mLine.end.x >> mLine.end.y;
		gData->mapLines.push_back(mLine);
	}
	fInput >> gData->nPacDot;
	fInput >> gData->pacMan.x >> gData->pacMan.y;
	fInput >> gData->timer;
	fInput.close();
}
void initData(HWND hWnd) {
	gData = new GameData();
	game = new Game(gData);
	
	hBmpMap = (HBITMAP)LoadImage(hInst, L"pacman-map.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	hBmpPacMan = (HBITMAP)LoadImage(hInst, L"pacman.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hBmpMap, sizeof(BITMAP), &bmpMapObj);
	GetObject(hBmpPacMan, sizeof(BITMAP), &bmpPacManObj);

	MoveWindow(hWnd, 0, 0, bmpMapObj.bmWidth, bmpMapObj.bmHeight, TRUE);

	SetTimer(hWnd, COUNTDOWN, 1000, NULL);

	hMenu = GetMenu(hWnd);
	EnableMenuItem(hMenu, ID_ENDGAME, MF_GRAYED | MF_BYCOMMAND);
}

void drawMap(HWND hWnd) {
	
	HDC hdc = GetDC(hWnd);
	HDC memDC = CreateCompatibleDC(hdc);
	SelectObject(memDC, hBmpMap);
	BitBlt(hdc, 0, 0, bmpMapObj.bmWidth, bmpMapObj.bmHeight, memDC, 0, 0, SRCCOPY);

	DeleteDC(memDC);
	ReleaseDC(hWnd, hdc);
}


void startGame(HWND hWnd) {
	PacMan pacMan(gData);
	game->generatePacDot(hWnd);
	game->drawPacMan(hWnd);
	EnableMenuItem(hMenu, ID_STARTGAME, MF_GRAYED | MF_BYCOMMAND);
	EnableMenuItem(hMenu, ID_ENDGAME, MF_ENABLED | MF_BYCOMMAND);
}

void endGame(HWND hWnd) {
	WCHAR mess[MAX_LOADSTRING];

	wsprintf(mess, L"Game over. You earned %d pac-dots", gData->nPacDot - gData->pacDots.size());
	MessageBox(hWnd, mess, L"Game Over", MB_OK);
	EnableMenuItem(hMenu, ID_ENDGAME, MF_GRAYED | MF_BYCOMMAND);
	EnableMenuItem(hMenu, ID_STARTGAME, MF_ENABLED | MF_BYCOMMAND);
}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static bool isGameStarted = false;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_STARTGAME:
				isGameStarted = true;
				startGame(hWnd);
				break;
			case ID_ENDGAME:
				isGameStarted = false;
				endGame(hWnd);
				break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
		initData(hWnd);
		importData();
		break;
	case WM_TIMER:
		if (isGameStarted) {
			--gData->timer;
			if (gData->timer == 0)
				endGame(hWnd);
		}
		break;
    case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		drawMap(hWnd);
	}
        break;
	case WM_KEYDOWN:
	{
		if (isGameStarted)
		{
			switch (wParam)
			{
			case VK_LEFT:
				if (game->isInMapLine(gData->pacMan.x - 1, gData->pacMan.y)) {
					gData->pacMan.x -= 1;
					game->eatPacDot();
					game->drawPacMan(hWnd);
				}
				break;
			case VK_RIGHT:
				if (game->isInMapLine(gData->pacMan.x + 1, gData->pacMan.y)) {
					gData->pacMan.x += 1;
					game->eatPacDot();
					game->drawPacMan(hWnd);
				}
				break;
			case VK_UP:
				if (game->isInMapLine(gData->pacMan.x, gData->pacMan.y - 1)) {
					gData->pacMan.y -= 1;
					game->eatPacDot();
					game->drawPacMan(hWnd);
				}
				break;
			case VK_DOWN:
				if (game->isInMapLine(gData->pacMan.x, gData->pacMan.y + 1)) {
					gData->pacMan.y += 1;
					game->eatPacDot();
					game->drawPacMan(hWnd);
				}
				break;
			}
			if (gData->pacDots.size() == 0)
				endGame(hWnd);
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
