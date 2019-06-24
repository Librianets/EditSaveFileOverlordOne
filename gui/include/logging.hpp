#ifndef __LOGGING_HPP__
#define __LOGGING_HPP__

extern class CDebugInfo		Cdbg;
extern class CAppLogging	CALog;
extern class CAppConsole	CACon;

#ifdef DEBUGMODE
#define debug(fmt, ...)				Cdbg.Debug(fmt, __VA_ARGS__);CACon.WriteDlgConsole(Cdbg.lpGetGlobalMsg());
#else
#define debug(fmt, ...)
#endif

#ifdef LOGGING
#define info(fmt, ...)				Cdbg.Info(fmt, __VA_ARGS__);CACon.WriteDlgConsole(Cdbg.lpGetGlobalMsg());
// как бы обойти нестыковку по параметрам
#else
#define info(fmt, ...)
#endif

#ifdef WINAPIMSG
#define errormsg(iMSG, iCategory)	CALog.ErrorMsg(iMSG, iCategory)
#else
#define errormsg(iMSG, iCategory)
#endif

#define MAXMSGLEN			0x0040		// 64

#define APP 		0x00	// сообщения приложения
#define PACKLIB 	0x02	// библиотека распаковки, упаковки
#define SI 			0x03	// библиотека saveinfo
#define SS 			0x04	// библиотека saveslot

typedef struct
{
	short int iPos;
	short int iMsgNum;
	wchar_t aMessageError [MAXMSGLEN];
} TMessageErrorTxt;

class CAppLogging
{
	public:
	CAppLogging()
	{
		
	}
	~CAppLogging()
	{
		ClearClass();
	}
	void ClearClass(void)
	{
		
	}
	
	void ErrorMsg(int iMSG, int iCategory);
	
	private:
	
};

class CAppConsole
{
	public:
	CAppConsole()
	{
		
	}
	~CAppConsole()
	{
		ClearClass();
	}
	void ClearClass(void)
	{
		
	}
	
	void WriteDlgConsole(wchar_t *aBufMsg);
	void InitConsole(void);
	void ConsoleShow(void);
	void ConsoleHide(void);
	void ConsoleClear(void);
	void ConsoleGetLine(void);
	
	public:
	void* hWndConsole; //HWND
	void* hMenuConsole;//HMENU
	void* hInstanceapp;//HINSTANCE
	void* hWndapp;//HWND
	
	private:

};

#endif //__LOGGING_HPP__