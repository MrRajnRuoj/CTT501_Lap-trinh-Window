#pragma once

#ifndef DLL_HEADER
#define DLL_HEADER

#define MAX_BUFFER	1024

// define a shared data structure
typedef struct {
	int sum;
	bool isLock;
} SHARED_DATA;

#endif
