#pragma once
#include <windows.h>

//---------------------------------------------------------------------------
class WApplication
{
public:
	// This constructor will initialize the application
	WApplication(   HINSTANCE hInst, char *ClasName,
					WNDPROC WndPrc, LPCTSTR MenuName, 
					WORD wIcon, WORD wSmallIcon, WORD wCursor);

	// Class Registration
	BOOL Register();
	LPCSTR GetMenuName();

protected:
	// Global variable that holds the application
	WNDCLASSEX _WndClsEx;
};
//---------------------------------------------------------------------------
