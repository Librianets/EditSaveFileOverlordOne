#include "global.hpp"

static HBITMAP	hBm;
static BITMAP	bm;

AppData gapp;
Data dapp[MAXCOUNTERPOINTER];

wchar_t gclass[MAXCLASSNAME] = L"Класс главного окна";
wchar_t gwnd[MAXCLASSNAME] = L"Редактор сохранений игры Overlord. Ver 1.0";

void clearval(void)
{

}

void initiationval(void)
{
gapp.inst = NULL;
gapp.wnd = NULL;
gapp.menu = NULL;
gapp._class = gclass;
gapp._wnd = gwnd;
}
