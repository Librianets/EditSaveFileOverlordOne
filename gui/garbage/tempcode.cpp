/*
HMODULE handle = GetModuleHandle(NULL);
HRSRC rc = FindResource(handle, MAKEINTRESOURCE(name), MAKEINTRESOURCE(type));
HGLOBAL rcData = LoadResource(handle, rc);
DWORD size = SizeofResource(handle, rc);
const char *data = static_cast<const char *>(LockResource(rcData));
*/




	//wprintf(L"%p\n", gapp.qwe);
	//wprintf(L"%ls\n", gapp._class);
	//wprintf(L"%ls\n", gapp._wnd);
	//wprintf(L"%i\n", *gapp.qwe);

	//Paintlogo();
	
	//HWND logos;
	//Paintlogo();
	/*logos = CreateDialog(win32_hinst, MAKEINTRESOURCE(ID_LOGO), NULL, about_funcs);
	if (logos == NULL)
	{
		MessageBox(NULL, L"окно!", L"Ошибка", MB_OK);
		exit(1);
	}
	ShowWindow(logos, SW_SHOW); //nCmdShow
	sleep(5);
	CloseWindow(logos);*/
	
	//WM_CREATE










/*
    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
*/
/*
IDD_ABOUTBOX DIALOGEX 0, 0, 170, 62
STYLE DS_SETFONT | DS_MODALFRAME | DS_FIXEDSYS | WS_POPUP | WS_CAPTION | WS_SYSMENU
CAPTION "О программе WindowsProject1"
FONT 8, "MS Shell Dlg"
BEGIN
    ICON            IDR_MAINFRAME,IDC_STATIC,14,14,21,20
    LTEXT           "WindowsProject1, Версия 1.0",IDC_STATIC,42,14,114,8,SS_NOPREFIX
    LTEXT           "(c) 2019",IDC_STATIC,42,26,114,8
    DEFPUSHBUTTON   "ОК",IDOK,113,41,50,14,WS_GROUP
END

*/
/*

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}*/




	
/*
#define maxfilesize		1048576
HANDLE hfileread;
CreateFile()
unsigned char [maxfilesize];
ReadFile(hFile, lpBuff, dwBuffSize, &dwCount, NULL);

Чтение из файла в буфер lpBuff размером dwBuffSize. В переменную dwCount записывается реальное количество прочитанных байт. Последний опциональный аргумент называется lpOverlapped и о нем сейчас знать не нужно.

WriteFile(hFile, lpBuff, dwBuffSize, &dwCount, NULL);
Аргументы и семантика процедуры WriteFile полностью аналогичны ReadFile.

CloseHandle(hFile);*/
	
/*
HANDLE CreateFile(
  LPCTSTR  lpFileName,                         // имя файла
  DWORD  dwDesiredAccess,                      // режим доступа
  DWORD  dwShareMode,                          // совместный доступ
  LPSECURITY_ATTRIBUTES  lpSecurityAttributes, // SD (дескр. защиты)
  DWORD  dwCreationDisposition,                // как действовать
  DWORD  dwFlagsAndAttributes,                 // атрибуты файла
  HANDLE  hTemplateFile                        // дескр.шаблона файла
);

BOOL ReadFile(
  HANDLE hFile,                // дескриптор файла
  LPVOID lpBuffer,             // буфер данных
  DWORD nNumberOfBytesToRead,  // число байтов для чтения
  LPDWORD lpNumberOfBytesRead, // число прочитанных байтов
  LPOVERLAPPED lpOverlapped    // асинхронный буфер
);*/