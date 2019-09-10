#include "WndMain.h"

//---------------------------------------------------------------------------
WWindow::WWindow()
{
	// Si on déclare une fenêtre avec le constructeur par défaut,
	// On met le handle de la fenêtre à NULL
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
	// Créer la nouvelle fenêtre avec la méthode Create
	_hwnd = CreateWindowEx(dXStyle, clsname, wndname, dStyle, x, y, width,
		height, parent, NULL, hinst, NULL);

	// On vérifie si la fenêtre s'est bien créée 
	if (_hwnd != NULL)
		return _hwnd;
	// Si un problème se produit, on retourne une fenêtre nulle 
	// be created, return a "nothing" window
	return NULL;
}
//---------------------------------------------------------------------------
BOOL WWindow::Show(int dCmdShow)
{
	// Affiche et mets à jour la fenêtre 
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
