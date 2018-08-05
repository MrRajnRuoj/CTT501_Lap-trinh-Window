#include "stdafx.h"
#include "Province.h"


Province::Province()
{
	this->population = 0;
	this->area = 0;
	this->populationDensity = 0;
	this->economicType = -1;
	Product pr1, pr2;
	wsprintf(pr1.name, L"");
	pr1.quantity = 0;
	wsprintf(pr2.name, L"");
	pr2.quantity = 0;
	this->listProduct.push_back(pr1);
	this->listProduct.push_back(pr2);
	this->flagEICon = false;
	this->flagPICon = false;
}

Province::Province(string strName, POINT *arrPoint)
{
	this->provinceName = strName;
	for (int i = 0; i < 6; ++i)
		this->arrPoint[i] = arrPoint[i];
	this->population = 0;
	this->area = 0;
	this->populationDensity = 0;
	this->economicType = -1;
	Product pr1, pr2;
	wsprintf(pr1.name, L"");
	pr1.quantity = 0;
	wsprintf(pr2.name, L"");
	pr2.quantity = 0;
	this->listProduct.push_back(pr1);
	this->listProduct.push_back(pr2);
	this->flagEICon = false;
	this->flagPICon = false;
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
