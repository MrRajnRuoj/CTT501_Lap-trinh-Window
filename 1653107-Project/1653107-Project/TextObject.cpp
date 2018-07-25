#include "stdafx.h"
#include "TextObject.h"


TextObject::TextObject(LOGFONT logFont, COLORREF color) : Object(logFont, color)
{
	this->type = 4;
}

TextObject::TextObject()
{
	this->type = 4;
}

TextObject::TextObject(const TextObject &tmpObj)
{
	this->type = 4;
	this->text = new WCHAR[wcslen(tmpObj.text) + 1];
	wcscpy(this->text, tmpObj.text);
	this->logFont = tmpObj.logFont;
	this->color = tmpObj.color;
	this->lftTp = tmpObj.lftTp;
	this->rghtBttn = tmpObj.rghtBttn;
}

TextObject::~TextObject()
{
	delete[] this->text;
}

void TextObject::draw(HDC hdc)
{
	HFONT hFont = CreateFontIndirect(&logFont);
	SelectObject(hdc, hFont);
	SetTextColor(hdc, color);
	TextOut(hdc, lftTp.x, lftTp.y, text, wcslen(text));
}

bool TextObject::pointInObj(int x, int y)
{
	if (y >= lftTp.y && y <= rghtBttn.y && x >= lftTp.x && x <= rghtBttn.x)
		return true;
	return false;
}

void TextObject::writeFile(ofstream &file)
{
	Object::writeFile(file);
	char str[256];
	sprintf(str, "%ws", this->text);
	file << strlen(str);
	file.write(str, strlen(str));
}

void TextObject::loadFile(ifstream &file)
{
	Object::loadFile(file);
	int length;
	file >> length;
	char str[256];
	this->text = new WCHAR[length + 1];
	file.read(str, length);
	str[length] = '\0';
	mbstowcs(this->text, str, length + 1);
}

