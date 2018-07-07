#include "stdafx.h"
#include "ChildWindow.h"

ChildWindow::ChildWindow() {
}

ChildWindow::~ChildWindow()
{
	ReleaseDC(this->hWnd, this->hdc);
}

void ChildWindow::init()
{
	ZeroMemory(&this->logFont, sizeof(this->logFont));
	this->color = RGB(0, 0, 0);
}

void ChildWindow::setHandle(HWND hWnd) {
	if (hWnd < 0)
		return;
	this->hdc = GetDC(hWnd);
	this->hWnd = hWnd;
	SetROP2(hdc, R2_NOTXORPEN);
}

HWND ChildWindow::getHandle() {
	return this->hWnd;
}

void ChildWindow::setLogFont(LOGFONT logFont) {
	this->logFont = logFont;
}

void ChildWindow::setColor(COLORREF color) {
	this->color = color;
}

void ChildWindow::onLButtonDown(int mode, HINSTANCE hInst, LPARAM lParam) {
	switch (mode)
	{
	case ID_DRAW_LINE:
		objTmp = new LineObject(this->color);
		objTmp->lftTp.x = objTmp->rghtBttn.x = LOWORD(lParam);
		objTmp->lftTp.y = objTmp->rghtBttn.y = HIWORD(lParam);
		break;
	case ID_DRAW_RECTANGLE:
		objTmp = new RectangleObject(this->color);
		objTmp->lftTp.x = objTmp->rghtBttn.x = LOWORD(lParam);
		objTmp->lftTp.y = objTmp->rghtBttn.y = HIWORD(lParam);
		break;
	case ID_DRAW_ELLIPSE:
		objTmp = new EllipseObject(this->color);
		objTmp->lftTp.x = objTmp->rghtBttn.x = LOWORD(lParam);
		objTmp->lftTp.y = objTmp->rghtBttn.y = HIWORD(lParam);
		break;
	case ID_DRAW_TEXT:
	{
		TextObject textObj(this->logFont, this->color);
		textObj.lftTp.x = textObj.rghtBttn.x = LOWORD(lParam);
		textObj.lftTp.y = textObj.rghtBttn.y = HIWORD(lParam);
		INT_PTR iptr = DialogBox(hInst, MAKEINTRESOURCE(IDD_INPUTTEXT), hWnd, inputTextDlgProc);
		if (iptr != IDCANCEL) {
			textObj.text = (WCHAR*)iptr;
			objTmp = new TextObject(textObj);
			arrObj.push_back(objTmp);
			HFONT hFont = CreateFontIndirect(&this->logFont);
			HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
			SetTextColor(hdc, color);
			TextOut(hdc, textObj.lftTp.x, textObj.lftTp.y, textObj.text, wcslen(textObj.text));
		}
	}
		break;
	case ID_DRAW_SELECTOBJECT:
		break;
	default:
		break;
	}
}

void ChildWindow::onMouseMove(int mode, WPARAM wParam, LPARAM lParam) {
	switch (mode)
	{
	case ID_DRAW_LINE:
		if (wParam & MK_LBUTTON) {
			HPEN hPen = CreatePen(PS_SOLID, 1, color);
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
			MoveToEx(hdc, objTmp->lftTp.x, objTmp->lftTp.y, NULL);
			LineTo(hdc, objTmp->rghtBttn.x, objTmp->rghtBttn.y);

			objTmp->rghtBttn.x = LOWORD(lParam);
			objTmp->rghtBttn.y = HIWORD(lParam);
			MoveToEx(hdc, objTmp->lftTp.x, objTmp->lftTp.y, NULL);
			LineTo(hdc, objTmp->rghtBttn.x, objTmp->rghtBttn.y);
			SelectObject(hdc, hOldPen);
			DeleteObject(hPen);
		}
		break;
	case ID_DRAW_RECTANGLE:
		if (wParam & MK_LBUTTON) {
			HPEN hPen = CreatePen(PS_SOLID, 1, color);
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
			HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Rectangle(hdc, objTmp->lftTp.x, objTmp->lftTp.y, objTmp->rghtBttn.x, objTmp->rghtBttn.y);

			objTmp->rghtBttn.x = LOWORD(lParam);
			objTmp->rghtBttn.y = HIWORD(lParam);
			Rectangle(hdc, objTmp->lftTp.x, objTmp->lftTp.y, objTmp->rghtBttn.x, objTmp->rghtBttn.y);
			SelectObject(hdc, hOldPen);
			SelectObject(hdc, hOldBrush);
			DeleteObject(hPen);
			DeleteObject(hBrush);
		}
		break;
	case ID_DRAW_ELLIPSE:
		if (wParam & MK_LBUTTON) {
			HPEN hPen = CreatePen(PS_SOLID, 1, color);
			HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
			HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, objTmp->lftTp.x, objTmp->lftTp.y, objTmp->rghtBttn.x, objTmp->rghtBttn.y);

			objTmp->rghtBttn.x = LOWORD(lParam);
			objTmp->rghtBttn.y = HIWORD(lParam);
			Ellipse(hdc, objTmp->lftTp.x, objTmp->lftTp.y, objTmp->rghtBttn.x, objTmp->rghtBttn.y);
			SelectObject(hdc, hOldPen);
			SelectObject(hdc, hOldBrush);
			DeleteObject(hPen);
			DeleteObject(hBrush);
		}
		break;
	case ID_DRAW_TEXT:
		break;
	case ID_DRAW_SELECTOBJECT:
		break;
	default:
		break;
	}
}

void ChildWindow::onLButtonUp(int mode) {
	switch (mode)
	{
	case ID_DRAW_LINE:
	case ID_DRAW_RECTANGLE:
	case ID_DRAW_ELLIPSE:
		this->arrObj.push_back(this->objTmp);
		break;
	case ID_DRAW_TEXT:
		break;
	case ID_DRAW_SELECTOBJECT:
		break;
	default:
		break;
	}
}

void ChildWindow::drawAllObj()
{
	for (int i = 0; i < this->arrObj.size(); ++i)
		this->arrObj[i]->draw(this->hWnd);
}

void ChildWindow::writeFile(ofstream &file) {
	file.write((char*)&this->color, sizeof(COLORREF));
	file.write((char*)&this->logFont, sizeof(LOGFONT));
	int n = arrObj.size();
	file << n << endl;
	for (int i = 0; i < n; ++i)
		arrObj[i]->writeFile(file);
}

void ChildWindow::loadFile(ifstream &file) {
	file.read((char*)&this->color, sizeof(COLORREF));
	file.read((char*)&this->logFont, sizeof(LOGFONT));
	int n, type;
	file >> n;
	for (int i = 0; i < n; ++i) {
		file >> type;
		switch (type)
		{
		case 1:
			objTmp = new LineObject();
			break;
		case 2:
			objTmp = new RectangleObject();
			break;
		case 3:
			objTmp = new EllipseObject();
			break;
		case 4:
			objTmp = new TextObject();
			break;
		default:
			break;
		}
		objTmp->loadFile(file);
		objTmp->draw(hWnd);
		arrObj.push_back(objTmp);
	}
}

INT_PTR CALLBACK inputTextDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hDlg, IDC_EDT_INPUTTEXT));
		return (INT_PTR)FALSE;
	case WM_COMMAND:
	{
		int wmID = LOWORD(wParam);
		switch (wmID)
		{
		case IDCANCEL:
			EndDialog(hDlg, IDCANCEL);
			break;
		case IDOK:
		{
			WCHAR *text = new WCHAR[MAX_LOADSTRING];
			GetDlgItemText(hDlg, IDC_EDT_INPUTTEXT, text, MAX_LOADSTRING);
			EndDialog(hDlg, (INT_PTR)text);
		}
			break;
		default:
			break;
		}
		return (INT_PTR)TRUE;
	}
	case WM_CLOSE:
		EndDialog(hDlg, IDCLOSE);
		break;
	default:
		break;
	}
	return (INT_PTR)FALSE;
}