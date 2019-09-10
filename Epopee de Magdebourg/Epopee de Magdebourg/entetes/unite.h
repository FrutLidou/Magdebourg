//-----------------------------------------------------------------
// Objet: Unité
// C++ - unite.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include 
//-----------------------------------------------------------------
#include <windows.h>
#include <Sprite.h>
#include <vector>

//-----------------------------------------------------------------
// Types personnalisés
//-----------------------------------------------------------------
//Type de l'unité
typedef WORD        UNITTYPE;
const UNITTYPE		UT_CASE = 0,
					UT_INFANTRY = 1,
					UT_ARQUEBUS = 2,
					UT_CAVALRY = 3,
					UT_CANON = 4,
					UT_COMMANDER = 5;

//-----------------------------------------------------------------
// Classe Unité : modélise une unité du jeu
//-----------------------------------------------------------------
class Unite
{
protected:
	// Variables membres
	Sprite*     u_sprite;
	POINT       u_position;			//position de l'unité dans le tableau
	int			u_maxHp;			//nombre maximal de points de vie de l'unité
	int			u_currentHp;		//points de vie actuel de l'unité
	int			u_degats;			//dégâts de base infligés par l'unité
	short		u_portee;			//portée a laquelle l'unité peut attaquer
	short		u_deplacement;		//nombre de cases de déplacement de l'unité
	UNITTYPE	u_type;				//type de l'unité
	bool		u_allie;			//determine si l'unité est alliée ou ennemie
	bool		u_moved;			//dit si l'unité a été déplacée ce tour
	bool		u_attacked;			//dit si l'unité a attaqué ce tour
	int			u_son;				//son produit quand l'unité attaque

public:
	// Constructeur(s)/Destructeur
	Unite(Sprite* sprite, POINT pos, short type, bool allie);

	// Méthodes generales 
	//BOOL         IsPointInside(int x, int y);

	// Méthodes accesseurs
	Sprite*	getSprite() { return u_sprite; };
	POINT   GetPosition() { return u_position; };
	void    SetPosition(POINT newPos);
	int		getMaxHp() { return u_maxHp; };
	void	setMaxHp(int newMax) { u_maxHp = newMax; u_currentHp = newMax; };
	int		getCurrentHp() { return u_currentHp; };
	int		getDegats() { return u_degats; };
	void	setDegats(int newDegats) { u_degats = newDegats; };
	short	getPortee() { return u_portee; };
	void	setPortee(short newPortee) { u_portee = newPortee; };
	short	getDeplacement() { return u_deplacement; };
	void	setDeplacement(short newDeplacement) { u_deplacement = newDeplacement; };
	int		getSon() { return u_son; };
	short	getUType() { return u_type; };
	bool	isAllie() { return u_allie; };
	bool	hasMoved() { return u_moved; };
	bool	hasAttacked() { return u_attacked; };
	void	move() { u_moved = true; };
	void	attack() { u_attacked = true; };

	bool	isDead() { return u_currentHp <= 0; };
	bool	damage(int degats, int uType, int selectedGeneral, bool generalMort[], int nbTours);
	void	switchSide();
	//bool	isOccupe(POINT point, std::vector<Unite*>& tab);
	bool	dejaParcourue(std::vector<POINT> casesParcourues, POINT pos);
	void	deplacer(Sprite* caseDispo, std::vector<Unite*>& tab, int distanceParcourue, POINT posActu, std::vector<POINT> casesParcourues, int selectedGeneral, short typeCase[][29]);
	void	attaquer(Sprite* caseAttaque, std::vector<Unite*>& tab, POINT posActu, std::vector<Unite*> tabGeneraux);
	void	drawHp(HDC hDC, Bitmap* hpDecile);
	void	drawMiniHp(HDC hDC, Bitmap* miniHpDecile, int x, int y);
	void	reset();
	Unite*	clone();
	void	heal(int hp);
	int static compterUnites(std::vector<Unite*>& tab);

	//Méthodes inline
	inline static int IsUnitInside(POINT positionEcran, std::vector<Unite*> tab, int x, int y)
	{
		bool inside = false;
		int i = 0;
		while (!inside && i < tab.size())
		{
			if (tab.at(i)->getUType() != 0)
			{
				POINT ptPoint;
				ptPoint.x = x + (positionEcran.x * 100);
				ptPoint.y = y + (positionEcran.y * 100);
				RECT zone;
				zone.top = (tab.at(i)->GetPosition().y) * 100;
				zone.bottom = (tab.at(i)->GetPosition().y + 1) * 100;
				zone.left = (tab.at(i)->GetPosition().x) * 100;
				zone.right = (tab.at(i)->GetPosition().x + 1) * 100;
				if (PtInRect(&zone, ptPoint))
					inside = true;
				else
					i++;
			}
			else
				i++;
		}
		if (!inside)
			i = -1;
		return i;
	}

	inline static int IsCaseInside(POINT positionEcran, std::vector<Unite*> tab, int x, int y)
	{
		bool inside = false;
		int i = 0;
		while (!inside && i < tab.size())
		{
			if (tab.at(i)->getUType() == 0)
			{
				POINT ptPoint;
				ptPoint.x = x + (positionEcran.x * 100);
				ptPoint.y = y + (positionEcran.y * 100);
				RECT zone;
				zone.top = (tab.at(i)->GetPosition().y) * 100;
				zone.bottom = (tab.at(i)->GetPosition().y + 1) * 100;
				zone.left = (tab.at(i)->GetPosition().x) * 100;
				zone.right = (tab.at(i)->GetPosition().x + 1) * 100;
				if (PtInRect(&zone, ptPoint))
					inside = true;
				else
					i++;
			}
			else
				i++;
		}
		if (!inside)
			i = -1;
		return i;
	}

	inline static Unite* getUnitAtPos(std::vector<Unite*> tab, POINT position)
	{
		Unite* unit = nullptr;
		for (int i = 0; i < tab.size(); i++)
		{
			if (tab.at(i)->GetPosition().x == position.x && tab.at(i)->GetPosition().y == position.y)
			{
				if (tab.at(i)->getUType() != 0)
				{
					unit = tab.at(i);
				}
			}
		}
		return unit;
	}
	inline static Unite* getUnitAtPos(std::vector<Unite*> tab, int x, int y)
	{
		POINT pos;
		pos.x = x;
		pos.y = y;
		return getUnitAtPos(tab, pos);
	}

	inline static int getIndex(std::vector<Unite*> tab, Unite* unit)
	{
		int index = -1;
		for (int i = 0; i < tab.size(); i++)
		{
			if (tab.at(i) == unit)
				index = i;
		}
		return index;
	}

	inline static bool isOccupe(POINT point, std::vector<Unite*>& tab)
	{
		int occupe = false;
		int i = 0;
		while (!occupe && i < tab.size())
		{
			if (point.x == tab.at(i)->GetPosition().x && point.y == tab.at(i)->GetPosition().y)
				occupe = true;
			i++;
		}
		return occupe;
	}
};