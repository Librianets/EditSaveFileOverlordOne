#include "global.hpp"

MSG msg;

void RunMsg(void)
{
	hAccel = LoadAccelerators(gapp.inst, MAKEINTRESOURCE(IDA_ACCEL)); 
 if (hAccel == NULL) {Error(ERROR_ACCELNOT, ERROR_EXIT_APP);}
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		if (IsDialogMessage(dlgapp[0].hWnd, &msg) == TRUE)
		{
		}
		else
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	}
}

void DestroyAll (void)
{
CloseWindow(gapp.wnd);
CloseHandle(hFileOpen);
UnregisterClass(gapp._class, gapp.inst);
PostQuitMessage(WM_NULL);
}