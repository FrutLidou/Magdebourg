//-----------------------------------------------------------------
// Objet: Sprite 
// C++ - Sprite.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include 
//-----------------------------------------------------------------
#include <windows.h>
#include "Bitmap.h"

//-----------------------------------------------------------------
// Types personnalisés
//-----------------------------------------------------------------
//Actions possibles du sprite quand il rencontre une limite
typedef WORD        BOUNDSACTION;
const BOUNDSACTION  BA_STOP   = 0,	 //s'arrêter
                    BA_WRAP   = 1,	 //passer du côté opposé
                    BA_BOUNCE = 2,	 //rebondir
                    BA_DIE    = 3;	 //mourir


// Action à accomplir pour une sprite en particulier
typedef WORD        SPRITEACTION;
const SPRITEACTION  SA_NONE = 0x0000L,  //aucune action entreprise
					SA_KILL = 0x0001L;	//supprimé le sprite de la liste

// Type de sprite dans la liste pour une sprite en particulier
typedef WORD        TYPESPRITE;
const TYPESPRITE    TS_AUTRE      = 0,
					TS_VAISSEAU   = 1,
					TS_Projectile = 2,
					TS_ASTEROIDE  = 3;
					

//-----------------------------------------------------------------
// Classe Sprite : modélise un objet dont 
//                 l'apparence est définie par la classe BITMAP
//-----------------------------------------------------------------

class Sprite
{
protected:
  // Variables membres
  Bitmap*       m_pBitmap;      
  RECT          m_rcPosition;		//position du sprite comme rectangle sur écran
  POINT         m_ptVelocity;
  int           m_iZOrder;
  RECT          m_rcBounds;			//rectangle de délimitation
  BOUNDSACTION  m_baBoundsAction;
  BOOL          m_bHidden;
  int           m_iNumFrames, m_iCurFrame;			//nombre de frames, frame courant
  int           m_iFrameDelay, m_iFrameTrigger;     //délai d'affichage et i-déclenchement
  //----------------------------------------------------------------------------
  RECT			m_rcCollision;		//rectangle de collision
  BOOL			m_bDying;			//sprite doit être détruit
  TYPESPRITE    m_typeSprite;       //donne identité au sprite
  //----------------------------------------------------------------------------

public:
  // Constructeur(s)/Destructeur
  Sprite(Bitmap* pBitmap);
  Sprite(Bitmap* pBitmap, RECT& rcBounds,
		 BOUNDSACTION baBoundsAction = BA_STOP);
  Sprite(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder,
		 RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP);
  virtual ~Sprite();

 // Méthodes generales 
  virtual SPRITEACTION  Update();
  BOOL          TestCollision(Sprite* pTestSprite);
  void			Draw(HDC hDC, BOOL bTrans = TRUE,
							  COLORREF crTransColor = RGB(255, 0, 255));
   BOOL         IsPointInside(int x, int y);

 // Méthodes Helper (prototype)
   virtual void  CalcCollisionRect();

  // Méthodes accesseurs
  RECT&   GetPosition()             { return m_rcPosition; };
  void    SetPosition(int x, int y);
  void    SetPosition(POINT ptPosition);
  void    SetPosition(RECT& rcPosition)
									{ CopyRect(&m_rcPosition, &rcPosition); };
  void    OffsetPosition(int x, int y);
  POINT   GetVelocity()             { return m_ptVelocity; };
  void    SetVelocity(int x, int y);
  void    SetVelocity(POINT ptVelocity);
  BOOL    GetZOrder()               { return m_iZOrder; };
  void    SetZOrder(int iZOrder)    { m_iZOrder = iZOrder; };
  void    SetBounds(RECT& rcBounds) { CopyRect(&m_rcBounds, &rcBounds); };
  void    SetBoundsAction(BOUNDSACTION ba) 
									{ m_baBoundsAction = ba; };
  BOOL    IsHidden()                { return m_bHidden; };
  void    SetHidden(BOOL bHidden)   { m_bHidden = bHidden; };
  int     GetWidth()				{ return (m_pBitmap->GetWidth() / m_iNumFrames); };
  int     GetHeight()               { return m_pBitmap->GetHeight(); };
  void    SetNumFrames(int iNumFrames);
  void    SetFrameDelay(int iFrameDelay)
									{ m_iFrameDelay = iFrameDelay; };
  Bitmap*  GetBitmap()				{ return m_pBitmap ; };
  void	   SetBitmap( Bitmap* bBitmap)	
									{m_pBitmap =  bBitmap; };
  void    UpdateFrame();
  RECT&   GetrcCollision()          { return m_rcCollision; };
  
  void	  Kill()         	        { m_bDying = TRUE; };

  void		  SetTypeSprite(TYPESPRITE tpSprite)   { m_typeSprite = tpSprite; };
  TYPESPRITE  GetTypeSprite()      { return m_typeSprite; };
};

//-----------------------------------------------------------------
// Méthodes générales Inline de la classe Sprite
//-----------------------------------------------------------------
//Détermine si un point est situé dans le rectangle de délimitation du sprite
inline BOOL Sprite::IsPointInside(int x, int y)
{
  POINT ptPoint;
  ptPoint.x = x;
  ptPoint.y = y;
  return PtInRect(&m_rcPosition, ptPoint);
}

//-----------------------------------------------------------------
// Méthodes accesseurs Inline de la classe Sprite (Méthodes incorporées)
//-----------------------------------------------------------------
//Ajuste la position d'un sprite avec ses coordonnées
inline void Sprite::SetPosition(int x, int y)
{
  OffsetRect(&m_rcPosition, x - m_rcPosition.left, y - m_rcPosition.top);
  CalcCollisionRect();
}
//Ajuste la position d'un sprite avec un point
inline void Sprite::SetPosition(POINT ptPosition)
{
  OffsetRect(&m_rcPosition, ptPosition.x - m_rcPosition.left,
			                ptPosition.y - m_rcPosition.top);
  CalcCollisionRect();
}

inline void Sprite::OffsetPosition(int x, int y)
{
  OffsetRect(&m_rcPosition, x, y);
  CalcCollisionRect();
}

inline void Sprite::SetVelocity(int x, int y)
{
  m_ptVelocity.x = x;
  m_ptVelocity.y = y;
}

inline void Sprite::SetVelocity(POINT ptVelocity)
{
  m_ptVelocity.x = ptVelocity.x;
  m_ptVelocity.y = ptVelocity.y;
}

inline void Sprite::SetNumFrames(int iNumFrames)
{
	// changer le nombre d'images du sprite
	m_iNumFrames = iNumFrames;

	//repositionner l'image selon le nombre de frame (largeur et hauteur)
	m_rcPosition.bottom = m_rcPosition.top + m_pBitmap->GetHeight();
	m_rcPosition.right = m_rcPosition.left + m_pBitmap->GetWidth();

	// recalculer la position du sprite selon le nombre d'images
	RECT rect = GetPosition();
	rect.right = rect.left + ((rect.right - rect.left) / iNumFrames);
	SetPosition(rect);

}

//-----------------------------------------------------------------
// Sprite : Méthodes "helper" Inline
//-----------------------------------------------------------------
inline void Sprite::UpdateFrame()
{
  if ((m_iFrameDelay >= 0) && (--m_iFrameTrigger <= 0))
  {
    // Réinitialiser le taux de rafraichissement ;
    m_iFrameTrigger = m_iFrameDelay;

    // Passer au frame suivant ou recommencer
    if (++m_iCurFrame >= m_iNumFrames)
        m_iCurFrame = 0;
  }
}

//-----------------------------------------------------------------
// Calcul du rectangle de collision d’un sprite
// (doit être initialisé par TOUS les constructeurs!)
//-----------------------------------------------------------------

inline void Sprite::CalcCollisionRect()
{
	int iXShrink = (m_rcPosition.left - m_rcPosition.right) / 12;
	int iYShrink = (m_rcPosition.top - m_rcPosition.bottom) / 12;
	CopyRect(&m_rcCollision, &m_rcPosition);
	InflateRect(&m_rcCollision, iXShrink, iYShrink);
}

//-----------------------------------------------------------------
// Comparaison des rectangles pour déterminer s’ils se chevauchent
// Renvoie TRUE s’il y a collision FALSE sinon
//-----------------------------------------------------------------
inline BOOL Sprite::TestCollision(Sprite* pTestSprite)
{
	RECT& rcTest = pTestSprite->GetrcCollision();
	return m_rcCollision.left <= rcTest.right &&
		   rcTest.left <= m_rcCollision.right &&
		   m_rcCollision.top <= rcTest.bottom &&
		   rcTest.top <= m_rcCollision.bottom;
}
