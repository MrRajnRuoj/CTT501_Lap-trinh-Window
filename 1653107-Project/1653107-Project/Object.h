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
	virtual void draw(HDC) = 0;
	virtual bool pointInObj(int x, int y) = 0;
	void paintSelectedObj(HDC);
	int checkMouseOnSizingPoint(int x, int y);
	virtual void writeFile(ofstream&);
	virtual void loadFile(ifstream&);
	int type;	// 1: Line, 2: Rectangle, 3: Ellipse, 4: Text
	Point lftTp, rghtBttn;

protected:
	LOGFONT logFont;
	COLORREF color;
};