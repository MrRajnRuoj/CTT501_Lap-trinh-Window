#include "stdafx.h"
#include "MapObject.h"

#define INPUT_FILE	"map.txt"
#define IMPORT __declspec(dllimport)

IMPORT void inputPopulation(HWND hWnd, HGLOBAL hGlobalProvince, int x, int y);

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
		listProvinces[idx].population = glbProvince->population;
		listProvinces[idx].area = glbProvince->area;
		listProvinces[idx].populationDensity = glbProvince->populationDensity;
		GlobalFree(hGlobalProvince);
	}
}

void MapObject::inputProductData(int x, int y)
{
	int idx = getIdxOfProvince(x, y);
}

int MapObject::getIdxOfProvince(int x, int y)
{
	for (int i = 0; i < listProvinces.size(); ++i) {
		if (listProvinces[i].checkProvincePosition(x, y))
			return i;
	}

	return -1;
}
