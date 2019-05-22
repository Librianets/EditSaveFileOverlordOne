#include "global.hpp"

MSG msg;
HACCEL hAccel;

void RunMsg(void)
{
	hAccel = LoadAccelerators(gapp.inst, MAKEINTRESOURCE(IDA_ACCEL)); 
 if (hAccel == NULL) {Error(ERROR_ACCELNOT, ERROR_EXIT_APP);}
	
	BOOL bMsgVal = 0x0;

	while( bMsgVal = GetMessage(&msg, NULL, 0, 0))
	{
		switch(bMsgVal)
		{
			case 0: break;
			case -1: break;
			default:
			{
				if (IsDialogMessage(dlgapp[0].hWnd, &msg) == TRUE)
				{
				}
				else
				{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				}
		
			}break;
		}
	}
}

void DestroyAll (void)
{
CGameSaveControlOne.~CGameSaveControl();
DestroyWindow(gapp.wnd);
UnregisterClass(gapp._class, gapp.inst);
PostQuitMessage(WM_NULL);
}