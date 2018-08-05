// H14.1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "H14.1.h"
#include <commdlg.h>
#include <Shlobj.h>

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
INT_PTR CALLBACK    Program(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.


    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H141));

    MSG msg;
	DialogBox(hInst, MAKEINTRESOURCE(IDD_COPY_PROGRAM), NULL, Program);

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
////
////  FUNCTION: MyRegisterClass()
////
////  PURPOSE: Registers the window class.
////
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
//    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H141));
//    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
//    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
//    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_H141);
//    wcex.lpszClassName  = szWindowClass;
//    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
//
//    return RegisterClassExW(&wcex);
//}
//
////
////   FUNCTION: InitInstance(HINSTANCE, int)
////
////   PURPOSE: Saves instance handle and creates main window
////
////   COMMENTS:
////
////        In this function, we save the instance handle in a global variable and
////        create and display the main program window.
////
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
////
////  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
////
////  PURPOSE:  Processes messages for the main window.
////
////  WM_COMMAND  - process the application menu
////  WM_PAINT    - Paint the main window
////  WM_DESTROY  - post a quit message and return
////
////
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
//		PostQuitMessage(0);
//        break;
//    default:
//        return DefWindowProc(hWnd, message, wParam, lParam);
//    }
//    return 0;
//}

INT_PTR CALLBACK Program(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static WCHAR sourceFile[256];
	static WCHAR destFolder[256];

	switch (message)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_NTHREAD), CB_ADDSTRING, 0, (LPARAM)L"1");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_NTHREAD), CB_ADDSTRING, 0, (LPARAM)L"2");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_NTHREAD), CB_ADDSTRING, 0, (LPARAM)L"3");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_NTHREAD), CB_ADDSTRING, 0, (LPARAM)L"4");
		SendMessage(GetDlgItem(hDlg, IDC_COMBO_NTHREAD), CB_ADDSTRING, 0, (LPARAM)L"5");
		return (INT_PTR)FALSE;
	case WM_COMMAND:
	{
		int wmID = LOWORD(wParam);
		switch (wmID)
		{
		case IDC_BUTTON_CHOOSE_FILE:
		{
			OPENFILENAME ofn;
			TCHAR szFile[256];
			TCHAR szFileTitle[256];
			TCHAR szFilter[] = L"";
			szFileTitle[0] = '\0';
			szFile[0] = '\0';
			// Khởi tạo struct
			ZeroMemory(&ofn, sizeof(OPENFILENAME));
			ofn.lStructSize = sizeof(OPENFILENAME);
			ofn.hwndOwner = hDlg;
			ofn.lpstrFilter = szFilter;
			ofn.nFilterIndex = 1;
			ofn.lpstrFile = szFile; // chuỗi tên file trả về
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFileTitle = szFileTitle;
			ofn.nMaxFileTitle = sizeof(szFileTitle);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			if (GetOpenFileName(&ofn)) {
				wsprintf(sourceFile, L"%s", szFile);
			}
		}
			break;
		case IDC_BUTTON_CHOOSE_FOLDER:
		{
			BROWSEINFO bInfo;
			bInfo.hwndOwner = hDlg;
			bInfo.pidlRoot = NULL;
			bInfo.pszDisplayName = destFolder;
			bInfo.lpszTitle = L"Please, select a folder"; // Title of the dialog
			bInfo.ulFlags = 0;
			bInfo.lpfn = NULL;
			bInfo.lParam = 0;
			bInfo.iImage = -1;

			LPITEMIDLIST lpItem = SHBrowseForFolder(&bInfo);
			if (lpItem != NULL)
			{
				SHGetPathFromIDList(lpItem, destFolder);
				
			}
		}
			break;
		case IDC_BUTTON_START:

			break;
		default:
			break;
		}
		return (INT_PTR)TRUE;
	}
	case WM_CLOSE:
		EndDialog(hDlg, IDCLOSE);
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return (INT_PTR)FALSE;
}
