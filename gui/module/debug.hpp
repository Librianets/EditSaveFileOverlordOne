#ifndef __DEBUG_HPP__
#define __DEBUG_HPP__

#define MAXMSGLOGLEN	0x0200 //512

class CDebugInfo
{
	public:
	CDebugInfo();
	~CDebugInfo();
	void ClearClass(void);
	
	void Debug(const wchar_t *fmt, ...);
	void Info(const wchar_t *fmt, ...);
	void WriteLog(int iLogSwitch, int iNumCount);
	
	wchar_t *lpGetGlobalMsg(void);
	void SetPath(wchar_t *Path, int iSizePath);
	
	private:
	wchar_t sPathFilelog [MAXMSGLOGLEN] = {0};
	wchar_t sGlobalMsg[MAXMSGLOGLEN]	= L"TEST TEST TEST";

};

#endif //__DEBUG_HPP__