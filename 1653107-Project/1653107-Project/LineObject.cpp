#include "stdafx.h"
#include "LineObject.h"

LineObject::LineObject()
{
}

LineObject::LineObject(COLORREF color) : Object(color)
{
	this->type = 1;
}

void LineObject::writeFile(ofstream &file)
{
	Object::writeFile(file);
}

void LineObject::loadFile(ifstream &file)
{
	Object::loadFile(file);
}

void LineObject::draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	HPEN hPen = CreatePen(PS_SOLID, 1, this->color);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, this->lftTp.x, this->lftTp.y, NULL);
	LineTo(hdc, this->rghtBttn.x, this->rghtBttn.y);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}
