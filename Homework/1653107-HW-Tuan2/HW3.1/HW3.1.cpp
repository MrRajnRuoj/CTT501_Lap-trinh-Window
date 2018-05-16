// HW3.1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "HW3.1.h"

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
    LoadStringW(hInstance, IDC_HW31, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HW31));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HW31));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HW31);
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

void addCheckBox(HWND hWnd, int itemID) {
	HMENU hMenu = GetMenu(hWnd);
	int flag;

	if (GetMenuState(hMenu, itemID, MF_BYCOMMAND) & MF_CHECKED)
		flag = MF_UNCHECKED;
	else
		flag = MF_CHECKED;
	CheckMenuItem(hMenu, itemID, flag);
}

void changeMenuBar(HWND hWnd, bool &isChangeMenu) {
	HMENU hMenu = GetMenu(hWnd);

	if (isChangeMenu) {
		EnableMenuItem(hMenu, ID_FILE_OPEN, MF_GRAYED);
		EnableMenuItem(hMenu, ID_FILE_SAVE, MF_GRAYED);
		EnableMenuItem(hMenu, ID_FILE_SAVE_AS, MF_GRAYED);
		EnableMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_GRAYED);
		EnableMenuItem(hMenu, ID_DRAW_LINE, MF_GRAYED);
		EnableMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_GRAYED);
		EnableMenuItem(hMenu, ID_DRAW_PIXEL, MF_GRAYED);
		EnableMenuItem(hMenu, ID_DRAW_FORMAT_BRUSH, MF_GRAYED);
		EnableMenuItem(hMenu, ID_DRAW_FORMAT_COLOR, MF_GRAYED);
	}
	else {
		EnableMenuItem(hMenu, ID_FILE_OPEN, MF_ENABLED);
		EnableMenuItem(hMenu, ID_FILE_SAVE, MF_ENABLED);
		EnableMenuItem(hMenu, ID_FILE_SAVE_AS, MF_ENABLED);
		EnableMenuItem(hMenu, ID_DRAW_ELLIPSE, MF_ENABLED);
		EnableMenuItem(hMenu, ID_DRAW_LINE, MF_ENABLED);
		EnableMenuItem(hMenu, ID_DRAW_RECTANGLE, MF_ENABLED);
		EnableMenuItem(hMenu, ID_DRAW_PIXEL, MF_ENABLED);
		EnableMenuItem(hMenu, ID_DRAW_FORMAT_BRUSH, MF_ENABLED);
		EnableMenuItem(hMenu, ID_DRAW_FORMAT_COLOR, MF_ENABLED);
	}
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
	static bool isChangeMenu = false;

    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
			case ID_FILE_NEW:
			case ID_FILE_OPEN:
			case ID_FILE_SAVE:
			case ID_FILE_SAVE_AS:
			case ID_DRAW_ELLIPSE:
			case ID_DRAW_LINE:
			case ID_DRAW_RECTANGLE:
			case ID_DRAW_PIXEL:
			case ID_DRAW_FORMAT_BRUSH:
			case ID_DRAW_FORMAT_COLOR:
				addCheckBox(hWnd, wmId);
				break;
			case ID_CHANGE_MENU:
				isChangeMenu = !isChangeMenu;
				changeMenuBar(hWnd, isChangeMenu);
				break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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
