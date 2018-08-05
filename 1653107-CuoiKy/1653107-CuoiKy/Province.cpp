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

void Province::writeFile(wofstream &fOut)
{
	wstring wstr = wstring(provinceName.begin(), provinceName.end());
	fOut << wstr.c_str() << endl;
	fOut << L"Dân cư:" << endl;
	fOut << L"Diện tích: " << area << L" km2" << endl;
	fOut << L"Dân số: " << population << endl;
	fOut << L"Mật độ dân số: " << populationDensity << L" người/km2" << endl;
	fOut << L"Sản phẩm:" << endl;
	fOut << L"Loại hình kinh tế: ";
	switch (economicType)
	{
	case 1:
		fOut << L"Nông nghiệp";
		break;
	case 2:
		fOut << L"Dịch vụ";
		break;
	case 3:
		fOut << L"Du lịch";
		break;
	case 4:
		fOut << L"Công nghiệp";
		break;
	}
	fOut << endl;
	fOut << L"Sản phẩm: " << listProduct[0].name << endl;
	fOut << L"Số lượng: " << listProduct[0].quantity << endl;
	fOut << L"Sản phẩm: " << listProduct[1].name << endl;
	fOut << L"Số lượng: " << listProduct[1].quantity << endl << endl;
}
