// DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DLL.h"
#include "resource.h"

#define EXPORTS __declspec(dllexport)

extern HINSTANCE hinstLib;
Province* glbProvince = NULL;


EXPORTS void inputPopulation(HWND hWnd, HGLOBAL hGlobalProvince, int x, int y) {
	BOOL* isSuccess;

	glbProvince = (Province*)GlobalLock(hGlobalProvince);
	if (glbProvince != NULL) 
		isSuccess = (BOOL*)DialogBox(hinstLib, MAKEINTRESOURCE(IDD_INPUTPOPULATION), hWnd, inputPopulationDlgProc);

	if (*isSuccess)
		addPopulationIcon(hWnd, x, y);

	GlobalUnlock(hGlobalProvince);
}

INT_PTR CALLBACK inputPopulationDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemInt(hDlg, IDC_EDIT_POPULATION, glbProvince->population, false);
		SetDlgItemInt(hDlg, IDC_EDIT_AREA, glbProvince->area, false);
		SetDlgItemInt(hDlg, IDC_EDIT_DENSITY, glbProvince->populationDensity, false);
		SetFocus(GetDlgItem(hDlg, IDC_EDIT_AREA)); 
		return (INT_PTR)FALSE;
	case WM_COMMAND:
	{
		int wmID = LOWORD(wParam);
		switch (wmID)
		{
		case IDC_BUTTON_DONE:
		{
			BOOL isPPValid, isAreaValid, isDensityValid;

			int population = GetDlgItemInt(hDlg, IDC_EDIT_POPULATION, &isPPValid, true);
			int area = GetDlgItemInt(hDlg, IDC_EDIT_AREA, &isAreaValid, true);
			int ppDensity = GetDlgItemInt(hDlg, IDC_EDIT_DENSITY, &isDensityValid, true);
			if (!isPPValid || !isAreaValid || !isDensityValid)
				MessageBox(hDlg, L"Dữ liệu nhập không hợp lệ!", L"Lỗi", MB_OK);
			else {
				BOOL* isSuccess = new BOOL(TRUE);
				glbProvince->population = population;
				glbProvince->area = area;
				glbProvince->populationDensity = ppDensity;
				EndDialog(hDlg, (INT_PTR)isSuccess);
			}
		}
			break;
		case IDC_BUTTON_DELETEDATA:

			break;
		default:
			break;
		}
		return (INT_PTR)TRUE;
	}
	case WM_CLOSE:
	{
		BOOL* isSuccess = new BOOL(FALSE);
		EndDialog(hDlg, (INT_PTR)isSuccess);
	}
		break;
	default:
		break;
	}
	return (INT_PTR)FALSE;
}

void addPopulationIcon(HWND hWnd, int x, int y) {
	HDC hdc = GetDC(hWnd);
	HDC memDC = CreateCompatibleDC(hdc);
	BITMAP bmpIcon;
	HBITMAP hBmpIcon = (HBITMAP)LoadImage(hinstLib, L"dancu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	GetObject(hBmpIcon, sizeof(BITMAP), &bmpIcon);
	SelectObject(memDC, hBmpIcon);
	StretchBlt(hdc, x - bmpIcon.bmWidth / 4, y - bmpIcon.bmHeight / 2, bmpIcon.bmWidth / 2, bmpIcon.bmHeight / 2, memDC, 0, 0, bmpIcon.bmWidth, bmpIcon.bmHeight, SRCCOPY);
	DeleteDC(memDC);
	ReleaseDC(hWnd, hdc);
}