#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

//////////		global include			//////////

#include <windows.h> 		// WINDOWS
#include <stdio.h> 			// Language C
#include <unistd.h> 		// Language C
#include <wchar.h>			// Language C
#include <stdlib.h>			// Language C
#include <string.h>			// Language C
#include <winuser.h>		// WINAPI

//////////		project include down	//////////

#define MAXCLASSNAME		64
#define MAXCOUNTERPOINTER 	64
#define MAXPATHLEN 			512
#define MSGOPENFILE			0x1000
#define MAXMSGLEN			64

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

extern RECT rectmainwnd;
extern AppData gapp;
extern Data dapp[MAXCOUNTERPOINTER];
extern sizeall scwnd, szwnd, pwnd, t_xy_dia;
extern HMENU hMenu;
extern HWND notmodaldialog;
extern HACCEL hAccel;
extern WNDCLASSEX WndC_main;
extern HWND hLogo;
extern HANDLE hConsole;

extern wchar_t s_gclass[MAXCLASSNAME];
extern wchar_t s_gwnd[MAXCLASSNAME];
extern wchar_t fileopen[MAXPATHLEN];

extern wchar_t sError[MAXMSGLEN];
extern wchar_t sWarning[MAXMSGLEN];
extern wchar_t s_gwndnot[MAXMSGLEN];
extern wchar_t s_gclassnot[MAXMSGLEN];
extern wchar_t s_gaccelnot[MAXMSGLEN];
extern wchar_t s_filecheck[MAXMSGLEN];
extern wchar_t s_console[MAXMSGLEN];

void clearval(void);
void initiationval(HINSTANCE hInstance);

#include "cw.hpp"			// project
#include "error.hpp"		// project
#include "resource.hpp"		// project
#include "winmain.hpp"		// project
#include "cw.hpp"			// project
#include "console.hpp"		// project
#endif //__GLOBAL_HPP__