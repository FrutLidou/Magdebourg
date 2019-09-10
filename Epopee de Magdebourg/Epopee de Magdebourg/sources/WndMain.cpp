#include "WndMain.h"

//---------------------------------------------------------------------------
WWindow::WWindow()
{
	// Si on d�clare une fen�tre avec le constructeur par d�faut,
	// On met le handle de la fen�tre � NULL
	_hwnd = NULL;
}
//---------------------------------------------------------------------------
HWND WWindow::Create(   HINSTANCE hinst,
						LPCTSTR clsname,
						LPCTSTR wndname,
						HWND parent,
						DWORD dStyle,
						DWORD dXStyle,
						int x,
						int y,
						int width,
						int height)
{
	// Cr�er la nouvelle fen�tre avec la m�thode Create
	_hwnd = CreateWindowEx(dXStyle, clsname, wndname, dStyle, x, y, width,
		height, parent, NULL, hinst, NULL);

	// On v�rifie si la fen�tre s'est bien cr��e 
	if (_hwnd != NULL)
		return _hwnd;
	// Si un probl�me se produit, on retourne une fen�tre nulle 
	// be created, return a "nothing" window
	return NULL;
}
//---------------------------------------------------------------------------
BOOL WWindow::Show(int dCmdShow)
{
	// Affiche et mets � jour la fen�tre 
	if (ShowWindow(_hwnd, dCmdShow) && UpdateWindow(_hwnd))
		return TRUE;
	return FALSE;
}
//---------------------------------------------------------------------------
HWND WWindow::GetHWND()
{
	// retourner le HWND
	return _hwnd;
}
//---------------------------------------------------------------------------
