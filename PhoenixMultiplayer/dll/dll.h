#pragma once
#include<stdio.h>
#include<stdlib.h>

#include <stdio.h>
#include <io.h>
#include <Windows.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <tchar.h>
#include <conio.h>
#include <stdlib.h>
#include <tchar.h>


//inputs cliente
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_LEFT 3
#define KEY_RIGHT 4
#define KEY_SPACE 5
#define KEY_EXIT 6

//SharedMemo
#define sharedMemName TEXT("MemPartilhada")

#define SM_SIZE 200000
HANDLE hMapFile;
LPCTSTR pBufConfig, pCircularBuf, pCircularInfo;

//buffer
#define BUF_TAM 2
typedef struct
{
	int bufReadIndex;
	int bufWriteIndex;
}CircularBufferInfo;
#define SemWriteBuff TEXT("SemEscreveCirBuff")
#define SemReadBuff TEXT("SemLeCirBuff")
#define MutexCirBuf TEXT("MutexCirBuf")

HANDLE hMutexBuff, hSEMempty, hSEMfull;



//sharedMemo Sync
#define EventCliCanRead TEXT("ClienteVaiLer")
#define EventSerCanRead TEXT("ServidorVaiLer")
HANDLE hSMClientCanRead, hSMServerCanRead;






typedef struct {

	int tecla;

}infoCliente;


#ifdef DLL_EXPORTS
#define DLL_IMP_API __declspec(dllexport)
#else
#define DLL_IMP_API __declspec(dllimport)
#endif

extern "C"
{
	DLL_IMP_API int riven(void);
	DLL_IMP_API int onServerCreate();
}