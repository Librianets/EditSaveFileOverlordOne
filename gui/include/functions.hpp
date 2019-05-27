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
	HWND hwnd;
	HMENU menu;
	wchar_t *gclass;
	wchar_t *gwnd;
	WNDPROC WndProc;
} AppData;

typedef struct 
{
	unsigned int x;
	unsigned int y;
} sizeall;

extern HDC			hDC;
extern HDC			hDC2;
extern HBITMAP		hBm;
extern BITMAP		bm;

extern WNDCLASSEX WndCMain;
extern RECT RECTmainwnd;
extern sizeall scwnd, szwnd, pwnd, t_xy_dia;

BOOL MainRegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance);
void SetPosDlg (HWND hwnd, HWND dia);
void CreateWnd (HWND hwnd);
void PaintWnd (HWND hwnd);
void CreateMainWindow (void);
void DlgInit (int numdlg);

extern class CGameSaveControl CGameSaveControlOne;
extern class CUnpackPack CUnpackPackOne;
extern class CSaveInfo CSaveInfoOne;
extern class CSaveInfoWndControl CSaveInfoWndControlOne;
extern class CGlobal CGG;


namespace OVERLORD
{
	int OpenFile(void);
	int SaveFile(void);
	int CloseFile(void);
	
	int SaveInfo(void);
	int SaveSlot(void);
}

class CGlobal
{
public:
	CGlobal();
	~CGlobal();
	
	// public val
	AppData gapp;
	Data dlgapp[MAXCOUNTERPOINTER];

	// public funcs
	void Init(HINSTANCE hInstance);
	void ClearClass(void);

private:

wchar_t sg_WndClass[MAXCLASSNAME] 		= L"Class main window";
wchar_t sg_Wnd[MAXCLASSNAME] 			= L"Редактор сохранений игры Overlord";

};


class CGameSaveControl
{
public:
	
	// public value
	unsigned long int iNumberReadByte;
	
	// function
	CGameSaveControl();
	~CGameSaveControl();
	
	void ClearClass(void); // исключительно для повышения управляемости
	int SelectGameFile(void);
	int SelectSaveGameFile(void);
	int ReadGameFile(void);
	int WriteGameFile(void);
	
	//Get, Set
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

};

class CSaveInfoWndControl
{
public:

	// public value
	
	// function
	CSaveInfoWndControl();
	~CSaveInfoWndControl();
	
	void ClearClass(void); // исключительно для повышения управляемости
	int CreateWnd(void);
	int CloseWnd(void);
	int SetWndLong(int num);
	//Get, Set
	HWND *GetHWNDSAVEINFO (void);
	
private:
short int ihwndCount = 30;
HWND HWNDSAVEINFO[30];
//HWND hWndSI[1];

};


#endif // __FUNCTIONS_HPP__