// H10.1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "H10.1.h"
#include <commdlg.h>
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
    LoadStringW(hInstance, IDC_H101, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H101));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H101));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_H101);
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
	static HBITMAP hBmp;
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
			switch (wmId)
			{
			case IDM_LOAD_RC_BITMAP:
			{
				HDC hdc, memDC;
				HBITMAP hOldBmp;
				BITMAP bmp;

				hBmp = LoadBitmap(hInst, MAKEINTRESOURCE(IDB_BITMAP1));
				hdc = GetDC(hWnd);
				memDC = CreateCompatibleDC(hdc);

				GetObject(hBmp, sizeof(BITMAP), &bmp);
				hOldBmp = (HBITMAP)SelectObject(memDC, hBmp);
				BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, memDC, 0, 0, SRCCOPY);
				SelectObject(memDC, hOldBmp);

				DeleteDC(memDC);
				ReleaseDC(hWnd, hdc);
				EnableMenuItem(GetMenu(hWnd), IDM_FIT_TO_WINDOW, MF_ENABLED | MF_BYCOMMAND);
			}
			break;
			case IDM_LOAD_FILE_BITMAP:
			{
				HDC hdc, memDC;
				BITMAP bmp;
				HBITMAP hOldBmp;

				hdc = GetDC(hWnd);
				memDC = CreateCompatibleDC(hdc);

				OPENFILENAME ofn;
				TCHAR szFile[256];
				TCHAR szFilter[] = L"(*.bmp)\0 * .bmp\0(*.ico)\0 * .ico\0";
				szFile[0] = '\0';
				// Khởi tạo struct
				ZeroMemory(&ofn, sizeof(OPENFILENAME));
				ofn.lStructSize = sizeof(OPENFILENAME);
				ofn.hwndOwner = hWnd;
				ofn.lpstrFilter = szFilter;
				ofn.nFilterIndex = 1;
				ofn.lpstrFile = szFile; // chuỗi tên file trả về
				ofn.nMaxFile = sizeof(szFile);
				ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
				if (GetOpenFileName(&ofn)) {
					hBmp = (HBITMAP)LoadImage(hInst, szFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
					hOldBmp = (HBITMAP)SelectObject(memDC, hBmp);
					GetObject(hBmp, sizeof(BITMAP), &bmp);
					BitBlt(hdc, 0, 0, bmp.bmWidth, bmp.bmHeight, memDC, 0, 0, SRCCOPY);
					SelectObject(memDC, hOldBmp);
				}

				DeleteDC(memDC);
				ReleaseDC(hWnd, hdc);
				EnableMenuItem(GetMenu(hWnd), IDM_FIT_TO_WINDOW, MF_ENABLED | MF_BYCOMMAND);
			}
				break;
			case IDM_FIT_TO_WINDOW:
			{
				HDC hdc, memDC;
				RECT r;
				hdc = GetDC(hWnd);
				memDC = CreateCompatibleDC(hdc);
				HBITMAP hOldBmp = (HBITMAP)SelectObject(memDC, hBmp);
				BITMAP bmp;
				GetObject(hBmp, sizeof(BITMAP), &bmp);
				GetClientRect(hWnd, &r);
				StretchBlt(hdc, 0, 0, r.right - r.left, r.bottom - r.top, memDC, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
				DeleteDC(memDC);
				ReleaseDC(hWnd, hdc);
			}
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_CREATE:
		EnableMenuItem(GetMenu(hWnd), IDM_FIT_TO_WINDOW, MF_DISABLED | MF_BYCOMMAND);
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
		DeleteObject(hBmp);
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
