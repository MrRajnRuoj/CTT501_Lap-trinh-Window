#pragma once
#include "Province.h"

class MapObject
{
public:
	MapObject();
	~MapObject();
	void importData();
	void setHandle(HWND);
	void inputPopulationData(int x, int y);
	void inputProductData(int x, int y);

private:
	int getIdxOfProvince(int x, int y);
	HWND hWnd;
	vector<Province> listProvinces;
};

