//-----------------------------------------------------------------
// Objet Unité
// C++ Source - unite.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include 
//-----------------------------------------------------------------
#include "unite.h"
#include "Sprite.h"
#include <iostream>
#include <stdlib.h>

//-----------------------------------------------------------------
// Unite Constructeur(s)/Destructeur
//-----------------------------------------------------------------

//Tableaux de valeurs
int hp[] = { 0,200,100,130,65,400 };
int degats[] = { 0,70,60,60,65,75 };
int portee[] = { 0,1,3,1,7,1 };
int deplacement[] = { 0,4,3,8,2,4 };
int son[] = {0,4000,4001,4002,4003,4004 };

//Bitmap pour la barre de vie
Bitmap* hpDecile;

//Unité qui peuvent attaquer Luigi Dumoulin
std::vector<Unite*> tabAttaqueLuigi;

Unite::Unite(Sprite* sprite, POINT pos, short type, bool allie)
{
	this->u_sprite = sprite;
	this->u_position = pos;
	this->u_maxHp = hp[type];
	this->u_currentHp = hp[type];
	this->u_degats = degats[type];
	this->u_portee = portee[type];
	this->u_deplacement = deplacement[type];
	this->u_type = type;
	this->u_allie = allie;
	this->u_moved = false;
	this->u_attacked = false;
	this->u_son = son[type];
}

//-----------------------------------------------------------------
// Unite Méthodes
//-----------------------------------------------------------------

void Unite::SetPosition(POINT newPos)
{
	this->u_position = newPos;
}

bool Unite::damage(int degats, int uType, int selectedGeneral, bool generalMort[], int nbTours)
{
	//Élément aléatoire
	double mod = (rand() % 100 + 51)/100.00;
	degats *= mod;
	//Vérifier si le général donne une bonus de dégâts
	if ((selectedGeneral == 0 && uType == UT_ARQUEBUS) || (selectedGeneral == 2 && uType == UT_INFANTRY))
		degats *= 1.5;
	//Si général = luigi, permettre à l'unité de l'attaquer
	if (selectedGeneral == 3 && getUnitAtPos(tabAttaqueLuigi, u_position) == 0)
		tabAttaqueLuigi.push_back(this);
	u_currentHp -= degats;
	if (isDead())
	{
		if (u_type == 5)
		{
			if (u_allie)
				generalMort[nbTours % 2] = true;
			else
				generalMort[(nbTours + 1) % 2] = true;

		}
	}
	return isDead();
}

bool Unite::dejaParcourue(std::vector<POINT> casesParcourues, POINT pos)
{
	int i = 0;
	bool parcourue = false;
	while (i < casesParcourues.size() && !parcourue)
	{
		if (casesParcourues.at(i).x == pos.x && casesParcourues.at(i).y == pos.y)
			parcourue = true;
		i++;
	}
	return parcourue;
}

void Unite::deplacer(Sprite* caseDispo, std::vector<Unite*>& tab, int distanceParcourue, POINT posActu, std::vector<POINT> casesParcourues, int selectedGeneral, short typeCase[][29])
{
	distanceParcourue++;
	//S'assurer que la case est à portée de l'unité
	if (distanceParcourue <= getDeplacement())
	{
		casesParcourues.push_back(posActu);
		for (int i = 0; i < 4; i++)
		{
			POINT newPos = posActu;
			switch (i)
			{
			case 0:
				newPos.y = posActu.y - 1;
				break;
			case 1:
				newPos.x = posActu.x + 1;
				break;
			case 2:
				newPos.y = posActu.y + 1;
				break;
			case 3:
				newPos.x = posActu.x - 1;
				break;
			}
			//S'assurer que la case est à l'intérieur de la carte
			if (newPos.y >= 0 && newPos.y <= 30
				&& newPos.x >= 0 && newPos.x <= 41)
			{
				//S'assurer que la case n'a pas déjà été parcourue
				if (!dejaParcourue(casesParcourues, newPos))
				{
					casesParcourues.push_back(newPos);
					//S'assurer que la case n'est pas difficile
					int a[20];
					if (typeCase[newPos.x][newPos.y] == 0 || (typeCase[newPos.x][newPos.y] == 1 && (getUType() == 1 || getUType() == 2)))
					{
						//S'assurer que la case n'est pas occupée
						if (!isOccupe(newPos, tab))
						{
							Unite* unit = new Unite(caseDispo, newPos, 0, false);
							tab.push_back(unit);
							deplacer(caseDispo, tab, distanceParcourue, newPos, casesParcourues, selectedGeneral, typeCase);
						}
						else
						{
							for (int i = 0; i < tab.size(); i++)
							{
								if (tab.at(i)->GetPosition().x == newPos.x && tab.at(i)->GetPosition().y == newPos.y)
								{
									if (tab.at(i)->isAllie() || tab.at(i)->getUType() == 0 || selectedGeneral == 4)
									{
										deplacer(caseDispo, tab, distanceParcourue, newPos, casesParcourues, selectedGeneral, typeCase);
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void Unite::attaquer(Sprite* caseAttaque, std::vector<Unite*>& tab, POINT posActu, std::vector<Unite*> tabGeneraux)
{
	for (int x = -getPortee(); x <= getPortee(); x++)
	{
		for (int y = -getPortee(); y <= getPortee(); y++)
		{
			int disTotal = abs(x) + abs(y);
			if (disTotal <= getPortee())
			{
				POINT posAttaque = posActu;
				posAttaque.x += x;
				posAttaque.y += y;
				if (!isOccupe(posAttaque, tab))
				{
					Unite* unit = new Unite(caseAttaque, posAttaque, 0, false);
					tab.push_back(unit);
				}
				else
				{
					for (int i = 0; i < tab.size(); i++)
					{
						if (tab.at(i)->GetPosition().x == posAttaque.x && tab.at(i)->GetPosition().y == posAttaque.y)
						{
							//Passif de Luigi Dumoulin
							if (tab.at(i)->getSprite() != tabGeneraux.at(3)->getSprite() || Unite::getUnitAtPos(tabAttaqueLuigi, posActu) != nullptr)
							{
								if (!tab.at(i)->isAllie() && tab.at(i)->getUType() != 0)
								{
									Unite* unit = new Unite(caseAttaque, posAttaque, 0, false);
									tab.push_back(unit);
								}
							}
						}
					}
				}
			}
		}
	}
}

void Unite::switchSide()
{
	u_allie = !u_allie;
}

void Unite::drawHp(HDC hDC, Bitmap* hpDecile)
{
	int nbDecile = ( (double) getCurrentHp() / (double) getMaxHp() * 10);
	int pos = 0;
	for (int i = 0; i < nbDecile; i++)
	{
		pos = i * 25;
		hpDecile->Draw(hDC, 1014 + pos, 174);
	}
}

void Unite::drawMiniHp(HDC hDC, Bitmap* hpDecile, int x, int y)
{
	int nbDecile = ((double)getCurrentHp() / (double)getMaxHp() * 10);
	int pos = 0;
	for (int i = 0; i < nbDecile; i++)
	{
		pos = i * 9;
		hpDecile->Draw(hDC, x * 100 + 6 + pos, y * 100 + 87);
	}
}

void Unite::reset()
{
	u_moved = false;
	u_attacked = false;
}

Unite* Unite::clone()
{
	Unite* clone = new Unite(*this);
	return clone;
}

void Unite::heal(int hp)
{
	if (u_currentHp + hp > u_maxHp)
		u_currentHp = u_maxHp;
	else
		u_currentHp += hp;
}

int Unite::compterUnites(std::vector<Unite*>& tab)
{
	int nb = 0;
	for (int i = 0; i < tab.size(); i++)
	{
		if (tab.at(i)->isAllie())
			nb++;
	}
	return nb;
}