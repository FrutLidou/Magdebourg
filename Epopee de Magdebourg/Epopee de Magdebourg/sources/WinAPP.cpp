#include "WinApp.h"
#include "resource.h"
//---------------------------------------------------------------------------
WApplication::WApplication(HINSTANCE hInst, char *ClsName,
	WNDPROC WndPrc, LPCTSTR MenuName, WORD wIcon, WORD wSmallIcon, WORD wCursor)
{   // Configure fen�tre principale
	// Initialise l'application utilisant les donn�es re�ues en param�tres
	_WndClsEx.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
	_WndClsEx.lpfnWndProc = WndPrc;
	_WndClsEx.cbClsExtra = 0;
	_WndClsEx.cbWndExtra = 0;

	_WndClsEx.hInstance = hInst;
	// icone dans la barre de t�che
	_WndClsEx.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(wIcon));
	_WndClsEx.hCursor = LoadCursor(GetModuleHandle(NULL), MAKEINTRESOURCE(wCursor));
	_WndClsEx.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	_WndClsEx.lpszMenuName = MenuName;
	_WndClsEx.lpszClassName = ClsName;
	//icone du haut fen�tre
	//_WndClsEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);  /* icone standard
	_WndClsEx.hIconSm = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(wSmallIcon));
	_WndClsEx.cbSize = sizeof(WNDCLASSEX);
}
//---------------------------------------------------------------------------
BOOL WApplication::Register()
{
	return RegisterClassEx(&_WndClsEx);
}

LPCSTR WApplication::GetMenuName()
{
	return _WndClsEx.lpszMenuName;
}


