#include "stdafx.h"
#include "EllipseObject.h"


EllipseObject::EllipseObject(COLORREF color) : Object(color)
{
	this->type = 3;
}

EllipseObject::EllipseObject()
{
}

void EllipseObject::draw(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	HPEN hPen = CreatePen(PS_SOLID, 1, this->color);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Ellipse(hdc, this->lftTp.x, this->lftTp.y, this->rghtBttn.x, this->rghtBttn.y);
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
	ReleaseDC(hWnd, hdc);
}

void EllipseObject::writeFile(ofstream &file)
{
	Object::writeFile(file);
}

void EllipseObject::loadFile(ifstream &file)
{
	Object::loadFile(file);
}

