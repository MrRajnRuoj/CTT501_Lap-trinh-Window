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
}

int Nhan(HWND hDlg, int a, int b) {
	typedef int(*MYPROC)(int, int);
	HINSTANCE hinstLib;
	MYPROC dllFncNhanAddr;
	hinstLib = LoadLibrary(L"CalculateInt.dll");

	if (hinstLib == NULL) {
		MessageBox(hDlg, L"Cannot load dll", L"Error", MB_OK);
		return -1;
	}
		
	dllFncNhanAddr = (MYPROC)GetProcAddress(hinstLib, "Nhan");
	if (dllFncNhanAddr == NULL) {
		MessageBox(hDlg, L"Cannot find function Nhan", L"Error", MB_OK);
		return -1;
	}
		
	int result = (dllFncNhanAddr)(a, b);
	FreeLibrary(hinstLib);
	return result;
}

int Chia(HWND hDlg, int a, int b) {
	if (b == 0) {
		MessageBox(hDlg, L"Could not devide by zero", L"Error", MB_OK);
		return -1;
	}
	typedef int(*MYPROC)(int, int);
	HINSTANCE hinstLib;
	MYPROC dllFncNhanAddr;
	hinstLib = LoadLibrary(L"CalculateInt.dll");

	if (hinstLib == NULL) {
		MessageBox(hDlg, L"Cannot load dll", L"Error", MB_OK);
		return -1;
	}

	dllFncNhanAddr = (MYPROC)GetProcAddress(hinstLib, "Chia");
	if (dllFncNhanAddr == NULL) {
		MessageBox(hDlg, L"Cannot find function Chia", L"Error", MB_OK);
		return -1;
	}

	int result = (dllFncNhanAddr)(a, b);
	FreeLibrary(hinstLib);
	return result;
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
				setResult(hDlg, CONG, Cong(a, b));
				break;
			case IDC_BUTTON_TRU:
				getValue(hDlg, a, b);
				setResult(hDlg, TRU, Tru(a, b));
				break;
			case IDC_BUTTON_NHAN:
				getValue(hDlg, a, b);
				setResult(hDlg, NHAN, Nhan(hDlg, a, b));
				break;
			case IDC_BUTTON_CHIA:
				getValue(hDlg, a, b);
				setResult(hDlg, CHIA, Chia(hDlg, a, b));
				break;
			case IDCANCEL:
			case IDC_BUTTON_QUIT:
				EndDialog(hDlg, LOWORD(wParam));
				PostQuitMessage(0);
				break;
			}
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}
