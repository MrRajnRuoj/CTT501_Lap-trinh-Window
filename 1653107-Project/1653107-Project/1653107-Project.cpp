// 1653107-Project.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "1653107-Project.h"
#include "ChildWindow.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR szChildClass[MAX_LOADSTRING];				// child windown class name
HWND hwndMDIClient = NULL;
HWND hFrameWnd = NULL;
HWND hToolBarWnd, hCurrWnd;
vector<ChildWindow*> arrChildWindow;
Mode curMode = Line;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    ChildWndProc(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_MY1653107PROJECT, szWindowClass, MAX_LOADSTRING);
	LoadStringW(hInstance, IDS_CHILD_CLASS, szChildClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);
    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY1653107PROJECT));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateMDISysAccel(hwndMDIClient,  &msg) && 
			!TranslateAccelerator(hFrameWnd, hAccelTable, &msg))
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1653107PROJECT));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY1653107PROJECT);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	// child window 
	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = ChildWndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 8; // 8 bytes - x64
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY1653107PROJECT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szChildClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassExW(&wcex);

	return 1;
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

   hFrameWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hFrameWnd)
   {
	   return FALSE;
   }

   ShowWindow(hFrameWnd, nCmdShow);
   UpdateWindow(hFrameWnd);

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
	static int nWnd = 0;
	static int curDrawSel;

	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case ID_FILE_NEW:
			++nWnd;
			onCreateChileWnd(nWnd);
			break;
		case ID_FILE_OPEN:
			MessageBox(hWnd, L"Bạn đã chọn Open", L"Notice", MB_OK);
			break;
		case ID_FILE_SAVE:
			MessageBox(hWnd, L"Bạn đã chọn Save", L"Notice", MB_OK);
			break;
		case ID_FILE_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_DRAW_COLOR:
			onChooseColor(hWnd);
			break; 
		case ID_DRAW_FONT:
			onChooseFont(hWnd);
			break;
		case ID_DRAW_LINE:
		case ID_DRAW_ELLIPSE:
		case ID_DRAW_RECTANGLE:
		case ID_DRAW_TEXT:
		case ID_DRAW_SELECTOBJECT:
		{
			HMENU hMenu = GetMenu(hWnd);
			CheckMenuItem(hMenu, curDrawSel, MF_UNCHECKED | MF_BYCOMMAND);
			CheckMenuItem(hMenu, wmId, MF_CHECKED | MF_BYCOMMAND);
			curDrawSel = wmId;
			curMode = (Mode)wmId;
			break;
		}
		case ID_WINDOW_TIDE:
			SendMessage(hwndMDIClient, WM_MDITILE, 0, 0);
			break;
		case ID_WINDOW_CASCADE:
			SendMessage(hwndMDIClient, WM_MDICASCADE, 0, 0);
			break;
		case ID_WINDOW_CLOSEALL:
			EnumChildWindows(hwndMDIClient, (WNDENUMPROC)MDICloseProc, 0L);
			break;
		}
	}
	break;
	case WM_CREATE:
	{
		onCreateMDIClient(hWnd);
		HMENU hMenu = GetMenu(hWnd);
		CheckMenuItem(hMenu, ID_DRAW_LINE, MF_CHECKED | MF_BYCOMMAND);
		curDrawSel = ID_DRAW_LINE;
		createToolBar(hWnd);
		addUserButton2Toolbar();
		return 0;
	}
	case WM_SIZE:
	{
		UINT w, h;

		w = LOWORD(lParam);
		h = HIWORD(lParam);
		MoveWindow(hwndMDIClient, 0, 29, w, h - 29, true);
		MoveWindow(hToolBarWnd, 0, 0, 0, 0, true);
		SendMessage(hwndMDIClient, WM_MDIICONARRANGE, 0, 0);
		return 0;
	}
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
	}

	return DefFrameProc(hWnd, hwndMDIClient, message, wParam, lParam);
}

// Processes messages for Child Windown
LRESULT CALLBACK ChildWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int idx = indexOfHandle(hWnd);
	switch (message)
	{
	case WM_CREATE:
		onInitMDIChild(hWnd);
		break;
	case WM_MDIACTIVATE:
		hCurrWnd = hWnd;
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_MOUSEMOVE:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	case WM_SIZE:
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
	}
	break;
	}
	return DefMDIChildProc(hWnd, message, wParam, lParam);
}

void onCreateMDIClient(HWND hWnd) {
	CLIENTCREATESTRUCT ccs;

	ccs.hWindowMenu = GetSubMenu(GetMenu(hWnd), 2);
	ccs.idFirstChild = 50001;
	hwndMDIClient = CreateWindow(L"MDICLIENT",
		(LPCTSTR)NULL,
		WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
		0, 0, 0, 0,
		hWnd,
		(HMENU)NULL,
		hInst,
		(LPVOID)&ccs);
	ShowWindow(hwndMDIClient, SW_SHOW);
}

void onCreateChileWnd(int nWnd) {
	MDICREATESTRUCT mdiCreate;
	WCHAR title[MAX_LOADSTRING];

	ZeroMemory(&mdiCreate, sizeof(MDICREATESTRUCT));
	wsprintf(title, L"Noname-%d.drw", nWnd);

	mdiCreate.szClass = szChildClass;
	mdiCreate.szTitle = title;
	mdiCreate.hOwner = hInst;
	mdiCreate.x = CW_USEDEFAULT;
	mdiCreate.y = CW_USEDEFAULT;
	mdiCreate.cx = CW_USEDEFAULT;
	mdiCreate.cy = CW_USEDEFAULT;
	mdiCreate.style = 0;
	mdiCreate.lParam = NULL;

	SendMessage(hwndMDIClient, WM_MDICREATE, 0, (LPARAM)(LPMDICREATESTRUCT)&mdiCreate);
}

void onChooseColor(HWND hWnd) {
	CHOOSECOLOR cc;
	COLORREF acrCustClr[16];
	DWORD rgbCurrent = RGB(255, 0, 0);

	ZeroMemory(&cc, sizeof(CHOOSECOLOR));
	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.hwndOwner = hWnd;
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
	if (ChooseColor(&cc)) {
		int idx = indexOfHandle(hCurrWnd);
		if (idx != -1)
			arrChildWindow[idx]->setColor(cc.rgbResult);
		else
			MessageBox(hWnd, L"Cannot find hCurrWnd to set color", L"Error", MB_OK);
	}
	else 
		MessageBox(hWnd, L"ChooseColor error!", L"Error", MB_OK);
}

void onChooseFont(HWND hWnd) {
	CHOOSEFONT cf;
	LOGFONT lf;

	ZeroMemory(&cf, sizeof(CHOOSEFONT));
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = hWnd;
	cf.lpLogFont = &lf;
	cf.Flags = CF_SCREENFONTS | CF_EFFECTS;
	if (ChooseFont(&cf)) {
		int idx = indexOfHandle(hCurrWnd);
		if (idx != -1)
			arrChildWindow[idx]->setFont(CreateFontIndirect(cf.lpLogFont));
		else
			MessageBox(hWnd, L"Cannot find hCurrWnd to set font", L"Error", MB_OK);
	}
	else
		MessageBox(hWnd, L"ChooseFont error!", L"Error", MB_OK);
}

LRESULT CALLBACK MDICloseProc(HWND hWnd, LPARAM lParam) {
	SendMessage(hwndMDIClient, WM_MDIDESTROY, (WPARAM)hWnd, 0L);
	return 1;
}

void createToolBar(HWND hWnd) {
	// loading Common Control DLL
	InitCommonControls();

	TBBUTTON tbButtons[] =
	{
		{ STD_FILENEW,	ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ STD_FILEOPEN,	ID_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ STD_FILESAVE,	ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
	};

	// create a toolbar
	hToolBarWnd = CreateToolbarEx(hWnd,
		WS_CHILD | WS_VISIBLE | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS,
		ID_TOOLBAR,
		sizeof(tbButtons) / sizeof(TBBUTTON),
		HINST_COMMCTRL,
		0,
		tbButtons,
		sizeof(tbButtons) / sizeof(TBBUTTON),
		BUTTON_WIDTH,
		BUTTON_HEIGHT,
		IMAGE_WIDTH,
		IMAGE_HEIGHT,
		sizeof(TBBUTTON));
}

void addUserButton2Toolbar() {
	// define new buttons
	TBBUTTON tbButtons[] =
	{
		{ 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
		{ 0, ID_DRAW_LINE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 1, ID_DRAW_RECTANGLE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 2, ID_DRAW_ELLIPSE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 3, ID_DRAW_TEXT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 4, ID_DRAW_SELECTOBJECT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
	};

	// structure contains the bitmap of user defined buttons. It contains 2 icons
	TBADDBITMAP	tbBitmap = { hInst,  IDB_BMP_TOOLBAR };

	// Add bitmap to Image-list of ToolBar
	int idx = (int)SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM) sizeof(tbBitmap) / sizeof(TBADDBITMAP),
		(LPARAM)(LPTBADDBITMAP)&tbBitmap);

	// identify the bitmap index of each button
	for (int i = 1; i <= 5; ++i)
		tbButtons[i].iBitmap += idx;


	// add buttons to toolbar
	SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM) sizeof(tbButtons) / sizeof(TBBUTTON),
		(LPARAM)(LPTBBUTTON)&tbButtons);
}

void onInitMDIChild(HWND hWnd) {
	ChildWindow* wndData;
	wndData = (ChildWindow*)VirtualAlloc(NULL, sizeof(ChildWindow), MEM_COMMIT, PAGE_READWRITE);
	wndData->setHandle(hWnd);
	if (SetWindowLongPtr(hWnd, 0, (LONG_PTR)wndData) == 0) {
		if (GetLastError() != 0)
			MessageBox(hWnd, L"Set data error", L"Error", MB_ICONERROR);
	}
	arrChildWindow.push_back(wndData);
}

int indexOfHandle(HWND hWnd) {
	for (int i = 0; i < arrChildWindow.size(); ++i) {
		if (arrChildWindow[i]->getHandle() == hWnd)
			return i;
	}
	return -1;
}