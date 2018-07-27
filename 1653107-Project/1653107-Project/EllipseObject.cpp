#include "stdafx.h"
#include "EllipseObject.h"


EllipseObject::EllipseObject(COLORREF color) : Object(color)
{
	this->type = 3;
}

EllipseObject::EllipseObject(ClipboardObject *clipObj) : Object(clipObj)
{
}

EllipseObject::EllipseObject()
{
}

void EllipseObject::draw(HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, this->color);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Ellipse(hdc, this->lftTp.x, this->lftTp.y, this->rghtBttn.x, this->rghtBttn.y);
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

bool EllipseObject::pointInObj(int x, int y)
{
	int top = (lftTp.y < rghtBttn.y ? lftTp.y : rghtBttn.y);
	int left = (lftTp.x < rghtBttn.x ? lftTp.x : rghtBttn.x);
	int buttom = (lftTp.y > rghtBttn.y ? lftTp.y : rghtBttn.y);
	int right = (lftTp.x > rghtBttn.x ? lftTp.x : rghtBttn.x);

	if (y < top || y> buttom || x < left || x > right)  // out of range
		return false;

	float a = (float)(right - left) / 2.0;
	float b = (float)(buttom - top) / 2.0;

	float h = (float)(right + left) / 2.0;
	float k = (float)(buttom + top) / 2.0;

	float result = pow(x - h, 2) / pow(a, 2) + pow(y - k, 2) / pow(b, 2);
	float delta = 0.2;

	if (result <= 1 + delta && result >= 1 - delta)
	{
		return true;
	}

	return false;
}

void EllipseObject::writeFile(ofstream &file)
{
	Object::writeFile(file);
}

void EllipseObject::loadFile(ifstream &file)
{
	Object::loadFile(file);
}

ClipboardObject * EllipseObject::pack2ClipboardObj()
{
	return Object::pack2ClipboardObj();
}

