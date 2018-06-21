// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <Windows.h>
#include "Shlwapi.h"
#include "DLL.h"
using namespace std;

HINSTANCE		hinstLib;
SHARED_DATA		*pSharedData;
HANDLE			hMapObject;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	hinstLib = hModule;				// store instance of DLL into a global variable

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// Create a named file mapping object 
		hMapObject = CreateFileMapping(
			(HANDLE)0xFFFFFFFF,		// use paging file
			NULL,					// no security attr.
			PAGE_READWRITE,			// read/write access
			0,						// size: high 32-bits
			sizeof(SHARED_DATA),	// size: low 32-bits
			L"MyHook Sample");		// name of map object

									// check if shared memory is existing
		bool isExisted;
		isExisted = (GetLastError() == ERROR_ALREADY_EXISTS);

		if (hMapObject == NULL)  return FALSE;

		//  Get a pointer to the file-mapped shared memory
		pSharedData = (SHARED_DATA *)MapViewOfFile(
			hMapObject,				// object to map view of 
			FILE_MAP_WRITE,			// read/write access       
			0,						// high offset: beginning high
			0,						// low offset: beginning low
			0);						// default: map entire file

		if (pSharedData == NULL)  return FALSE;

		// Init value for shared memory ONLY at the first time
		if (!isExisted) {
			pSharedData->sum = 0;
			pSharedData->isLock = false;
		}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		// Unmap shared memory from the process's address space
		UnmapViewOfFile(pSharedData);
		// Close the process's handle to the file-mapping object
		CloseHandle(hMapObject);
		break;
	}
	return TRUE;
}

