#include <windows.h> 		// WINDOWS
#include <vector>			// Language C++
using std::vector;

#include "resource.hpp"		// project
#include "global.hpp"		// project
#include "functions.hpp"	// project

#include "debug.hpp"		// project
#include "logging.hpp"		// project

#include "mainfuncs.hpp"	// project

MSG msg;
HACCEL hAccel;

WPARAM RunMsg(void)
{
	hAccel = LoadAccelerators(COA.gapp.inst, MAKEINTRESOURCE(IDA_ACCEL));
	if (hAccel == NULL) {errormsg(ERROR_ACCELNOT, APP);}
	
	// потом написать обработчик акселерата
	
	int bMsgVal = 0x0;

	while( bMsgVal = GetMessage(&msg, NULL, 0, 0))
	{
		switch(bMsgVal)
		{
			//case 0: break;// 0
			case -1: break;
			default:
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}break;
		}
	}
return msg.wParam;
}

void DestroyAll (void)
{
/*CGameSaveControlOne.~CGameSaveControl();
CUnpackPackOne.~CUnpackPack();
CSIOO.~CSaveInfo();
CSIWC.~CSaveInfoWndControl();
COA.~CGlobal();

CALog.~CAppLogging();
CACon.~CAppConsole();
Cdbg.~CDebugInfo();*/

DestroyWindow(COA.gapp.hwnd);
UnregisterClass(COA.gapp.gclass, COA.gapp.inst);

PostQuitMessage(WM_NULL);
}