#ifndef __FUNCTIONS_HPP__
#define __FUNCTIONS_HPP__

BOOL MainRegClass (WNDCLASSEX classex, WNDPROC Proc, LPCWSTR szClassName, HINSTANCE hinstance);
DWORD SizeFile(HANDLE hFileOpen);
BOOL IdentificationFile (void);
BOOL ReadFile (void);
BOOL SelectFile (void);

void SetPosDlg (HWND hwnd, HWND dia);
void CreateWnd (HWND hwnd);
void PaintWnd (HWND hwnd);
void CreateMainWindow (void);


void DlgInit (int numdlg);

#endif // __FUNCTIONS_HPP__