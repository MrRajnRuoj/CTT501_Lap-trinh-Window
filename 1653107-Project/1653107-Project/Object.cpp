#include "stdafx.h"
#include "Object.h"

Object::Object(COLORREF color)
{
	this->color = color;
}

Object::Object(LOGFONT logFont, COLORREF color)
{
	this->logFont = logFont;
	this->color = color;
}

Object::Object()
{
}

void Object::writeFile(ofstream &file)
{
	file << this->type;
	file.write((char*)&this->color, sizeof(this->color));
	file.write((char*)&this->logFont, sizeof(this->logFont));
	file.write((char*)&this->lftTp, sizeof(this->lftTp));
	file.write((char*)&this->rghtBttn, sizeof(this->rghtBttn));
}

void Object::loadFile(ifstream &file)
{
	file.read((char*)&this->color, sizeof(this->color));
	file.read((char*)&this->logFont, sizeof(this->logFont));
	file.read((char*)&this->lftTp, sizeof(this->lftTp));
	file.read((char*)&this->rghtBttn, sizeof(this->rghtBttn));
}
