#include "global.hpp"		// project

MSG msg;
HACCEL hAccel;

void RunMsg(void)
{
	hAccel = LoadAccelerators(CGG.gapp.inst, MAKEINTRESOURCE(IDA_ACCEL)); 
	if (hAccel == NULL) {Log.ErrorMsg(ERROR_ACCELNOT);}
	
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
}

void DestroyAll (void)
{
CGameSaveControlOne.~CGameSaveControl();
CUnpackPackOne.~CUnpackPack();
CSaveInfoOne.~CSaveInfo();
CSaveInfoWndControlOne.~CSaveInfoWndControl();
CGG.~CGlobal();
Log.~CLogging();

DestroyWindow(CGG.gapp.hwnd);
UnregisterClass(CGG.gapp.gclass, CGG.gapp.inst);

PostQuitMessage(WM_NULL);
}