// Pac-Man.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Pac-Man.h"
#include <vector>
#include <cmath>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

struct Tam
{
	int x;
	int y;
};
std::vector<Tam> posPacDot;
Tam posPacMan;

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
	LoadStringW(hInstance, IDC_PACMAN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PACMAN));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PACMAN));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_PACMAN);
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
		CW_USEDEFAULT, 0, 500, 300, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
void generatePacMan(HWND hWnd) {
	RECT rect;
	GetClientRect(hWnd, &rect);
	srand(NULL);
	Tam pmTam;
	bool check = false;
	do
	{
		pmTam.x = rand() % (rect.right - rect.left + 1) + (rect.left - 20);
		pmTam.y = rand() % (rect.bottom - rect.top + 1) + (rect.top - 20);
		for (int i = 0; i < posPacDot.size(); ++i) {
			if (posPacDot[i].x > pmTam.x - 20 && posPacDot[i].x > pmTam.x + 20 &&
				posPacDot[i].y < pmTam.y - 20 && posPacDot[i].y < pmTam.y + 20)
				check = true;
			else
				check = false;

		}
		if (check == true)
			break;
	} while (true);
	posPacMan = pmTam;
}

void drawPacMan(HWND hWnd) {
	HDC hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	Rectangle(hdc, posPacMan.x - 10, posPacMan.y - 10, posPacMan.x + 10, posPacMan.y + 10);
	ReleaseDC(hWnd, hdc);
}

void generatePacDot(HWND hWnd) {
	RECT rect;
	GetClientRect(hWnd, &rect);

	srand(NULL);
	for (int i = 0; i < 10; i++) {
		Tam tam;

		tam.x = rand() % (rect.right - rect.left + 1) + (rect.left - 6);
		tam.y = rand() % (rect.bottom - rect.top + 1) + (rect.top - 6);

		posPacDot.push_back(tam);
	}
}

void drawPacDot(HWND hWnd, Tam tam) {
	HDC hdc = GetDC(hWnd);

	Ellipse(hdc, tam.x - 6, tam.y - 6, tam.x + 6, tam.y + 6);
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
	static bool isStart = false;

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_StartGame:
			isStart = true;
			for (int i = 0; i < 10; ++i)
				drawPacDot(hWnd, posPacDot[i]);
			drawPacMan(hWnd);
			break;
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
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
		{
			RECT r;
			GetClientRect(hWnd, &r);
			if (posPacMan.x - 10 > 0) {
				drawPacMan(hWnd);
				--posPacMan.x;
				//drawPacMan(hWnd);
			}
			break;
		}
		case VK_UP:
			break;
		case VK_RIGHT:
			break;
		case VK_DOWN:
			break;
		default:
			break;
		}
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		
		if (isStart) {
			for (int i = 0; i < 10; ++i)
				drawPacDot(hWnd, posPacDot[i]);
			drawPacMan(hWnd);
		}
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CREATE:
		generatePacDot(hWnd);
		generatePacMan(hWnd);
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
