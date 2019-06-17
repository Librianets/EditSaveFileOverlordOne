#include "global.hpp"		// project

MSG msg;
HACCEL hAccel;

WPARAM RunMsg(void)
{
	hAccel = LoadAccelerators(CGG.gapp.inst, MAKEINTRESOURCE(IDA_ACCEL)); 
	if (hAccel == NULL) {errormsg(ERROR_ACCELNOT, APP);}

	BOOL bMsgVal = 0x0;

	while( bMsgVal = GetMessage(&msg, NULL, 0, 0))
	{
		switch(bMsgVal)
		{
			case 0: break;
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
CGameSaveControlOne.~CGameSaveControl();
CUnpackPackOne.~CUnpackPack();
CSaveInfoOne.~CSaveInfo();
CSaveInfoWndControlOne.~CSaveInfoWndControl();
CGG.~CGlobal();

CALog.~CAppLogging();
CACon.~CAppConsole();
Cdbg.~CDebugInfo();

DestroyWindow(CGG.gapp.hwnd);
UnregisterClass(CGG.gapp.gclass, CGG.gapp.inst);

PostQuitMessage(WM_NULL);
}