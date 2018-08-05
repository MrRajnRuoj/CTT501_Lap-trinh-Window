#pragma once
#include "stdafx.h"

struct Product {
	WCHAR name[256];
	WCHAR quantity[256];
};

class Province 
{
public:
	Province();
	Province(string strName, POINT*);
	~Province();
	bool checkProvincePosition(int x, int y);
	string getName();
	int population;
	int area;
	int populationDensity;
	WCHAR economicType[256];
	vector<Product> listProduct;

private:
	string provinceName;
	POINT arrPoint[6];
};

