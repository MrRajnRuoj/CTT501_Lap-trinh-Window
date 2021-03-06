﻿// HW4.1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "HW4.1.h"
#include <fstream>
#include <locale>
#include <codecvt>
#include <iostream>
#include <io.h>
#include <fcntl.h>

#define MAX_LOADSTRING 100
#define MAX_LENGTH		35

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

INT_PTR CALLBACK    inputDlgProc(HWND, UINT, WPARAM, LPARAM);

struct INFO_DATA
{
	WCHAR hoten[MAX_LENGTH];
	BOOL phai;
	WCHAR bomon[MAX_LENGTH];
};
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
    LoadStringW(hInstance, IDC_HW41, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HW41));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HW41));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HW41);
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
			case ID_DIALOG_INPUT:
			{
				INT_PTR iptr = DialogBox(hInst, MAKEINTRESOURCE(IDD_NhapThongTin), hWnd, inputDlgProc);
				if (iptr != IDCLOSE) {
					INFO_DATA* infData = (INFO_DATA*)iptr;
					const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
					std::wofstream fOut;
					fOut.open("info.txt", std::ios::out | std::ios::app);
					fOut.imbue(utf8_locale);
					WCHAR text[100];
					wsprintf(text, L"Họ tên: %s \nPhái: %s \nBộ môn: %s", infData->hoten, infData->phai == true ? L"Nam" : L"Nữ", infData->bomon);
					fOut << text << L"\n";
					fOut.close();
					delete infData;
				}
			}
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

INT_PTR CALLBACK inputDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, IDC_EDT_Hoten));
		CheckRadioButton(hDlg, IDC_RADIO_Nam, IDC_RADIO_Nu, IDC_RADIO_Nam);
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_Bomon), CB_ADDSTRING, 0, (LPARAM)L"Khoa học máy tính");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_Bomon), CB_ADDSTRING, 0, (LPARAM)L"Công nghệ phần mềm");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_Bomon), CB_ADDSTRING, 0, (LPARAM)L"Hệ thống thông tin");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_Bomon), CB_ADDSTRING, 0, (LPARAM)L"Mạng máy tính");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_Bomon), CB_ADDSTRING, 0, (LPARAM)L"Công nghệ tri thức");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_Bomon), CB_SETCURSEL, 0, 0);
		EnableWindow(GetDlgItem(hDlg, IDOK), FALSE);
		return (INT_PTR)FALSE;
	case WM_COMMAND:
	{
		int wmID = LOWORD(wParam);
		switch (wmID)
		{
		case IDC_EDT_Hoten:
			if (HIWORD(wParam) == EN_CHANGE) {
				EnableWindow(GetDlgItem(hDlg, IDOK), SendMessage((HWND)lParam, WM_GETTEXTLENGTH, 0, 0));
			}
			break;
		case IDCLOSE:
			EndDialog(hDlg, IDCLOSE);
			break;
		case IDOK:
			INFO_DATA* infData;
			infData = new INFO_DATA;
			GetDlgItemText(hDlg, IDC_EDT_Hoten, infData->hoten, MAX_LENGTH);
			infData->phai = IsDlgButtonChecked(hDlg, IDC_RADIO_Nam);
			GetDlgItemText(hDlg, IDC_COMBO_Bomon, infData->bomon, MAX_LENGTH);
			EndDialog(hDlg, (INT_PTR)infData);
			break;
		default:
			break;
		}
		return (INT_PTR)TRUE;
	}
	case WM_CLOSE:
		EndDialog(hDlg, IDCLOSE);
		break;
	default:
		break;
	}
	return (INT_PTR)FALSE;
}