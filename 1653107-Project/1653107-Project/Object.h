#pragma once
#include "stdafx.h"

struct Point {
	int x;
	int y;
};

class Object
{
public:
	virtual void draw() = 0;
	Point lftTp, rghtBttn;
};