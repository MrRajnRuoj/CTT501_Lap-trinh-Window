#pragma once

#include "resource.h"

enum Mode
{
	Line = ID_DRAW_LINE,
	Rectangle = ID_DRAW_RECTANGLE,
	Ellipse = ID_DRAW_ELLIPSE,
	Text = ID_DRAW_TEXT,
	Select = ID_DRAW_SELECTOBJECT
};

void onCreateChileWnd(int nWnd);
void onCreateMDIClient(HWND hWnd);
void onChooseColor(HWND hWnd);
void onChooseFont(HWND hWnd);
LRESULT CALLBACK MDICloseProc(HWND hWnd, LPARAM lParam);
void createToolBar(HWND hWnd);
void addUserButton2Toolbar();
void onInitMDIChild(HWND hWnd);
int indexOfHandle(HWND hWnd);