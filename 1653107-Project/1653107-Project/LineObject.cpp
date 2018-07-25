#include "stdafx.h"
#include "LineObject.h"

LineObject::LineObject()
{
}

LineObject::LineObject(COLORREF color) : Object(color)
{
	this->type = 1;
}

bool LineObject::pointInObj(int mouseX, int mouseY)
{
	float slope, intercept, epsilon;
	float x1, y1, x2, y2;
	float px, py;
	float left, top, right, bottom; // Bounding Box For Line Segment
	float dx, dy;
	epsilon = 4.0 + 2.0;  //for error tolerance

	x1 = lftTp.x;
	y1 = lftTp.y;
	x2 = rghtBttn.x;
	y2 = rghtBttn.y;
	px = mouseX;
	py = mouseY;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx == 0)  //vertical line
	{
		//only check Y coordinate
		if (y1 < y2)
		{
			top = y1;
			bottom = y2;
		}
		else
		{
			top = y1;
			bottom = y2;
		}

		if (px == x1 && py >= top && py <= bottom)
			return true;
		else
			return false;
	}

	if (x1 < x2)
	{
		left = x1;
		right = x2;
	}
	else
	{
		left = x2;
		right = x1;
	}

	if (y1 < y2)
	{
		top = y1;
		bottom = y2;
	}
	else
	{
		top = y2;
		bottom = y1;
	}

	if (mouseY < top || mouseY> bottom || mouseX < left || mouseX > right)  //first if mouse out of range, just return false
		return false;

	slope = dy / dx;

	intercept = y1 - slope * x1; // which is same as y2 - slope * x2

	if (slope * px + intercept > (py - epsilon) &&
		slope * px + intercept < (py + epsilon))
	{
		if (px >= left && px <= right &&
			py >= top && py <= bottom)
		{
			return true;
		}
	}
	return false;
}

//void LineObject::paintSelectedObj(HDC hdc)
//{
//	if (lftTp.x == rghtBttn.x && lftTp.y == rghtBttn.y)
//		return;
//	HPEN hPen, hOldPen;
//	hPen = CreatePen(PS_DOT, 1, RGB(0, 102, 255));
//	hOldPen = (HPEN)SelectObject(hdc, hPen);
//	HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(NULL_BRUSH));  
//
//																	   
//	int top = (lftTp.y < rghtBttn.y ? lftTp.y : rghtBttn.y);
//	int left = (lftTp.x < rghtBttn.x ? lftTp.x : rghtBttn.x);
//	int buttom = (lftTp.y > rghtBttn.y ? lftTp.y : rghtBttn.y);
//	int right = (lftTp.x > rghtBttn.x ? lftTp.x : rghtBttn.x);
//	Rectangle(hdc, left, top, right, buttom);
//	DeleteObject(hPen);
//	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
//	SelectObject(hdc, hPen);
//	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
//	//draw the 8-points
//	Rectangle(hdc, left - 3, top - 3, left + 3, top + 3);
//	Rectangle(hdc, right - 3, top - 3, right + 3, top + 3);
//	Rectangle(hdc, left - 3, buttom - 3, left + 3, buttom + 3);
//	Rectangle(hdc, right - 3, buttom - 3, right + 3, buttom + 3);
//	Rectangle(hdc, left - 3, (buttom + top) / 2 - 3, left + 3, (buttom + top) / 2 + 3);
//	Rectangle(hdc, right - 3, (buttom + top) / 2 - 3, right + 3, (buttom + top) / 2 + 3);
//	Rectangle(hdc, (right + left) / 2 - 3, top - 3, (right + left) / 2 + 3, top + 3);
//	Rectangle(hdc, (right + left) / 2 - 3, buttom - 3, (right + left) / 2 + 3, buttom + 3);
//
//	SelectObject(hdc, oldBrush);
//	SelectObject(hdc, hOldPen);
//	DeleteObject(oldBrush);
//	DeleteObject(hPen);
//}

void LineObject::writeFile(ofstream &file)
{
	Object::writeFile(file);
}

void LineObject::loadFile(ifstream &file)
{
	Object::loadFile(file);
}

void LineObject::draw(HDC hdc)
{
	HPEN hPen = CreatePen(PS_SOLID, 1, this->color);
	HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, this->lftTp.x, this->lftTp.y, NULL);
	LineTo(hdc, this->rghtBttn.x, this->rghtBttn.y);
	SelectObject(hdc, hOldPen);
	DeleteObject(hPen);
}
