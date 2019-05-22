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

//extern OPENFILENAME ofn;

extern WNDCLASSEX WndCMain;
extern RECT RECTmainwnd;

extern AppData gapp;
extern Data dlgapp[MAXCOUNTERPOINTER];
extern sizeall scwnd, szwnd, pwnd, t_xy_dia;

extern vector<HWND> HWNDSAVEINFO;

BOOL MainRegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance);
void SetPosDlg (HWND hwnd, HWND dia);
void CreateWnd (HWND hwnd);
void PaintWnd (HWND hwnd);
void CreateMainWindow (void);
void DlgInit (int numdlg);
void CreateWndSaveInfo (HWND hwnd);
void CloseWndSaveInfo ();

extern class CGameSaveControl CGameSaveControlOne;
extern class CUnpackPack CUnpackPackOne;

namespace OVERLORD
{
	int OpenFile(void);
}


class CGameSaveControl
{
public:
	CGameSaveControl()
	{
	memset(&szFileName, 0, sizeof(szFileName));
	memset(&szFileTitle, 0, sizeof(szFileTitle));
	memset(&ofn, 0, sizeof(ofn));
	}
	
	~CGameSaveControl()
	{
		aBufferRead.~vector();
		memset(&szFileName, 0, sizeof(szFileName));
		memset(&szFileTitle, 0, sizeof(szFileTitle));
		memset(&ofn, 0, sizeof(ofn));
	}
	
	int SelectFile(void); // 0 true
	int ReadSaveFile(void);
	vector <unsigned char> *lpGetBuffer(void);
	unsigned long int GetiNumberReadByte(void);
	
private:

#if WIN32PROJECT
#if WINAPIPROJECT
	OPENFILENAME ofn;
#else

#endif
#endif

	wchar_t szFileName[MAXPATHLEN];
	wchar_t szFileTitle[MAXPATHLEN];
	vector <unsigned char> aBufferRead;
	unsigned long int iNumberReadByte;

};

#endif // __FUNCTIONS_HPP__