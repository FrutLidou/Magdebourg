//-----------------------------------------------------------------
// Bitmap Object
// Entete C++ - Bitmap.h
//-----------------------------------------------------------------
//Ajouter
//msimg32.lib
//dans Editeur de liens - Général - Entree
//Dépendances supplémentaires
#pragma once

//-----------------------------------------------------------------
// Include 
//-----------------------------------------------------------------
#include <windows.h>


//-----------------------------------------------------------------
// Type de données utiles
//-----------------------------------------------------------------
struct BITMAPINFO_256
{
	BITMAPINFOHEADER  bmiHeader;
	RGBQUAD           bmiColors[256];
};

//-----------------------------------------------------------------
// Bitmap Class
//-----------------------------------------------------------------
class Bitmap
{
protected:
	// Variables membres
	HBITMAP m_hBitmap;
	int     m_iWidth, m_iHeight;
	RECT    m_rcPosition;   //position du bitmap à l'écran
	

	// Methodes "Helper"
	void Free();

public:
	// Constructeur(s) / Destructeur(s)
	Bitmap();
	Bitmap(HDC hDC, LPTSTR szFileName);// à partir fichier
	Bitmap(HDC hDC, UINT uiResID, HINSTANCE hInstance); // à partir ressources
	Bitmap(HDC hDC, int iWidth, int iHeight, COLORREF crColor = RGB(0, 0, 0)); // vierge
	virtual ~Bitmap();

	// Méthodes générales
	BOOL Create(HDC hDC, LPTSTR szFileName);
	BOOL Create(HDC hDC, UINT uiResID, HINSTANCE hInstance);
	BOOL Create(HDC hDC, int iWidth, int iHeight, COLORREF crColor);
	void Draw(HDC hDC, int x, int y, BOOL bTrans = FALSE,
		COLORREF crTransColor = RGB(255, 0, 255));
	void DrawPart(HDC hDC, int x, int y, int xPart, int yPart,
		int wPart, int hPart, BOOL bTrans = FALSE,
		COLORREF crTransColor = RGB(255, 0, 255));
	int  GetWidth()       { return m_iWidth; };
	int  GetHeight()      { return m_iHeight; };

	BOOL IsPointInside(int x, int y);
	void ResetPosition0() { m_rcPosition = { 0,0,0,0 }; };  //remettre position à zéro si bitmap non affiché
	   
};
