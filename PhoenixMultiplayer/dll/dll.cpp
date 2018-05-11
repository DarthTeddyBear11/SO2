


#include <aclapi.h>
#include <strsafe.h>
#include <sddl.h> 

#include "dll.h"

//#include "resource.h"



int ola(void) {


	_tprintf(TEXT("Olá Mundo"));
	_getch();
	return 0;
}


//cliente
//int leComando() {
//
//	int KEY_code = 0;
//
//	while (KEY_code != KEY_EXIT)
//	{
//		if (_getwch())
//		{
//			KEY_code = _getwch();
//			//printf("KEY_code = %i \n", KEY_code);
//
//			switch (KEY_code)
//			{
//			case KEY_LEFT:
//				//move para esquerda
//				break;
//
//			case KEY_RIGHT:
//				//Move para direita                
//				break;
//
//			case KEY_UP:
//				//Do something                     
//				break;
//
//			case KEY_DOWN:
//				//Do something                     
//				break;
//
//			case KEY_SPACE:
//				//Dispara                 
//				break;
//
//			}
//
//		}
//	}
//
//	return 0;
//
//
//
//}


int onServerCreate(){

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



