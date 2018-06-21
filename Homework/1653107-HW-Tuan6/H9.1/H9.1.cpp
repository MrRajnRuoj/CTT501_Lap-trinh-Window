// H9.1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <shellapi.h>
#include "H9.1.h"

#define MAX_LOADSTRING			100
#define IMPORT					__declspec(dllimport)
#define MY_WM_NOTIFYICON		WM_USER + 1
#define TRAY_ICON_ID			1	

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
INT_PTR CALLBACK    DialogProc(HWND, UINT, WPARAM, LPARAM);

IMPORT void _doInstallHook(HWND);
IMPORT void _doRemoveHook(HWND);

void  doMinimize(HWND hWnd);
void doMyNotify(HWND hWnd, WPARAM wParam, LPARAM lParam);
BOOL MyTaskBarAddIcon(HWND hWnd, UINT uID, HICON hIcon, LPCWSTR lpszTip);
BOOL MyTaskBarDeleteIcon(HWND hWnd, UINT uID);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
	hInst = hInstance;
	DialogBox(hInst, MAKEINTRESOURCE(IDD_MAIN_DIALOG), NULL, DialogProc);

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H91));

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


INT_PTR CALLBACK DialogProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
		_doInstallHook(hDlg);
        return (INT_PTR)TRUE;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        switch (wmId)
        {
		case IDC_SYSTEM_TRAY:
			doMinimize(hDlg);
			break;
		case IDC_QUIT:
        case IDCLOSE:
			_doRemoveHook(hDlg);
            EndDialog(hDlg, LOWORD(wParam));
            PostQuitMessage(0);
            return true;
        default:
            break;
        }
    }
	break;
    case WM_DESTROY:
		_doRemoveHook(hDlg);
        PostQuitMessage(0);
        break;
	case MY_WM_NOTIFYICON:
		doMyNotify(hDlg, wParam, lParam);
		break;
    }
    return (INT_PTR)FALSE;
}

void  doMinimize(HWND hWnd) {
	ShowWindow(hWnd, SW_HIDE);

	HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_SMALL));
	MyTaskBarAddIcon(hWnd, TRAY_ICON_ID, hIcon, L"Click to restore!");
}

BOOL MyTaskBarAddIcon(HWND hWnd, UINT uID, HICON hIcon, LPCWSTR lpszTip) {
	BOOL Kq;
	NOTIFYICONDATA tnid;

	tnid.cbSize = sizeof(NOTIFYICONDATA);
	tnid.hWnd = hWnd;
	tnid.uID = uID;
	tnid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
	tnid.uCallbackMessage = MY_WM_NOTIFYICON;
	tnid.hIcon = hIcon;
	if (lpszTip)
		lstrcpyn(tnid.szTip, lpszTip, sizeof(tnid.szTip));
	else
		tnid.szTip[0] = '\0';

	Kq = Shell_NotifyIcon(NIM_ADD, &tnid);

	if (hIcon)
		DestroyIcon(hIcon);

	return Kq;
}

BOOL MyTaskBarDeleteIcon(HWND hWnd, UINT uID)
{
	BOOL Kq;
	NOTIFYICONDATA tnid;

	tnid.cbSize = sizeof(NOTIFYICONDATA);
	tnid.hWnd = hWnd;
	tnid.uID = uID;

	Kq = Shell_NotifyIcon(NIM_DELETE, &tnid);
	return Kq;
}

void doMyNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	if (lParam == WM_LBUTTONDOWN) {

		MyTaskBarDeleteIcon(hWnd, TRAY_ICON_ID);

		ShowWindow(hWnd, SW_SHOW);

		ShowWindow(hWnd, SW_RESTORE);
	}
}