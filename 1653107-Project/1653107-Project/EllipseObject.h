#pragma once
#include "Object.h"

class EllipseObject : public Object
{
public:
	EllipseObject(COLORREF);
	EllipseObject();
	void draw(HDC);
	bool pointInObj(int x, int y);
	void writeFile(ofstream&);
	void loadFile(ifstream&);
};

