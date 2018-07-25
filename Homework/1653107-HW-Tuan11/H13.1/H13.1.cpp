// H13.1.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "H13.1.h"
#include <commdlg.h>
#include   <mmsystem.h>
#include <vfw.h>
#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
WCHAR szFileName[MAX_LOADSTRING];
MCIDEVICEID		mciWaveDevID = NULL;

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
	LoadStringW(hInstance, IDC_H131, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_H131));

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
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_H131));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_H131);
	wcex.lpszClassName = szWindowClass;
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

void openFile(HWND hWnd) {
	OPENFILENAME ofn;
	wchar_t  szFilter[] = L"Wave file\0*.wav\0MIDI file\0*.mid\0All files\0*.*\0";

	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFilter = szFilter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFile = szFileName;
	ofn.nMaxFile = 128;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (!GetOpenFileName(&ofn))
		MessageBox(hWnd, L"Error opening file!", L"Error", MB_OK);
}
bool isWave() {
	HMMIO hmmio;

	// Mo file 
	if (!(hmmio = mmioOpen(szFileName, 0, MMIO_READ | MMIO_ALLOCBUF)))
		return FALSE;

	MMCKINFO mmckinfoParent;   // Group Header (special chunk)

							   // Dinh vi nhom wave (group header) 
	mmckinfoParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');

	// Neu khong co nhom wave thi day la khong phai thuoc dinh dang wave
	if (mmioDescend(hmmio, (LPMMCKINFO)&mmckinfoParent, 0, MMIO_FINDRIFF))
		return FALSE;

	// Nguoc lai dung -> dung
	return TRUE;

}
bool isMIDI() {
	HMMIO hmmio;

	// Mo file 
	if (!(hmmio = mmioOpen(szFileName, 0, MMIO_READ | MMIO_ALLOCBUF)))
		return FALSE;

	MMCKINFO mmckinfoSubchunk;

	memset(&mmckinfoSubchunk, 0, sizeof(mmckinfoSubchunk));

	// Tim nhom MThd 
	mmckinfoSubchunk.ckid = mmioFOURCC('M', 'T', 'h', 'd');

	// Neu khong tim thay nhom MThd -> khong phai file Midi
	if (mmioDescend(hmmio, &mmckinfoSubchunk, 0, MMIO_FINDCHUNK))
		return FALSE;

	// Nguoc lai -> dung
	return TRUE;
}
void playMedia(HWND hWnd, int& volume) {
	// Mo wave/midi
	MCI_OPEN_PARMS	mciOpenParams;
	MCIERROR		dwReturn;

	// mciOpenParams.lpstrDeviceType phai dung voi flag MCI_OPEN_TYPE
	if (isWave())	mciOpenParams.lpstrDeviceType = L"waveaudio";
	else if (isMIDI())  mciOpenParams.lpstrDeviceType = L"sequencer";
	else {
		MessageBox(hWnd, L"File type not supported !", L"Error", MB_OK);
		return;
	}

	mciOpenParams.lpstrElementName = szFileName;	// phai dung voi flag MCI_OPEN_ELEMENT

	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
		(DWORD)(LPVOID)&mciOpenParams))
	{
		wchar_t szError[128];

		mciGetErrorString(dwReturn, szError, 128);

		MessageBox(hWnd, szError, L"Error", MB_OK);
		return;
	}

	// Lay Device ID
	mciWaveDevID = mciOpenParams.wDeviceID;

	// Play file
	MCI_PLAY_PARMS mciPlayParams;
	mciPlayParams.dwCallback = (unsigned long)hWnd;			// cua so nhan message MM_MCINOTIFY
	waveOutSetVolume(NULL, volume);
	if (dwReturn = mciSendCommand(mciWaveDevID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParams))
	{
		wchar_t szError[128];

		mciSendCommand(mciWaveDevID, MCI_CLOSE, 0, 0L);

		mciGetErrorString(dwReturn, szError, 128);

		MessageBox(hWnd, szError, L"Error", MB_OK);
		return;
	}
}
void stopMedia(LPARAM lParam) {
	if (mciWaveDevID)
		mciSendCommand(mciWaveDevID, MCI_STOP, 0, 0);
	mciSendCommand(lParam, MCI_CLOSE, 0, 0L);
}
void pauseMedia() {
	if (mciWaveDevID)
		mciSendCommand(mciWaveDevID, MCI_PAUSE, 0, 0);
}
void resumeMedia() {
	if (mciWaveDevID)
		mciSendCommand(mciWaveDevID, MCI_RESUME, 0, 0);
}
void increaseVolume(int &volume) {
	if (mciWaveDevID) {
		volume += 13000;
		if (volume > 65535)
			volume = 65535;
		waveOutSetVolume(NULL, volume);
	}
}
void decreaseVolume(int& volume) {
	if (mciWaveDevID) {
		volume -= 13000;
		if (volume < 0)
			volume = 0;
		waveOutSetVolume(NULL, volume);
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
	static int volume;
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_OPEN:
			openFile(hWnd);
			break;
		case IDM_PLAY:
			playMedia(hWnd, volume);
			break;
		case IDM_PAUSE:
			pauseMedia();
			break;
		case IDM_RESUME:
			resumeMedia();
			break;
		case IDM_STOP:
			stopMedia(lParam);
			break;
		case IDM_VOLUME_INC:
			increaseVolume(volume);
			break;
		case IDM_VOLUME_DEC:
			decreaseVolume(volume);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_CREATE:
		volume = 39000;
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
