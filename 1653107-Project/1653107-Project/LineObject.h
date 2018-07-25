#pragma once
#include "Object.h"

class LineObject : public Object
{
public:
	LineObject();
	LineObject(COLORREF);
	bool pointInObj(int x, int y);
	void writeFile(ofstream&);
	void loadFile(ifstream&);
	void draw(HDC);
};