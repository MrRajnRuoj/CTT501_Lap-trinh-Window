#include "stdafx.h"
#include "Object.h"

Object::Object(COLORREF color)
{
	this->color = color;
}

Object::Object(LOGFONT logFont, COLORREF color)
{
	this->logFont = logFont;
	this->color = color;
}

Object::Object()
{
}

void Object::paintSelectedObj(HDC hdc)
{
	if (lftTp.x == rghtBttn.x && lftTp.y == rghtBttn.y)
		return;
	HPEN hPen, hOldPen;
	hPen = CreatePen(PS_DOT, 1, RGB(0, 102, 255));
	hOldPen = (HPEN)SelectObject(hdc, hPen);
	HGDIOBJ oldBrush = SelectObject(hdc, GetStockObject(NULL_BRUSH));


	int top = (lftTp.y < rghtBttn.y ? lftTp.y : rghtBttn.y);
	int left = (lftTp.x < rghtBttn.x ? lftTp.x : rghtBttn.x);
	int buttom = (lftTp.y > rghtBttn.y ? lftTp.y : rghtBttn.y);
	int right = (lftTp.x > rghtBttn.x ? lftTp.x : rghtBttn.x);
	Rectangle(hdc, left, top, right, buttom);
	DeleteObject(hPen);
	hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(WHITE_BRUSH));
	//draw the 8-points
	Rectangle(hdc, left - 3, top - 3, left + 3, top + 3);
	Rectangle(hdc, right - 3, top - 3, right + 3, top + 3);
	Rectangle(hdc, left - 3, buttom - 3, left + 3, buttom + 3);
	Rectangle(hdc, right - 3, buttom - 3, right + 3, buttom + 3);
	Rectangle(hdc, left - 3, (buttom + top) / 2 - 3, left + 3, (buttom + top) / 2 + 3);
	Rectangle(hdc, right - 3, (buttom + top) / 2 - 3, right + 3, (buttom + top) / 2 + 3);
	Rectangle(hdc, (right + left) / 2 - 3, top - 3, (right + left) / 2 + 3, top + 3);
	Rectangle(hdc, (right + left) / 2 - 3, buttom - 3, (right + left) / 2 + 3, buttom + 3);

	SelectObject(hdc, oldBrush);
	SelectObject(hdc, hOldPen);
	DeleteObject(oldBrush);
	DeleteObject(hPen);
}

int Object::checkMouseOnSizingPoint(int x, int y)
{
	int top = (lftTp.y < rghtBttn.y ? lftTp.y : rghtBttn.y);
	int left = (lftTp.x < rghtBttn.x ? lftTp.x : rghtBttn.x);
	int buttom = (lftTp.y > rghtBttn.y ? lftTp.y : rghtBttn.y);
	int right = (lftTp.x > rghtBttn.x ? lftTp.x : rghtBttn.x);

	if (y < top - 4 || y> buttom + 4 || x < left - 4 || x > right + 4)  // out of range
		return 0;

	if (y >= top - 4 && y <= top + 1 && x >= left - 4 && x <= left + 1)  //left top
		return 1;
	else if (x >= right - 1 && x <= right + 4 && y >= buttom - 1 && y <= buttom + 4)  //right buttom
		return 2;
	else if (x >= left - 4 && x <= left + 1 && y >= buttom - 1 && y <= buttom + 4)  //left buttom
		return 3;
	else if (x >= right - 1 && x <= right + 4 && y >= top - 4 && y <= top + 1) //right top
		return 4;
	else if (x >= left - 4 && x <= left + 1 && y >= (buttom + top) / 2 - 3 && y <= (buttom + top) / 2 + 2)  // left mid
		return 5;
	else if (x >= right - 1 && x <= right + 4 && y >= (buttom + top) / 2 - 3 && y <= (buttom + top) / 2 + 2)  //right mid
		return 6;
	else if (x >= (right + left) / 2 - 3 && x <= (right + left) / 2 + 2 && y >= top - 4 && y <= top + 1) // top mid
		return 7;
	else if (x >= (right + left) / 2 - 3 && x <= (right + left) / 2 + 2 && y >= buttom - 1 && y <= buttom + 4) //buttom mid
		return 8;

	//check mouse is on the selecting rectangle. only apply for line/circle

	if ((abs(x - left) <= 1 || abs(x - right) <= 1) && (y > top && y < buttom))
	{
		return 9;
	}
	if ((abs(y - top) <= 1 || abs(y - buttom) <= 1) && (x > left && x < right))
	{
		return 9;
	}

	return 0;
}

void Object::writeFile(ofstream &file)
{
	file << this->type;
	file.write((char*)&this->color, sizeof(this->color));
	file.write((char*)&this->logFont, sizeof(this->logFont));
	file.write((char*)&this->lftTp, sizeof(this->lftTp));
	file.write((char*)&this->rghtBttn, sizeof(this->rghtBttn));
}

void Object::loadFile(ifstream &file)
{
	file.read((char*)&this->color, sizeof(this->color));
	file.read((char*)&this->logFont, sizeof(this->logFont));
	file.read((char*)&this->lftTp, sizeof(this->lftTp));
	file.read((char*)&this->rghtBttn, sizeof(this->rghtBttn));
}
