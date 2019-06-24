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
	wchar_t *lpGetGlobalMsg(void);
	
	private:
	wchar_t sGlobalMsg[MAXMSGLOGLEN]	= L"TEST TEST TEST";

};

#endif //__DEBUG_HPP__