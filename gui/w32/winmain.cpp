#include "winmain.h"

int WINAPI wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR  lpszCmdParam, int nCmdShow)
{
	MessageBox(NULL, L"Запуск редактора сохранений игры Overlord", L"Проверка", MB_OK);
	
	win32_hinst = hInstance;
	lia_RegClass(global_class, global_call, name_global_class, win32_hinst);
	Paintlogo();
	
	//WM_CREATE
	global_window = CreateWindowEx(WS_EX_CLIENTEDGE , name_global_class, name_global_window, \
	WS_OVERLAPPEDWINDOW, 10, 10, 600, 480, NULL, NULL, win32_hinst, NULL);

	if (!global_window)
	{
		MessageBox(NULL, L"Не удается создать главное окно!", L"Ошибка", MB_OK);
		exit(1);
	}

	ShowWindow(global_window,SW_SHOW); //nCmdShow
	ShowWindow(global_window,SW_SHOW); //nCmdShow
	
	UpdateWindow(global_window);//WM_PAINT
	


	
	
	while(GetMessage(&msg,NULL,0,0))
	{
		if (IsDialogMessage(notmodaldialog, &msg) == TRUE)
		{
			
		}
		else
		{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		}
	} return msg.wParam;
	
}