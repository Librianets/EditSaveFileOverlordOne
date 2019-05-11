#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__

#ifndef __GLOBAL_HPP__
#include <windows.h> 		// WINDOWS
#include <stdio.h> 			// Language C
#include <unistd.h> 		// Language C
#include <wchar.h>			// Language C
#include <winuser.h>		// WINAPI
#endif //__GLOBAL_HPP__

#define	ID_APP_ICON			100
#define	IDB_LOGO				101
#define	ID_LOGO					102
#define	IDB_LOGOMINI			103
#define	IDI_CONSOLE_SHOW			104
#define	IDI_CONSOLE_HIDE			105
#define	IDDLG_CONSOLE			106
#define	ID_CONSOLE_LB			107


#define	IDM_MENU				200
#define	IDM_MENUCONSOLE			201
#define	IDA_ACCEL				250	

#define	IDDLG_ABOUT				5001
#define	IDI_ABOUT1				5002
#define	IDI_EXIT					5003
#define IDI_CREATEFILE			5004
#define IDI_OPENFILE				5005

#define	ID_KEY_0				10000
#define	ID_KEY_1				10001
#define	ID_KEY_2				10001
#define	ID_KEY_100				10100
#define	ID_KEY_1000				11000





/////////	POSITION	/////////
//szwnd.x = (1280/2); //640
//szwnd.y = (1024/2); //512

#define CX_CONSOLE_DLG			0
#define CY_CONSOLE_DLG			143 // (512-(200+25)/2
#define X_CONSOLE_DLG 			300 //300*2=600 1920/2=960
#define Y_CONSOLE_DLG			100 //200*2=400 1280/2=640

#define CX_ABOUT_DLG			30
#define CY_ABOUT_DLG			30
#define X_ABOUT_DLG 			200
#define Y_ABOUT_DLG				100

#endif //__RESOURCE_HPP__