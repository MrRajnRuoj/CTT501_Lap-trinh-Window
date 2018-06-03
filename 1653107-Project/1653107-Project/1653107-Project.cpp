// 1653107-Project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1653107-Project.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR szChildClass[MAX_LOADSTRING];				// child windown class name
HWND hwndMDIClient = NULL;
HWND hFrameWnd = NULL;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildWndProc(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_MY1653107PROJECT, szWindowClass, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_CHILD_CLASS, szChildClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1653107PROJECT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(hFrameWnd, hAccelTable, &msg))
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1653107PROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1653107PROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	// child window 
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = ChildWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 8; // 8 bytes - x64
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1653107PROJECT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szChildClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	return 1;
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

   hFrameWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hFrameWnd)
   {
	   return FALSE;
   }

   ShowWindow(hFrameWnd, nCmdShow);
   UpdateWindow(hFrameWnd);

   return TRUE;
}
void onCreateMDIClient(HWND hWnd) {
	CLIENTCREATESTRUCT ccs;

	ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), 2);
	ccs.idFirstChild = 50001;
	hwndMDIClient = CreateWindow(L"MDICLIENT",
		(LPCTSTR)NULL,
		WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
		0, 0, 0, 0,
		hWnd,
		(HMENU)NULL,
		hInst,
		(LPVOID)&ccs);
	ShowWindow(hwndMDIClient, SW_SHOW);
}

void onCreateChileWnd(int nWnd) {
	MDICREATESTRUCT mdiCreate;
	WCHAR title[MAX_LOADSTRING];

	ZeroMemory(&mdiCreate, sizeof(MDICREATESTRUCT));
	wsprintf(title, L"Noname-%d.drw", nWnd);

	mdiCreate.szClass = szChildClass;
	mdiCreate.szTitle = title;
	mdiCreate.hOwner = hInst;
	mdiCreate.x = CW_USEDEFAULT;
	mdiCreate.y = CW_USEDEFAULT;
	mdiCreate.cx = CW_USEDEFAULT;
	mdiCreate.cy = CW_USEDEFAULT;
	mdiCreate.style = 0;
	mdiCreate.lParam = NULL;

	SendMessage(hwndMDIClient, WM_MDICREATE, 0, (LONG)(LPMDICREATESTRUCT)&mdiCreate);
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
	static int nWnd = 0;

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_FILE_NEW:
			++nWnd;
			onCreateChileWnd(nWnd);
			break;
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			break;
		}
	}
	break;
	case WM_CREATE:
		onCreateMDIClient(hWnd);
		return 0;
	case WM_SIZE:
	{
		UINT w, h;

		w = LOWORD(lParam);
		h = HIWORD(lParam);
		MoveWindow(hwndMDIClient, 0, 0, w, h, TRUE);
		break;
	}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefFrameProc(hWnd, hwndMDIClient, message, wParam, lParam);
}

// Processes messages for Child Windown
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		break;
	case WM_MDIACTIVATE:
		break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	case WM_SIZE:
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	}
	return DefMDIChildProc(hWnd, message, wParam, lParam);
}