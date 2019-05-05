#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

#include <windows.h> 		// WINDOWS
#include <stdio.h> 			// Language C
#include <unistd.h> 		// Language C
#include <wchar.h>			// Language C
#include <stdlib.h>			// Language C
#include <string.h>			// Language C
#include "cw.hpp"			// project
#include "error.hpp"		// project
#include "resource.hpp"		// project
#include "winmain.hpp"		// project
#include "cw.hpp"			// project
#include "console.hpp"		// project


#define MAXCLASSNAME		64
#define MAXCOUNTERPOINTER 	64

typedef struct {
	HWND hWnd;
	wchar_t *funcs;
} Data;

typedef struct {
	HINSTANCE inst;
	HWND wnd;
	HMENU menu;
	//wchar_t *qwe;
	wchar_t *_wnd;
	wchar_t *_class;
	wchar_t *funcs;
} AppData;

extern AppData gapp;
extern Data dapp[MAXCOUNTERPOINTER];

extern wchar_t gclass[MAXCLASSNAME];
extern wchar_t gwnd[MAXCLASSNAME];

//extern static HBITMAP      hBm;
//extern static BITMAP       bm;


void clearval(void);
void initiationval(void);

#endif //__GLOBAL_HPP__