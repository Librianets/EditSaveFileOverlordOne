#ifndef __FUNCTIONS_HPP__
#define __FUNCTIONS_HPP__

typedef struct 
{
	HWND hWnd;
	DLGPROC WndProc;
} Data;

typedef struct 
{
	HINSTANCE inst;
	HWND wnd;
	HMENU menu;
	wchar_t *_wnd;
	wchar_t *_class;
	WNDPROC WndProc;
} AppData;

typedef struct 
{
	unsigned int x;
	unsigned int y;
} sizeall;

extern HANDLE 		hFileOpen;
extern HDC			hDC;
extern HDC			hDC2;
extern HBITMAP		hBm;
extern BITMAP		bm;

extern OPENFILENAME ofn;

extern WNDCLASSEX WndCMain;
extern RECT RECTmainwnd;

extern AppData gapp;
extern Data dlgapp[MAXCOUNTERPOINTER];
extern sizeall scwnd, szwnd, pwnd, t_xy_dia;

extern vector<HWND> HWNDSAVEINFO;

BOOL MainRegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance);
DWORD SizeFile(HANDLE hFileOpen);
BOOL ReadFile (void);
BOOL SelectFile (void);
BOOL SaveFileEnd (void);

void SetPosDlg (HWND hwnd, HWND dia);
void CreateWnd (HWND hwnd);
void PaintWnd (HWND hwnd);
void CreateMainWindow (void);
void DlgInit (int numdlg);
void CreateWndSaveInfo (HWND hwnd);
void CloseWndSaveInfo ();

namespace LIA
{ 
	BOOL OpenFile(void);
	BOOL SaveFile(void);
}

#endif // __FUNCTIONS_HPP__