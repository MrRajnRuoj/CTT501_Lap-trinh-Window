// CalculateInt.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#define EXPORTS __declspec(dllexport)

EXPORTS int Cong(int a, int b) {
	return a + b;
}

EXPORTS int Tru(int a, int b) {
	return a - b;
}

EXPORTS int Nhan(int a, int b) {
	return a * b;
}

EXPORTS int Chia(int a, int b) {
	if (b == 0)
		return -1;
	return a / b;
}

