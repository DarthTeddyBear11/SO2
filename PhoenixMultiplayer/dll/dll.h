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
// O bloco ifdef seguinte é o modo standard de criar macros que tornam a exportação de
// funções e variáveis mais simples. Todos os ficheiros neste projeto DLL são
// compilados com o símbolo DLL_IMP_EXPORTS definido. Este símbolo não deve ser definido
// em nenhum projeto que use a DLL. Desta forma, qualquer outro projeto que inclua este
// este ficheiro irá ver as funções e variáveis DLL_IMP_API como sendo importadas de uma
// DLL.


#include <windows.h>

//Definir uma constante para facilitar a leitura do protótipo da função
//Este .h deve ser incluído no projeto que o vai usar (modo implícito)

//Esta macro é definida pelo sistema caso estejamos na DLL (<DLL_IMP>_EXPORTS definida)
//ou na app (<DLL_IMP>_EXPORTS não definida) onde DLL_IMP é o nome deste projeto
#ifdef DLL_EXPORTS

#define DLL_IMP_API __declspec(dllexport)
#else
#define DLL_IMP_API __declspec(dllimport)
#endif
extern "C"
{
	//Variável global da DLL

	//Funções a serem exportadas/importadas
	//do servidor
	DLL_IMP_API int OnServerCreate();
	DLL_IMP_API int ola(void);


}