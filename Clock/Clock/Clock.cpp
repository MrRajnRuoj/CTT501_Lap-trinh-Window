// Clock.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Clock.h"

#define MAX_LOADSTRING 100
#define COUNTDOWN 1000

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HBITMAP hBmp = NULL;
HFONT hFont;
HRGN hRgn;
BITMAP bmpObj;
int timer = 300;

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
    LoadStringW(hInstance, IDC_CLOCK, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CLOCK));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CLOCK));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CLOCK);
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

void initData(HWND hWnd) {
	hBmp = (HBITMAP)LoadImage(hInst, L"clock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hBmp, sizeof(BITMAP), &bmpObj);

	hRgn = CreateEllipticRgn(0, 0, bmpObj.bmWidth, bmpObj.bmHeight);
	SetWindowRgn(hWnd, hRgn, TRUE);
	MoveWindow(hWnd, 0, 0, bmpObj.bmWidth, bmpObj.bmHeight, TRUE);

	hFont = CreateFont(78, 0, 0, 0, FW_DONTCARE, false, false, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
	SetTimer(hWnd, COUNTDOWN, 1000, NULL);
}

void drawClock(HWND hWnd) {
	HDC hdc = GetWindowDC(hWnd);
	SYSTEMTIME st;
	WCHAR sTime[50];
	RECT r;

	HDC memDC = CreateCompatibleDC(hdc);	// Create "virtual" DC in memory

	SelectObject(memDC, hBmp);
	//GetLocalTime(&st);
	//wsprintf(sTime, L"%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
	wsprintf(sTime, L"00:%02d:%02d", timer / 60, timer % 60);
	GetWindowRect(hWnd, &r);
	r.right -= r.left;
	r.left = 0;
	r.bottom -= r.top;
	r.top = 0;
	// start debug
	WCHAR mess[MAX_LOADSTRING];
	wsprintf(mess, L"left: %d top: %d right: %d buttom: %d\n", r.left, r.top, r.right, r.bottom);
	OutputDebugString(sTime);
	// end debug
	SelectObject(memDC, hFont);
	DrawText(memDC, sTime, lstrlen(sTime), &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	BitBlt(hdc, 0, 0, bmpObj.bmWidth, bmpObj.bmHeight, memDC, 0, 0, SRCCOPY);

	DeleteDC(memDC);
	ReleaseDC(hWnd, hdc);
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
    switch (message)
    {
	case WM_CREATE:
		initData(hWnd);
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
    case WM_PAINT:
		//drawClock(hWnd);
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		//
		EndPaint(hWnd, &ps);
	}
        break;
	case WM_TIMER:
		drawClock(hWnd);
		--timer;
		break;
	case WM_RBUTTONDOWN:
		DestroyWindow(hWnd);
		break;
    case WM_DESTROY:
		DeleteObject(hBmp);
		DeleteObject(hFont);
		DeleteObject(hRgn);
        PostQuitMessage(0);
		KillTimer(hWnd, COUNTDOWN);
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
