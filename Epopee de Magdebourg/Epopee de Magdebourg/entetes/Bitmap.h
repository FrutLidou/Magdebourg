//-----------------------------------------------------------------
// Bitmap Object
// Entete C++ - Bitmap.h
//-----------------------------------------------------------------
//Ajouter
//msimg32.lib
//dans Editeur de liens - G�n�ral - Entree
//D�pendances suppl�mentaires
#pragma once

//-----------------------------------------------------------------
// Include 
//-----------------------------------------------------------------
#include <windows.h>


//-----------------------------------------------------------------
// Type de donn�es utiles
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
	RECT    m_rcPosition;   //position du bitmap � l'�cran
	

	// Methodes "Helper"
	void Free();

public:
	// Constructeur(s) / Destructeur(s)
	Bitmap();
	Bitmap(HDC hDC, LPTSTR szFileName);// � partir fichier
	Bitmap(HDC hDC, UINT uiResID, HINSTANCE hInstance); // � partir ressources
	Bitmap(HDC hDC, int iWidth, int iHeight, COLORREF crColor = RGB(0, 0, 0)); // vierge
	virtual ~Bitmap();

	// M�thodes g�n�rales
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
	void ResetPosition0() { m_rcPosition = { 0,0,0,0 }; };  //remettre position � z�ro si bitmap non affich�
	   
};
