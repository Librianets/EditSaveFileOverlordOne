#ifndef __GLOBAL_HPP__
#define __GLOBAL_HPP__

//////////////////////////////////////////////////
//////////			global include		//////////
//////////////////////////////////////////////////
//////////////////////////////////////////////////
//////////		project include down	//////////
//////////////////////////////////////////////////

#include <windows.h> 		// WINDOWS
#include <stdio.h> 			// Language C
#include <stdarg.h>			// Language C
#include <unistd.h> 		// Language C
#include <wchar.h>			// Language C
#include <stdlib.h>			// Language C
#include <string.h>			// Language C
#include <wctype.h>			// Language C
#include <iostream>			// Language C++
#include <vector>			// Language C++
#include <iterator>			// Language C++
#include <winuser.h>		// WINAPI
#include <zlib.h>			// ZLIB

using std::vector;

//////////////////////////////////////////////////
#define FAILURE				-0x0001 // флаг провала выполнения функции // вместо BOOL
#define SUCCESS				0x0000 // флаг успешного выполнения функции // вместо BOOL

#define MAXCLASSNAME		0x0040 		// 64
#define MAXCOUNTERPOINTER 	0x0040 		// 64
#define MAXPATHLEN 			0x0200 		// 512
#define MAXSIZEFILE			0x00100000 	// 1 048 576
#define MAXMSGLEN			0x0040		// 64

#define DLG_ABOUT 			0x1000

#define MSG_SELECTOPENFILE	0x2001
#define MSG_READFILE		0x2002
#define MSG_CHECKFILE		0x2003
#define MSG_DECOMP			0x2004
#define MSG_COMP			0x2005
#define MSG_WRITEFILE		0x2006
#define MSG_SAVEINFO		0x2007
#define MSG_SAVESLOT		0x2008

/////////////////////////////////////////////////
/////////////////////////////////////////////////
#include "global.hpp"		// project
#include "resource.hpp"		// project
#include "winmain.hpp"		// project
#include "proc.hpp"			// project
#include "mainfuncs.hpp"	// project
#include "functions.hpp"	// project
#include "packunpack.hpp"	// project
#include "saveinfo.hpp"		// project
#include "logging.hpp"		// project

#endif //__GLOBAL_HPP__