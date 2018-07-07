#pragma once
#include "Object.h"

class EllipseObject : public Object
{
public:
	EllipseObject(COLORREF);
	EllipseObject();
	void draw(HWND);
	void writeFile(ofstream&);
	void loadFile(ifstream&);
};

