#pragma once
#include "stdafx.h"
#include "1653107-Project.h"
#include "DrawObject.h"

class ChildWindow
{
public:
	//~ChildWindow();
	void setHandle(HWND);
	HWND getHandle();
	void setFont(HFONT);
	void setColor(COLORREF);
	void onLButtonDown(Mode, LPARAM);
	void onMouseMove(Mode, WPARAM, LPARAM);
	void onLButtonUp(Mode);

private:
	HWND hWnd;
	HFONT font;
	COLORREF color;
	HDC hdc;
	DrawObject* dObjTmp;
	vector<DrawObject*> arrDrawObj;
};