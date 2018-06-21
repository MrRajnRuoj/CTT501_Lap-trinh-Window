#pragma once

#ifndef DLL_HEADER
#define DLL_HEADER

#define MAX_BUFFER	1024

// define a shared data structure
typedef struct {
	WCHAR	buffer[MAX_BUFFER];	// buffer to store typed chars
	int		n;					// number of chars in buffer
								// ... and other fields, if needed
} SHARED_DATA;

#endif
