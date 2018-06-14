#pragma once
#include "stdafx.h"
#include "1653107-Midterm.h"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;
HBITMAP hBmpMap = NULL;
HBITMAP hBmpPacMan = NULL;
HRGN hRgn;
BITMAP bmpMapObj, bmpPacManObj;

struct Point {
	int x;
	int y;
};

struct MapLine {
	Point start;
	Point end;
};

struct PacDot {
	Point p;
};

class GameData
{
public:
	vector<MapLine> mapLines;
	vector<PacDot> pacDots;
	Point pacMan;
	int nPacDot;
	int timer;
};

class PacMan
{
public:
	PacMan(GameData* gData) {
		this->data = gData;
	}

private:
	GameData* data;
};

class Game
{
public:
	Game(GameData* gData) {
		this->data = gData;
	}

	void generatePacDot(HWND hWnd) {
		srand(time(NULL));
		int idxMapLine;
		PacDot pacDot;

		for (int i = 0; i < data->nPacDot; ++i) {
			idxMapLine = rand() % ((data->mapLines.size() - 1) + 1) + 0;
			pacDot.p.x = rand() % (data->mapLines[idxMapLine].end.x - data->mapLines[idxMapLine].start.x + 1) + data->mapLines[idxMapLine].start.x;
			pacDot.p.y = rand() % (data->mapLines[idxMapLine].end.y - data->mapLines[idxMapLine].start.y + 1) + data->mapLines[idxMapLine].start.y;
			data->pacDots.push_back(pacDot);
		}
		drawPacDot(hWnd);
	}
	void drawPacMan(HWND hWnd) {
		HDC hdc = GetDC(hWnd);
		HDC memDC = CreateCompatibleDC(hdc);
		SelectObject(memDC, hBmpPacMan);
		BitBlt(hdc, data->pacMan.x - bmpPacManObj.bmWidth / 2, data->pacMan.y - bmpPacManObj.bmHeight / 2, bmpPacManObj.bmWidth, bmpPacManObj.bmHeight, memDC, 0, 0, SRCCOPY);
		DeleteDC(memDC);
		ReleaseDC(hWnd, hdc);
	}

	bool isInMapLine(int x, int y) {
		bool check = false;
		for (int i = 0; i < data->mapLines.size(); ++i) {
			if (x >= data->mapLines[i].start.x && x <= data->mapLines[i].end.x &&
				y >= data->mapLines[i].start.y && y <= data->mapLines[i].end.y) {
				check = true;
				break;
			}
		}
		return check;
	}

	void eatPacDot() {
		for (int i = 0; i < data->pacDots.size(); ++i) {
			if (data->pacDots[i].p.x > (data->pacMan.x - bmpPacManObj.bmWidth / 2) && data->pacDots[i].p.x < (data->pacMan.x + bmpPacManObj.bmWidth / 2) && data->pacDots[i].p.y >(data->pacMan.y - bmpPacManObj.bmHeight / 2) && data->pacDots[i].p.y < (data->pacMan.y + bmpPacManObj.bmHeight / 2))
				data->pacDots.erase(data->pacDots.begin() + i);
		}
	}
private:


	void drawPacDot(HWND hWnd) {
		HDC hdc = GetDC(hWnd);
		for (int i = 0; i < data->pacDots.size(); ++i) {
			Ellipse(hdc, data->pacDots[i].p.x - 3, data->pacDots[i].p.y - 3, data->pacDots[i].p.x + 3, data->pacDots[i].p.y + 3);
		}

		ReleaseDC(hWnd, hdc);
	}

	GameData* data;
};