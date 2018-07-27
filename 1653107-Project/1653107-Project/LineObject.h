#pragma once
#include "Object.h"

class LineObject : public Object
{
public:
	LineObject();
	LineObject(COLORREF);
	LineObject(ClipboardObject*);
	bool pointInObj(int x, int y);
	void writeFile(ofstream&);
	void loadFile(ifstream&);
	void draw(HDC);
	ClipboardObject* pack2ClipboardObj();
};