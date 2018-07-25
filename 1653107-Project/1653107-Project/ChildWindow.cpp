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
	color = RGB(0, 0, 0);
	idxLastSelectedObj = -1;
	mouseDownOnObj = false;
	changeMouse = false;
	isResizing = false;
	currCursor = 0;
	hCursor[0] = LoadCursor(NULL, IDC_ARROW);
	hCursor[1] = LoadCursor(NULL, IDC_SIZEALL);
	hCursor[2] = LoadCursor(NULL, IDC_SIZENESW);
	hCursor[3] = LoadCursor(NULL, IDC_SIZENWSE);
	hCursor[4] = LoadCursor(NULL, IDC_SIZENS);
	hCursor[5] = LoadCursor(NULL, IDC_SIZEWE);
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
			SIZE sz;
			textObj.text = (WCHAR*)iptr;
			HFONT hFont = CreateFontIndirect(&this->logFont);
			HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
			SetTextColor(hdc, color);
			GetTextExtentPoint32(hdc, textObj.text, wcslen(textObj.text), &sz);
			textObj.rghtBttn.x = textObj.lftTp.x + sz.cx;
			textObj.rghtBttn.y = textObj.lftTp.y + sz.cy;
			TextOut(hdc, textObj.lftTp.x, textObj.lftTp.y, textObj.text, wcslen(textObj.text));
			objTmp = new TextObject(textObj);
			arrObj.push_back(objTmp);
		}
	}
	break;
	case ID_DRAW_SELECTOBJECT:
	{
		if (changeMouse == false) {
			int idx = checkSelectObject(LOWORD(lParam), HIWORD(lParam));
			if (idx != -1 && mouseDownOnObj == false)
				mouseDownOnObj = true;
			else if (idx == -1 && mouseDownOnObj == true) {
				arrObj[idxLastSelectedObj]->paintSelectedObj(hdc);
				mouseDownOnObj = false;
				idxLastSelectedObj = -1;
			}
		}
		else if (changeMouse == true) {
			isResizing = true;
			pBeforeMove.x = LOWORD(lParam);
			pBeforeMove.y = HIWORD(lParam);
		}
	}
	break;
	default:
		break;
	}
}

void ChildWindow::onMouseMove(int mode, WPARAM wParam, LPARAM lParam) {
	static int mousePos = 0;
	HPEN hPen = CreatePen(PS_SOLID, 1, color);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	switch (mode)
	{
	case ID_DRAW_LINE:
		if (wParam & MK_LBUTTON) {
			MoveToEx(hdc, objTmp->lftTp.x, objTmp->lftTp.y, NULL);
			LineTo(hdc, objTmp->rghtBttn.x, objTmp->rghtBttn.y);

			objTmp->rghtBttn.x = LOWORD(lParam);
			objTmp->rghtBttn.y = HIWORD(lParam);
			MoveToEx(hdc, objTmp->lftTp.x, objTmp->lftTp.y, NULL);
			LineTo(hdc, objTmp->rghtBttn.x, objTmp->rghtBttn.y);
		}
		break;
	case ID_DRAW_RECTANGLE:
		if (wParam & MK_LBUTTON) {
			Rectangle(hdc, objTmp->lftTp.x, objTmp->lftTp.y, objTmp->rghtBttn.x, objTmp->rghtBttn.y);

			objTmp->rghtBttn.x = LOWORD(lParam);
			objTmp->rghtBttn.y = HIWORD(lParam);
			Rectangle(hdc, objTmp->lftTp.x, objTmp->lftTp.y, objTmp->rghtBttn.x, objTmp->rghtBttn.y);
		}
		break;
	case ID_DRAW_ELLIPSE:
		if (wParam & MK_LBUTTON) {
			Ellipse(hdc, objTmp->lftTp.x, objTmp->lftTp.y, objTmp->rghtBttn.x, objTmp->rghtBttn.y);

			objTmp->rghtBttn.x = LOWORD(lParam);
			objTmp->rghtBttn.y = HIWORD(lParam);
			Ellipse(hdc, objTmp->lftTp.x, objTmp->lftTp.y, objTmp->rghtBttn.x, objTmp->rghtBttn.y);
		}
		break;
	case ID_DRAW_TEXT:
		break;
	case ID_DRAW_SELECTOBJECT:
	{
		if (mouseDownOnObj == false) {
			int idx = checkSelectObject(LOWORD(lParam), HIWORD(lParam));
			if (idx != -1 && idxLastSelectedObj == -1) {
				arrObj[idx]->paintSelectedObj(hdc);
				idxLastSelectedObj = idx;
			}
			else if (idx == -1 && idxLastSelectedObj != -1) {
				arrObj[idxLastSelectedObj]->paintSelectedObj(hdc);
				idxLastSelectedObj = -1;
			}
		}
		else if (idxLastSelectedObj != -1) {
			if (isResizing == false) {
				mousePos = arrObj[idxLastSelectedObj]->checkMouseOnSizingPoint(LOWORD(lParam), HIWORD(lParam));
				if (mousePos == 1 || mousePos == 2) {
					currCursor = 3;	// NWSE
					changeMouse = true;
				}
				else if (mousePos == 7 || mousePos == 8) {
					currCursor = 4;	// NS
					changeMouse = true;
				}
				else if (mousePos == 3 || mousePos == 4) {
					currCursor = 2;	// NESW
					changeMouse = true;
				}
				else if (mousePos == 5 || mousePos == 6) {
					currCursor = 5;	// NS
					changeMouse = true;
				}
				else if (mousePos == 9) {
					currCursor = 1;	// NS
					changeMouse = true;
				}
				else if (changeMouse) {
					currCursor = 0;	// normal
					changeMouse = false;
				}
				SetCursor(hCursor[currCursor]);
			}
			else {
				switch (arrObj[idxLastSelectedObj]->type)
				{
				case 1:	// resizing line
				case 2:	// resizing rectangle
				case 3: // resizing ellipse
				case 4:	// text
				{
					arrObj[idxLastSelectedObj]->draw(hdc);
					arrObj[idxLastSelectedObj]->paintSelectedObj(hdc);
					switch (mousePos)
					{
					case 1:
						arrObj[idxLastSelectedObj]->lftTp.x = LOWORD(lParam);
						arrObj[idxLastSelectedObj]->lftTp.y = HIWORD(lParam);
						break;
					case 2:
						arrObj[idxLastSelectedObj]->rghtBttn.x = LOWORD(lParam);
						arrObj[idxLastSelectedObj]->rghtBttn.y = HIWORD(lParam);
						break;
					case 3:
						arrObj[idxLastSelectedObj]->lftTp.x = LOWORD(lParam);
						arrObj[idxLastSelectedObj]->rghtBttn.y = HIWORD(lParam);
						break;
					case 4:
						arrObj[idxLastSelectedObj]->lftTp.y = HIWORD(lParam);
						arrObj[idxLastSelectedObj]->rghtBttn.x = LOWORD(lParam);
						break;
					case 5:
						arrObj[idxLastSelectedObj]->lftTp.x = LOWORD(lParam);
						break;
					case 6:
						arrObj[idxLastSelectedObj]->rghtBttn.x = LOWORD(lParam);
						break;
					case 7:
						arrObj[idxLastSelectedObj]->lftTp.y = HIWORD(lParam);
						break;
					case 8:
						arrObj[idxLastSelectedObj]->rghtBttn.y = HIWORD(lParam);
						break;
					case 9:
					{
						int xi = LOWORD(lParam) - pBeforeMove.x;
						int yi = HIWORD(lParam) - pBeforeMove.y;
						arrObj[idxLastSelectedObj]->lftTp.x += xi;
						arrObj[idxLastSelectedObj]->lftTp.y += yi;
						arrObj[idxLastSelectedObj]->rghtBttn.x += xi;
						arrObj[idxLastSelectedObj]->rghtBttn.y += yi;
						pBeforeMove.x = LOWORD(lParam);
						pBeforeMove.y = HIWORD(lParam);
					}
						break;
					default:
						break;
					}
					arrObj[idxLastSelectedObj]->draw(hdc);
					arrObj[idxLastSelectedObj]->paintSelectedObj(hdc);
				}
					break;
				default:
					break;
				}
			}
		}
	}
	break;
	default:
		break;
	}
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
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
		if (isResizing == true)
			isResizing = false;
		break;
	default:
		break;
	}
}

void ChildWindow::drawAllObj()
{
	for (int i = 0; i < this->arrObj.size(); ++i)
		this->arrObj[i]->draw(hdc);
	if (idxLastSelectedObj != -1)
		arrObj[idxLastSelectedObj]->paintSelectedObj(hdc);
}

int ChildWindow::checkSelectObject(int x, int y) {
	for (int i = 0; i < arrObj.size(); ++i) {
		if (arrObj[i]->pointInObj(x, y))
			return i;
	}
	return -1;
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
		objTmp->draw(hdc);
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