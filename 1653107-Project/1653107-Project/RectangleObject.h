#pragma once
#include "Object.h"
class RectangleObject : public Object
{
public:
	RectangleObject(COLORREF);
	RectangleObject();
	void draw(HWND);
	void writeFile(ofstream&);
	void loadFile(ifstream&);
};

