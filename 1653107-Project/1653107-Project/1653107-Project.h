#pragma once

#include "resource.h"
#include "ChildWindow.h"
#define MAX_LOADSTRING 100


void onCreateChileWnd(int nWnd);
void onCreateMDIClient(HWND hWnd);
void onChooseColor(HWND hWnd);
void onChooseFont(HWND hWnd);
void onOpenFileSaveDlg(HWND hWnd);
void onSaveFile(WCHAR* fileName, HWND hWnd);
void onOpenFileDlg(HWND hWnd);
void onLoadFile(WCHAR* fileName, HWND hWnd);
LRESULT CALLBACK MDICloseProc(HWND hWnd, LPARAM lParam);
void createToolBar(HWND hWnd);
void addUserButton2Toolbar();
void onInitMDIChild(HWND hWnd);
int indexOfHandle(HWND hWnd);