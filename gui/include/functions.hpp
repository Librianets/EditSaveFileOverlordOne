#ifndef __FUNCTIONS_HPP__
#define __FUNCTIONS_HPP__

extern class CGameSaveControl CGameSaveControlOne;
extern class CUnpackPack CUnpackPackOne;
extern class CSaveInfo CSaveInfoOne;
extern class CSaveInfoWndControl CSaveInfoWndControlOne;
extern class CGlobal CGG;

void SetPosDlg (HWND hwnd, HWND dia);
HDC CreateWnd (HWND hwnd);
void PaintWnd (HWND hwnd, HDC hDC2);
void CreateMainWindow (void);
void DlgInit (int numdlg);

namespace OVERLORD
{
	int OpenFile(void);
	int SaveFile(void);
	int CloseFile(void);
	
	int SaveInfo(void);
	int SaveSlot(void);
}

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

typedef struct 
{
	int iEnable;
	int iStatus;
	RECT rectCB;
	RECT rectText;
	wchar_t sText[30];
} TCheckBox;

typedef struct 
{
	RECT rectWnd;
	wchar_t sText[30];
	wchar_t sClassName[30];
} TWndSI;

/////////////////////////////////////////////
/////////////////	CLASS	/////////////////
/////////////////////////////////////////////
class CGlobal
{
public:
	CGlobal();
	~CGlobal();
	
	// public val
	AppData gapp;
	Data dlgapp[MAXCOUNTERPOINTER];
	HDC 		HdcPaint;
	BITMAP		bitmap;
	HBITMAP		hBitmap;
	sizeall scwnd, szwnd, pwnd, t_xy_dia;
	
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
	
	// public val
	unsigned long int iNumberReadByte;
	
	// public funcs
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

#ifdef WINAPIPROJECT
	OPENFILENAME ofn;
#else

#endif

	wchar_t szFileName[MAXPATHLEN];
	wchar_t szFileTitle[MAXPATHLEN];
	vector <unsigned char> aBufferRead;

};

class CSaveInfoWndControl
{
public:
CSaveInfoWndControl();
~CSaveInfoWndControl();

// public val
HWND hWndSI[5];

TCheckBox aCBSI[10] =
{
	{0, 0, {15,15,30,30}, {aCBSI[0].rectCB.left+15+5, aCBSI[0].rectCB.top, aCBSI[0].rectText.left+115, aCBSI[0].rectCB.bottom}, L"Сохранение №1"},
	{0, 0, {15,40,30,55}, {aCBSI[1].rectCB.left+15+5, aCBSI[1].rectCB.top, aCBSI[1].rectText.left+115, aCBSI[1].rectCB.bottom}, L"Сохранение №2"},
	{0, 0, {15,65,30,80}, {aCBSI[2].rectCB.left+15+5, aCBSI[2].rectCB.top, aCBSI[2].rectText.left+115, aCBSI[2].rectCB.bottom}, L"Сохранение №3"},
	{0, 0, {15,90,30,105}, {aCBSI[3].rectCB.left+15+5, aCBSI[3].rectCB.top, aCBSI[3].rectText.left+115, aCBSI[3].rectCB.bottom}, L"Сохранение №4"},
	{0, 0, {15,115,30,130}, {aCBSI[4].rectCB.left+15+5, aCBSI[4].rectCB.top, aCBSI[4].rectText.left+115, aCBSI[4].rectCB.bottom}, L"Сохранение №5"},
	{0, 0, {15,140,30,155}, {aCBSI[5].rectCB.left+15+5, aCBSI[5].rectCB.top, aCBSI[5].rectText.left+115, aCBSI[5].rectCB.bottom}, L"Сохранение №6"},
	{0, 0, {15,165,30,180}, {aCBSI[6].rectCB.left+15+5, aCBSI[6].rectCB.top, aCBSI[6].rectText.left+115, aCBSI[6].rectCB.bottom}, L"Сохранение №7"},
	{0, 0, {15,190,30,205}, {aCBSI[7].rectCB.left+15+5, aCBSI[7].rectCB.top, aCBSI[7].rectText.left+115, aCBSI[7].rectCB.bottom}, L"Сохранение №8"},
	{0, 0, {15,215,30,230}, {aCBSI[8].rectCB.left+15+5, aCBSI[8].rectCB.top, aCBSI[8].rectText.left+115, aCBSI[8].rectCB.bottom}, L"Сохранение №9"},
	{0, 0, {15,240,30,255}, {aCBSI[9].rectCB.left+15+5, aCBSI[9].rectCB.top, aCBSI[9].rectText.left+115, aCBSI[9].rectCB.bottom}, L"Сохранение №10"}
};

TWndSI aWndSI[5] =
{
	{{5, 6, 155, 270}, L"Окно №1", L"ClassNameOne"},
	{{5, 281, 155, 225}, L"Окно №2", L"ClassNameTwo"},
	{{165, 6, 470, 500}, L"Окно №3", L"ClassNameThree"},
	{{0, 0, 0, 0}, L"Окно №4", L"ClassNameFour"},
	{{0, 0, 0, 0}, L"Окно №5", L"ClassNameFive"}
};
	
	// public funcs
	void ClearClass(void); // исключительно для повышения управляемости
	int CreateWnd(void);
	int CloseWnd(void);
	int SetWndLong(int num);
	
	//Get, Set
	
private:
short int ihwndCount = 5;

};

#endif // __FUNCTIONS_HPP__