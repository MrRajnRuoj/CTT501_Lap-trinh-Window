#include "stdafx.h"
#include "Province.h"


Province::Province()
{
}

Province::Province(string strName, POINT *arrPoint)
{
	this->provinceName = strName;
	for (int i = 0; i < 6; ++i)
		this->arrPoint[i] = arrPoint[i];
}


Province::~Province()
{
}

bool Province::checkProvincePosition(int x, int y)
{
	int i, j;
	bool check = false;
	int nvert = 6;

	for (i = 0, j = nvert - 1; i < nvert; j = i++) {
		if (((arrPoint[i].y>y) != (arrPoint[j].y>y)) &&
			(x < (arrPoint[j].x - arrPoint[i].x) * (y - arrPoint[i].y) / (arrPoint[j].y - arrPoint[i].y) + arrPoint[i].x))
			check = !check;
	}
	return check;
}

string Province::getName()
{
	return this->provinceName;
}
