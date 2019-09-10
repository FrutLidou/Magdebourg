#pragma once
#include <windows.h>

//---------------------------------------------------------------------------
class WWindow
{
public:
	// On utilisera le constructeur par défaut pour déclarer une fenêtre 
	WWindow();
	// Pour créer physiquement la fenêtre avec ses caractéristiques 
	HWND Create(HINSTANCE hinst,
		LPCTSTR clsname,
		LPCTSTR wndname,
		HWND parent = NULL,
		DWORD dStyle = WS_OVERLAPPEDWINDOW,
		DWORD dXStyle = 0L,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		int width = CW_USEDEFAULT,
		int height = CW_USEDEFAULT);

	// This method will be used to display the window
	BOOL Show(int dCmdShow = SW_SHOWNORMAL);

	// Parce que chaque fenetre a son HANDLE on doit pouvoir le connaitre 
	// après sa création
	// Retourne le handle d'une fenêtre utilisée dans l'application
	HWND GetHWND();

protected:
	// C'est lle handle global de la fenêtre
	HWND _hwnd;
};
//---------------------------------------------------------------------------
