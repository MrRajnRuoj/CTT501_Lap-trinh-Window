// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <Windows.h>
#include <fstream>
#include <locale>
#include <codecvt>
#include "Pathcch.h"
#include "Shlwapi.h"
#include "DLL.h"
using namespace std;

HINSTANCE		hinstLib;
SHARED_DATA		*pSharedData;
HANDLE			hMapObject;

BOOL APIENTRY DllMain(HMODULE hModule,
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
			ZeroMemory(pSharedData->buffer, MAX_BUFFER);
			pSharedData->n = 0;
		}

		// Write down name of the current module
		WCHAR szFullPathName[255], *szFileName;
		wcscat_s(pSharedData->buffer, L"Hook was attached to:");
		GetModuleFileName(NULL, szFullPathName, 255);
		szFileName = PathFindFileName(szFullPathName);
		wcscat_s(pSharedData->buffer, szFileName);
		wcscat_s(pSharedData->buffer, L"\n");
		pSharedData->n += 22 + wcslen(szFileName);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		// write log data to file
		GetModuleFileName(NULL, szFullPathName, 255);
		PathCchRemoveFileSpec((LPTSTR)szFullPathName, 255);
		wcscat_s(szFullPathName, L"/log-data.txt");
		wfstream f;
		f.open(szFullPathName, ios::out);
		const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
		f.imbue(utf8_locale);
		f << pSharedData->buffer;
		f.close();
		// Unmap shared memory from the process's address space
		UnmapViewOfFile(pSharedData);
		// Close the process's handle to the file-mapping object
		CloseHandle(hMapObject);
		break;
	}
	return TRUE;
}

