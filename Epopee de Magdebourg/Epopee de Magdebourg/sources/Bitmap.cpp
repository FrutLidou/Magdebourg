//-----------------------------------------------------------------
//  Objet: Bitmap
//  Source C++   - Bitmap.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include 
//-----------------------------------------------------------------
#include "Bitmap.h"

//-----------------------------------------------------------------
// Bitmap Constructeur(s)/Destructeur
//-----------------------------------------------------------------
Bitmap::Bitmap()
	: m_hBitmap(NULL), m_iWidth(0), m_iHeight(0)
{
}

// � partir d'un fichier
Bitmap::Bitmap(HDC hDC, LPTSTR szFileName)
	: m_hBitmap(NULL), m_iWidth(0), m_iHeight(0)
{
	Create(hDC, szFileName);
}

// � partir d'une ressource
Bitmap::Bitmap(HDC hDC, UINT uiResID, HINSTANCE hInstance)
	: m_hBitmap(NULL), m_iWidth(0), m_iHeight(0)
{
	Create(hDC, uiResID, hInstance);
}

// un bitmap vierge
Bitmap::Bitmap(HDC hDC, int iWidth, int iHeight, COLORREF crColor)
	: m_hBitmap(NULL), m_iWidth(0), m_iHeight(0)
{
	Create(hDC, iWidth, iHeight, crColor);
}

Bitmap::~Bitmap()
{
	Free();
}

//-----------------------------------------------------------------
// Methodes Bitmap "Helper" 
//-----------------------------------------------------------------
void Bitmap::Free()
{
	// d�truire les objets bitmap
	if (m_hBitmap != NULL)
	{
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}
}

//-----------------------------------------------------------------
// Bitmap -M�thodes g�n�rales
//-----------------------------------------------------------------
BOOL Bitmap::Create(HDC hDC, LPTSTR szFileName)
{
	// Lib�rer le pointeur objet bitmap
	Free();

	// Ouvrir le fichier bitmap
	HANDLE hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	// Obtenir l'entete du fichier bitmap 
	BITMAPFILEHEADER  bmfHeader;
	DWORD             dwBytesRead;
	BOOL bOK = ReadFile(hFile, &bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesRead, NULL);
	if ((!bOK) || (dwBytesRead != sizeof(BITMAPFILEHEADER)) ||
		(bmfHeader.bfType != 0x4D42))
	{
		CloseHandle(hFile);
		return FALSE;
	}

	BITMAPINFO* pBitmapInfo = (BITMAPINFO*)(new BITMAPINFO_256);
	if (pBitmapInfo != NULL)
	{
		// lire l'entete du fichier bitmap 
		bOK = ReadFile(hFile, pBitmapInfo, sizeof(BITMAPINFOHEADER), &dwBytesRead, NULL);
		if ((!bOK) || (dwBytesRead != sizeof(BITMAPINFOHEADER)))
		{
			CloseHandle(hFile);
			Free();
			return FALSE;
		}

		// stocker largeur et hauteur du bitmap
		m_iWidth = (int)pBitmapInfo->bmiHeader.biWidth;
		m_iHeight = (int)pBitmapInfo->bmiHeader.biHeight;

		// Passer l'info concernant la couleur si n�cessaire (24 bits pas n�cessaire)
		if (pBitmapInfo->bmiHeader.biSize != sizeof(BITMAPINFOHEADER))
			SetFilePointer(hFile, pBitmapInfo->bmiHeader.biSize - sizeof
			(BITMAPINFOHEADER), NULL, FILE_CURRENT);

		// lire les informations couleur
		bOK = ReadFile(hFile, pBitmapInfo->bmiColors,
			pBitmapInfo->bmiHeader.biClrUsed * sizeof(RGBQUAD), &dwBytesRead,
			NULL);

		// Donner un handle au bitmap et copier les bits image
		PBYTE pBitmapBits;
		m_hBitmap = CreateDIBSection(hDC, pBitmapInfo, DIB_RGB_COLORS,
			(PVOID*)&pBitmapBits, NULL, 0);
		if ((m_hBitmap != NULL) && (pBitmapBits != NULL))
		{
			SetFilePointer(hFile, bmfHeader.bfOffBits, NULL, FILE_BEGIN);
			bOK = ReadFile(hFile, pBitmapBits, pBitmapInfo->bmiHeader.biSizeImage,
				&dwBytesRead, NULL);
			if (bOK)
				return TRUE;
		}
	}

	// Quelque chose d'�trange s'est produit, alors nettoyage !
	Free();
	return FALSE;
}

BOOL Bitmap::Create(HDC hDC, UINT uiResID, HINSTANCE hInstance)
{
	// Lib�re les infos bitmap pr�c�dentes
	Free();

	// Trouver le bitmap d�clar� en ressource
	HRSRC hResInfo = FindResource(hInstance, MAKEINTRESOURCE(uiResID), RT_BITMAP);
	if (hResInfo == NULL)
		return FALSE;

	// Charger le bitmap sous forme de ressource
	HGLOBAL hMemBitmap = LoadResource(hInstance, hResInfo);
	if (hMemBitmap == NULL)
		return FALSE;

	// Verrouiller la ressource et acc�der � l'image bitmap enti�re 
	PBYTE pBitmapImage = (BYTE*)LockResource(hMemBitmap);
	if (pBitmapImage == NULL)
	{
		FreeResource(hMemBitmap);
		return FALSE;
	}

	// Stock� hauteur et largeur du bitmap
	BITMAPINFO* pBitmapInfo = (BITMAPINFO*)pBitmapImage;
	m_iWidth = (int)pBitmapInfo->bmiHeader.biWidth;
	m_iHeight = (int)pBitmapInfo->bmiHeader.biHeight;

	// Donner un handle au bitmap et copier les bits image
	PBYTE pBitmapBits;
	m_hBitmap = CreateDIBSection(hDC, pBitmapInfo, DIB_RGB_COLORS, (PVOID*)&pBitmapBits, NULL, 0);
	if ((m_hBitmap != NULL) && (pBitmapBits != NULL))
	{
		const PBYTE pTempBits = pBitmapImage + pBitmapInfo->bmiHeader.biSize + pBitmapInfo->bmiHeader.biClrUsed * sizeof(RGBQUAD);
		CopyMemory(pBitmapBits, pTempBits, pBitmapInfo->bmiHeader.biSizeImage);

		// d�verrouiller et lib�rer l'objet bitmap
		UnlockResource(hMemBitmap);
		FreeResource(hMemBitmap);
		return TRUE;  //
	}
	else {
		// Nettoyage pcq quelque chose cloche !
		UnlockResource(hMemBitmap);
		FreeResource(hMemBitmap);
		Free();
		return FALSE;
	}
}

//Cr�er un bitmap sans ressource (rectangle de couleur)
BOOL Bitmap::Create(HDC hDC, int iWidth, int iHeight, COLORREF crColor)
{
	// Cr�er un bitmap de dimension sp�cifi� vierge
	m_hBitmap = CreateCompatibleBitmap(hDC, iWidth, iHeight);
	if (m_hBitmap == NULL)
		return FALSE;

	// Actualiser Hauteur et largeur
	m_iWidth = iWidth;
	m_iHeight = iHeight;

	// Cr�er un HDC pour dessiner le bitmap
	HDC hMemDC = CreateCompatibleDC(hDC);

	// Cr�er un "brush de couleur" pour remplissage du bitmap
	HBRUSH hBrush = CreateSolidBrush(crColor);

	// Associer le bitmap au HDC
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, m_hBitmap);

	// Remplissage du bitmap avec "brush"
	RECT rcBitmap = { 0, 0, m_iWidth, m_iHeight };
	FillRect(hMemDC, &rcBitmap, hBrush);

	// Restauration et Nettoyage
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
	DeleteObject(hBrush);

	return TRUE;
}

// Dessiner le bitmap � l'�cran
void Bitmap::Draw(HDC hDC, int x, int y, BOOL bTrans, COLORREF crTransColor)
{
	DrawPart(hDC, x, y, 0, 0, GetWidth(), GetHeight(), bTrans, crTransColor);
		
	

}
BOOL Bitmap::IsPointInside(int x, int y)
{
	POINT ptPoint;
	ptPoint.x = x;
	ptPoint.y = y;
	return PtInRect(&m_rcPosition, ptPoint);
}


void Bitmap::DrawPart(HDC hDC, int x, int y, int xPart, int yPart,
	int wPart, int hPart, BOOL bTrans, COLORREF crTransColor)
{
	if (m_hBitmap != NULL)
	{
		// cr�er un contexte de p�riph�tique pour le bitmap
		HDC hMemDC = CreateCompatibleDC(hDC);

		// s�lectionner le bitmap et le placer dans le contexte de p�riph�rique
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, m_hBitmap);

		// dessine le bitmap selon la transparence
		if (bTrans)
			TransparentBlt(hDC, x, y, wPart, hPart, hMemDC, xPart, yPart,
				wPart, hPart, crTransColor);
		else
			BitBlt(hDC, x, y, wPart, hPart, hMemDC, xPart, yPart, SRCCOPY);

		// Restaurer et supprimer le contexte de p�riph�rique
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
	// Garder la position du bitmap apr�s l'avoir dessin�
	m_rcPosition.left = x;
	m_rcPosition.top = y;
	m_rcPosition.right = x + GetWidth();
	m_rcPosition.bottom = y + GetHeight();
}


