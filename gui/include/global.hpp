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

#include <iostream>
#include <vector>
//#include <iterator>
using std::vector;

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
#define MSG_WRITEFILE		0x1006
#define MSG_SAVEINFO		0x1007
#define MSG_SAVESLOT		0x1008

/////////////////////////////////////////////////
/////////////////////////////////////////////////
void ClearVal(void);
void InitiationVal(HINSTANCE hInstance);

/////////////////////////////////////////////////
/////////////////////////////////////////////////


/////////////////////////////////////////////////
/////////////////////////////////////////////////
extern HWND hDlgAbout;
extern HWND hDlgConsole;
extern wchar_t sgClass[MAXCLASSNAME];
extern wchar_t sgWnd[MAXCLASSNAME];
extern wchar_t sGlobalMsg[MAXPATHLEN];
extern unsigned char aGlobalBuffer[MAXSIZEFILE];
//extern unsigned char aBufferOne[MAXSIZEFILE];

/////////////////////////////////////////////////
/////////////////////////////////////////////////

#include "console.hpp"		// project
#include "resource.hpp"		// project
#include "winmain.hpp"		// project
#include "error.hpp"		// project
#include "proc.hpp"			// project
#include "mainfuncs.hpp"	// project
#include "functions.hpp"	// project
#include "packunpack.hpp"	// project
#include "saveinfo.hpp"	// project

#endif //__GLOBAL_HPP__