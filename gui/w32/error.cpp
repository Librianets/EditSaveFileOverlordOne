#include "global.hpp"

MSG msg;

void error (int msg, int flag_exit)
{//--HN
	
	switch (msg)
	{
		case gwndnot:
		{
			MessageBox(NULL, s_gwndnot, sError, MB_OK);
			break;
		}
		case gclassnot:
		{
			MessageBox(NULL, s_gclassnot, sError, MB_OK);
			break;
		}
		case gaccelnot:
		{
			MessageBox(NULL, s_gaccelnot, sError, MB_OK);
			break;
		}
		
		case filecheck:
		{
			MessageBox(NULL, s_filecheck, sWarning, MB_OK);
			break;
		}
		
		case console:
		{
			MessageBox(NULL, s_console, sWarning, MB_OK);
			break;
		}
	}
	
	if (flag_exit == exit_app){exit(1);} //PostQuitMessage(WM_NULL);
}