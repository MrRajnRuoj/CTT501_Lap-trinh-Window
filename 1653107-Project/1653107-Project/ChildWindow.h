#pragma once
#include "stdafx.h"
#include "1653107-Project.h"
#include "Object.h"
#include "LineObject.h"
#include "RectangleObject.h"
#include "EllipseObject.h"
#include "TextObject.h"
#include "Resource.h"

class ChildWindow
{
public:
	ChildWindow();
	~ChildWindow();
	void init();
	void setHandle(HWND);
	HWND getHandle();
	void setLogFont(LOGFONT);
	void setColor(COLORREF);
	void onLButtonDown(int, HINSTANCE, LPARAM);
	void onMouseMove(int, WPARAM, LPARAM);
	void onLButtonUp(int);
	void drawAllObj();
	void writeFile(ofstream&);
	void loadFile(ifstream&);

private:
	HWND hWnd;
	LOGFONT logFont;
	COLORREF color;
	HDC hdc;
	Object* objTmp;
	vector<Object*> arrObj;
};

INT_PTR CALLBACK inputTextDlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);