#pragma once
#include "Object.h"
class RectangleObject : public Object
{
public:
	RectangleObject(COLORREF);
	RectangleObject(ClipboardObject*);
	RectangleObject();
	void draw(HDC);
	bool pointInObj(int x, int y);
	void writeFile(ofstream&);
	void loadFile(ifstream&);
	ClipboardObject* pack2ClipboardObj();
};

