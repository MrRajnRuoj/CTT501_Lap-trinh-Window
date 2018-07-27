#pragma once
#include "stdafx.h"

struct Point {
	int x;
	int y;
};

struct ClipboardObject {
	int type;
	LOGFONT logFont;
	COLORREF color;
	Point lftTp, rghtBttn;
	WCHAR text[256];
};

class Object
{
public:
	Object(COLORREF);
	Object(LOGFONT, COLORREF);
	Object(ClipboardObject*);
	Object();
	virtual void draw(HDC) = 0;
	virtual bool pointInObj(int x, int y) = 0;
	void paintSelectedObj(HDC);
	int checkMouseOnSizingPoint(int x, int y);
	virtual void writeFile(ofstream&);
	virtual void loadFile(ifstream&);
	virtual ClipboardObject* pack2ClipboardObj();
	int type;	// 1: Line, 2: Rectangle, 3: Ellipse, 4: Text
	Point lftTp, rghtBttn;

protected:
	LOGFONT logFont;
	COLORREF color;
};