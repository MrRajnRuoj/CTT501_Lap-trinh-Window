#pragma once
#include "Object.h"

class TextObject : public Object
{
public:
	TextObject(LOGFONT, COLORREF);
	TextObject();
	TextObject(const TextObject&);
	~TextObject();
	void draw(HDC);
	bool pointInObj(int x, int y);
	void writeFile(ofstream&);
	void loadFile(ifstream&);
	WCHAR *text;
};

