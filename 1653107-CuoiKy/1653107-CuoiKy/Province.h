#pragma once
#include "stdafx.h"

struct Product {
	WCHAR name[256];
	int quantity;
};

class Province 
{
public:
	Province();
	Province(string strName, POINT*);
	~Province();
	bool checkProvincePosition(int x, int y);
	
	int population;
	int area;
	int populationDensity;
	int economicType;
	vector<Product> listProduct;
	POINT pICon, eICon;
	bool flagPICon, flagEICon;
	void writeFile(wofstream&);

private:
	string provinceName;
	POINT arrPoint[6];
};

