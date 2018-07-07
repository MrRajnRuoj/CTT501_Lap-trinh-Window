#include "stdafx.h"
#include "RectangleObject.h"


RectangleObject::RectangleObject(COLORREF color) : Object(color)
{
	this->type = 2;
}

RectangleObject::RectangleObject()
{
}

void RectangleObject::draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	HPEN hPen = CreatePen(PS_SOLID, 1, this->color);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, this->lftTp.x, this->lftTp.y, this->rghtBttn.x, this->rghtBttn.y);
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	ReleaseDC(hWnd, hdc);
}

void RectangleObject::writeFile(ofstream &file)
{
	Object::writeFile(file);
}

void RectangleObject::loadFile(ifstream &file)
{
	Object::loadFile(file);
}


