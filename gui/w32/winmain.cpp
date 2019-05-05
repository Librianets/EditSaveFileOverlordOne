#include "global.hpp"


HMENU hMenu;
HWND notmodaldialog;
HWND global_window;
HACCEL haccel;
WNDCLASSEX global_class;
HWND logo;


int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR lpszCmdParam, int nCmdShow)
{
	initiationval();
	gapp.inst = hInstance;
	
	CreateMainWindow();
	runmsg();

return 0;	
}