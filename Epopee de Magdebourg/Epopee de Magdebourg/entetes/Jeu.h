//-----------------------------------------------------------------
// UFO Application
// C++ Header - Jeu.h
//-----------------------------------------------------------------

#pragma once

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include <windows.h>
#include "Resource.h"
#include "GameEngine.h"
#include "Bitmap.h"
#include "Sprite.h"
#include "unite.h"
#include <string>
#include <vector>

//-----------------------------------------------------------------
// Global Variables
//-----------------------------------------------------------------
HINSTANCE   _hInstance;
GameEngine* _pGame;
HDC _hOffscreenDC;			//contexte de périphérique hors écran
HBITMAP _hOffscreenBitmap;  //bitmap hors écran


const int   _iMAXVitesse = 8;
Bitmap*		_pTitreJeu;
Bitmap*		_pDemarrer;
Bitmap*		_pHistoire;
Bitmap*		_pInstructions;
Bitmap*		_pQuitter;
Bitmap*		_pOptions;
Bitmap*		_pMagdebourg;
Bitmap*		_pTHistoire;
Bitmap*		_pTInstructions;
Bitmap*		_pTOptions;
Bitmap*		_pRetour;
Bitmap*		_pFondJeu;
Bitmap*		_pTillyBmp;
Bitmap*		_pMenuHist1;
Bitmap*		_pMenuHist2;
Bitmap*		_pNext;
Bitmap*		_pPrecedent;
Bitmap*		_pRien;
Bitmap*		_pCaseB;
Bitmap*		_pUArquebuse;
Bitmap*		_pUCanon;
Bitmap*		_pCaseR;
Bitmap*		_pUCavalerie;
Bitmap*		_pUInfanterie;
Bitmap*		_pUVelours;
Bitmap*		_pMarkVert;
Bitmap*		_pMarkJaune;
Bitmap*		_pMarkRouge;
Bitmap*		_pSideBar;
Bitmap*		_pInfanterieLogo;
Bitmap*		_pMenuBg;
Bitmap*		_pBtnFinTour;
Bitmap*		_pHpDecile;
Bitmap*		_pHpBar;
Bitmap*		_pMiniHpDecile;
Bitmap*		_pMiniHpBar;
Bitmap*		_pChoixPerso;
Bitmap*		_pChoisir;
Bitmap*		_pAmirBmp;
Bitmap*		_pAnfrayBmp;
Bitmap*		_pKonradBmp;
Bitmap*		_pLuigiBmp;
Bitmap*		_pBtnActif;
Bitmap*		_pCaseV;
Bitmap*		_pBtnNextUnit;
Bitmap*		_pBtnAttaquer;
Bitmap*		_pBtnDeplacer;
Bitmap*		_pMnuRecords;
Bitmap*		_pBtnCredits;
Bitmap*		_pMnuCredits;
Bitmap*		_p1Titre;
Bitmap*		_p2Titre;
Bitmap*		_pInstructions1;
Bitmap*		_pInstructions2;
Bitmap*		_pInstructions3;
Bitmap*		_pModeDemo;
Bitmap*		_pSwitchOff;
Bitmap*		_pSwitchOn;

Sprite*		_pRodrich;
Sprite*		_pArquebuse;
Sprite*		_pCanon;
Sprite*		_pCavalerie;
Sprite*		_pInfanterie;
Sprite*		_pVelours;
Sprite*		_pFondMap;
Sprite*		_pCaseDispo;
Sprite*		_pCaseAttaque;
Sprite*		_pCaseSoin;
Sprite*		_pAmir;
Sprite*		_pAnfray;
Sprite*		_pKonrad;
Sprite*		_pLuigi;

int         _iSoucoupeX, _iSoucoupeY;
int         _iVitesseX, _iVitesseY;

char      _ClasseFenetre[11] = "magdebourg";
char      _TitreFenetre[23] =  "L'Épopée de Magdebourg"; 

/*const int _iHauteur = 650;
const int _iLargeur = 750;*/
const int _iHauteur = 800;
const int _iLargeur = 1280;
int nbTours = 0;

POINT positionEcran = { 0,0 };
std::vector<Unite*> tabUnites;
std::vector<Unite*> tabGeneraux;
std::vector<Bitmap*> tabLogo;
std::vector<Bitmap*> tabPersonnages;
std::vector<Bitmap*> tabDescActif;
std::vector<POINT> casesParcourues;
short typeCase[38][29];

byte _EtatDuJeu = 1;
const byte  _EtatQuitter = 0,
			_EtatDebutJeu = 1,
			_EtatInstructions1 = 2,
			_EtatDemarrer = 3,
			_EtatHistoire = 4,
			_EtatOptions = 5,
			_EtatHistoire2 = 6,
			_EtatChoixGeneral1 = 7,
			_EtatChoixGeneral2 = 8,
			_EtatCredits = 9,
			_EtatInstructions2 = 10,
			_EtatInstructions3 = 11;
int selectedUnit = -1;
int selectedGeneral[] = { 0,0 };
int generalActifDelai[] = {3,2,0,3,1};
int actifDelay[] = { 0,0 };
bool generalMort[] = { false, false };
int etatActif = -1;
bool etatAttaquer = false;
int nbKillsParType[5] = {0,0,0,0,0};
bool pressedShift = false;
bool jeuDemo = false;
//Records
int plusBasNbTours;
int plusGrandNbUnites;
short typeUnitePlusDeKills;
int plusGrandNbKillsUnit;


//Fonctions

std::vector<Unite*> fillTableau();
std::vector<Unite*> fillGeneraux();
void fillCases(short typeCases[][29]);
void ajouterVelours(std::vector<Unite*>& tab, int selectedGeneral[], Unite* velours);
void afficherUnites(HDC hDC, std::vector<Unite*> tab, Bitmap* hpBar, Bitmap* hpDecile);
void clearUnites(std::vector<Unite*>& tab);
void switchPlayer(std::vector<Unite*> tab, int &nbTours);
bool hasWon(std::vector<Unite*> tab);
void useActif(std::vector<Unite*>& tabUnites, int selectedGeneral);
void soutienDuLoliFanberg(Unite* caseSelectionnee);
void infirmiereDuCouvent(Unite* caseSelectionnee);
void assassin(Unite* caseSelectionnee);
int stalkerChoisirDest(Unite* caseSelectionnee, short typeCase[][29]);
void stalker(Unite* source, Unite* dest);
int findNextUnit(std::vector<Unite*> tab, int indice);
void focusUnite(Unite* selection, Sprite* fond);
void win();
void lireStats();
void ecrireStats();