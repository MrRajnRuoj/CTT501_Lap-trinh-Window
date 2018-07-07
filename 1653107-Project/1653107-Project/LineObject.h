#pragma once
#include "Object.h"

class LineObject : public Object
{
public:
	LineObject();
	LineObject(COLORREF);
	void writeFile(ofstream&);
	void loadFile(ifstream&);
	void draw(HWND);
};