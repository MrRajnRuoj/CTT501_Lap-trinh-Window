// DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <Windowsx.h>
#include "DLL.h"

#define EXPORT  __declspec(dllexport)

extern HINSTANCE hinstLib;
extern SHARED_DATA  *pSharedData;

HHOOK hHook = NULL;

LRESULT CALLBACK MouseHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0) // do not process message 
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	// process when Ctrl+Right mouse clicked
	if (wParam == WM_RBUTTONDOWN && GetAsyncKeyState(VK_CONTROL) < 0)
	{
		WCHAR szBuf[128];
		MOUSEHOOKSTRUCT *mHookData = (MOUSEHOOKSTRUCT *)lParam;
		wsprintf(szBuf, L"Ctrl+Right clicked at: %d, %d\n", mHookData->pt.x, mHookData->pt.y);
		wcscat_s(pSharedData->buffer, szBuf);
		pSharedData->n += wcslen(szBuf);
	}
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)	// do not process message 
		return CallNextHookEx(hHook, nCode, wParam, lParam);

	if ((nCode == HC_ACTION) && (wParam == WM_KEYUP))
		if (pSharedData->n == MAX_BUFFER)
			MessageBox(GetFocus(), L"Buffer is overflow", L"Error", MB_OK);
		else
		{
			PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
			pSharedData->buffer[pSharedData->n] = (WCHAR)p->vkCode;
			pSharedData->n++;
			pSharedData->buffer[pSharedData->n] = 0;
		}
	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

EXPORT void _doInstallHook(HWND hWnd)
{
	if (hHook != NULL) return;

	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardHookProc, hinstLib, 0);
	if (hHook)
		MessageBox(hWnd, L"Setup hook successfully", L"Result", MB_OK);
	else
		MessageBox(hWnd, L"Setup hook fail", L"Result", MB_OK);
}

EXPORT void _doRemoveHook(HWND hWnd)
{
	if (hHook == NULL) return;
	UnhookWindowsHookEx(hHook);
	hHook = NULL;
	MessageBox(hWnd, L"Remove hook successfully", L"Result", MB_OK);
}

