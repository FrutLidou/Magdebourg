//-----------------------------------------------------------------
// Objet Sprite Objet
// C++ Source - Sprite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include 
//-----------------------------------------------------------------
#include "Sprite.h"

//-----------------------------------------------------------------
// Sprite Constructeur(s)/Destructeur
//-----------------------------------------------------------------
Sprite::Sprite(Bitmap* pBitmap)
{
  // Initialiser les variables membres
  // Sprite immobile à 0,0
  m_pBitmap = pBitmap;
  SetRect(&m_rcPosition, 0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());

  m_ptVelocity.x = m_ptVelocity.y = 0;
  m_iZOrder = 0;
  SetRect(&m_rcBounds, 0, 0, 640, 480);
  m_baBoundsAction = BA_STOP;
  m_bHidden = FALSE;
  m_iNumFrames = 1;
  m_iCurFrame = m_iFrameDelay = m_iFrameTrigger = 0;
  m_typeSprite = 0;
  CalcCollisionRect();

}
//Accepte rectangle de délimitation et action de limite
//place le sprite de façon aléatoire dans le rectangle de délimitation
Sprite::Sprite(Bitmap* pBitmap, RECT& rcBounds, BOUNDSACTION baBoundsAction)
{
   // Calculer une position aléatoire
  int iXPos = rand() % (rcBounds.right - rcBounds.left);
  int iYPos = rand() % (rcBounds.bottom - rcBounds.top);

   // Initialiser les variables membres 
  m_pBitmap = pBitmap;
  SetRect(&m_rcPosition, iXPos, iYPos, 
	                     iXPos + pBitmap->GetWidth(),
                         iYPos + pBitmap->GetHeight());
  CalcCollisionRect();
  m_ptVelocity.x = m_ptVelocity.y = 0;
  m_iZOrder = 0;
  CopyRect(&m_rcBounds, &rcBounds);
  m_baBoundsAction = baBoundsAction;
  m_bHidden = FALSE;
  m_iNumFrames = 1;
  m_iCurFrame = m_iFrameDelay = m_iFrameTrigger = 0;
  m_typeSprite = 0;


}
//Sprite personnalisé
Sprite::Sprite(Bitmap* pBitmap, POINT ptPosition, POINT ptVelocity, int iZOrder,
			   RECT& rcBounds, BOUNDSACTION baBoundsAction)
{
   // Initialiser les variables membres 
  m_pBitmap = pBitmap;
  SetRect(&m_rcPosition, ptPosition.x, ptPosition.y, pBitmap->GetWidth(), pBitmap->GetHeight());
  CalcCollisionRect();
  m_ptVelocity = ptPosition;
  m_iZOrder = iZOrder;
  CopyRect(&m_rcBounds, &rcBounds);
  m_baBoundsAction = baBoundsAction;
  m_bHidden = FALSE;
  m_iNumFrames = 1;
  m_iCurFrame = m_iFrameDelay = m_iFrameTrigger = 0;
  m_typeSprite = 0;


}
//Destructeur
Sprite::~Sprite()
{
}

//-----------------------------------------------------------------
// Sprite: Méthodes générales
//-----------------------------------------------------------------

//----------------------------------------------------------------------------
//Fonction SPRITE::Update
//Actualise la position du sprite en appliquant sa vitesse à sa position
//et en appliquant les réactions appropriées concernant son mouvement.
SPRITEACTION Sprite::Update()
{ 
  //Gérer l’état mort (se produit lors d’une collision ou autre dans le jeu)
  if (m_bDying) return SA_KILL;
	
  //Actualisé l'image à afficher dans le sprite.
  UpdateFrame();

  // Actualiser la position du sprite (simuler le mouvement)
  POINT ptNewPosition, ptSpriteSize, ptBoundsSize;
  ptNewPosition.x = m_rcPosition.left + m_ptVelocity.x;
  ptNewPosition.y = m_rcPosition.top  + m_ptVelocity.y;
  ptSpriteSize.x  = m_rcPosition.right  - m_rcPosition.left;
  ptSpriteSize.y  = m_rcPosition.bottom - m_rcPosition.top;
  ptBoundsSize.x  = m_rcBounds.right  - m_rcBounds.left;
  ptBoundsSize.y  = m_rcBounds.bottom - m_rcBounds.top;

  // Vérifier les limites (bounds)
  //VÉRIFIER LES ACTIONS DE DÉLIMITATIONS
  switch (m_baBoundsAction)
  {
	  case BA_WRAP:   /// Wrap: passage au côté opposé ?
			if ((ptNewPosition.x + ptSpriteSize.x) < m_rcBounds.left)
			  ptNewPosition.x = m_rcBounds.right;
			else if (ptNewPosition.x > m_rcBounds.right)
				  ptNewPosition.x = m_rcBounds.left - ptSpriteSize.x;
				if ((ptNewPosition.y + ptSpriteSize.y) < m_rcBounds.top)
					  ptNewPosition.y = m_rcBounds.bottom;
					else if (ptNewPosition.y > m_rcBounds.bottom)
					  ptNewPosition.y = m_rcBounds.top - ptSpriteSize.y;
			break;
	  case BA_BOUNCE:  // Rebond
		  {
			BOOL bBounce = FALSE;
			POINT ptNewVelocity = m_ptVelocity;
			if (ptNewPosition.x < m_rcBounds.left)
				{
				  bBounce = TRUE;
				  ptNewPosition.x = m_rcBounds.left;
				  ptNewVelocity.x = -ptNewVelocity.x;
				}
			else if ((ptNewPosition.x + ptSpriteSize.x) > m_rcBounds.right)
					{
					  bBounce = TRUE;
					  ptNewPosition.x = m_rcBounds.right - ptSpriteSize.x;
					  ptNewVelocity.x = -ptNewVelocity.x;
					}
					if (ptNewPosition.y < m_rcBounds.top)
						{
						  bBounce = TRUE;
						  ptNewPosition.y = m_rcBounds.top;
						  ptNewVelocity.y = -ptNewVelocity.y;
						}
						else if ((ptNewPosition.y + ptSpriteSize.y) > m_rcBounds.bottom)
							{
							  bBounce = TRUE;
							  ptNewPosition.y = m_rcBounds.bottom - ptSpriteSize.y;
							  ptNewVelocity.y = -ptNewVelocity.y;
							}
			if (bBounce)
			  SetVelocity(ptNewVelocity);
		  }
			break;
	  case BA_DIE:// Mort code à venir 
		  //on meurt quand on arrive sur bordure

		  if ((ptNewPosition.x + ptSpriteSize.x) < m_rcBounds.left ||
			  ptNewPosition.x > m_rcBounds.right ||
			  (ptNewPosition.y + ptSpriteSize.y) < m_rcBounds.top ||
			  ptNewPosition.y > m_rcBounds.bottom)
		  	  return SA_KILL;
		  //  …

			break;
	  case BA_STOP: // Arrêt (valeur par défaut)
			if (ptNewPosition.x  < m_rcBounds.left || ptNewPosition.x > (m_rcBounds.right - ptSpriteSize.x))
				{
				  ptNewPosition.x = max(m_rcBounds.left, min(ptNewPosition.x, m_rcBounds.right - ptSpriteSize.x));
				  SetVelocity(0, 0);
				}
			if (ptNewPosition.y  < m_rcBounds.top || ptNewPosition.y > (m_rcBounds.bottom - ptSpriteSize.y))
				{
				  ptNewPosition.y = max(m_rcBounds.top, min(ptNewPosition.y, m_rcBounds.bottom - ptSpriteSize.y));
				  SetVelocity(0, 0);
				}
		    break;
  }

  //Mettre à jour la position du sprite
 SetPosition(ptNewPosition);
 //Retourne l’état OK après le repositionnement
 return SA_NONE;
 
}//fin Sprite::Udpate()

//---------------------------------------------------------------------------
// Fonction Sprite::Draw
//Dessine le sprite à sa position courante en utilisant le bitmap spécifié
//---------------------------------------------------------------------------
void Sprite::Draw(HDC hDC, BOOL bTrans, COLORREF crTransColor)
{  
	switch (m_typeSprite)
	{
		case TS_VAISSEAU:
			crTransColor = RGB(255, 0, 255);
			bTrans = TRUE;
			break;
		case TS_ASTEROIDE:
		case TS_Projectile:
			bTrans = TRUE;
			crTransColor = RGB(0, 0, 0);
	}
  // Dessine le sprite s'il n'est pas caché
  if (m_pBitmap != NULL && !m_bHidden)
  {
    // Dessine l'image appropriée si nécessaire
    if (m_iNumFrames == 1)
      m_pBitmap->Draw(hDC, m_rcPosition.left, m_rcPosition.top, bTrans, crTransColor);
    else
      m_pBitmap->DrawPart(hDC, m_rcPosition.left, m_rcPosition.top,
					            m_iCurFrame * GetWidth(), 0,  
								GetWidth(), GetHeight(), bTrans,crTransColor);
  }

}
