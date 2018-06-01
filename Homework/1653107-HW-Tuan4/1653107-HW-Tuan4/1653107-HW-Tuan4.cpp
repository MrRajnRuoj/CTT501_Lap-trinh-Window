// 1653107-HW-Tuan4.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1653107-HW-Tuan4.h"

#define MAX_LOADSTRING 100

struct CHILD_WND_DATA {
	BYTE type;
	HWND hWnd;
	COLORREF rgbColor;
	LOGFONT logFont;
};

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HWND hwndMDIClient = NULL;
HWND hFrameWindow = NULL;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    EditTextWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    BitmapWndProc(HWND, UINT, WPARAM, LPARAM);

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
	LoadStringW(hInstance, IDC_MY1653107HWTUAN4, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1653107HWTUAN4));

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

	// frame window	
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1653107HWTUAN4));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MY1653107HWTUAN4);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	// child window (Edit text class)
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = EditTextWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 8; // 8 bytes - x64
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1653107HWTUAN4));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"MDI_EDIT_TEXT";
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	// child window (Bitmap class)
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = BitmapWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 8; // 8 bytes - x64
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1653107HWTUAN4));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"MDI_BITMAP";
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

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
	hFrameWindow = hWnd;
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

void onMDIActive(HWND hWnd) {
	CHILD_WND_DATA* wndData = (CHILD_WND_DATA*)GetWindowLongPtr(hWnd, 0);
	if (wndData == NULL)
		return;
	HMENU hMenu = GetMenu(hFrameWindow);
	EnableMenuItem(hMenu, 2, MF_ENABLED | MF_BYPOSITION);
	EnableMenuItem(hMenu, IDM_CHOOSE_COLOR, MF_ENABLED | MF_BYCOMMAND);
	if (wndData->type == 0) {
		EnableMenuItem(hMenu, 1, MF_ENABLED | MF_BYPOSITION);
		EnableMenuItem(hMenu, 3, MF_DISABLED | MF_BYPOSITION);
		EnableMenuItem(hMenu, IDM_CHOOSE_FONT, MF_ENABLED | MF_BYCOMMAND);
	}
	else {
		EnableMenuItem(hMenu, 1, MF_DISABLED | MF_BYPOSITION);
		EnableMenuItem(hMenu, 3, MF_ENABLED | MF_BYPOSITION);
		EnableMenuItem(hMenu, IDM_CHOOSE_FONT, MF_DISABLED | MF_BYCOMMAND);
	}
}

void onInitMDIChild(HWND hWnd, int type) {
	CHILD_WND_DATA* wndData;
	wndData = (CHILD_WND_DATA*)VirtualAlloc(NULL, sizeof(CHILD_WND_DATA), MEM_COMMIT, PAGE_READWRITE);
	wndData->type = type;
	wndData->hWnd = hWnd;
	SetLastError(0);
	if (SetWindowLongPtr(hWnd, 0, (LONG_PTR)wndData) == 0) {
		if (GetLastError() != 0)
			MessageBox(hWnd, L"Set data error", L"Error", MB_ICONERROR);
	}
}
LRESULT CALLBACK MDICloseProc(HWND hWnd, LPARAM lParam) {
	SendMessage(hwndMDIClient, WM_MDIDESTROY, (WPARAM)hWnd, 0L);
	return 1;
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
	static UINT curDrawSel = -1;
	static UINT nWndText = 0;
	static UINT nWndBitmap = 0;

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_NEW_TEXT:
		{
			MDICREATESTRUCT mdiCreate;
			WCHAR title[MAX_LOADSTRING];
			wsprintf(title, L"Text %d", ++nWndText);

			ZeroMemory(&mdiCreate, sizeof(MDICREATESTRUCT));
			mdiCreate.szClass = L"MDI_EDIT_TEXT";
			mdiCreate.szTitle = title;
			mdiCreate.hOwner = hInst;
			mdiCreate.x = CW_USEDEFAULT;
			mdiCreate.y = CW_USEDEFAULT;
			mdiCreate.cx = CW_USEDEFAULT;
			mdiCreate.cy = CW_USEDEFAULT;
			mdiCreate.style = 0;
			mdiCreate.lParam = NULL;

			SendMessage(hwndMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mdiCreate);
			break;
		}
		case IDM_NEW_BITMAP:
		{
			MDICREATESTRUCT mdiCreate;
			WCHAR title[MAX_LOADSTRING];
			wsprintf(title, L"Bitmap %d", ++nWndBitmap);

			ZeroMemory(&mdiCreate, sizeof(MDICREATESTRUCT));
			mdiCreate.szClass = L"MDI_BITMAP";
			mdiCreate.szTitle = title;
			mdiCreate.hOwner = hInst;
			mdiCreate.x = CW_USEDEFAULT;
			mdiCreate.y = CW_USEDEFAULT;
			mdiCreate.cx = CW_USEDEFAULT;
			mdiCreate.cy = CW_USEDEFAULT;
			mdiCreate.style = 0;
			mdiCreate.lParam = NULL;

			SendMessage(hwndMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mdiCreate);
			break;
		}
		case IDM_PIXEL:
		case IDM_RECTANGLE:
		case IDM_ELLIPSE:
		case IDM_LINE:
		{
			HMENU hMenu = GetMenu(hWnd);
			CheckMenuItem(hMenu, curDrawSel, MF_UNCHECKED | MF_BYCOMMAND);
			CheckMenuItem(hMenu, wmId, MF_CHECKED | MF_BYCOMMAND);
			curDrawSel = wmId;
			break;
		}
		case IDM_VERTICAL:
			TileWindows(hwndMDIClient, MDITILE_VERTICAL, NULL, NULL, NULL);
			break;
		case IDM_HORIZONTAL:
			TileWindows(hwndMDIClient, MDITILE_HORIZONTAL, NULL, NULL, NULL);
			break;
		case IDM_CASCADE:
			SendMessage(hwndMDIClient, WM_MDICASCADE, 0, 0);
			break;
		case IDM_CLOSE_ALL:
			EnumChildWindows(hwndMDIClient, (WNDENUMPROC)MDICloseProc, 0L);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		}
	}
	break;
	case WM_CREATE:
	{
		CLIENTCREATESTRUCT ccs;
		ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), 4);
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

		HMENU hMenu = GetMenu(hWnd);
		EnableMenuItem(hMenu, 1, MF_DISABLED | MF_BYPOSITION);
		EnableMenuItem(hMenu, 2, MF_DISABLED | MF_BYPOSITION);
		EnableMenuItem(hMenu, 3, MF_DISABLED | MF_BYPOSITION);
		break;
	}
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
	default:
		break;
	}
	return DefFrameProc(hWnd, hwndMDIClient, message, wParam, lParam);
}

// Processes messages for EditText MDI
LRESULT CALLBACK EditTextWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		onInitMDIChild(hWnd, 0);
		break;
	case WM_MDIACTIVATE:
		onMDIActive(hWnd);
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

// Processes messages for Bitmap MDI
LRESULT CALLBACK BitmapWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		onInitMDIChild(hWnd, 1);
		break;
	case WM_MDIACTIVATE:
		onMDIActive(hWnd);
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
