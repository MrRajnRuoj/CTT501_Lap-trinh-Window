#include "stdafx.h"
#include "RectangleObject.h"


RectangleObject::RectangleObject(COLORREF color) : Object(color)
{
	this->type = 2;
}

RectangleObject::RectangleObject()
{
}

void RectangleObject::draw(HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, this->color);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);
	Rectangle(hdc, this->lftTp.x, this->lftTp.y, this->rghtBttn.x, this->rghtBttn.y);
	SelectObject(hdc, hOldPen);
	SelectObject(hdc, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

bool RectangleObject::pointInObj(int x, int y)
{
	int top = (lftTp.y < rghtBttn.y ? lftTp.y : rghtBttn.y);
	int left = (lftTp.x < rghtBttn.x ? lftTp.x : rghtBttn.x);
	int buttom = (lftTp.y > rghtBttn.y ? lftTp.y : rghtBttn.y);
	int right = (lftTp.x > rghtBttn.x ? lftTp.x : rghtBttn.x);

	if (y < top || y> buttom || x < left || x > right)  // out of range
		return false;

	else
	{
		if ((abs(x - left) <= 2 || abs(x - right) <= 2) && (y > top && y < buttom))
		{
			return true;
		}
		else if ((abs(y - top) <= 2 || abs(y - buttom) <= 2) && (x > left && x < right))
		{
			return true;
		}
	}
	return false;
}

void RectangleObject::writeFile(ofstream &file)
{
	Object::writeFile(file);
}

void RectangleObject::loadFile(ifstream &file)
{
	Object::loadFile(file);
}


