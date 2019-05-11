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
#include <winuser.h>		// WINAPI
#include <wctype.h>			// Language C

//////////		project include down	//////////

#define MAXCLASSNAME		0x0064
#define MAXCOUNTERPOINTER 	0x0064
#define MAXPATHLEN 			0x0512
#define MSGOPENFILE			0x1000
#define MAXMSGLEN			0x0064

#define DLG_ABOUT 			0x1000

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
extern HWND hDlgAbout;
extern HWND hDlgConsole;
extern HWND hLogo;
extern WNDCLASSEX WndC_main;

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
extern wchar_t globalmsg[MAXPATHLEN];

BOOL CALLBACK AboutWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK ConsoleWndProc (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI MainWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL MainRegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance);

void clearval(void);
void initiationval(HINSTANCE hInstance);
void position_dia (HWND hwnd, HWND dia);
void Createwnd (HWND hwnd);
void Paintwnd (HWND hwnd);
void destroy_all (void);
void runmsg (void);
void CreateMainWindow (void);
void checkfile (void);
void openfile (void);
void dialoginit (int numdlg);

#include "cw.hpp"			// project
#include "error.hpp"		// project
#include "resource.hpp"		// project
#include "winmain.hpp"		// project
#include "cw.hpp"			// project
#include "console.hpp"		// project

#endif //__GLOBAL_HPP__