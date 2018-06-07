// 1653107-HW-Tuan5.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1653107-HW-Tuan5.h"

#define MAX_LOADSTRING 100
#define IMPORT __declspec(dllimport)
#define CONG	12345
#define TRU		12346
#define NHAN	12347
#define CHIA	12348

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
//LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    CalculateWndProc(HWND, UINT, WPARAM, LPARAM);

// Load function from dll
IMPORT int Cong(int a, int b);
IMPORT int Tru(int a, int b);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	//LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	//LoadStringW(hInstance, IDC_MY1653107HWTUAN5, szWindowClass, MAX_LOADSTRING);
	//MyRegisterClass(hInstance);

	// Perform application initialization:
	//if (!InitInstance (hInstance, nCmdShow))
	//{
	//    return FALSE;
	//}
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG_CALCULATE), NULL, CalculateWndProc);
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1653107HWTUAN5));

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
//ATOM MyRegisterClass(HINSTANCE hInstance)
//{
//    WNDCLASSEXW wcex;
//
//    wcex.cbSize = sizeof(WNDCLASSEX);
//
//    wcex.style          = CS_HREDRAW | CS_VREDRAW;
//    wcex.lpfnWndProc    = WndProc;
//    wcex.cbClsExtra     = 0;
//    wcex.cbWndExtra     = 0;
//    wcex.hInstance      = hInstance;
//    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1653107HWTUAN5));
//    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1653107HWTUAN5);
//    wcex.lpszClassName  = szWindowClass;
//    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}

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
//BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//{
//   hInst = hInstance; // Store instance handle in our global variable
//
//   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
//      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);
//
//   if (!hWnd)
//   {
//      return FALSE;
//   }
//
//   ShowWindow(hWnd, nCmdShow);
//   UpdateWindow(hWnd);
//
//   return TRUE;
//}

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
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//    switch (message)
//    {
//    case WM_COMMAND:
//        {
//            int wmId = LOWORD(wParam);
//            // Parse the menu selections:
//            switch (wmId)
//            {
//            case IDM_ABOUT:
//                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
//                break;
//            case IDM_EXIT:
//                DestroyWindow(hWnd);
//                break;
//            default:
//                return DefWindowProc(hWnd, message, wParam, lParam);
//            }
//        }
//        break;
//    case WM_PAINT:
//        {
//            PAINTSTRUCT ps;
//            HDC hdc = BeginPaint(hWnd, &ps);
//            // TODO: Add any drawing code that uses hdc here...
//            EndPaint(hWnd, &ps);
//        }
//        break;
//    case WM_DESTROY:
//        PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}
void getValue(HWND hDlg, int& a, int& b) {
	WCHAR strValueA[MAX_LOADSTRING];
	WCHAR strValueB[MAX_LOADSTRING];

	GetDlgItemText(hDlg, IDC_VALUE_A, strValueA, MAX_LOADSTRING);
	GetDlgItemText(hDlg, IDC_VALUE_B, strValueB, MAX_LOADSTRING);
	a = _wtoi(strValueA);
	b = _wtoi(strValueB);
}

void setResult(HWND hDlg, int type, int result) {
	WCHAR strResult[MAX_LOADSTRING], strType[MAX_LOADSTRING];

	if (type == CONG)
		wsprintf(strType, L"+");
	else if (type == TRU)
		wsprintf(strType, L"-");
	else if (type == NHAN)
		wsprintf(strType, L"*");
	else if (type == CHIA)
		wsprintf(strType, L"/");
	wsprintf(strResult, L"Ket qua a %s b = %d", strType, result);
	SetDlgItemText(hDlg, IDC_STATIC_Result, strResult);
	SetWindowText(GetDlgItem(hDlg, IDC_STATIC_Result), strResult);
}

// Message handler for calculate box.
INT_PTR CALLBACK CalculateWndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	//UNREFERENCED_PARAMETER(lParam);
	static int a, b;

	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			// Parse the menu selections:
			switch (wmId)
			{
			case IDC_BUTTON_CONG:
				getValue(hDlg, a, b);
				//int result = Cong(a, b);
				setResult(hDlg, CONG, Cong(a, b));
				break;
			case IDC_BUTTON_TRU:
				getValue(hDlg, a, b);
				//int result = Tru(a, b);

				break;
			case IDC_BUTTON_NHAN:
				getValue(hDlg, a, b);
				break;
			case IDC_BUTTON_CHIA:
				getValue(hDlg, a, b);
				break;
			case IDCANCEL:
			case IDC_BUTTON_QUIT:
				EndDialog(hDlg, LOWORD(wParam));
				break;
			}
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}
