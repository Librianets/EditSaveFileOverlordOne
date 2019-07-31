#ifndef __FUNCTIONS_HPP__
#define __FUNCTIONS_HPP__

#define ERROR_NOTCORRECT 		0x0000
#define ERROR_GWNDNOT 			-0x0001
#define ERROR_GCLASSNOT 		-0x0002
#define ERROR_CREATECONSOLE 	-0x0004
#define ERROR_OPENFILE 			-0x0005
#define ERROR_FILESIZE 			-0x0006
#define ERROR_SAVEFILE 			-0x0007
#define ERROR_LIMITMAXSIZE 		-0x00011

//#define ERROR_NOTFILESELECT 	-0x000A
//#define ERROR_FILECHECK 		-0x0005

extern class CGameSaveControl CGameSaveControlOne;
extern class CUnpackPack CUnpackPackOne;
extern class CSaveInfo CSaveInfoOne;
extern class CSaveInfoWndControl CSIWC;
extern class COverlordApp COA;

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
} DataWnd, *pDataWnd;

typedef struct 
{
	HINSTANCE inst;
	HWND hwnd;
	HMENU menu;
	wchar_t *gclass;
	wchar_t *gwnd;
	WNDPROC WndProc;
} AppData, *pAppData;

typedef struct 
{
	int 	iEnable;
	int 	iStatus;
	RECT 	rectCB;
	wchar_t sText[30];
	HWND	hWnd;
} TCheckBox;

typedef struct 
{
	RECT rectWnd;
	wchar_t sText[30];
} TWndSI;

/////////////////////////////////////////////
/////////////////	CLASS	/////////////////
/////////////////////////////////////////////
class COverlordApp
{
public:
	COverlordApp();
	~COverlordApp();
	void ClearClass(void);
	
	void Init(HINSTANCE hInstance);
	int SetPosDlg(HWND hwnd, HWND dia, POINT *pt);
	HWND CreateMainWndApp(void);
	void ShowWnd(HWND hWnd);
	void DlgInit(int numdlg);
	void PaintWnd(HWND hwnd, HDC hDC2);
	HDC CreateWnd(HWND hwnd);
	void ParseCommandLine(PWSTR lpszCmdParam);
	
//// class status ////////////////////////
	int iErrorStatus = 0; 				//
	int SetErrorStatus (int iError);	//
	int GetErrorStatus (void);			//
	void ClearErrorStatus (void);		//
//// class status ////////////////////////

public:

	LPWSTR *pArgv; 	//	
	int iArgc;		//
	vector <wchar_t> aPathApp;
	int iSizePath;

	AppData 	gapp;
	DataWnd 	dlgapp[1];
	HDC 		HdcPaint;
	BITMAP		bitmap;
	HBITMAP		hBitmap;
	int iSizeWndX = 1280/2;//min 640
	int iSizeWndY = 1023/2;//min 512

private:
	HWND statusbar;
	wchar_t sg_WndClass[MAXCLASSNAME] 		= L"Class main window";
	wchar_t sg_Wnd[MAXCLASSNAME] 			= L"Редактор сохранений игры Overlord";
	WNDCLASSEX WndCExMain;
	BOOL MainRegClass(WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance);

};

class CGameSaveControl
{
public:
	
	// public val
	unsigned long int iNumberReadByte;
	wchar_t szFileTitle[MAXPATHLEN];
	wchar_t szFileName[MAXPATHLEN];
	// public funcs
	CGameSaveControl();
	~CGameSaveControl();
	
	void ClearClass(void);// исключительно для повышения управляемости
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
	void ClearClass(void);// исключительно для повышения управляемости
	
	int CreateWnd(void);
	int CloseWnd(void);
	int SetWndLong(int num);
	BOOL RegClassGroupBox(WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance);
	int RefreshAlternativeInfoSI(int iSaveSelect);
	
	
public:
	HWND hWndSI[5];
	//HWND hEditControl[10];
	//HWND hUpDownControl[10];
		
	int iPosSaveInCB[10];
	WNDCLASSEX WndCExGroupBoxOne;
	
	TCheckBox aCBSI[10] =
	{
		{0, 0, {10,20,135,23}, 			L"Сохранение №1", NULL},
		{0, 0, {10,20+(23+2)*1,135,23}, L"Сохранение №2", NULL},
		{0, 0, {10,20+(23+2)*2,135,23}, L"Сохранение №3", NULL},
		{0, 0, {10,20+(23+2)*3,135,23}, L"Сохранение №4", NULL},
		{0, 0, {10,20+(23+2)*4,135,23}, L"Сохранение №5", NULL},
		{0, 0, {10,20+(23+2)*5,135,23}, L"Сохранение №6", NULL},
		{0, 0, {10,20+(23+2)*6,135,23}, L"Сохранение №7", NULL},
		{0, 0, {10,20+(23+2)*7,135,23}, L"Сохранение №8", NULL},
		{0, 0, {10,20+(23+2)*8,135,23}, L"Сохранение №9", NULL},
		{0, 0, {10,20+(23+2)*9,135,23}, L"Сохранение №10", NULL}
	};

	TWndSI aWndSI[5] =
	{
		{{5, 6, 155, 276}, 		L"Сохранения"},
		{{5, 281, 155, 506}, 	L"Доп.информация"},
		{{160, 6, 635, 506}, 	L"Информация"},
		{{10, 286, 140, 200}, 	L"Ниспадающее меню"},
		{{10, 316, 140, 185}, 	L"Ниспадающее меню"}
	};
	
private:

};

#endif // __FUNCTIONS_HPP__