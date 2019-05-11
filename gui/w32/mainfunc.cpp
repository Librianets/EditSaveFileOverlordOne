#include "global.hpp"

void runmsg(void)
{
	hAccel = LoadAccelerators(gapp.inst, MAKEINTRESOURCE(IDA_ACCEL)); 
    if (hAccel == NULL) {error(gaccelnot, exit_app);}
	
	while(GetMessage(&msg, NULL, 0, 0))
	{
		if (IsDialogMessage(dapp[0].hWnd, &msg) == TRUE)
		{
		}
		else
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	}
}

void destroy_all (void)
{
CloseWindow(gapp.wnd);
UnregisterClass(gapp._class, gapp.inst);
PostQuitMessage(WM_NULL);
}