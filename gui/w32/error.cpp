#include "global.hpp"

MSG msg;

void error (int msg, int flag_exit)
{
	switch (msg)
	{
		case gwndnot:
		{
			MessageBox(NULL, L"Не удалось создать главное окно", L"Ошибка", MB_OK);
			break;
		}
		case gclassnot:
		{
			MessageBox(NULL, L"Не удалось зарегистрировать класс окна", L"Ошибка", MB_OK);
			break;
		}
		case gaccelnot:
		{
			MessageBox(NULL, L"Проблемы с таблицей акселератов", L"Ошибка", MB_OK);
			break;
		}
	}
	
	if (flag_exit == exit_app){exit(1);}
}