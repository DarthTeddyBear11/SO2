#pragma once
#include <stdio.h>
#include <io.h>
#include <Windows.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <tchar.h>
#include <conio.h>
#include <stdlib.h>


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

//handles sync e sharedMemo


//DLL.h
// O bloco ifdef seguinte � o modo standard de criar macros que tornam a exporta��o de
// fun��es e vari�veis mais simples. Todos os ficheiros neste projeto DLL s�o
// compilados com o s�mbolo DLL_IMP_EXPORTS definido. Este s�mbolo n�o deve ser definido
// em nenhum projeto que use a DLL. Desta forma, qualquer outro projeto que inclua este
// este ficheiro ir� ver as fun��es e vari�veis DLL_IMP_API como sendo importadas de uma
// DLL.


#include <windows.h>

//Definir uma constante para facilitar a leitura do prot�tipo da fun��o
//Este .h deve ser inclu�do no projeto que o vai usar (modo impl�cito)

//Esta macro � definida pelo sistema caso estejamos na DLL (<DLL_IMP>_EXPORTS definida)
//ou na app (<DLL_IMP>_EXPORTS n�o definida) onde DLL_IMP � o nome deste projeto
#ifdef DLL_EXPORTS

#define DLL_IMP_API __declspec(dllexport)
#else
#define DLL_IMP_API __declspec(dllimport)
#endif
extern "C"
{
	//Vari�vel global da DLL

	//Fun��es a serem exportadas/importadas
	//do servidor
	DLL_IMP_API int OnServerCreate();
	DLL_IMP_API int ola(void);


}