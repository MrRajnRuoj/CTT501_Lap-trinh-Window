#pragma once
#include "stdafx.h"

struct Point {
	int x;
	int y;
};

class Object
{
public:
	Object(COLORREF);
	Object(LOGFONT, COLORREF);
	Object();
	virtual void draw(HWND) = 0;
	virtual void writeFile(ofstream&);
	virtual void loadFile(ifstream&);
	Point lftTp, rghtBttn;

protected:
	int type;	// 1: Line, 2: Rectangle, 3: Ellipse, 4: Text
	LOGFONT logFont;
	COLORREF color;
};