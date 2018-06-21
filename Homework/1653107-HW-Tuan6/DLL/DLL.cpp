// DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <Windowsx.h>
#include "DLL.h"

#define EXPORT		__declspec(dllexport)
#define VKC_CTRL		162
#define VKC_SHIFT	160
#define VKC_L		76
#define VKC_U		85

extern HINSTANCE hinstLib;
extern SHARED_DATA  *pSharedData;

HHOOK hHook = NULL;

LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0) 	// do not process message 
		return CallNextHookEx(hHook, nCode, wParam, lParam);
	
	if ((nCode == HC_ACTION) && (wParam == WM_KEYDOWN || wParam == WM_KEYUP || wParam == WM_SYSKEYDOWN || WM_SYSKEYUP)) {
		PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)lParam;
		switch (p->vkCode)
		{
		case VKC_CTRL:
			pSharedData->sum = VKC_CTRL;
			break;
		case VKC_SHIFT:
			if (pSharedData->sum == VKC_CTRL)
				pSharedData->sum += VKC_SHIFT;
			break;
		case VKC_L:
			if (pSharedData->sum == VKC_CTRL + VKC_SHIFT) 
				pSharedData->isLock = true;
			break;
		case VKC_U:
			if (pSharedData->sum == VKC_CTRL + VKC_SHIFT) 
				pSharedData->isLock = false;
			break;
		default:
			pSharedData->sum = 0;
			break;
		}
		if (pSharedData->isLock)
			return 1;
	}

	return CallNextHookEx(hHook, nCode, wParam, lParam);
}

EXPORT void _doInstallHook(HWND hWnd)
{
	if (hHook != NULL) return;

	hHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardHookProc, hinstLib, 0);
	if (!hHook)
		MessageBox(hWnd, L"Setup hook fail", L"Result", MB_OK);
}

EXPORT void _doRemoveHook(HWND hWnd)
{
	if (hHook == NULL) return;
	UnhookWindowsHookEx(hHook);
	hHook = NULL;
}

