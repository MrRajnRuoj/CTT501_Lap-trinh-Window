#pragma once
#include "Object.h"

class TextObject : public Object
{
public:
	TextObject(LOGFONT, COLORREF);
	TextObject();
	TextObject(const TextObject&);
	~TextObject();
	void draw(HWND);
	void writeFile(ofstream&);
	void loadFile(ifstream&);
	WCHAR *text;
};

