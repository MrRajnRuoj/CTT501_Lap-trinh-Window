// HW1.3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "HW1.3.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR szWindowClass1[MAX_LOADSTRING];
WCHAR szWindowClass2[MAX_LOADSTRING];
WCHAR szWindowClass3[MAX_LOADSTRING];
int openWindow = 0;
bool isContinue = true;
int nOpenningWindow[3] = { 0 };

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
ATOM                RegisterChildClass(HINSTANCE hInstance, int windowClass);

BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcClass1(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcClass2(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK	WndProcClass3(HWND, UINT, WPARAM, LPARAM);

void createWindow(HINSTANCE, int nCmdShow, int windowClass);

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
	LoadStringW(hInstance, IDC_HW13, szWindowClass, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_CLASS1_TITLE, szWindowClass1, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_CLASS2_TITLE, szWindowClass2, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_CLASS3_TITLE, szWindowClass3, MAX_LOADSTRING);
	MyRegisterClass(hInstance);
	RegisterChildClass(hInstance, 1);
	RegisterChildClass(hInstance, 2);
	RegisterChildClass(hInstance, 3);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HW13));

	MSG msg;

	// Main message loop:

	while (isContinue) {
		if (GetMessage(&msg, nullptr, 0, 0) && !TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (openWindow == 1) {
			createWindow(hInstance, nCmdShow, 1);
		}
		else if (openWindow == 2) {
			createWindow(hInstance, nCmdShow, 2);
		}
		else if (openWindow == 3) {
			createWindow(hInstance, nCmdShow, 3);
		}
		openWindow = 0;
		

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
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HW13));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCEW(IDC_HW13);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

ATOM RegisterChildClass(HINSTANCE hInstance, int windowClass)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	if (windowClass == 1) {
		wcex.lpfnWndProc = WndProcClass1;
		wcex.lpszClassName = szWindowClass1;
	}
	else if (windowClass == 2) {
		wcex.lpfnWndProc = WndProcClass2;
		wcex.lpszClassName = szWindowClass2;
	}
	else if (windowClass == 3) {
		wcex.lpfnWndProc = WndProcClass3;
		wcex.lpszClassName = szWindowClass3;
	}

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HW13));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	
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

void createWindow(HINSTANCE hInstance, int nCmdShow, int windowClass) {
	WCHAR title[50];
	HWND hWnd;

	wsprintf(title, L"Class %d - Window %d", windowClass, nOpenningWindow[windowClass]);
	if (windowClass == 1) {
		hWnd = CreateWindowW(szWindowClass1, title, WS_OVERLAPPEDWINDOW, 200, 200, 500, 500, nullptr, nullptr, hInstance, nullptr);
	}
	else if (windowClass == 2) {
		hWnd = CreateWindowW(szWindowClass2, title, WS_OVERLAPPEDWINDOW, 200, 200, 500, 500, nullptr, nullptr, hInstance, nullptr);
	}
	else if (windowClass == 3) {
		hWnd = CreateWindowW(szWindowClass3, title, WS_OVERLAPPEDWINDOW, 200, 200, 500, 500, nullptr, nullptr, hInstance, nullptr);
	}

	if (!hWnd) {
		return;
	}
	++nOpenningWindow[windowClass];
	ShowWindow(hWnd, nCmdShow);
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
	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
			case ID_CLASS1:
				openWindow = 1;
				break;
			case ID_CLASS2:
				openWindow = 2;
				break;
			case ID_CLASS3:
				openWindow = 3;
				break;
			case ID_EXIT:
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
			EndPaint(hWnd, &ps);
		}
		break;
	case WM_CLOSE:
		DestroyWindow(hWnd);
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


LRESULT CALLBACK WndProcClass1(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		
		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		PAINTSTRUCT ps;
		HDC hdc = GetDC(hWnd);
		int xPos = LOWORD(lParam);
		int yPos = HIWORD(lParam);

		Ellipse(hdc, xPos - 100, yPos - 100, xPos + 100, yPos + 100);
		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hWnd);
	case WM_DESTROY:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProcClass2(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		PAINTSTRUCT ps;
		HDC hdc = GetDC(hWnd);
		int xPos = LOWORD(lParam);
		int yPos = HIWORD(lParam);

		Rectangle(hdc, xPos - 50, yPos - 50, xPos + 50, yPos + 50);
		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hWnd);
	case WM_DESTROY:
		DestroyWindow(hWnd);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK WndProcClass3(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_EXIT:
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

		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		PAINTSTRUCT ps;
		HDC hdc = GetDC(hWnd);
		int xPos = LOWORD(lParam);
		int yPos = HIWORD(lParam);

		Rectangle(hdc, xPos - 100, yPos - 50, xPos + 100, yPos + 50);
		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
		break;
	}
	case WM_CLOSE:
		DestroyWindow(hWnd);
	case WM_DESTROY:
		DestroyWindow(hWnd);
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
