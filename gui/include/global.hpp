#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

//////////		global include			//////////

#include <windows.h> 		// WINDOWS
#include <stdio.h> 			// Language C
#include <stdarg.h>			// Language C
#include <unistd.h> 		// Language C
#include <wchar.h>			// Language C
#include <stdlib.h>			// Language C
#include <string.h>			// Language C
#include <wctype.h>			// Language C
#include <winuser.h>		// WINAPI
#include <zlib.h>			// ZLIB
//////////		project include down	//////////

#define MAXCLASSNAME		0x0040 		// 64
#define MAXCOUNTERPOINTER 	0x0040 		// 64
#define MAXPATHLEN 			0x0200 		// 512
#define MAXSIZEFILE			0x00100000 	// 1 048 576
#define MAXMSGLEN			0x0040		// 64

#define DLG_ABOUT 			0x1000
#define MSG_SELECTOPENFILE	0x1001
#define MSG_READFILE		0x1002
#define MSG_CHECKFILE		0x1003
#define MSG_DECOMP			0x1004
#define MSG_COMP			0x1005

/////////////////////////////////////////////////
/////////////////////////////////////////////////
void ClearVal(void);
void InitiationVal(HINSTANCE hInstance);




/////////////////////////////////////////////////
/////////////////////////////////////////////////
typedef struct 
{
	HWND hWnd;
	DLGPROC WndProc;
} Data;

typedef struct 
{
	HINSTANCE inst;
	HWND wnd;
	HMENU menu;
	wchar_t *_wnd;
	wchar_t *_class;
	WNDPROC WndProc;
} AppData;

typedef struct 
{
	unsigned int x;
	unsigned int y;
} sizeall;

typedef union
{//--HN
	wchar_t sValue[128];
	unsigned short usiValue;
	unsigned int uiValue;
	unsigned long ulValue;
	unsigned long long ullValue;
	float fValue;
} typeval;




/////////////////////////////////////////////////
/////////////////////////////////////////////////
extern RECT RECTmainwnd;
extern AppData gapp;
extern Data dlgapp[MAXCOUNTERPOINTER];
extern sizeall scwnd, szwnd, pwnd, t_xy_dia;
extern HMENU hMenu;
extern HWND notmodaldialog;
extern HACCEL hAccel;
extern HWND hDlgAbout;
extern HWND hDlgConsole;
extern HWND hLogo;
extern HANDLE hFileOpen;

extern WNDCLASSEX WndCMain;

extern HDC			hDC;
extern HDC			hDC2;
extern HBITMAP		hBm;
extern BITMAP		bm;

extern wchar_t sgClass[MAXCLASSNAME];
extern wchar_t sgWnd[MAXCLASSNAME];
extern wchar_t fileopen[MAXPATHLEN];
extern wchar_t sError[MAXMSGLEN];
extern wchar_t sWarning[MAXMSGLEN];
extern wchar_t sWndNot[MAXMSGLEN];
extern wchar_t sClassNot[MAXMSGLEN];
extern wchar_t sAccaelNot[MAXMSGLEN];
extern wchar_t sFileSelect[MAXMSGLEN];
extern wchar_t sConsole[MAXMSGLEN];
extern wchar_t sGlobalMsg[MAXPATHLEN];
extern wchar_t sOpenFile[MAXMSGLEN];
extern wchar_t sFileSize[MAXMSGLEN];

extern wchar_t sFailCheckConst[MAXMSGLEN];
extern wchar_t sCheckCrc32[MAXMSGLEN];
extern wchar_t sDecompress[MAXMSGLEN];
extern wchar_t sCheckSum[MAXMSGLEN];

extern unsigned char aGlobalBuffer[MAXSIZEFILE];
extern unsigned char aBufferDecomp[MAXSIZEFILE];

extern OPENFILENAME ofn;

/////////////////////////////////////////////////
/////////////////////////////////////////////////

#include "console.hpp"		// project
#include "resource.hpp"		// project
#include "winmain.hpp"		// project
#include "error.hpp"		// project
#include "proc.hpp"			// project
#include "mainfuncs.hpp"	// project
#include "functions.hpp"	// project
#include "PackUnpack.hpp"	// project

#endif //__GLOBAL_HPP__