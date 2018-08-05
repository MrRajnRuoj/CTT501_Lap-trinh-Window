#include "stdafx.h"
#include "MapObject.h"

#define INPUT_FILE	"map.txt"
#define IMPORT __declspec(dllimport)

IMPORT void inputPopulation(HWND hWnd, HGLOBAL hGlobalProvince, int x, int y);
IMPORT void inputProduct(HWND hWnd, HGLOBAL hGlobalProvince, int x, int y);

MapObject::MapObject()
{
}


MapObject::~MapObject()
{
}

void MapObject::importData()
{
	fstream fIn;
	int nProvince = 0;
	string provinceName;
	POINT arrPoint[6];

	fIn.open(INPUT_FILE, ios::in);
	fIn >> nProvince;

	for (int i = 0; i < nProvince; ++i) {
		fIn >> provinceName;
		for (int j = 0; j < 6; ++j)
			fIn >> arrPoint[j].x >> arrPoint[j].y;
		Province prTmp(provinceName, arrPoint);
		listProvinces.push_back(prTmp);
	}

	fIn.close();
}

void MapObject::setHandle(HWND hWnd)
{
	this->hWnd = hWnd;
}

void MapObject::inputPopulationData(int x, int y)
{
	int idx = getIdxOfProvince(x, y);
	if (idx != -1) {
		HGLOBAL hGlobalProvince = GlobalAlloc(GHND, sizeof(Province));
		Province* glbProvince = (Province*)GlobalLock(hGlobalProvince);
		CopyMemory(glbProvince, &listProvinces[idx], sizeof(Province));
		GlobalUnlock(hGlobalProvince);

		inputPopulation(hWnd, hGlobalProvince, x, y);

		glbProvince = (Province*)GlobalLock(hGlobalProvince);
		listProvinces[idx].population = glbProvince->population;
		listProvinces[idx].area = glbProvince->area;
		listProvinces[idx].populationDensity = glbProvince->populationDensity;
		listProvinces[idx].flagPICon = glbProvince->flagPICon;
		listProvinces[idx].pICon = glbProvince->pICon;
		GlobalUnlock(hGlobalProvince);

		GlobalFree(hGlobalProvince);
	}
}

void MapObject::inputProductData(int x, int y)
{
	int idx = getIdxOfProvince(x, y);
	if (idx != -1) {
		HGLOBAL hGlobalProvince = GlobalAlloc(GHND, sizeof(Province));
		Province* glbProvince = (Province*)GlobalLock(hGlobalProvince);
		CopyMemory(glbProvince, &listProvinces[idx], sizeof(Province));
		GlobalUnlock(hGlobalProvince);

		inputProduct(hWnd, hGlobalProvince, x, y);

		glbProvince = (Province*)GlobalLock(hGlobalProvince);
		listProvinces[idx].economicType, glbProvince->economicType;
		listProvinces[idx].listProduct = glbProvince->listProduct;
		listProvinces[idx].flagEICon = glbProvince->flagEICon;
		listProvinces[idx].eICon = glbProvince->eICon;
		GlobalUnlock(hGlobalProvince);
		
		GlobalFree(hGlobalProvince);
	}
}

void MapObject::drawICon()
{
	HDC hdc = GetDC(hWnd);
	
	BITMAP bmpPIcon, bmpEIcon;
	HBITMAP hBmpPIcon = (HBITMAP)LoadImage(NULL, L"dancu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	HBITMAP hBmpEIcon = (HBITMAP)LoadImage(NULL, L"sanpham.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	GetObject(hBmpPIcon, sizeof(BITMAP), &bmpPIcon);
	GetObject(hBmpEIcon, sizeof(BITMAP), &bmpEIcon);
	

	for (int i = 0; i < listProvinces.size(); ++i) {
		if (listProvinces[i].flagPICon) {
			HDC memDC = CreateCompatibleDC(hdc);
			SelectObject(memDC, hBmpPIcon);
			StretchBlt(hdc, listProvinces[i].pICon.x - bmpPIcon.bmWidth / 4, listProvinces[i].pICon.y - bmpPIcon.bmHeight / 2, bmpPIcon.bmWidth / 2, bmpPIcon.bmHeight / 2, memDC, 0, 0, bmpPIcon.bmWidth, bmpPIcon.bmHeight, SRCCOPY);
			DeleteDC(memDC);
		}
		if (listProvinces[i].flagEICon) {
			HDC memDC = CreateCompatibleDC(hdc);
			SelectObject(memDC, hBmpEIcon);
			StretchBlt(hdc, listProvinces[i].eICon.x - bmpEIcon.bmWidth / 4, listProvinces[i].eICon.y - bmpEIcon.bmHeight / 2, bmpEIcon.bmWidth / 2, bmpEIcon.bmHeight / 2, memDC, 0, 0, bmpEIcon.bmWidth, bmpEIcon.bmHeight, SRCCOPY);
			DeleteDC(memDC);
		}
	}
	
	DeleteObject(hBmpEIcon);
	DeleteObject(hBmpPIcon);
	ReleaseDC(hWnd, hdc);
}

int MapObject::getIdxOfProvince(int x, int y)
{
	for (int i = 0; i < listProvinces.size(); ++i) {
		if (listProvinces[i].checkProvincePosition(x, y))
			return i;
	}

	return -1;
}
