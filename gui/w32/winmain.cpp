#include "winmain.h"

LRESULT CALLBACK funcs1 (HWND window1, UINT msg, WPARAM wParam, LPARAM IParam);

//BOOL RegClass (WNDPROC Proc, LPCTSTR szClassName, HINSTANCE hinstance); 


HWND window1;
MSG msg;
char name_class[] = "class1";
char name_window1[] = "window1";
HINSTANCE hinst = NULL;

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	
	hinst = hInstance;

	WNDCLASSEX class1;
	class1.cbSize = sizeof(class1);
	class1.style = CS_HREDRAW|CS_VREDRAW;
	class1.lpfnWndProc = funcs1;
	class1.cbClsExtra = 0;
	class1.cbWndExtra = 0;
	class1.hInstance = hinst;
	class1.hIcon = NULL;
	class1.hCursor = NULL;
	class1.hbrBackground = (HBRUSH)COLOR_WINDOW;
	class1.lpszMenuName = NULL;
	class1.lpszClassName = name_class;
	class1.hIconSm = NULL;
	
	if (!RegisterClassEx(&class1)){MessageBox(NULL, "Не могу зарегистрировать класс окна!123", "Ошибка", MB_OK);return 0;}



	window1 = CreateWindowEx(0, name_class, name_window1, WS_OVERLAPPEDWINDOW, 10, 10, 600, 480, NULL, NULL, hinst, NULL);
	if (!window1){MessageBox(NULL, "Не удается создать главное окно!124", "Ошибка", MB_OK);return 0;}

	ShowWindow(window1,nCmdShow);
	UpdateWindow(window1);
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

	//UnregisterClass(name_class, hinst);
	MessageBox(0, "Project OG_ESD", "A test window", MB_OK);
}

LRESULT CALLBACK funcs1 (HWND window1, UINT msg, WPARAM wParam, LPARAM IParam)
{
PAINTSTRUCT ps;
RECT Rect;
HDC hdc, hCmpDC;
HBITMAP hBmp;


     switch (msg)
      {
            case WM_PAINT:
                  GetClientRect(window1, &Rect);
                  hdc = BeginPaint(window1, &ps);

                  // Создание теневогоs контекста для двойной буфферизации
                  hCmpDC = CreateCompatibleDC(hdc);
                  hBmp = CreateCompatibleBitmap(hdc, Rect.right - Rect.left,
                        Rect.bottom - Rect.top);
                  SelectObject(hCmpDC, hBmp);

                  // Закраска фоновым цветом
                  LOGBRUSH br;
                  br.lbStyle = BS_SOLID;
                  br.lbColor = 0xEECCCC;
                  HBRUSH brush;
                  brush = CreateBrushIndirect(&br);
                  FillRect(hCmpDC, &Rect, brush);
                  DeleteObject(brush);

                  // Здесь рисуем на контексте hCmpDC

                  // Копируем изображение из теневого контекста на экран
                  SetStretchBltMode(hdc, COLORONCOLOR);
                  BitBlt(hdc, 0, 0, Rect.right - Rect.left, Rect.bottom - Rect.top,
                        hCmpDC, 0, 0, SRCCOPY);

                  // Удаляем ненужные системные объекты
                  DeleteDC(hCmpDC);
                  DeleteObject(hBmp);
                  hCmpDC = NULL; 

                  EndPaint(window1, &ps);
                  break;

            case WM_DESTROY:
                  PostQuitMessage(0);
                  break;

            default:
                  return (DefWindowProc(window1, msg, wParam, IParam));
      }
      return (0);
}




















/*




	//RegClass (FunClass1, name_window1, hinst);
	
	WNDCLASSEX Class1; // название структы класса
	Class1.cbSize = sizeof (WNDCLASSEX);
	Class1.style = CS_HREDRAW | CS_VREDRAW; // стиль окна
	Class1.lpfnWndProc = funcs1; // функция окна
	Class1.cbClsExtra = 0; // дополнительные байты
	Class1.cbWndExtra = 0; // дополнительные байты
	Class1.hInstance = hinst; // дескриптор тек.приложения
	Class1.hIcon = LoadIcon (NULL, IDI_WINLOGO);
	//Class1.hIcon = LoadIcon(hinstance, "myicon");
	// иконка
	Class1.hCursor = LoadCursor (NULL, IDC_ARROW);
	// курсор
	Class1.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	//GetStockObject (WHITE_BRUSH); // фон
	Class1.lpszMenuName = NULL; // название меню
	Class1.lpszClassName = name_class; // указатель на строку
	Class1.hIconSm = Class1.hIcon;
	RegisterClassEx(&Class1);
	/*
	
	
/*
HWND CreateWindowExA(
  DWORD     dwExStyle,
  LPCSTR    lpClassName,
  LPCSTR    lpWindowName,
  DWORD     dwStyle,
  int       X,
  int       Y,
  int       nWidth,
  int       nHeight,
  HWND      hWndParent,
  HMENU     hMenu,
  HINSTANCE hInstance,
  LPVOID    lpParam
);
//CREATESTRUCT qwe;
CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, &name_class, "OG_ESD", NULL, 50, 50, 100, 100, window1, NULL, hinst, NULL);
*/
	
	
	
	
	
	
	




/*
BOOL RegClass (WNDPROC Proc, LPCTSTR name_window1, HINSTANCE hinstance)
{
	WNDCLASSEX Class1; // название структы класса
	Class1.cbSize = sizeof (WNDCLASSEX);
	Class1.style = CS_HREDRAW | CS_VREDRAW; // стиль окна
	Class1.lpfnWndProc = Proc; // функция окна
	Class1.cbClsExtra = 0; // дополнительные байты
	Class1.cbWndExtra = 0; // дополнительные байты
	Class1.hInstance = hinstance; // дескриптор тек.приложения
	Class1.hInstance = LoadIcon (NULL, IDI_WINLOGO);
	//Class1.hIcon = LoadIcon(hinstance, "myicon");
	// иконка
	Class1.hCursor = LoadCursor (NULL, IDC_ARROW);
	// курсор
	Class1.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	//GetStockObject (WHITE_BRUSH); // фон
	Class1.lpszMenuName = NULL; // название меню
	Class1.lpszClassName = name_window1; // указатель на строку
	Class1.hIconSm = Class1.hIcon;
	return (RegisterClassEx(&Class1) !=0); // регистрация класса
}*/
/*

LRESULT CALLBACK funcs1 (HWND hWnd, UINT msg, UINT wParam, LONG IParam)
{

switch(msg)
{

	case WM_CREATE:{return 0;}
	
	case WM_PAINT:{return 0;}
	
	case WM_DESTROY:{PostQuitMessage(0);return 0;}
} 

return DefWindowProc(hWnd, msg, wParam, IParam);
}*/