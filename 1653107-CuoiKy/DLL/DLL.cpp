// DLL.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DLL.h"
#include "resource.h"

#define EXPORTS __declspec(dllexport)

extern HINSTANCE hinstLib;
Province* glbProvince = NULL;


EXPORTS void inputPopulation(HWND hWnd, HGLOBAL hGlobalProvince, int x, int y) {
	BOOL* isSuccess = NULL;

	glbProvince = (Province*)GlobalLock(hGlobalProvince);
	if (glbProvince != NULL) {
		isSuccess = (BOOL*)DialogBox(hinstLib, MAKEINTRESOURCE(IDD_INPUTPOPULATION), hWnd, inputPopulationDlgProc);
		if (*isSuccess) {
			glbProvince->pICon.x = x;
			glbProvince->pICon.y = y;
			InvalidateRect(hWnd, NULL, true);
		}
	}
		
	GlobalUnlock(hGlobalProvince);
	delete isSuccess;
}

EXPORTS void inputProduct(HWND hWnd, HGLOBAL hGlobalProvince, int x, int y) {
	BOOL* isSuccess = NULL;

	glbProvince = (Province*)GlobalLock(hGlobalProvince);
	if (glbProvince != NULL) {
		isSuccess = (BOOL*)DialogBox(hinstLib, MAKEINTRESOURCE(IDD_INPUTPRODUCT), hWnd, inputProductDlgProc);
		if (*isSuccess) {
			glbProvince->eICon.x = x;
			glbProvince->eICon.y = y;
			InvalidateRect(hWnd, NULL, true);
		}
	}

	GlobalUnlock(hGlobalProvince);
	delete isSuccess;
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
				glbProvince->flagPICon = true;
				EndDialog(hDlg, (INT_PTR)isSuccess);
			}
		}
			break;
		case IDC_BUTTON_DELETEDATA:
			if (MessageBox(hDlg, L"Bạn có thực sự muốn xóa thông tin dân cư của tỉnh?", L"Xác nhận", MB_YESNO) == IDYES) {
				BOOL* isSuccess = new BOOL(TRUE);
				glbProvince->population = 0;
				glbProvince->area = 0;
				glbProvince->populationDensity = 0;
				glbProvince->flagPICon = false;
				EndDialog(hDlg, (INT_PTR)isSuccess);
			}
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

INT_PTR CALLBACK inputProductDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_INITDIALOG:
		SendMessage(GetDlgItem(hDlg, IDC_CB_ECONOMICTYPE), CB_ADDSTRING, 0, (LPARAM)L"Nông nghiệp");
		SendMessage(GetDlgItem(hDlg, IDC_CB_ECONOMICTYPE), CB_ADDSTRING, 0, (LPARAM)L"Dịch vụ");
		SendMessage(GetDlgItem(hDlg, IDC_CB_ECONOMICTYPE), CB_ADDSTRING, 0, (LPARAM)L"Du lịch");
		SendMessage(GetDlgItem(hDlg, IDC_CB_ECONOMICTYPE), CB_ADDSTRING, 0, (LPARAM)L"Công nghiệp");
		if (glbProvince->economicType != -1)
			SendMessage(GetDlgItem(hDlg, IDC_CB_ECONOMICTYPE), CB_SETCURSEL, glbProvince->economicType, 0);
		else
			SendMessage(GetDlgItem(hDlg, IDC_CB_ECONOMICTYPE), CB_SETCURSEL, 0, 0);
		SetDlgItemText(hDlg, IDC_EDIT_PRODUCT1, glbProvince->listProduct[0].name);
		SetDlgItemInt(hDlg, IDC_EDIT_QUANTITYPRODUCT1, glbProvince->listProduct[0].quantity, false);
		SetDlgItemText(hDlg, IDC_EDIT_PRODUCT2, glbProvince->listProduct[1].name);
		SetDlgItemInt(hDlg, IDC_EDIT_QUANTITYPRODUCT2, glbProvince->listProduct[1].quantity, false);
		SetFocus(GetDlgItem(hDlg, IDC_EDIT_PRODUCT1));
		return (INT_PTR)FALSE;
	case WM_COMMAND:
	{
		int wmID = LOWORD(wParam);
		switch (wmID)
		{
		case IDC_BTN_DONE:
		{
			BOOL isQ1Valid, isQ2Valid;
			WCHAR product1[256], product2[256];
			int quantity1, quantity2;

			int eTypeSel = SendMessage(GetDlgItem(hDlg, IDC_CB_ECONOMICTYPE), CB_GETCURSEL, 0, 0);
			GetDlgItemText(hDlg, IDC_EDIT_PRODUCT1, product1, 256);
			quantity1 = GetDlgItemInt(hDlg, IDC_EDIT_QUANTITYPRODUCT1, &isQ1Valid, true);
			GetDlgItemText(hDlg, IDC_EDIT_PRODUCT2, product2, 256);
			quantity2 = GetDlgItemInt(hDlg, IDC_EDIT_QUANTITYPRODUCT2, &isQ2Valid, true);
			if (!isQ1Valid || !isQ2Valid)
				MessageBox(hDlg, L"Dữ liệu nhập không hợp lệ!", L"Lỗi", MB_OK);
			else {
				BOOL* isSuccess = new BOOL(TRUE);
				glbProvince->economicType = eTypeSel;
				wcscpy(glbProvince->listProduct[0].name, product1);
				glbProvince->listProduct[0].quantity = quantity1;
				wcscpy(glbProvince->listProduct[1].name, product2);
				glbProvince->listProduct[1].quantity = quantity2;
				glbProvince->flagEICon = true;
				EndDialog(hDlg, (INT_PTR)isSuccess);
			}
		}
		break;
		case IDC_BTN_DELETEDATA:
			if (MessageBox(hDlg, L"Bạn có thực sự muốn xóa thông tin sản phẩm của tỉnh?", L"Xác nhận", MB_YESNO) == IDYES) {
				BOOL* isSuccess = new BOOL(TRUE);
				glbProvince->economicType = -1;
				wsprintf(glbProvince->listProduct[0].name, L"");
				glbProvince->listProduct[0].quantity = 0;
				wsprintf(glbProvince->listProduct[1].name, L"");
				glbProvince->listProduct[1].quantity = 0;
				glbProvince->flagEICon = false;
				EndDialog(hDlg, (INT_PTR)isSuccess);
			}
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