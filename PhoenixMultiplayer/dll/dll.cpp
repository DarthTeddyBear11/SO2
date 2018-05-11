#include"dll.h"

int riven() {
	printf("\nOla mundo da DLL V2.0\n\n");
	return 0;
}

int onServerCreate()
{

	CircularBufferInfo cbuffer;
	hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE,
		0, SM_SIZE, sharedMemName);
	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not create file mapping object (%d).\n"),
			GetLastError());
		return 0;
	}

	pBufConfig = (LPTSTR)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pBufConfig == NULL)
	{
		CloseHandle(hMapFile);
		_tprintf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());
		return 0;
	}


	pCircularInfo = pBufConfig + sizeof(infoCliente);

	//Circular Buffer Set Up
	cbuffer.bufReadIndex = 0;
	cbuffer.bufWriteIndex = 0;


	hSMServerCanRead = CreateEvent(NULL, TRUE, FALSE, EventSerCanRead);
	if (hSMServerCanRead == NULL)
	{
		UnmapViewOfFile(pBufConfig);
		CloseHandle(hMapFile);
		_tprintf(TEXT("Could not create a IO Shared Memory Event 1- (%d).\n"),
			GetLastError());
		return 0;
	}
	hSMClientCanRead = CreateEvent(NULL, TRUE, FALSE, EventCliCanRead);
	if (hSMClientCanRead == NULL)
	{
		UnmapViewOfFile(pBufConfig);
		CloseHandle(hMapFile);
		CloseHandle(hSMServerCanRead);
		_tprintf(TEXT("Could not create a IO Shared Memory Event 2- (%d).\n"),
			GetLastError());
		return 0;
	}

	// Intial free space in buffer
	hSEMempty = CreateSemaphore(NULL, BUF_TAM, BUF_TAM, SemReadBuff);
	if (hSEMempty == NULL)
	{
		UnmapViewOfFile(pBufConfig);
		CloseHandle(hMapFile);
		CloseHandle(hSMServerCanRead);
		CloseHandle(hSMClientCanRead);
		_tprintf(TEXT("Could not create a IO Shared Memory Event 3- (%d).\n"),
			GetLastError());
		return 0;
	}

	hSEMfull = CreateSemaphore(NULL, 0, BUF_TAM, SemWriteBuff);
	if (hSEMfull == NULL)
	{
		UnmapViewOfFile(pBufConfig);
		CloseHandle(hMapFile);
		CloseHandle(hSMServerCanRead);
		CloseHandle(hSMClientCanRead);
		_tprintf(TEXT("Could not create a IO Shared Memory Event 4- (%d).\n"),
			GetLastError());
		return 0;
	}

	hMutexBuff = CreateMutex(NULL, FALSE, MutexCirBuf);
	if (hMutexBuff == NULL)
	{
		UnmapViewOfFile(pBufConfig);
		CloseHandle(hMapFile);
		CloseHandle(hSMServerCanRead);
		CloseHandle(hSMClientCanRead);
		CloseHandle(hSEMempty);
		CloseHandle(hSEMfull);
		_tprintf(TEXT("Could not create a IO Shared Memory Event 5- (%d).\n"),
			GetLastError());
		return 0;
	}
	return 1;
}