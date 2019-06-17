#ifndef __FUNCTIONS_HPP__
#define __FUNCTIONS_HPP__

#define ERROR_NOTCORRECT 		0x0000
#define ERROR_GWNDNOT 			-0x0001
#define ERROR_GCLASSNOT 		-0x0002
#define ERROR_CREATECONSOLE 	-0x0004
#define ERROR_OPENFILE 			-0x0005
#define ERROR_FILESIZE 			-0x0006
#define ERROR_SAVEFILE 			-0x0007
#define ERROR_SAVECOUNT 		-0x0008
#define ERROR_LIMITMAXSIZE 		-0x0009

//#define ERROR_NOTFILESELECT 	-0x000A
//#define ERROR_FILECHECK 		-0x0005

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
	
	// public funcs
	int Init(HINSTANCE hInstance);
	void ClearClass(void);
	int SetPosDlg(HWND hwnd, HWND dia, POINT *pt);
	HWND CreateMainWndApp(void);
	void ShowWnd(HWND hWnd);
	void DlgInit(int numdlg);
	void PaintWnd (HWND hwnd, HDC hDC2);
	HDC CreateWnd (HWND hwnd);
	
	
private:
int iSizeWndX = 1280/2; //min 640
int iSizeWndY = 1024/2; //min 512
wchar_t sg_WndClass[MAXCLASSNAME] 		= L"Class main window";
wchar_t sg_Wnd[MAXCLASSNAME] 			= L"Редактор сохранений игры Overlord";

WNDCLASSEX WndCExMain;

BOOL MainRegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance);

};

class CGameSaveControl
{
public:
	
	// public val
	unsigned long int iNumberReadByte;wchar_t szFileTitle[MAXPATHLEN];
	wchar_t szFileName[MAXPATHLEN];
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

	OPENFILENAME ofn;
	
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
BOOL RegClassGroupBox(WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance);
short int ihwndCount = 5;

WNDCLASSEX WndCExGroupBoxOne;
WNDCLASSEX WndCExGroupBoxTwo;
WNDCLASSEX WndCExGroupBoxThree;

};

#endif // __FUNCTIONS_HPP__