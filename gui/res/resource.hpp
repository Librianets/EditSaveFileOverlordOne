#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__

#ifndef __GLOBAL_HPP__
#include <windows.h> 		// WINDOWS
#include <stdio.h> 			// Language C
#include <unistd.h> 		// Language C
#include <wchar.h>			// Language C
#include <winuser.h>		// WINAPI
#endif //__GLOBAL_HPP__

///////////////// OTHER /////////////////
#define	ID_APP_ICON				0x0000
#define	IDB_LOGOMINI			0x0001
#define	IDB_LOGO				0x0002
#define	IDA_ACCEL				0x0003	
////////////////////////////////////////


///////////////// MENU /////////////////
#define	IDM_MENU				0x0010
#define	IDM_MENUERROR_CONSOLE			0x0011
////////////////////////////////////////


///////////////// DIALOGS /////////////////
#define	IDDLG_ABOUT				0x0100
#define	IDDLG_ERROR_CONSOLE			0x0101
////////////////////////////////////////

///////////////// MENUITEM /////////////////
#define	IDI_ABOUT1				0x1001
#define	IDI_EXIT				0x1002
#define IDI_CREATEFILE			0x1003
#define IDI_OPENFILE			0x1004
#define	IDI_CONSOLE_SHOW		0x1005
#define	IDI_CONSOLE_HIDE		0x1006
#define	IDI_CONSOLE_LB			0x1007
#define	IDI_CONSOLE_CLEAR		0x1008
#define	IDI_CONSOLECOMLINE		0x1009
#define	IDI_GETLINECONSOLE		0x1010
#define	IDI_CLOZEFILE			0x1011
#define	IDI_SAVEFILE			0x1012

////////////////////////////////////////

///////////////// KEYACCEL /////////////////
#define	ID_KEY_0				0x5001
#define	ID_KEY_1				0x5002
#define	ID_KEY_2				0x5003
#define	ID_KEY_100				0x5004
#define	ID_KEY_1000				0x5005
////////////////////////////////////////




/////////	POSITION	/////////
//szwnd.x = (1280/2); //640
//szwnd.y = (1024/2); //512

#define CX_CONSOLE_DLG			0
#define CY_CONSOLE_DLG			143 // (512-(200+25)/2
#define X_CONSOLE_DLG 			300 //300*2=600 1920/2=960
#define Y_CONSOLE_DLG			100 //200*2=400 1280/2=640

#define CX_ABOUT_DLG			0
#define CY_ABOUT_DLG			0
#define X_ABOUT_DLG 			200
#define Y_ABOUT_DLG				150

#endif //__RESOURCE_HPP__