// CoCaro.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "CoCaro.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
BOOL turn = true;	// true: P1 - false: P2

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void drawX(HDC hdc, int x, int y);
void drawO(HDC hdc, int x, int y);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings

	/*
	 * int LoadString(HINSTANCE hInstance, UINT uID, LPTSTR lpBuffer, int nBufferMax);
	 * hInstance: dialog chứa file string resource được thực thi
	 * uID: id của chuỗi string trong string resource
	 * lpBuffer: con trỏ đến chuỗi chứa string được load vào
	 * bBufferMax: kích thước tối đa của chuỗi string được load vào
	 * Chức năng: Chuyển các chuỗi từ string resource (string table) vào chương trình
	 */
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_COCARO, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	/*
	 * HACCEL LoadAccelerators(HINSTANCE hInstance, LPCTSTR lpTableName)
	 * hInstance: Instance xử lý khi được nạp bảng accelerator
	 * lpTableName: Tên bảng accelerator
	 * Chức năng: Nạp bảng accerlerator từ resource data
	 */
	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_COCARO));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_COCARO));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_COCARO);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	/*
	 * ATOM RegisterClassExW(const WNDCLASSEXW*)
	 * Chức năng: Đăng ký một lớp cửa sổ cho những lần dùng tiếp theo
	 */
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


	 // Chức năng: Tạo một cửa sổ mới từ cửa sổ hiện tại
	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	/*
	 * BOOL ShowWindow(HWND hWnd, int  nCmdShow)
	 * hWnd: Cửa sổ vừa tạo
	 * nCmdShow: Tham số khởi tạo cách hiển thị cho cửa sổ
	 * Chứ năng: Hiển thị cửa sổ được truyền vào với cách thức khởi tạo được truyền vào ở tham số thứ 2
	 */
	ShowWindow(hWnd, nCmdShow);

	/*
	 * BOOL UpdateWindow(HWND hWnd)
	 * hWnd: Cửa sổ cần vẽ
	 * Chức năng: Hiển thị (vẽ) cửa sổ lên giao diện người dùng
	 */
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
	case WM_COMMAND: // Người dùng chọn menu item
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
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
	case WM_PAINT: // Hệ thống hoặc ứng dụng yêu cầu vẽ cửa sổ hoặc các hàm UpdateWindow, RedrawWindow, DispatchMessage được gọi
	{
		PAINTSTRUCT ps;
		RECT* cRect = new RECT;
		POINT* point = new POINT;

		HDC hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, cRect);
		for (int i = cRect->left, j = cRect->top; i < cRect->right || j < cRect->bottom; i += 20, j += 20) {
			MoveToEx(hdc, i, cRect->top, point);
			LineTo(hdc, i, cRect->bottom);
		}
		for (int i = cRect->top; i < cRect->bottom; i += 20) {
			MoveToEx(hdc, cRect->left, i, point);
			LineTo(hdc, cRect->right, i);
		}
		//LineTo(hdc, 100, 200);
		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
	}
	break;
	case WM_DESTROY: // Cửa sổ đang bị hủy / đóng
		PostQuitMessage(0);
		break;
	case WM_LBUTTONDOWN:
	{
		PAINTSTRUCT ps;
		POINT* point = new POINT;
		HDC hdc = GetDC(hWnd);
		wchar_t mess[50];
		
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);
		wsprintf(mess, L"You clicked at x=%d y=%d", x, y);
		MessageBox(hWnd, mess, L"Notice", NULL);
		if (turn) {
			drawX(hdc, x, y);
			turn = !turn;
		}
			
		else {
			drawO(hdc, x, y);
			turn = !turn;
		}

		EndPaint(hWnd, &ps);
		ReleaseDC(hWnd, hdc);
	}
	default:
		// Hàm xử lý mặc định khi không có message nào được xử lý. Đảm bảo mọi message đề được xử lý
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

void drawX(HDC hdc, int x, int y) {
	int left = x - x % 20;
	int top = y - y % 20;

	HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, hpen);
	MoveToEx(hdc, left + 3, top + 3, NULL);
	LineTo(hdc, left + 17, top + 17);
	MoveToEx(hdc, left + 17, top + 3, NULL);
	LineTo(hdc, left + 3, top + 17);
}

void drawO(HDC hdc, int x, int y) {
	int left = x - x % 20;
	int top = y - y % 20;

	HPEN hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, hpen);
	Ellipse(hdc, left + 3, top + 3, left + 17, top + 17);
}